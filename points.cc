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

#include "points.h"
#include "decl.h"
#include "configuration.h"

static unsigned int points;
static unsigned long nextlife;
static int lifes;

#define LIFE_INCREMENT 5000

void pts_reset(void) {
  points = 0;
  lifes = config.start_lives();
  nextlife = LIFE_INCREMENT;
}

void pts_add(int add) {
  points += add;

  while (points >= nextlife) {
    nextlife += LIFE_INCREMENT;
    lives_add();
  }
}

void lives_add(void) {
    lifes++;
    if (lifes > 8)
      lifes = 8;
}

unsigned int pts_points(void) {
  return points;
}

unsigned char pts_lifes(void) {
  return lifes;
}

void pts_died(void) {
  lifes--;
}

bool pts_lifesleft(void) {
  return lifes != 0;
}

