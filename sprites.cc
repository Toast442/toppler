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

#include "sprites.h"

#include "decl.h"

#include <stdlib.h>
#include <string.h>

spritecontainer::~spritecontainer(void) {
  freedata();
}

void spritecontainer::freedata(void) {
  for (int i = 0; i < usage; i++)
    SDL_FreeSurface(array[i]);

  delete [] array;

  array = 0;
  usage = 0;
  size = 0;
}

Uint16 spritecontainer::save(SDL_Surface *s) {
  if (usage == size) {
    SDL_Surface **array2 = new SDL_Surface*[size + 200];

    assert_msg(array2, "could not alloc memory for sprite array");

    if (usage)
      memcpy(array2, array, usage * sizeof(SDL_Surface*));

    if (array)
      delete [] array;

    array = array2;

    size += 200;
  }

  Uint16 erg = usage;
  array[usage++] = s;

  return erg;
}

spritecontainer fontsprites;
spritecontainer layersprites;
spritecontainer objectsprites;
spritecontainer restsprites;

