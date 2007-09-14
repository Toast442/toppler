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

#ifndef POINTS_H
#define POINTS_H

/* handles points and lives */

/* reset points to 0 and lives to 3 */
void pts_reset(void);

/* add points, updating the life counter, if necessary */
void pts_add(int add);

/* returns the current points and lives */
unsigned int pts_points(void);
unsigned char pts_lifes(void);

/* adds one life */
void lives_add();

/* removes one life */
void pts_died(void);

/* returns true, if lifes != 0 */
bool pts_lifesleft(void);

#endif
