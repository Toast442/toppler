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

#include "toppler.h"

#include "robots.h"
#include "elevators.h"
#include "snowball.h"
#include "level.h"
#include "sound.h"

/* the position of the animal on the tower */
int anglepos;
long verticalpos;

/* the state of the toppler */
int state, substate;

/* have we entered the target door */
bool targetdoor;

/* some help variables for the falling toppler */
int falling_howmuch;
long falling_direction;
int falling_minimum;

/* some variables defining how to jump */
int jumping_direction, jumping_how, jumping_howlong;

/* used to time the turning of the tower when a door was entered */
int door_turner;

long elevator_direction;

/* how much must the toppler topple down */
int topple_min;

/* used when on an elevator to delay the toppling until we
 reached the next brick layer */
bool topple_delay;

/* technique points; is decreased each time the toppler gets
 thrown down */
int technic;

/* true if the toppler is visible */
static bool tvisible;
/* should the output routine put an elevator
 platform below the toppler ? */
static bool on_elevator;
/* the actual shape of the toppler */
static int topplershape;
/* the direction the toppler is looking at */
static bool look_left;


/* values for status */
#define STATE_STANDING 0
#define STATE_JUMPING 1
#define STATE_FALLING 2
#define STATE_TURNING 3
#define STATE_DOOR 4
#define STATE_SHOOTING 5
#define STATE_ELEVATOR 6
#define STATE_TOPPLING 7
#define STATE_DROWN 8
#define STATE_DROWNED 9
#define STATE_FINISHED 10


void top_init(void) {
  anglepos = 4;
  verticalpos = 8;
  state = 0;
  substate = 0;
  tvisible = true;
  on_elevator = false;
  look_left = true;
  targetdoor = false;
  topple_delay = false;
  door_turner = 0;
  technic = 0x100;
}

/* tests the underground of the animal at the given position returning
 0 if everything is all right
 1 if there is no underground below us (fall vertical)
 2 if there is no underground behind us (fall backwards)
 3 if there is no underground in front of us (fall forwards) */
static int testunderground(int verticalpos, int anglepos, bool look_left) {
  static unsigned char unter[32] = {
    0x11, 0x20, 0x02, 0x00,
    0x11, 0x00, 0x32, 0x00,
    0x11, 0x00, 0x32, 0x00,
    0x11, 0x00, 0x11, 0x00,
    0x11, 0x00, 0x11, 0x00,
    0x11, 0x00, 0x11, 0x00,
    0x11, 0x23, 0x00, 0x00,
    0x11, 0x23, 0x00, 0x00
  };

  int erg;

  int r = (verticalpos / 4) - 1;
  int c = ((anglepos + 0x7a) / 8) & 0xf;

  erg = (lev_is_empty(r, c) || lev_is_door(r, c)) ? 0 : 2;

  c = ((anglepos + 0x7a) / 8 + 1) & 0xf;

  if ((!lev_is_empty(r, c)) && (!lev_is_door(r, c))) erg++;

  erg = unter[(anglepos & 0x7) * 4 + erg];

  if (look_left)
    return erg >> 4;
  else
    return erg & 0xf;
}



/* makes the toppler fall down, the parameter specifies in
 which direction:
 0 = down start falling
 1 = backwards
 2 = forwards
 3 = down but already at a high speed (e.g. after a jump) */
static void falling(int nr) {

  state = STATE_FALLING;
  substate = 0;

  switch (nr) {
    case 0:
      topplershape = 0;
      falling_direction = 0;
      falling_minimum = -1;
      falling_howmuch = 1;
      break;

    case 1:
      topplershape = 0xf;
      falling_direction = look_left ? -1 : 1;
      falling_minimum = -1;
      falling_howmuch = 1;
      break;

    case 2:
      topplershape = 0xe;
      falling_direction = look_left ? 1 : -1;
      falling_minimum = -1;
      falling_howmuch = 1;
      break;

    case 3:
      topplershape = 0;
      falling_direction = 0;
      falling_minimum = -1;
      falling_howmuch = 3;
      break;
  }
}

static void walking(void) {

  state = STATE_STANDING;
  substate = 0;
}

static void elevator(long dir) {

  elevator_direction = dir;
  substate = 0;
  state = STATE_ELEVATOR;

  ele_select((Uint16)verticalpos, anglepos);
}

static void shooting(void) {

  if (snb_exists()) {
    walking();
    return;
  }
  state = STATE_SHOOTING;
  substate = 0;
  topplershape = 0;
  ttsounds::instance()->startsound(SND_SHOOT);
}

static void door(void) {

  state = STATE_DOOR;
  substate = 0;
}

static void turn(void) {

  state = STATE_TURNING;
  substate = 0;
}

static void jump(int left_right) {

  state = STATE_JUMPING;
  substate = 0;
  jumping_direction = left_right;
  jumping_how = 0;
  jumping_howlong = 0xc;
}

static void step(int left_right) {

  state = STATE_JUMPING;
  substate = 0;
  jumping_direction = left_right;
  jumping_how = 1;
  jumping_howlong = 0x7;
}

static void drown(void) {

  state = STATE_DROWN;
  substate = 0;
  verticalpos = 0;

  ttsounds::instance()->setsoundvol(SND_SPLASH, 128);
  ttsounds::instance()->startsound(SND_SPLASH);
}

static void topple(void) {

  state = STATE_TOPPLING;
  substate = 0;
  targetdoor = false;

  technic -= 2;
  if (technic < 0) technic = 0;
}

/* tries to move the toppler by the given amount, returns true on
 success and false if the move is not possible (collision with
 a tower element) */
static bool movetoppler(long x, long y) {

  if (verticalpos + y < 0) {
    drown();
    return false;
  }
  if (!lev_testfigure((anglepos + x) & 0x7f, verticalpos + y, -3, 2, 0, 0, 9))
    return false;
  anglepos = (anglepos + x) & 0x7f;
  verticalpos += y;
  return true;
}

static void slidestep(int left_right, bool look_left) {

  if (left_right)
    return;

  int dir;

  if (look_left)
    dir = lev_is_sliding(verticalpos / 4 - 1, (anglepos) / 8);
  else
    dir = lev_is_sliding(verticalpos / 4 - 1, (anglepos-1) / 8);

  movetoppler((long)dir, 0);
}

/* the state machine of the animal */
void top_updatetoppler(int left_right, int up_down, bool space) {

  /* table specifying the number for the animal sprite if it is turning
   around */
  static unsigned char umdreh[7] = {
    0x8, 0x9, 0xa, 0xb, 0xa, 0x9, 0x8
  };

  /* the sprites if the animal turns to enter the door */
  static unsigned char door1[4] = {
    0x10, 0x11, 0x12, 0x13
  };

  /* and when it enters the door */
  static unsigned char door2[6] = {
    0x13, 0x14, 0x14, 0x15, 0x15, 0x16
  };

  /* when it leaves the door */
  static unsigned char door3[6] = {
    0x17, 0x18, 0x18, 0x19, 0x19, 0xb
  };

  /* the shapes of the toppler when it turns after leaving a door*/
  static unsigned char door4[4] = { 0xa, 0x9, 0x8, 0x0 };

  /* the height differences for jumping */
  static long jump0[12] = { 3, 2, 2, 1, 1, 0, 0, -1, -1, -2, -2, -3 };
  static long jump1[7] = { 2, 2, 1, 0, -1, -2, -2 };

  /* sprites for throwing the snowball */
  static unsigned char schiessen[3] = {
    0x00, 0x1a, 0x1b
  };

  /* the sprites for toppling over */
  static unsigned char toppler1[4] = {
    0x00, 0x1c, 0x1d, 0x1e
  };

  /* the vertical movement for toppling */
  static long toppler2[16] = {
    3, 2, 1, 1, 1, 0, 0, -1, -2, -2, -3, -3, -3, -3, -3, -4
  };

  int inh, b;

  switch (state) {

  case STATE_STANDING:
    lev_removevanishstep(verticalpos / 4 - 1, anglepos / 8);
    switch (testunderground(verticalpos, anglepos, look_left)) {
      case 0:
        if (left_right == 0) {
          if (space)
            shooting();
          else {
            if (lev_is_up_station(verticalpos / 4 - 1, anglepos / 8) &&
                (up_down == 1)) {
              elevator(up_down);
              break;
            }
            if (lev_is_down_station(verticalpos / 4 - 1, anglepos / 8) &&
                (up_down == -1)) {
              elevator(up_down);
              break;
            }

            if (lev_is_door_upperend(verticalpos / 4, anglepos / 8) &&
                (up_down == 1)) {
              targetdoor = lev_is_targetdoor(verticalpos / 4, anglepos / 8);
              door();
              break;
            }

            slidestep(left_right, look_left);
            topplershape = 0xc;
          }
        } else {
          if ((substate == 2) || (substate == 6)) ttsounds::instance()->startsound(SND_TAP);
          if (left_right == -1) {
            if (look_left)
              turn();
            else {
              if (space)
                jump(left_right);
              else {
                if (!movetoppler(left_right, 0L))
                  step(left_right);
                else {
                  substate = (substate + 1) & 0x7;
                  topplershape = substate;
                }
              }
            }
          } else {
            if (!look_left)
              turn();
            else {
              if (space)
                jump(left_right);
              else {
                if (!movetoppler(left_right, 0L))
                  step(left_right);
                else {
                  substate = (substate + 1) & 0x7;
                  topplershape = substate;
                }
              }
            }
          }
        }
        break;

      case 1:
        falling(0);
        break;

      case 2:
        falling(1);
        break;

      case 3:
        falling(2);
        break;
    }
    break;

  case STATE_JUMPING:
    topplershape = substate & 7;
    movetoppler(jumping_direction, 0L);
    if (jumping_how == 0)
      inh = jump0[substate];
    else
      inh = jump1[substate];

    if (movetoppler(0, inh)) {
      substate++;
      if (substate >= jumping_howlong) {
        if (movetoppler(0, -1))
          falling(3);
        else {
          state = STATE_FALLING;
          substate = 1;
        }
      }
    } else {
      b = inh;
      do {
        if (inh < 0)
          inh++;
        else
          inh--;
      } while (!((inh == 0) || movetoppler(0L, inh)));
      if (b < 0) {
        walking();
        ttsounds::instance()->startsound(SND_TAP);
      } else {
        substate++;
        if (substate >= jumping_howlong) {
          if (movetoppler(0L, -1L))
            falling(3);
          else {
            state = STATE_FALLING;
            substate = 1;
          }
        }
      }
    }
    break;

  case STATE_FALLING:
    if (substate == 0) {
      falling_minimum++;
      if (!movetoppler(falling_direction, 0))
        falling_direction = 0;
      if (movetoppler(0, -falling_howmuch)) {
        falling_howmuch++;
        if (falling_howmuch > 4)
          falling_howmuch = 4;
      } else {
        do {
          falling_howmuch--;
        } while (falling_howmuch && !movetoppler(0, -falling_howmuch));
        ttsounds::instance()->startsound(SND_TAP);
        if (falling_howmuch != 0) {
          falling_howmuch++;
          if (falling_howmuch > 4)
            falling_howmuch = 4;
        } else {
          if ((falling_direction == 0) || (falling_minimum >= 2)) {
            substate++;
            topplershape = 14 - substate;
            substate++;
            if (substate == 3) {
              walking();
            }
          } else {
            falling_howmuch++;
            if (falling_howmuch > 4)
              falling_howmuch = 4;
          }
        }
      }
    } else {
      topplershape = 14 - substate;
      substate++;
      if (substate == 3)
        walking();
    }
    break;

  case STATE_TURNING:
    topplershape = umdreh[substate];
    substate++;
    if ((substate == 4) || (substate == 7)) ttsounds::instance()->startsound(SND_TAP);
    if (substate == 4) look_left = !look_left;
    if (substate == 7) walking();
    break;

  case STATE_DOOR:


    switch (substate) {

    case 0:
    case 1:
    case 2:
    case 3:
      topplershape = door1[substate];
      if (((anglepos) & 7) == 4)
        substate++;
      else if (((anglepos) & 7) > 4)
        movetoppler(-1L, 0L);
      else
        movetoppler(1L, 0L);

      break;

    case 4:
    case 5:
    case 6:
      substate = 7;
      break;

    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
      topplershape = door2[substate - 7];
      substate++;
      break;

    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
      topplershape = door3[substate - 29];
      tvisible = true;
      substate++;
      break;

    case 35:
      if (!movetoppler(0L, -4L)) {
        if (left_right == -1)
          look_left = false;
        else
          look_left = true;
        substate++;
      }
      break;

    case 36:
    case 37:
    case 38:
    case 39:
      topplershape = door4[substate - 36];
      substate++;
      break;

    case 40:
      walking();
      break;

    default:
      if (substate >= 13 && substate <= 28) {
        if ((door_turner % 4) == 0)
          ttsounds::instance()->startsound(SND_DOORTAP);

        tvisible = false;
        if (targetdoor) {
          state = STATE_FINISHED;
          ttsounds::instance()->startsound(SND_FANFARE);
        } else {
          if (look_left)
            anglepos += 2;
          else
            anglepos -= 2;

          anglepos &= 0x7f;
          door_turner++;
          if ((door_turner & 1) == 0)
            substate++;
        }
      }
      break;
    }
    break;

  case STATE_SHOOTING:
    slidestep(left_right, look_left);
    if (substate == 3) {
      walking();
    } else {
      topplershape = schiessen[substate];
      if (substate == 1)
        snb_start(verticalpos, anglepos, look_left);
      substate++;
    }
    break;

  case STATE_ELEVATOR:

    if (substate == 0) {
      /* move the animal to the center of the elevator platform */
      if (((anglepos) & 7) != 4) {
        if (((anglepos) & 7) < 4)
          (anglepos)++;
        else
          (anglepos)--;
        anglepos &= 0x7f;
        return;
      }
      substate++;
      on_elevator = true;
      ele_activate((Sint8)elevator_direction);
      ttsounds::instance()->startsound(SND_TICK);
      return;
    }
    verticalpos += elevator_direction;

    if ((substate > 0) && (verticalpos & 3) == 0) {

      if (ele_is_atstop()) {
        on_elevator = false;
        ele_deactivate();
        walking();
      } else {
        ele_move();
        ttsounds::instance()->startsound(SND_TICK);
      }
    }
    break;

  case STATE_TOPPLING:
    if (substate < topple_min) {

      topplershape = toppler1[(substate / 2) & 3];

      if (substate < 15)
        verticalpos += toppler2[substate];
      else
        verticalpos += toppler2[15];

      if (verticalpos < 0)
        drown();
      else
        substate++;

    } else {
      topplershape = 0;
      verticalpos -= 4;
      if (verticalpos < 0)
        drown();
      else if (movetoppler(0, 0))
        falling(3);
    }
    break;

  case STATE_DROWN:
    if (substate == 0x8) ttsounds::instance()->startsound(SND_DROWN);
    if (substate < 0x18) {
      topplershape = substate / 4 + 31;
      substate++;
    } else {
      tvisible = false;
      if (substate < 0x20)
        substate++;
      else {
        state = STATE_DROWNED;
      }
    }
    break;

  case STATE_DROWNED:
  case STATE_FINISHED:
    break;

  }
}

void top_testcollision(void) {
  int nr;

  if ((state == STATE_TOPPLING) ||
      (state == STATE_DROWN) ||
      ((state == STATE_DOOR) && (substate >= 10) && (substate < 31)) ||
      (!tvisible))
    return;

  if (topple_delay) {
    if (state == STATE_ELEVATOR) {
      if ((verticalpos & 3) == 0) {
        ele_deactivate();
        on_elevator = false;

        topple_delay = false;
        topple();
      }
    } else {
      topple_delay = false;
      topple();
    }
    return;
  } else {
    nr = rob_topplercollision(anglepos, verticalpos + 1);
    if (nr != -1) {

      if (rob_kind(nr) == OBJ_KIND_CROSS)
        topple_min = 15;
      else
        topple_min = 20;

      if (state == STATE_ELEVATOR) {
        if ((verticalpos & 3) == 0) {
          ele_deactivate();
          topple_delay = false;
          on_elevator = false;
          topple();
        } else {
          topple_delay = true;
        }
      } else {
        topple();
      }
    } else if ((state == STATE_ELEVATOR) && !movetoppler(0L, 0L)) {

      topple_min = 20;
      if ((verticalpos & 3) == 0) {
        ele_deactivate();
        topple_delay = false;
        on_elevator = false;
        topple();
      } else {
        topple_delay = true;
      }
    }
  }
}


int top_verticalpos(void) { return verticalpos; }
int top_anglepos(void) { return anglepos; }
bool top_visible(void) { return tvisible; }
bool top_look_left(void) { return look_left; }
int top_shape(void) { return topplershape; }
bool top_onelevator(void) { return on_elevator; }
int top_technic(void) { return technic; }

bool top_died(void) { return state == STATE_DROWNED; }
bool top_targetreached(void) { return state == STATE_FINISHED; }
bool top_ended(void) { return ((state == STATE_DROWNED) || (state == STATE_FINISHED)); }
bool top_dying(void) {
  return ((state == STATE_DROWN) ||
          (state == STATE_DROWNED) ||
          (state == STATE_FINISHED));
}
bool top_walking(void) { return state == STATE_STANDING; }

void top_drop1layer(void) { verticalpos -= 4; }

void top_hide(void) { tvisible = false; }
void top_show(int shape, int vpos, int apos) {
  tvisible = true;
  topplershape = shape;
  verticalpos = vpos;
  anglepos = apos;
  look_left = true;
}

void top_sidemove(void) {
  // FIXME: the toppler needs the be brought out of the way of the elevater when they fall down
  // that needs to happen at least when standing, walking and jumping, but it might be also in other
  // cases
  // it is definitively not necessary when falling and drowning
  // i hope this if is right
  if ((state != STATE_STANDING) &&
      (state != STATE_JUMPING) &&
      (state != STATE_TURNING) &&
      (state != STATE_SHOOTING))
    return;

  if (movetoppler( 0, 0)) return;

  int i = 1;
  while (1) {
    if (movetoppler( i, 0)) break;
    if (movetoppler(-i, 0)) break;
    i++;
  }
}

