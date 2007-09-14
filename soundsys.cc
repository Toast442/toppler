#include "decl.h"
#include "soundsys.h"
#include "archi.h"

#include <stdio.h>
#include <string.h>

ttsounds::ttsounds(void)
{
  useSound = false;
  n_sounds = 0;
  sounds = NULL;

  debugprintf(9, "ttsounds::ttsounds\n");
}

ttsounds::~ttsounds(void)
{
  closesound();

#ifdef HAVE_LIBSDL_MIXER
  for (int t = 0; t < n_sounds; t++)
    if (sounds[t].sound)
      Mix_FreeChunk(sounds[t].sound);
#endif

  delete [] sounds;

  debugprintf(9, "ttsounds::~ttsounds\n");
}

void ttsounds::addsound(char *fname, int id, int vol, int loops)
{
  struct ttsnddat *tmp;
  bool need_add = true;
  int add_pos = n_sounds;

  if (sounds && n_sounds)
    for (int t = 0; t < n_sounds; t++)
      if (!sounds[t].in_use) {
        need_add = false;
        add_pos = t;
        break;
      }

  if (need_add) {
    tmp = new struct ttsnddat [n_sounds + 1];

    if (!tmp) return;

    if (n_sounds) {
      memcpy(tmp, sounds, sizeof(struct ttsnddat) * n_sounds);
      delete [] sounds;
    }
    sounds = tmp;
  }

#ifdef HAVE_LIBSDL_MIXER
  file f(dataarchive, fname);

  sounds[add_pos].sound = Mix_LoadWAV_RW(f.rwOps(), 1);
#endif

  if (sounds[add_pos].sound) {
    sounds[add_pos].in_use = true;
    sounds[add_pos].play = false;
    sounds[add_pos].id_num = id;
    sounds[add_pos].channel = -1;
    sounds[add_pos].volume = vol;
    sounds[add_pos].loops = loops;
    debugprintf(8,"ttsounds::addsound(\"%s\", %i, %i) = %i\n", fname, vol, loops, add_pos);
  } else
    debugprintf(0,"ttsounds::addsound(): No such file as '%s'\n", fname);

  n_sounds++;

  return;
}

void ttsounds::play(void)
{
  if (!useSound) return;

  for (int t = 0; t < n_sounds; t++)
    if (sounds[t].in_use && sounds[t].play) {

#ifdef HAVE_LIBSDL_MIXER
      sounds[t].channel = Mix_PlayChannel(-1, sounds[t].sound, sounds[t].loops);
      Mix_Volume(sounds[t].channel, sounds[t].volume);
#endif

      sounds[t].play = false;
    }
  debugprintf(9,"ttsounds::play()\n");
}

void ttsounds::stop(void)
{
  for (int t = 0; t < n_sounds; t++) stopsound(t);
}

void ttsounds::stopsound(int snd)
{
  if (useSound) {
    if ((snd >= 0) && (snd < n_sounds)) {
      if (sounds[snd].channel != -1) {

#ifdef HAVE_LIBSDL_MIXER
        Mix_HaltChannel(sounds[snd].channel);
#endif
        sounds[snd].channel = -1;
      }
      sounds[snd].play = false;
    }
  }
  debugprintf(9,"ttsounds::stopsound(%i)\n", snd);
}

void ttsounds::startsound(int snd)
{
  if (!useSound) return;

  if ((snd >= 0) && (snd < n_sounds)) sounds[snd].play = true;

  debugprintf(9,"ttsounds::startsound(%i)\n", snd);
}

void ttsounds::setsoundvol(int snd, int vol)
{
  if (useSound) {
    if ((snd >= 0) && (snd < n_sounds)) {
      if (sounds[snd].channel != -1) {

#ifdef HAVE_LIBSDL_MIXER
        Mix_Volume(sounds[snd].channel, vol);
#endif

      }
      sounds[snd].volume = vol;
    }

    debugprintf(9,"ttsounds::setsoundvol(%i, %i)\n", snd, vol);
  }
}

ttsounds * ttsounds::instance(void) {
  if (!inst)
    inst = new ttsounds();

  return inst;
}

class ttsounds *ttsounds::inst = 0;

void ttsounds::opensound(void) {

#ifdef HAVE_LIBSDL_MIXER
  if(SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
    debugprintf(0, "Couldn't init the sound system, muting.\n");
    return;
  }

  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
    debugprintf(0, "Could not open audio, muting.\n");
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    return;
  }

  useSound = true;
#endif

}

void ttsounds::closesound(void) {

  if (!useSound) return;

#ifdef HAVE_LIBSDL_MIXER
  while (Mix_Playing(-1)) dcl_wait();

  Mix_CloseAudio();
  SDL_QuitSubSystem(SDL_INIT_AUDIO);
#endif

  useSound = false;
}

