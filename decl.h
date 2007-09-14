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

#ifndef DECL_H
#define DECL_H

#include <config.h>

#include <stdio.h>
#include <stdarg.h>
#include <dirent.h>

#if ENABLE_NLS == 1
#include <libintl.h>
#endif

/* screen width and height, in pixels. */
#define SCREENWID 640
#define SCREENHEI 480

/* font width and height, in pixels. */
#define FONTWID 24
#define FONTMINWID 10
#define FONTMAXWID 40
#define FONTHEI 40

/* the tower dimensions */
#define TOWER_SLICE_HEIGHT 16
#define TOWER_RADIUS 96
#define TOWER_COLUMNS 16  // must be a power of 2
#define TOWER_STEPS_PER_COLUMN 8
#define TOWER_ANGLES (TOWER_COLUMNS*TOWER_STEPS_PER_COLUMN)

/* title sprite "NEBULOUS" width and height, in pixels */
#define SPR_TITLEWID 602
#define SPR_TITLEHEI 90

/* star sprite size */
#define SPR_STARWID 32
#define SPR_STARHEI 32

/* size of one layer sprite of tower */
#define SPR_SLICEWID 192
#define SPR_SLICEHEI 16
#define SPR_SLICEANGLES 8
#define SPR_SLICEFRAMES 1
#define SPR_SLICESPRITES (SPR_SLICEANGLES * SPR_SLICEFRAMES)

/* size of the battlement sprite on top of the tower */
#define SPR_BATTLWID 144 * 2
#define SPR_BATTLHEI 24 * 2
#define SPR_BATTLFRAMES 8

/* size of platform sprite */
#define SPR_STEPWID 40
#define SPR_STEPHEI 15
#define SPR_STEPFRAMES 1

/* size of elevator sprite */
#define SPR_ELEVAWID 32
#define SPR_ELEVAHEI 15
#define SPR_ELEVAFRAMES 1

/* size of elevator stick / wall */
#define SPR_STICKWID 14
#define SPR_STICKHEI 15

/* size of shootable flashing box */
#define SPR_BOXWID 16
#define SPR_BOXHEI 16

/* size of our hero */
#define SPR_HEROWID 40
#define SPR_HEROHEI 40

/* size of hero's ammunition, the snowball */
#define SPR_AMMOWID 16
#define SPR_AMMOHEI 16

/* size of robot sprite */
#define SPR_ROBOTWID 32
#define SPR_ROBOTHEI 32

/* cross sprite size */
#define SPR_CROSSWID 32
#define SPR_CROSSHEI 32

/* size of the bonus game fish */
#define SPR_FISHWID  40
#define SPR_FISHHEI  40

/* submarine sprite size */
#define SPR_SUBMWID 120
#define SPR_SUBMHEI 80

/* submarine ammunition, torpedo */
#define SPR_TORPWID 32
#define SPR_TORPHEI 6

/* torpedo launch offset relative to submarine */
#define TORPEDO_OFS_X 80
#define TORPEDO_OFS_Y 30

/* submarine moving limits in bonus game */
#define SUBM_MIN_X 0
#define SUBM_MIN_Y 60
#define SUBM_MAX_X (SCREENWID/2)
#define SUBM_MAX_Y 280

/* submarine target coord during automatic guidance.
   the sub also starts from this coord. */
#define SUBM_TARGET_X (SCREENWID/2)-(SPR_SUBMWID/2)
#define SUBM_TARGET_Y 60

/* # of stars on the background during game */
#define NUM_STARS 100

/* define this if you want debugging keys during game.
   (press up+down+left+right at the same time.)
   debuggers don't get their name on hiscore table.  */
#ifdef TESTER
#define GAME_DEBUG_KEYS
#endif

/*   define this if you want the bonus game to be accessible
 from the main menu. */
#ifdef TESTER
#define HUNT_THE_FISH
#endif

/* names of the different data files */
#define grafdat         "graphics.dat"
#define fontdat         "font.dat"
#define spritedat       "sprites.dat"
#define topplerdat      "dude.dat"
#define menudat         "menu.dat"
#define crossdat        "cross.dat"
#define titledat        "titles.dat"
#define scrollerdat     "scroller.dat"

/* the special characters in the font */
#define fonttoppler     '\x01' // static view of our hero for status lines
#define fontpoint       '\x02'
#define fontemptytagbox '\x03' // checkbox
#define fonttagedtagbox '\x04' // checkbox with tickmark
#define fontptrup       '\x05' // arrow up
#define fontptrright    '\x06' // arrow right
#define fontptrdown     '\x07' // arrow down
#define fontptrleft     '\x08' // arrow left

#define FDECL(f,p) f p
#define SIZE(x) (int)(sizeof(x) / sizeof(x[0]))

#define PASSWORD_CHARS "abcdefghijklmnopqrstuvwxyz0123456789"

void dcl_setdebuglevel(int level);
void debugprintf(int lvl, char *fmt, ...);

/* waits around 1/18 of a second */
void dcl_wait(void);

/* returns true, if the last wait didn't have enough time */
bool dcl_wait_overflow(void);

/* true, if files exitst */
bool dcl_fileexists(const char *n);

/* opens files looking into the right directories */
FILE *open_data_file(const char *name);
//FILE *open_global_config_file(const char *name);
FILE *open_local_config_file(const char *name);
FILE *create_local_config_file(const char *name);
FILE *open_local_data_file(const char *name);
FILE *create_local_data_file(const char *name);

/* returns the filename that would be opened with open_data_file in
 * f, f is max len characters
 * returns true, if the file pointer of open_data_file would be not NULL
 */
bool get_data_file_path(const char * fname, char * f, int len);

/* Is the TT window active? */
extern bool tt_has_focus;

#define MENU_DCLSPEED 4
#define DEFAULT_GAME_SPEED 0
#define MAX_GAME_SPEED 3  /* from 0 to this; bigger == faster */
/* set dcl_wait() delay, and return the previous delay */
int dcl_update_speed(int spd);

/* for errorchecking */
#define assert_msg(cond,text) if (!(cond)) { printf(_("Assertion failure: %s\n"), text); exit(1); }

//#define CONFIGDIR "/etc"

/* a function that returns a alphabetically sorted list of
 files in the given dir filtered dith the function given at
 3rd parameter
 */
int alpha_scandir(const char *dir, struct dirent ***namelist,
                  int (*select)(const struct dirent *));

/* for internationalisation */
#if ENABLE_NLS == 1
#define _(x) gettext(x)
#define N_(x) x
#else
#define _(x) x
#define N_(x) x
#endif

#ifdef WIN32
typedef int mbstate_t;
size_t mbrtowc (wchar_t * out, const char *s, int n, mbstate_t * st);
#endif

#endif
