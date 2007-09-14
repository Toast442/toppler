#ifndef SOUNDSYS_H
#define SOUNDSYS_H

#ifdef HAVE_LIBSDL_MIXER
#include <SDL_mixer.h>
#endif

struct ttsnddat {
  bool in_use; //is this datablock in use (sndfile is loaded)
  bool play;   //is this block goind to get played next time?
  int id_num;  //unique ID # of this sound
  int channel; //sound channel
  int volume;  //sound volume
  int loops;   //how many times to loop this sound?
#ifdef HAVE_LIBSDL_MIXER
  Mix_Chunk *sound; //sound data
#endif
};

class ttsounds {
public:
  ~ttsounds(void);

  void addsound(char *fname, int id, int vol, int loops);

  void play(void); //play all active sounds
  void stop(void); //stop all sounds

  void stopsound(int snd); //stop the sound from playing
  void startsound(int snd); //the sound will play in the next update
  void setsoundvol(int snd, int vol); //set sound volume

  /* tries to open and initialize the sound device */
  void opensound(void);
  /* closes the sound device */
  void closesound(void);

  /* singleton function, use this function to access the one and only
   * instance of this class
   */
  static ttsounds * instance(void);

private:
  ttsounds(void);

  /* this var is only true, if we the user wants sound, and wa
   * can init it
   */
  bool useSound;

  int n_sounds; // # of sounds allocated
  struct ttsnddat *sounds;

  static class ttsounds *inst;

};

#endif
