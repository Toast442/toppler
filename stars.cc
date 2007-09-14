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

#include "stars.h"

#include "decl.h"
#include "sprites.h"
#include "screen.h"

#include "SDL.h"
#include "stdlib.h"

#define starstep 5

typedef struct {
  long x, y;
  int state;
  int size;
} _star;

static unsigned short star_spr_nr;
static int num_stars;
static _star *stars = (_star *)0;

void sts_draw(void)
{
  for (int t = 0; t < num_stars; t++)
    scr_blit(objectsprites.data((long)star_spr_nr + stars[t].size - (stars[t].state != 0)), stars[t].x, stars[t].y);
}

void sts_init(int sn, int nstar) {
  if (stars) {
    if (nstar <= num_stars) {
      star_spr_nr = sn;
      num_stars = nstar;
      return;
    } else sts_done();
  }
  assert(nstar > 1, "sts_init with too few stars!");

  stars = new _star[nstar];
  assert(stars, "Failed to alloc memory!");
  num_stars = nstar;

  for (int t = 0; t < num_stars; t++) {
    stars[t].x = rand() / (RAND_MAX / SCREENWID) - SPR_STARWID;
    stars[t].y = rand() / (RAND_MAX / SCREENHEI) - SPR_STARHEI;
    stars[t].state = 0;
    stars[t].size = rand() / (RAND_MAX / 7);
  }

  star_spr_nr = sn;
}

void sts_done(void)
{
  if (stars) delete [] stars;
  num_stars = 0;
  stars = 0;
}

void sts_blink(void)
{
  for (int t = 0; t < num_stars; t++) {
    if (stars[t].state > 0) stars[t].state = (stars[t].state + 1) % 4;
    else if (!(rand() & 0xff)) stars[t].state++;
  }
}

void sts_move(long x, long y)
{
  int t;

  for (t = 0; t < num_stars; t++) {
    stars[t].x += starstep * x;
    stars[t].y += y;
    if (stars[t].x > SCREENWID) {
      stars[t].x = rand() / (RAND_MAX / starstep) - SPR_STARWID;
      stars[t].y = rand() / (RAND_MAX / SCREENHEI);
    } else {
      if (stars[t].x < -SPR_STARWID) {
        stars[t].x = SCREENWID - rand() / (RAND_MAX / starstep);
        stars[t].y = rand() / (RAND_MAX / SCREENHEI);
      }
    }
    if (stars[t].y > SCREENHEI) {
      stars[t].y = -SPR_STARHEI;
      stars[t].x = rand() / (RAND_MAX / (SCREENWID + SPR_STARWID)) - SPR_STARWID;
    } else {
      if (stars[t].y < -SPR_STARHEI) {
        stars[t].y = SCREENHEI;
        stars[t].x = rand() / (RAND_MAX / (SCREENWID + SPR_STARWID)) - SPR_STARWID;
      }
    }
  }
}

