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

#ifndef ELEVATORS_H
#define ELEVATORS_H

#include "sdlinc.h"


/* this module handles all the necessities for up to 10
 elevators */

/* initializes the elevator structures */
void ele_init(void);

/* activates the elevator. there can be only one
 active elevator */
void ele_select(Uint16 row, Uint8 col);

/* the elevator gets started */
void ele_activate(Sint8 dir);

/* moves the elevator one level up */
void ele_move(void);

/* return true, if the elevator is at a station */
bool ele_is_atstop(void);

/* the animal leaves the elevator or got thrown off.
 after a timeout the elevator will automatically fall down */
void ele_deactivate(void);

/* call once per update to check elevator falldown */
void ele_update(void);

#endif
