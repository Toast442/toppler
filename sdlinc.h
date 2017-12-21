/* Tower Toppler - Nebulus
 * Copyright (C) 2000-2012  Andreas Rˆver
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

#ifndef sdlinc_h
#define sdlinc_h

#if __MACOSX__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2/SDL_types.h>
#include <SDL2/SDL_endian.h>
#include <SDL2/SDL_keyboard.h>

#pragma clang diagnostic pop

#else

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_types.h>
#include <SDL_endian.h>
#include <SDL_keyboard.h>
#endif

#endif /* sdlinc_h */
