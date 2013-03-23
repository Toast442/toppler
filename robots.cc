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

#include "robots.h"

#include "decl.h"
#include "level.h"
#include "screen.h"
#include "toppler.h"
#include "sound.h"

#include <stdlib.h>

#define MAX_OBJECTS 4

/* this field contains the robots */
static struct {

  /* the position of the robot */
  int anglepos;
  long verticalpos;

  /* what kind of robot it is, an under classification
   and what kind it will be after the appearing animation */
  rob_kinds kind;
  long subKind;
  rob_kinds futureKind;

  /* a timer for the animations of the robots */
  long time;
} object[MAX_OBJECTS];


/* the position up to where the robots are worked out */
static int robots_ready;
static int robots_angle;

/* the data for the next cross that will appear */
static int next_cross_timer;
static int cross_direction;
static int nextcrosscolor;


/******** PRIVATE FUNCTIONS ********/

/* returns the index of the figure the given figure (nr) collides
 with or -1 if there is no such object */
static int figurecollision(int nr) {

  /* help field for collisions between two objects */
  static unsigned char collision[16] = {
    0x1c, 0x3e, 0x3e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x3e, 0x3e, 0x1c, 0x00
  };

  int t;
  long i, j;

  for (t = 0; t < MAX_OBJECTS; t++) {
    if (t != nr &&
        object[t].kind != OBJ_KIND_CROSS &&
        object[t].kind != OBJ_KIND_NOTHING &&
        object[t].kind != OBJ_KIND_DISAPPEAR &&
        object[t].kind != OBJ_KIND_APPEAR) {
      i = object[nr].anglepos - object[t].anglepos;
      j = object[t].verticalpos - object[nr].verticalpos;
      if ((-4 < i) && (i < 4)  && (-8 < j) && (j < 8)) {
        if ((collision[j + 7] >> (i + 3)) & 1)
          return t;
        else
          return -1;
      }
    }
  }
  return -1;
}

/* returns true, if the robot cannot be at the given position without colliding
 with an element from the tower */
static bool testroboter(int nr) {
  return (!lev_testfigure((long)object[nr].anglepos, object[nr].verticalpos, -2L, 1L, 1L, 1L, 7L));
}

/* makes the robot disappear when it falls into water */
static void drown_robot(int nr) {
  object[nr].verticalpos = 0;
  object[nr].time = 0;
  object[nr].kind = OBJ_KIND_DISAPPEAR;
}

/* tests the underground of the given object (only used for freeze ball) returns
 0 if nothing needs to be done
 1 for falling
 2 for reverse direction
 */
static int test_robot_undergr(int nr) {

  int row, col;
  row = object[nr].verticalpos / 4 - 1;
  col = (object[nr].anglepos / 8) & 0xf;

  if (lev_is_box(row, col)) return 0;
  if (lev_is_platform(row, col) || lev_is_stick(row, col)) {
    if (lev_is_elevator(row, col))
      return 2;
    else
      return 0;
  }

  if ((object[nr].anglepos & 7) < 2) {
    if (lev_is_empty(row, (col - 1) & 0xf)) return 1;
    if (lev_is_door(row, (col - 1) & 0xf)) return 1;
    if ((object[nr].subKind & 0x80) == 0)
      return 2;
    else
      return 0;
  }

  if ((object[nr].anglepos & 7) > 6) {
    if (lev_is_empty(row, (col + 1) & 0xf)) return 1;
    if (lev_is_door(row, (col + 1) & 0xf)) return 1;
    if ((object[nr].subKind & 0x80) == 0)
      return 0;
    else
      return 2;
  }

  return 1;
}

/* update the position for the cross */
static void updatecross(int t) {

  object[t].anglepos += object[t].subKind;
  object[t].time -= object[t].subKind;

  /* after the cross reached the middle speed it up */
  if (object[t].anglepos == 60)
    object[t].subKind *= 2;

  /* if cross reached screenedge, remove it an reinitialize
   counter for next one */
  if (((object[t].subKind > 0) && (object[t].anglepos >= 120)) ||
      ((object[t].subKind < 0) && (object[t].anglepos <= 0))) {
    object[t].kind = OBJ_KIND_NOTHING;
    next_cross_timer = 125;
  }
}

/* remove objects that drop below the screen */
static bool checkverticalposition(int verticalpos, int t) {

  if (object[t].verticalpos + 48 < verticalpos) {
    object[t].kind = OBJ_KIND_DISAPPEAR;
    object[t].time = 0;
    return true;
  } else
    return false;

}

/* checks if the robot is at a position that it can not be
 if not remove it */
static bool checkvalidposition(int t) {

  if (testroboter(t)) {
    object[t].kind = OBJ_KIND_DISAPPEAR;
    object[t].time = 0;
    return true;
  } else
    return false;

}

/* move the robot a the horizontal amount, if this places it
 at an impossible position, reverse its direction and don't move it */
static void moverobothorizontal(int t) {

  object[t].anglepos += object[t].subKind;
  object[t].anglepos &= 0x7f;
  if (testroboter(t) || (figurecollision(t) != -1)) {
    object[t].subKind = -object[t].subKind;
    object[t].anglepos += object[t].subKind;
    object[t].anglepos &= 0x7f;
  }

}


/******* PUBLIC FUNCTIONS *********/

rob_kinds rob_kind(int nr) { return object[nr].kind; }
int rob_time(int nr) { return object[nr].time; }
int rob_angle(int nr) { return object[nr].anglepos; }
int rob_vertical(int nr) { return object[nr].verticalpos; }

void rob_initialize(void) {

  for (int b = 0; b < MAX_OBJECTS; b++) {
    object[b].kind = OBJ_KIND_NOTHING;
    object[b].time = -1;
  }

  next_cross_timer = 125;
  nextcrosscolor = rand() / (RAND_MAX / 8);
  cross_direction = 1;

  robots_ready = 0;
  robots_angle = 0;

}

int rob_topplercollision(int angle, int vertical) {
  long i, j;

  for (int t = 0; t < MAX_OBJECTS; t++) {
    if (object[t].kind != OBJ_KIND_CROSS &&
        object[t].kind != OBJ_KIND_NOTHING &&
        object[t].kind != OBJ_KIND_DISAPPEAR &&
        object[t].kind != OBJ_KIND_APPEAR) {
      i = angle - object[t].anglepos;
      j = object[t].verticalpos - vertical;
      if ((-4 < i) && (i < 4)  && (-8 < j) && (j < 8))
        return t;
    } else if (object[t].kind == OBJ_KIND_CROSS) {
      if (object[t].anglepos >= 53 && object[t].anglepos <= 67 &&
          object[t].verticalpos + 7 >= vertical &&
          vertical + 9 >= object[t].verticalpos)
        return t;
    }
  }
  return -1;
}

int rob_snowballcollision(int angle, int vertical) {

  /* help field for collisions between two objects */
  static unsigned char collision[16] = {
     0x00, 0x1c, 0x1c, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x10
  };

  long i, j;
  for (int t = 0; t < MAX_OBJECTS; t++) {
    if (object[t].kind != OBJ_KIND_CROSS &&
        object[t].kind != OBJ_KIND_NOTHING &&
        object[t].kind != OBJ_KIND_DISAPPEAR &&
        object[t].kind != OBJ_KIND_APPEAR) {
      i = angle - object[t].anglepos;
      j = object[t].verticalpos - vertical;
      if ((-4 < i) && (i < 4)  && (-8 < j) && (j < 8)) {
        if ((collision[j + 7] >> (i + 3)) & 1)
          return t;
        else
          return -1;
      }
    }
  }
  return -1;
}

void rob_new(int verticalpos) {

  static struct {
    unsigned char r, g, b;
  } crosscols[8] = {
    { 0xff, 0x00, 0x00 },
    { 0x00, 0xff, 0x00 },
    { 0x00, 0x00, 0xff },
    { 0xff, 0xff, 0x00 },
    { 0x00, 0xff, 0xff },
    { 0xff, 0x00, 0xff },
    { 0x80, 0x80, 0x80 },
    { 0xff, 0xff, 0xff }
  };

  int a, b;

  int h = verticalpos / 4 + 9;

  for (int t = 0; t < MAX_OBJECTS; t++) {
    if (object[t].kind == OBJ_KIND_NOTHING) {


      /* if there is currently no chance for a new robot check for a cross */
      if ((robots_ready == lev_towerrows() * 8) || (h <= robots_ready)) {

        /* check if time is ripe */
        if (next_cross_timer == -1) return;
        next_cross_timer--;
        if (next_cross_timer != -1) return;

        /* set colors for the cross */
        scr_setcrosscolor(crosscols[nextcrosscolor].r,
                          crosscols[nextcrosscolor].g,
                          crosscols[nextcrosscolor].b);
        nextcrosscolor = (nextcrosscolor + 1) & 7;

        /* fill in the data for the robot */
        object[t].kind = OBJ_KIND_CROSS;
        object[t].time = 0;
        cross_direction *= -1;
        object[t].subKind = cross_direction;
        if (cross_direction > 0)
          object[t].anglepos = 0;
        else
          object[t].anglepos = 120;
        object[t].verticalpos = verticalpos;

        ttsounds::instance()->startsound(SND_CROSS);

      } else {
        bool is_robo = false;

        /* find next robot */
        do {
          b = lev_tower(robots_ready, robots_angle);
          is_robo = lev_is_robot(robots_ready, robots_angle);
          a = robots_angle;
          h = robots_ready;
          robots_angle = (robots_angle + 1) & 0xf;
        } while ((!is_robo) && robots_angle != 0);

        if (robots_angle == 0)
          robots_ready++;

        /* no robot found */
        if (!is_robo) return;

        /* fill in data for robot */
        switch (b) {

        case TB_ROBOT1:
          object[t].subKind = 1;
          object[t].futureKind = OBJ_KIND_FREEZEBALL;
          break;

        case TB_ROBOT2:
          object[t].subKind = 1;
          object[t].futureKind = OBJ_KIND_JUMPBALL;
          break;

        case TB_ROBOT3:
          object[t].subKind = 0;
          object[t].futureKind = OBJ_KIND_JUMPBALL;
          break;

        case TB_ROBOT4:
          object[t].subKind = 1;
          object[t].futureKind = OBJ_KIND_ROBOT_VERT;
          break;

        case TB_ROBOT5:
          object[t].subKind = 2;
          object[t].futureKind = OBJ_KIND_ROBOT_VERT;
          break;

        case TB_ROBOT6:
          object[t].subKind = 1;
          object[t].futureKind = OBJ_KIND_ROBOT_HORIZ;
          break;

        case TB_ROBOT7:
          object[t].subKind = 2;
          object[t].futureKind = OBJ_KIND_ROBOT_HORIZ;
          break;
        }
        object[t].anglepos = (a * 8) + 4;
        object[t].verticalpos = h * 4;
        object[t].kind = OBJ_KIND_APPEAR;
        object[t].time = 0;

        /* empty the field in the level datastructure */
        lev_clear(h, a);
      }

      return;
    }
  }
}

void rob_update(void) {

  /* the vertical movement of the jumping ball */
  static long jumping_ball[11] = {
    2, 2, 1, 1, 0, 0, -1, -1, -2, -2, -4
  };

  int h;

  for (int t = 0; t < MAX_OBJECTS; t++) {
    switch (object[t].kind) {
      case OBJ_KIND_NOTHING:
        break;

      case OBJ_KIND_CROSS:
        updatecross(t);
        break;

      case OBJ_KIND_DISAPPEAR:
        if (object[t].time == 6)
          object[t].kind = OBJ_KIND_NOTHING;
        else
          object[t].time++;
        break;

      case OBJ_KIND_APPEAR:
        if (object[t].time == 6) {
          object[t].kind = object[t].futureKind;
          object[t].time = 0;
        } else
          object[t].time++;
        break;

      case OBJ_KIND_FREEZEBALL_FROZEN:
        object[t].time--;
        if (object[t].time > 0)
          break;
        object[t].kind = OBJ_KIND_FREEZEBALL;

      case OBJ_KIND_FREEZEBALL:

        if (checkverticalposition(top_verticalpos(), t) ||
            checkvalidposition(t)) break;

        switch (test_robot_undergr(t)) {
          case 1:
            object[t].kind = OBJ_KIND_FREEZEBALL_FALLING;
            object[t].time = 10;
            break;
          case 2:
            object[t].subKind = -object[t].subKind;
            break;
        }
        moverobothorizontal(t);
        break;

      case OBJ_KIND_FREEZEBALL_FALLING:

        if (checkverticalposition(top_verticalpos(), t) ||
            checkvalidposition(t)) break;

        moverobothorizontal(t);

        if (object[t].verticalpos + jumping_ball[object[t].time] < 0) {
          drown_robot(t);
          break;
        }

        h = jumping_ball[object[t].time];

        while (h != 0) {

          object[t].verticalpos += h;
          if (!testroboter(t) || (figurecollision(t) != -1)) break;
          object[t].verticalpos -= h;

          if (h > 0)
            h--;
          else
            h++;
        }

        if ((h == 0) && (jumping_ball[object[t].time] < 0)) {
          object[t].kind = OBJ_KIND_FREEZEBALL;
          object[t].time = 0;
        }
        break;

      case OBJ_KIND_JUMPBALL:

        if (checkverticalposition(top_verticalpos(), t) ||
            checkvalidposition(t)) break;

        h = object[t].subKind;
        moverobothorizontal(t);

        if (h * object[t].subKind < 0) {
          unsigned char w = (object[t].anglepos - top_anglepos()) & 0x7f;
          if (w >= 0x40)
            w |= 0x80;
          if (w >= 0x80)
            w = 0xff & (~w + 1);

          ttsounds::instance()->setsoundvol(SND_BOINK, 120-w);
          ttsounds::instance()->startsound(SND_BOINK);
        }

        if (object[t].verticalpos + jumping_ball[object[t].time] < 0) {
          drown_robot(t);
          break;
        }

        h = jumping_ball[object[t].time];

        while (h != 0) {

          object[t].verticalpos += h;
          if (!testroboter(t) || (figurecollision(t) != -1)) break;
          object[t].verticalpos -= h;

          if (h > 0)
            h--;
          else
            h++;
        }

        /* ball is bouncing */
        if ((h == 0) && (jumping_ball[object[t].time] < 0)) {

          unsigned char w = (object[t].anglepos - top_anglepos()) & 0x7f;
          if (w >= 0x40)
            w |= 0x80;
          if (w >= 0x80)
            w = 0xff & (~w + 1);

          ttsounds::instance()->setsoundvol(SND_BOINK, 128-2*w);
          ttsounds::instance()->startsound(SND_BOINK);

          /* restart bounce cyclus */
          object[t].time = 0;

          /* start the bounding ball moving sideways in direction of the animal */
          if (object[t].subKind == 0 && top_visible() && top_walking() &&
              object[t].verticalpos == top_verticalpos()) {

            /* check if the animal is near enough to the ball */
            unsigned char w = (object[t].anglepos - top_anglepos()) & 0x7f;
            h = -1;
            if (w >= 0x40)
              w |= 0x80;
            if (w >= 0x80) {
              w = 0xff & (~w + 1);
              h = 1;
            }

            if (w < 0x20) object[t].subKind = h;
          }
          break;
        }

        object[t].time++;
        if (object[t].time > 10)
          object[t].time = 10;

        break;

      case OBJ_KIND_ROBOT_HORIZ:

        if (checkverticalposition(top_verticalpos(), t) ||
            checkvalidposition(t)) break;

        moverobothorizontal(t);

        object[t].time = (object[t].time + 1) & 0x1f;
        break;

      case OBJ_KIND_ROBOT_VERT:

        if (checkverticalposition(top_verticalpos(), t) ||
            checkvalidposition(t)) break;

        if ((object[t].verticalpos + object[t].subKind) < 0)
          drown_robot(t);
        else {
          object[t].verticalpos += object[t].subKind;

          if (testroboter(t) || (figurecollision(t) != -1)) {
            object[t].subKind *= -1;
            object[t].verticalpos += object[t].subKind;
          }
        }

        object[t].time = (object[t].time + 1) & 0x1f;
        break;
    }
  }
}

int rob_gothit(int nr) {

  if (object[nr].kind == OBJ_KIND_FREEZEBALL) {
    object[nr].time = 0x4b;
    object[nr].kind = OBJ_KIND_FREEZEBALL_FROZEN;
    return 0;
  } else if (object[nr].kind == OBJ_KIND_JUMPBALL) {
    object[nr].kind = OBJ_KIND_DISAPPEAR;
    object[nr].time = 0;
    return 100;
  } else
    return 0;
}

void rob_disappearall(void) {

  for (int t = 0; t < MAX_OBJECTS; t++) {
    if (object[t].kind != OBJ_KIND_NOTHING) {
      object[t].kind = OBJ_KIND_DISAPPEAR;
      object[t].time = 0;
    }
  }
}

