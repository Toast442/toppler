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

#ifndef SCREEN_H
#define SCREEN_H

#include "archi.h"
#include "sprites.h"

#include <SDL.h>

/* this module handles nearly all the output onto the screen */

/* screen flags for scr_drawall() */
typedef enum {
    SF_NONE,
    SF_REC,     /* display blinking "REC" */
    SF_DEMO     /* display "DEMO" */
} screenflag;

void scr_color_ramp(int *r, int *g, int *b);

void scr_savedisplaybmp(char *fname);

void scr_setclipping(int x = -1, int y = -1, int w = -1, int h = -1);

/* initializes the module, loads the graphics, sets up the display */
void scr_init(void);

/* call this when changing from windowed to fullscreen */
void scr_reinit(void);

/* call this when the sprites need to be reloaded */
/* the flags for the sprites that need to be reloaded */
enum {
  RL_FONT = 1,
  RL_OBJECTS = 2,
  RL_SCROLLER = 4
};

void scr_reload_sprites(Uint8 what);


/* frees graphics */
void scr_done(void);

/* loads a number of sprites, enters them into the sprite collection
 and returns the index of the first sprite */
void scr_read_palette(file * fi, Uint8 *pal);
Uint16 scr_loadsprites(spritecontainer *spr, file * fi, int num, int w, int h, bool sprite, const Uint8 *pal, bool usealpha);


/* changes the colors of the slices, doors and battlement
 */
void scr_settowercolor(Uint8 red, Uint8 green, Uint8 blue);
void scr_setcrosscolor(Uint8 red, Uint8 green, Uint8 blue);

/* all paint routines paint onto an invisible surface, to show this surface
 call scr_swap() */

/* writes some text onto the screen */
void scr_writetext(long x, long y, const char *s, int maxchars = -1);

/* centers the text horizontally */
void scr_writetext_center(long y, const char *s);

/* like scr_writetext_center, but tries to break the lines of text so
 * that they are not longer than the screen is wide
 */
void scr_writetext_broken_center(long y, const char *s);

/* output text that can be interleaved with commands. these commands
 have the form ~ followed by letter followed by a fixed set of parameters.
 currently the following command(s) are defined:

 t###: moves the x position to the given coordinate, relative to the
       screen. The number must have 3 digits
 T###: moves the x position to the given coordinate, relative to the
       starting x position. The number must have 3 digits.
 b#  : displays a tower block. The '#' is a character, as represented
       in towerblockdata[].ch. Does NOT show robots.
 e#  : displays tower blocks in level editor style. The '#' is a character,
       as represented in towerblockdata[].ch.
 */
void scr_writeformattext(long x, long y, const char *s);
/* returns the length of formatted text in pixels. */
long scr_formattextlength(long x, long y, const char *s);

/* returns the number of pixels the first chars characters in
 text needs in the display (if the string is only n chars long
 then only n chars are calculated) */
int scr_textlength(const char *s, int chars = 32000);

/* draws a filled rectangle with color col */
void scr_putbar(int x, int y, int br, int h, Uint8 colr, Uint8 colg, Uint8 col, Uint8 alpha);

/* darkens all the pixels on the screen a bit */
void scr_darkenscreen(void);

/* draws a rectangle */
void scr_putrect(int x, int y, int br, int h, Uint8 colr, Uint8 colg, Uint8 col, Uint8 alpha);

/* put the drawing surface onto a visible surface */
void scr_swap(void);

/* blits a sprite onto the invisible surface */
void scr_blit(SDL_Surface * s, int x, int y);

/* draws everything necessary for the towergame */
void scr_drawall(long vert, long angle, long time, bool svisible, int subshape, int substart, screenflag flags);

/* draws everything for the edit mode */
void scr_drawedit(long vert, long angle, bool showtime);

/* draws the bonus game layers behind the tower */
void scr_draw_bonus1(long horiz, long towerpos);

/* draws the bonus game layers before the tower */
void scr_draw_bonus2(long horiz, long towerpos);

void scr_draw_submarine(long vert, long x, long number);
void scr_draw_fish(long vert, long x, long number);
void scr_draw_torpedo(long vert, long x);

/* returns the number of robots in the currently loaded data set */
Uint8 scr_numrobots(void);

#endif

