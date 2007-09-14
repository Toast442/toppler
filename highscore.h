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

#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <SDL_types.h>

/* this modules contains all the function for highscoretable access
 * because this is the only section that needs the sticky bit privileges
 * it's the one that handled the group id things as well
 */

/* the number of characters a name can be long in the highscoretable */
#define SCORENAMELEN 9

/* call this at init time, so that the program can desice on the
 * highscore table file to use. This files will then be used the
 * complete running time
 */
void hsc_init(void);

/* selects one mission by name, if there is currently no table
 * for this mission the table is assumed to be empty
 */
void hsc_select(const char * mission);

/* how many value entries has the selected table? */
Uint8 hsc_entries(void);

/* fills name, points and tower with the values of the nr-th entry,
 * if you give 0 pointers the values are ignored,
 * name must be at least SCORENAMELEN+1 characters long */
void hsc_entry(Uint8 nr, char *name, Uint32 *points, Uint8 *tower);

/* returns true, if the player will enter the highscore table with his points
 * you can use this function on locked and unlocked highscore tables
 * but of course the information may change until you have locked the table
 */
bool hsc_canEnter(Uint32 points);

/* enters one user into the table with his number of points and the reached tower
 * the table gets locked, the entry written in and the unlocked
 * returned is the position in the table the user got, or 0xff if he didn't get in
 * the table will be saved automatically
 */
Uint8 hsc_enter(Uint32 points, Uint8 tower, char *name);

#endif
