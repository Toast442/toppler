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

#ifndef toppler_h
#define toppler_h

/* this modules handles the the green animal, updates its position
 on the tower and its shape corresponding to the shape of the tower */


/* initializes the variables, call this function each time you start at the tower. */
void top_init(void);

/* actualizes the position and shape of the toppler considering the given keyposition */
void top_updatetoppler(int left_right, int up_down, bool space);

/* tests, if the toppler collides with something while it is on the elevator */
void top_testcollision(void);

/* the following functions return several of the necessary variables for the toppler */

/* its vertial position on the tower */
int top_verticalpos(void);

/* the angle position on the tower */
int top_anglepos(void);

/* is it visible */
bool top_visible(void);

/* does it look left (or right) */
bool top_look_left(void);

/* the shape, independent of the direction */
int top_shape(void);

/* is it on an elevator */
bool top_onelevator(void);

/* technique bonus points, how often got it thrown down */
int top_technic(void);

/* the actual state of the toppler */

/* drowned */
bool top_died(void);

/* reached target */
bool top_targetreached(void);

/* the game ended, either drowned or reached target */
bool top_ended(void);

/* the animal is currently drowning */
bool top_dying(void);

/* it is moving */
bool top_walking(void);

/* needed for destruction of tower, to drop the toppler
 one layer of the tower */
void top_drop1layer(void);

/* hide the toppler */
void top_hide(void);

/* show it and set its shape, vertical and angular position */
void top_show(int shape, int vpos, int apos);

/* move the toppler to the side until it is at a valid position
 this function is necessary for the downfalling elevators to
 push the animal aside  */
void top_sidemove(void);


#endif
