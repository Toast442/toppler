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

#include <string.h>
#include "sound.h"

#include "decl.h"
#include "archi.h"
#include "configuration.h"

static bool samplesloaded = false;

void snd_init(void) {
  if (!config.nosound()) {
    ttsounds::instance()->opensound();

    if (!samplesloaded) {

      ttsounds::instance()->addsound("water.wav",    SND_WATER,     128, -1);
      ttsounds::instance()->addsound("tap.wav",      SND_TAP,       MIX_MAX_VOLUME, 0);
      ttsounds::instance()->addsound("boing.wav",    SND_BOINK,     0,    0);
      ttsounds::instance()->addsound("hit.wav",      SND_HIT,       MIX_MAX_VOLUME, 0);
      ttsounds::instance()->addsound("honk.wav",     SND_CROSS,     MIX_MAX_VOLUME, 0);
      ttsounds::instance()->addsound("tick.wav",     SND_TICK,      MIX_MAX_VOLUME, 0);
      ttsounds::instance()->addsound("bubbles.wav",  SND_DROWN,     MIX_MAX_VOLUME, 2);
      ttsounds::instance()->addsound("splash.wav",   SND_SPLASH,    0,    0);
      ttsounds::instance()->addsound("swoosh.wav",   SND_SHOOT,     MIX_MAX_VOLUME, 0);
      ttsounds::instance()->addsound("alarm.wav",    SND_ALARM,     MIX_MAX_VOLUME, 0);
      ttsounds::instance()->addsound("score.wav",    SND_SCORE,     MIX_MAX_VOLUME, 0);
      ttsounds::instance()->addsound("rumble.wav",   SND_CRUMBLE,   MIX_MAX_VOLUME, 0);
      ttsounds::instance()->addsound("fanfare.wav",  SND_FANFARE,   MIX_MAX_VOLUME, 0);
      ttsounds::instance()->addsound("sonar.wav",    SND_SONAR,     MIX_MAX_VOLUME/6, 0);
      ttsounds::instance()->addsound("torpedo.wav",  SND_TORPEDO,   MIX_MAX_VOLUME, 0);
      //TTSound->addsound("subfall.wav",  SND_SUB_DOWN,  MIX_MAX_VOLUME, 0);
      //TTSound->addsound("subraise.wav", SND_SUB_RAISE, MIX_MAX_VOLUME, 0);
      //TTSound->addsound("start.wav",    SND_START,     MIX_MAX_VOLUME, 0);
      //TTSound->addsound("timeout.wav",  SND_TIMEOUT,   MIX_MAX_VOLUME, 0);
      //TTSound->addsound("fall.wav",     SND_FALL,      MIX_MAX_VOLUME, 0);

      samplesloaded = true;
    }
  }
}

void snd_done(void) {
  ttsounds::instance()->closesound();
}


void snd_playTitle(void) {
  ttsounds::instance()->playmusic("toppler.ogg");
}


void snd_stopTitle(void) {
  ttsounds::instance()->stopmusic();
}

void snd_musicVolume(int vol) {
  ttsounds::instance()->fadeToVol(vol);
}
