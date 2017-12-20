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

#ifndef LEVEL_H
#define LEVEL_H

#include <SDL_types.h>

/* handles one mission with towers and the necessary manipulations
 on the towerlayout when the game is going on */

/* tower blocks.
   if you change these, also change towerblockdata[] in level.cc */
typedef enum {
    TB_EMPTY,
    TB_STATION_TOP,
    TB_STATION_MIDDLE,
    TB_STATION_BOTTOM,
    TB_ROBOT1,
    TB_ROBOT2,
    TB_ROBOT3,
    TB_ROBOT4,
    TB_ROBOT5,
    TB_ROBOT6,
    TB_ROBOT7,
    TB_STICK,
    TB_STEP,
    TB_STEP_VANISHER,
    TB_STEP_LSLIDER,
    TB_STEP_RSLIDER,
    TB_BOX,
    TB_DOOR,
    TB_DOOR_TARGET,
    TB_STICK_TOP,
    TB_STICK_MIDDLE,
    TB_STICK_BOTTOM,
    TB_ELEV_TOP,
    TB_ELEV_MIDDLE,
    TB_ELEV_BOTTOM,
    TB_STICK_DOOR,
    TB_STICK_DOOR_TARGET,
    TB_ELEV_DOOR,
    TB_ELEV_DOOR_TARGET,
    NUM_TBLOCKS
} towerblock;

/* lev_is_consistent() returns one of these.
 * If you add to these, also add to problemstr[] in leveledit.cc */

typedef enum {
  TPROB_NONE,            // no problems found
  TPROB_NOSTARTSTEP,     // no starting step
  TPROB_STARTBLOCKED,    // starting position is blocked
  TPROB_UNDEFBLOCK,      // unknown block
  TPROB_NOELEVATORSTOP,  // elevator doesn't have stopping station(s)
  TPROB_ELEVATORBLOCKED, // elevator is blocked
  TPROB_NOOTHERDOOR,     // door doesn't have opposing end
  TPROB_BROKENDOOR,      // door is not whole
  TPROB_NOEXIT,          // no exit doorway
  TPROB_UNREACHABLEEXIT, // exit is unreachable
  TPROB_SHORTTIME,       // there's not enough time
  TPROB_SHORTTOWER,      // the tower is too short
  TPROB_NONAME,          // the tower has no name
  NUM_TPROBLEMS,
} lev_problem;

/* tries to find all missions installed on this system
 * returns the number of missions found
 */
void lev_findmissions();
Uint16 lev_missionnumber();

/* returns the name of the Nth mission */
const char * lev_missionname(Uint16 num);

/* Convert a char into towerblock */
Uint8 conv_char2towercode(wchar_t ch);

/* Get tower password. Note that the password changes when
   the tower changes. */
char *lev_get_passwd(void);
/* Do we show the tower password to user at the beginning
   of current tower? */
bool lev_show_passwd(int levnum);
/* Which tower does password allow entry to in the
   current mission? */
int lev_tower_passwd_entry(const char *passwd);

/* loads a mission from the file with the given name */
bool lev_loadmission(Uint16 num);

/* free all the memory allocated by the mission and the mission list */
void lev_done();

/* clear the tower array */
void lev_clear_tower(void);

/* returns the number of towers that are in the current mission */
Uint8 lev_towercount(void);

/* selects one of the towers in this mission */
void lev_selecttower(Uint8 number);

/* returns the color for the current tower */
Uint8 lev_towercol_red(void);
Uint8 lev_towercol_green(void);
Uint8 lev_towercol_blue(void);

void lev_set_towercol(Uint8 r, Uint8 g, Uint8 b);

/* returns the value at this position in the level array */
Uint8 lev_tower(Uint16 row, Uint8 column);
/* sets the value at this pos in the level array */
Uint8 lev_set_tower(Uint16 row, Uint8 column, Uint8 block);

/* returns the height of the tower */
Uint8 lev_towerrows(void);

/* the name of the tower */
char *lev_towername(void);
void lev_set_towername(const char *str);

/* tower demo */
void lev_set_towerdemo(int demolen, Uint16 *demobuf);
void lev_get_towerdemo(int &demolen, Uint16 *&demobuf);

/* the number of the actual tower */
Uint8 lev_towernr(void);

/* returns true, if current tower is the last one */
bool lev_lasttower(void);

/* the number of the robot used */
Uint8 lev_robotnr(void);
void lev_set_robotnr(Uint8 robot);

/* the time the player has to reach the top */
Uint16 lev_towertime(void);

void lev_set_towertime(Uint16 time);

/* removes one layer of the tower (for destruction) */
void lev_removelayer(Uint8 layer);

/* if the positions contains a vanishing step, remove it */
void lev_removevanishstep(int row, int col);

// returns true if the given position contains an upper end of a door
bool lev_is_door_upperend(int row, int col);

// returns true, if the given positions contains a level of a door
bool lev_is_door(int row, int col);

// returns true, if block in tower pos is a robot
bool lev_is_robot(int row, int col);

// returns true, if the given coordinates contains a layer of a target door
bool lev_is_targetdoor(int row, int col);

/* all for the elevators */

/* completely empty */
bool lev_is_empty(int row, int col);

/* contains a flashing box */
bool lev_is_box(int row, int col);

/* empty this field */
void lev_clear(int row, int col);

/* a station (not necessary with a platform */
bool lev_is_station(int row, int col);
bool lev_is_up_station(int row, int col);
bool lev_is_down_station(int row, int col);
bool lev_is_bottom_station(int row, int col);

/* contains a platform */
bool lev_is_platform(int row, int col);

/* contains stick */
bool lev_is_stick(int row, int col);

/* is part of an elevator */
bool lev_is_elevator(int row, int col);

/* sliding step
   returns: 0 = no sliding, 1 = sliding right, -1 = sliding left */
int lev_is_sliding(int row, int col);

/* start and stop elevator */
void lev_platform2stick(int row, int col);
void lev_stick2platform(int row, int col);

/* move up and down */
void lev_stick2empty(int row, int col);
void lev_empty2stick(int row, int col);
void lev_platform2empty(int row, int col);

/* checks the given figure for validity of its position (can
 it be there without colliding ?) */
bool lev_testfigure(int angle, int vert, int back,
                    int fore, int typ, int height, int width);


/* used for the elevator */
unsigned char lev_putplatform(int row, int col);
void lev_restore(int row, int col, unsigned char bg);

/* --- the following commands are for the level editor ---  */

/* load and save a tower in a human readable format */
bool lev_loadtower(const char *fname);
bool lev_savetower(const char *fname);

/* rotate row clock and counter clockwise */
void lev_rotaterow(int row, bool clockwise);


/* insert and delete one row */
void lev_insertrow(int position);
void lev_deleterow(int position);

/* creates a simple tower consisting of 'hei' rows */
void lev_new(Uint8 hei);

/* functions to change one field on the tower */
void lev_putspace(int row, int col);
void lev_putrobot1(int row, int col);
void lev_putrobot2(int row, int col);
void lev_putrobot3(int row, int col);
void lev_putrobot4(int row, int col);
void lev_putrobot5(int row, int col);
void lev_putrobot6(int row, int col);
void lev_putrobot7(int row, int col);
void lev_putrobot8(int row, int col);
void lev_putstep(int row, int col);
void lev_putvanishingstep(int row, int col);
void lev_putslidingstep_left(int row, int col);
void lev_putslidingstep_right(int row, int col);
void lev_putdoor(int row, int col);
void lev_puttarget(int row, int col);
void lev_putstick(int row, int col);
void lev_putbox(int row, int col);
void lev_putelevator(int row, int col);
void lev_putmiddlestation(int row, int col);
void lev_puttopstation(int row, int col);

/* creates a copy of the current tower, the functions
 * allocate the necessary RAM and the restore function
 * frees the RAM again
 */
void lev_save(unsigned char *&data);
void lev_restore(unsigned char *&data);

/* check the tower for consistency. This function checks doors
 * and elevators, and if something is found, row and col contain the
 * coordinates, and the return value is one of TPROB_xxx
 */
lev_problem lev_is_consistent(int &row, int &col);

/* mission creation: first call mission_new(), then
 * for each tower mission_addtower() and finally to complete
 * the mission mission_finish(). never use another calling order
 * or you may create corrupted mission files.
 */
bool lev_mission_new(char * name, Uint8 prio = 255);
void lev_mission_addtower(char * name);
void lev_mission_finish();

#endif
