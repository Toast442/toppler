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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

#include <SDL.h>
#pragma clang diagnostic pop

#include "menu.h"

class textsystem {

public:
  textsystem(const char *title, menuopt_callback_proc pr);
  ~textsystem();
  void addline(char *line);
  void run();

private:
  void draw();

  char *title;
  int  numlines;                  // # of lines
  int  shownlines;                // # of lines shown on screen
  int  ystart;                    // screen y coord where text starts
  int max_length;                // how long is the longest line?
  char **lines;
  menuopt_callback_proc mproc;    // background drawing proc
  int xoffs;                     // current x offset
  int yoffs;                     // current y offset
  int disp_xoffs;                // displayed x offset
  int disp_yoffs;                // displayed y offset
};

#endif /* TXTSYS_H */
