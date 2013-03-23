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

#ifndef BONUS_H
#define BONUS_H

/* this module contains the bonus game with the submarine and fish catching
 it is currently not very well tuned */

/* returns true, if the game can go on, false on user break
 */
bool bns_game(void);

/* needs to be called bevore every new game, to (re)initialize the
 * datastructures
 */
void bns_restart(void);

#endif
