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

#ifndef SPRITES_H
#define SPRITES_H

#include "sdlinc.h"


/* coordinates a collection of sprites */

class spritecontainer {

public:

  spritecontainer(void) : size(0), usage(0), array(0) {};
  ~spritecontainer(void);

  void freedata(void);

  SDL_Surface * data(const Uint16 nr) const {if (nr < usage) return array[nr]; else return 0; }
  Uint16 save(SDL_Surface * s);

private:

  Uint16 size;
  Uint16 usage;

  SDL_Surface ** array;
};

extern spritecontainer fontsprites;   // for all sprites that are alpha toggled with font option
extern spritecontainer layersprites;  // for all sprites that are alpha toggled with the layer option
extern spritecontainer objectsprites; // for all sprites that are alpha toggled with the robots option
extern spritecontainer restsprites;   // for the rest

#endif
