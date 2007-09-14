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

#ifndef MENU_H
#define MENU_H

#include "decl.h"

#include <SDL_types.h>
#include <SDL_keyboard.h>

#include "menusys.h"

/* load graphics */
void men_init(void);

/* the main menu */
void men_main(void);

/* free graphics */
void men_done(void);

#ifdef GAME_DEBUG_KEYS
void run_debug_menu(void);
#endif

/* menu shown to user when he presses esc during play */
bool men_game(void);

#endif
