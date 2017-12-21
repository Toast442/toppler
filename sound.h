/* Tower Toppler - Nebulus
 * Copyright (C) 2000-2012  Andreas Röver
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

#ifndef SOUND_H
#define SOUND_H

#include "config.h"
#include "soundsys.h"

#ifdef HAVE_LIBSDL_MIXER
#include "sdlinc.h"
#endif

/* this module handles all the soundoutput necessary for the game */

enum {
  SND_WATER,
  SND_TAP,
  SND_BOINK,
  SND_HIT,
  SND_CROSS,
  SND_TICK,
  SND_DROWN,
  SND_SPLASH,
  SND_SHOOT,
  SND_ALARM,
  SND_SCORE,
  SND_CRUMBLE,
  SND_FANFARE,
  SND_SONAR,
  SND_TORPEDO,
  SND_DOORTAP = SND_TAP
};

void snd_init(void);
void snd_done(void);

void snd_playTitle(void);
void snd_stopTitle(void);
void snd_musicVolume(int vol);

#endif

