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

#ifndef SNOWBALL_H
#define SNOWBALL_H

/* updates and handles the snowball that can be thrown by
 the animal */

/* init, delete snowball */
void snb_init(void);

/* updates the position of the snowball */
void snb_movesnowball(void);

/* checks is there is already a snowball */
bool snb_exists(void);

/* creates a new one */
void snb_start(int verticalpos, int anglepos, bool look_left);

/* returns the position of the ball */
int snb_verticalpos(void);
int snb_anglepos(void);

#endif
