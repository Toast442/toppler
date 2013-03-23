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

#ifndef TXTSYS_H
#define TXTSYS_H

#include <SDL.h>
#include "menu.h"

class textsystem {

public:
  textsystem(char *title, menuopt_callback_proc pr);
  ~textsystem();
  void addline(char *line);
  void run();

private:
  void draw();

  char *title;
  int  numlines;                  // # of lines
  int  shownlines;                // # of lines shown on screen
  int  ystart;                    // screen y coord where text starts
  long max_length;                // how long is the longest line?
  char **lines;
  menuopt_callback_proc mproc;    // background drawing proc
  long xoffs;                     // current x offset
  long yoffs;                     // current y offset
  long disp_xoffs;                // displayed x offset
  long disp_yoffs;                // displayed y offset
};

#endif /* TXTSYS_H */
