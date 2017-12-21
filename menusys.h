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

#ifndef MENUSYS_H
#define MENUSYS_H

#include "decl.h"

#include "sdlinc.h"

/* This module defines a menu system that has the following features
*/

#define MENUTITLELEN  1000
#define MENUOPTIONLEN MENUTITLELEN

/* Menu option flags */
typedef enum {
  MOF_NONE     = 0x00,
  MOF_PASSKEYS = 0x01,  /* Do keys get passed onto this option? */
  MOF_LEFT     = 0x02,  /* Option string is left justified */
  MOF_RIGHT    = 0x04   /* Option string is right justified */
} menuoptflags;

struct _menusystem;

/* menu option callback function. gets called with the
   menusystem as it's parameter, and should return a
   string describing this option. If the parameter
   is null, then this is called just to get the
   string back. */
typedef const char *FDECL((*menuopt_callback_proc), (struct _menusystem *));

/* menu background callback procedure. this should draw the
   background screen for the menu. */
typedef void FDECL((*menubg_callback_proc), (void));


/* menu option */
typedef struct {
   char oname[MENUOPTIONLEN];    /* text shown to user */
   menuopt_callback_proc oproc;  /* callback proc, supplies actions and the name */
   int  ostate;                  /* callback proc can use this */
   menuoptflags  oflags;         /* MOF_foo */
   SDL_Keycode quickkey;              /* quick jump key; if user presses this key,
                                  * this menu option is hilited.
                                  */
} _menuoption;


typedef struct _menusystem {
   char title[MENUTITLELEN];     /* title of the menu */
   int numoptions;               /* # of options in this menu */
   _menuoption *moption;         /* the options */
   menuopt_callback_proc mproc;
   menuopt_callback_proc timeproc;
   long curr_mtime;              /* current time this menu has been running */
   long mtime;                   /* time when to call timeproc */
   int hilited;                  /* # of the option that is hilited */
   int mstate;                   /* menu state, free to use by callback procs */
   int maxoptlen;                /* longest option name length, in pixels.
                                  * the hilite bar is slightly longer than this
                                  */
   bool exitmenu;                /* if true, the menu exits */
   bool wraparound;              /* if true, the hilite bar wraps around */
   int ystart;                   /* y pos where this menu begins, in pixels */
   int yhilitpos;                /* y pos of the hilite bar, in pixels */
   int opt_steal_control;        /* if >= 0, that option automagically gets
                                  * keys passed to it, and normal key/mouse
                                  * processing doesn't happen.
                                  */
   SDL_Keycode key;                   /* the key that was last pressed */

   struct _menusystem * parent;  /* the current parrent, or NULL */

} _menusystem;

/* input line; asks the user for a string.
 *
 * This function returns immediately, and the return
 * value tells whether the user finished editing the string.
 */
bool men_input(char *origs, int max_len, int xpos = -1,
               int ypos = (SCREENHEI  * 2) / 3,
               const char *allowed = NULL);

/* asks a yes/no question; return 0 if "no",
   1 if "yes" */
unsigned char men_yn(const char *s, bool defchoice, menuopt_callback_proc pr = 0);

/* shows string s, waits a certain time, (-1 = indefinitely),
   and if fire = 1 -> "press fire", if fire = 2 -> "press space" */
void men_info(const char *s, long timeout = -1, int fire = 0);


/* sets the function that gets called whenever the background
   needs to be drawn in men_yn(), and men_info() */
void set_men_bgproc(menubg_callback_proc proc);


/* create a new menu */
_menusystem *new_menu_system(const char *title, menuopt_callback_proc pr,
                                    int molen = 0, int ystart = 25);

/* add an option to the menu */
_menusystem *add_menu_option(_menusystem *ms, const char *name, menuopt_callback_proc pr,
                                    SDL_Keycode quickkey = SDLK_UNKNOWN, menuoptflags flags = MOF_NONE, int state = 0);

/* displays the given menu on screen and lets the user interact with it*/
_menusystem *run_menu_system(_menusystem *ms, _menusystem *parent);


void free_menu_system(_menusystem *ms);


_menusystem *set_menu_system_timeproc(_menusystem *ms, long t, menuopt_callback_proc pr);

#endif
