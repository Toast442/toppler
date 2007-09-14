/* Tower Toppler - Nebulus
 * Copyright (C) 2000-2006  Andreas Röver
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include "decl.h"
#include "soundsys.h"
#include "archi.h"

#include <stdio.h>
#include <string.h>

ttsounds::ttsounds(void)
{
#ifdef HAVE_LIBSDL_MIXER
  useSound = false;
  n_sounds = 0;
  sounds = NULL;

  debugprintf(9, "ttsounds::ttsounds\n");

  title = 0;
#endif
}

ttsounds::~ttsounds(void)
{
#ifdef HAVE_LIBSDL_MIXER
  closesound();

  for (int t = 0; t < n_sounds; t++)
    if (sounds[t].sound)
      Mix_FreeChunk(sounds[t].sound);

  delete [] sounds;

  debugprintf(9, "ttsounds::~ttsounds\n");
#endif
}

void ttsounds::addsound(char *fname, int id, int vol, int loops)
{
#ifdef HAVE_LIBSDL_MIXER
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

  file f(dataarchive, fname);

  sounds[add_pos].sound = Mix_LoadWAV_RW(f.rwOps(), 1);

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
#endif
}

void ttsounds::play(void)
{
#ifdef HAVE_LIBSDL_MIXER
  if (!useSound) return;

  for (int t = 0; t < n_sounds; t++)
    if (sounds[t].in_use && sounds[t].play) {

      sounds[t].channel = Mix_PlayChannel(-1, sounds[t].sound, sounds[t].loops);
      Mix_Volume(sounds[t].channel, sounds[t].volume);

      sounds[t].play = false;
    }
  debugprintf(9,"ttsounds::play()\n");
#endif
}

void ttsounds::stop(void)
{
#ifdef HAVE_LIBSDL_MIXER
  for (int t = 0; t < n_sounds; t++) stopsound(t);
#endif
}

void ttsounds::stopsound(int snd)
{
#ifdef HAVE_LIBSDL_MIXER
  if (useSound) {
    if ((snd >= 0) && (snd < n_sounds)) {
      if (sounds[snd].channel != -1) {

        Mix_HaltChannel(sounds[snd].channel);
        sounds[snd].channel = -1;
      }
      sounds[snd].play = false;
    }
  }
  debugprintf(9,"ttsounds::stopsound(%i)\n", snd);
#endif
}

void ttsounds::startsound(int snd)
{
#ifdef HAVE_LIBSDL_MIXER
  if (!useSound) return;

  if ((snd >= 0) && (snd < n_sounds)) sounds[snd].play = true;

  debugprintf(9,"ttsounds::startsound(%i)\n", snd);
#endif
}

void ttsounds::setsoundvol(int snd, int vol)
{
#ifdef HAVE_LIBSDL_MIXER
  if (useSound) {
    if ((snd >= 0) && (snd < n_sounds)) {
      if (sounds[snd].channel != -1) {

        Mix_Volume(sounds[snd].channel, vol);

      }
      sounds[snd].volume = vol;
    }

    debugprintf(9,"ttsounds::setsoundvol(%i, %i)\n", snd, vol);
  }
#endif
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
#ifdef HAVE_LIBSDL_MIXER
  if (!useSound) return;

  while (Mix_Playing(-1)) dcl_wait();

  Mix_CloseAudio();
  SDL_QuitSubSystem(SDL_INIT_AUDIO);

  useSound = false;
#endif
}


void ttsounds::playmusic(const char * fname) {
#ifdef HAVE_LIBSDL_MIXER
  if (!useSound) return;

  char f[500];
  if (get_data_file_path(fname, f, 500)) {
    title = Mix_LoadMUS(f);
    Mix_PlayMusic(title, -1);
    musicVolume = MIX_MAX_VOLUME;
  }
#endif
}
void ttsounds::stopmusic(void) {
#ifdef HAVE_LIBSDL_MIXER
  if (!useSound) return;

  if (title) {
    Mix_FadeOutMusic(1000);

    while (Mix_FadingMusic() != MIX_NO_FADING) dcl_wait();
  }
#endif
}

void ttsounds::fadeToVol(int vol) {
#ifdef HAVE_LIBSDL_MIXER
  if (!title) return;
  
  while (musicVolume != vol) {

    if (musicVolume > vol) {
      musicVolume -= 4;
      if (musicVolume < vol)
        musicVolume = vol;
    } else {
      musicVolume += 4;
      if (musicVolume > vol)
        musicVolume = vol;
    }

    Mix_VolumeMusic(musicVolume);
    dcl_wait();
  }
#endif
}

