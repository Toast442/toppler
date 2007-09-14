/* Tower Toppler - Nebulus
 * Copyright (C) 2000-2004  Andreas Röver
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

#ifndef KEYB_H
#define KEYB_H

#include "decl.h"

#include <SDL_types.h>
#include <SDL_keyboard.h>

typedef enum {
  no_key       =  0x0000,
  up_key       =  0x0001,
  down_key     =  0x0002,
  left_key     =  0x0004,
  right_key    =  0x0008,
  fire_key     =  0x0010,
  break_key    =  0x0020,
  pause_key    =  0x0040,
/*  mousebttn1   =  0x0100,
  mousebttn2   =  0x0200,
  mousebttn3   =  0x0400,
  mousebttn4   =  0x0800,
  mousebttn5   =  0x1000,*/
  any_key      =  0xFFFF
} ttkey;

typedef void FDECL((*keyb_wait_proc), (void));

void key_init(void);
void key_done(void);

/* waits until the game window gets focus */
void wait_for_focus(void);

/* returns bitmask with currently pressed keys */
Uint16 key_keystat(void);

/* true, if key is pressed */
bool key_keypressed(ttkey key);

/* returns if a key has been pushed and released (typed) but only for the keys in
 the list */
ttkey key_readkey(void);

/* Returns the last pressed key, in SDLKey format */
SDLKey key_sdlkey(void);

/* Converts sdlkey to internal key representation, or returns no_key
   if SDLKey cannot be converted. */
ttkey key_sdlkey2conv(SDLKey k, bool game);

/* Converts internal key to sdlkey, or returns SDLK_UNKNOWN. */
SDLKey key_conv2sdlkey(ttkey k, bool game);

/* returns a typed character */
char key_chartyped(void);

/* combines key_sdlkey(), key_readkey() and key_chartyped() */
void key_keydatas(SDLKey &sdlkey, ttkey &tkey, char &ch);

/* waits until no key is pressed, calling bg while waiting */
void key_wait_for_none(keyb_wait_proc bg);

/* returns the current mouse coordinate and button pressed. */
bool key_mouse(Uint16 *x, Uint16 *y, ttkey *bttn);

/* redefine a key, so that it returns code  */
void key_redefine(ttkey code, SDLKey key);

#endif

