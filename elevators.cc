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

#include "elevators.h"

#include "level.h"
#include "decl.h"
#include "toppler.h"

#include <stdlib.h>

#define MAX_ELE 10

/* elevators are handled in a quite complicated way: while
 the toppler is moving on the elevator the platform is invisible
 and drawn together with the toppler. The stick below the elevator
 is always drawn in such a way that the last one will appear or disappear
 below the platform under the toppler */

static struct {
  /* the current position of the platform */
  Uint8 angle;
  Uint16 vertical;

  /* time until the elevator falls down */
  Sint8 time;

  /* background value necessary because in between the stations it
   is impossible to show a platform so we save the actual value
   there and force a station at the position, when the elevator moves
   further down we restore the value there */
  Uint8 bg;
} elevators[MAX_ELE];

static Sint8 active_ele;
static Sint8 ele_dir;

void ele_init(void) {

  for (Uint8 t = 0; t < MAX_ELE; t++)
    elevators[t].time = -1;

  active_ele = -1;
}

void ele_select(Uint16 row, Uint8 col) {

  assert_msg(active_ele == -1, "Select more than one elevator.");

  Uint8 what = 0;

  col /= 8;
  row /= 4;
  row--;

  for (int t = 0; t < MAX_ELE; t++) {
    if ((elevators[t].time == -1) && (what == 0)) {
      what = 1;
      active_ele = t;
    }
    if ((elevators[t].angle == col) && (elevators[t].vertical == row)) {
      what = 2;
      active_ele = t;
    }
  }

  elevators[active_ele].angle = col;
  elevators[active_ele].vertical = row;
  elevators[active_ele].time = -1;

}

void ele_activate(Sint8 dir) {

  assert_msg(active_ele != -1, "Work with unselected elevator, activate.");

  lev_platform2stick(elevators[active_ele].vertical, elevators[active_ele].angle);
  ele_dir = dir;
  if (dir == -1) ele_move();
}

void ele_move(void) {

  assert_msg(active_ele != -1, "Work with unselected elevator, move.");

  if (ele_dir == 1) {
    elevators[active_ele].vertical++;
  
    lev_empty2stick(elevators[active_ele].vertical, elevators[active_ele].angle);
  } else {
    lev_stick2empty(elevators[active_ele].vertical, elevators[active_ele].angle);
  
    elevators[active_ele].vertical--;
  }
}

bool ele_is_atstop(void) {

  assert_msg(active_ele != -1, "Work with unselected elevator, is_atstop.");

  if (ele_dir == 1)
    return lev_is_station(elevators[active_ele].vertical + 1, elevators[active_ele].angle);
  else
    return lev_is_station(elevators[active_ele].vertical, elevators[active_ele].angle);
}

void ele_deactivate(void) {

  assert_msg(active_ele != -1, "Deselected an inactive elevator.");

  if (ele_dir == 1) ele_move();

  lev_stick2platform(elevators[active_ele].vertical, elevators[active_ele].angle);

  Uint8 ae = active_ele;
  active_ele = -1;

  if (!lev_is_station(elevators[ae].vertical, elevators[ae].angle))
    elevators[ae].bg = lev_putplatform(elevators[ae].vertical, elevators[ae].angle);
  else
    if (lev_is_bottom_station(elevators[ae].vertical, elevators[ae].angle))
      return;
    else
      elevators[ae].bg = lev_tower(elevators[ae].vertical, elevators[ae].angle);

  elevators[ae].time = 0x7d;
}

void ele_update(void) {

  for (Uint8 t = 0; t < MAX_ELE; t++) {
    if (elevators[t].time == 0) {
      lev_restore(elevators[t].vertical, elevators[t].angle, elevators[t].bg);
      lev_platform2empty(elevators[t].vertical, elevators[t].angle);
      elevators[t].vertical--;
      lev_stick2platform(elevators[t].vertical, elevators[t].angle);
      if (lev_is_bottom_station(elevators[t].vertical, elevators[t].angle)) {
        elevators[t].time = -1;
        top_sidemove();
      } else
        elevators[t].bg = lev_putplatform(elevators[t].vertical, elevators[t].angle);
    }

    if (elevators[t].time > 0)
      elevators[t].time--;
  }
}

