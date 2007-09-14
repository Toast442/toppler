/* Tower Toppler - Nebulus
 * Copyright (C) 2000-2004  Andreas Röver
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

#include "decl.h"
#include "configuration.h"

#include <SDL.h>

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#if (SYSTEM != SYS_WINDOWS)

#include <unistd.h>
#include <pwd.h>
#include <dirent.h>

#endif

static bool wait_overflow = false;
/* Not read from config file */
int  curr_scr_update_speed = MENU_DCLSPEED;

int dcl_update_speed(int spd) {
    int tmp = curr_scr_update_speed;
    curr_scr_update_speed = spd;
    return tmp;
}

void dcl_wait(void) {
  static Uint32 last;

  if (SDL_GetTicks() >= last + (Uint32)(55-(curr_scr_update_speed*5))) {
    wait_overflow = true;
    last = SDL_GetTicks();
    return;
  }

  wait_overflow = false;
  while ((SDL_GetTicks() - last) < (Uint32)(55-(curr_scr_update_speed*5)) ) SDL_Delay(2);
  last = SDL_GetTicks();
}

bool dcl_wait_overflow(void) { return wait_overflow; }

static int current_debuglevel;

void dcl_setdebuglevel(int level) {
  current_debuglevel = level;
}


void debugprintf(int lvl, char *fmt, ...) {
    if (lvl <= current_debuglevel) {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
    }
}

/* returns true, if file exists, this is not the
 optimal way to do this. it would be better to open
 the dir the file is supposed to be in and look there
 but this is not really portable so this
 */
bool dcl_fileexists(const char *n) {

  FILE *f = fopen(n, "r");

  if (f) {
    fclose(f);
    return true;
  } else
    return false;
}

char * homedir()
{

#if (SYSTEM == SYS_LINUX || SYSTEM == SYS_MACOSX)

  return getenv("HOME");

#else

  return "./";

#endif

}

/* checks if home/.toppler exists and creates it, if not */
static void checkdir(void) {

#if (SYSTEM == SYS_LINUX || SYSTEM == SYS_MACOSX)

  char n[200];

  snprintf(n, 199, "%s/.toppler", homedir());

  DIR *d = opendir(n);

  if (!d) {
    mkdir(n, S_IRWXU);
  }

#endif

}

FILE *open_data_file(const char *name) {


#if (SYSTEM == SYS_LINUX || SYSTEM == SYS_MACOSX)
  // look into actual directory
  if (dcl_fileexists(name))
    return fopen(name, "rb");

  // look into the data dir
  char n[200];

  snprintf(n, 200, TOP_DATADIR"/%s", name);
  if (dcl_fileexists(n))
    return fopen(n, "rb");

  return NULL;

#else

  if (dcl_fileexists(name))
    return fopen(name, "rb");

  return NULL;

#endif
}

FILE *open_local_config_file(const char *name) {

#if (SYSTEM == SYS_LINUX || SYSTEM == SYS_MACOSX)

  checkdir();

  char n[200];

  snprintf(n, 199, "%s/.toppler/%s", homedir(), name);
  if (dcl_fileexists(n))
    return fopen(n, "r+");

  return NULL;

#else

  if (dcl_fileexists(name))
    return fopen(name, "r+");

  return NULL;

#endif
}

FILE *create_local_config_file(const char *name) {

#if (SYSTEM == SYS_LINUX || SYSTEM == SYS_MACOSX)

  checkdir();

  char n[200];

  snprintf(n, 199, "%s/.toppler/%s", homedir(), name);

  return fopen(n, "w");

#else

  return fopen(name, "w");

#endif

}

/* used for tower and mission saving */

FILE *open_local_data_file(const char *name) {

#if (SYSTEM == SYS_LINUX || SYSTEM == SYS_MACOSX)

  checkdir();

  char n[200];

  snprintf(n, 199, "%s/.toppler/%s", homedir(), name);

  return fopen(n, "r");

#else

  return fopen(name, "rb");

#endif

}

FILE *create_local_data_file(const char *name) {

#if (SYSTEM == SYS_LINUX || SYSTEM == SYS_MACOSX)

  checkdir();

  char n[200];

  snprintf(n, 199, "%s/.toppler/%s", homedir(), name);
  return fopen(n, "w+");

#else

  fclose(fopen(name, "w+"));
  return fopen(name, "rb+");

#endif

}

static int sort_by_name(const void *a, const void *b) {
  return(strcmp((*((struct dirent **)a))->d_name, ((*(struct dirent **)b))->d_name));
}

#if (SYSTEM == SYS_WINDOWS)

int alpha_scandir(const char *dir, struct dirent ***namelist,
            int (*select)(const struct dirent *)) {
  HANDLE hand;
  WIN32_FIND_DATA finddata;
  int i = 0;
  size_t entrysize;

  struct dirent entry;

  char name[200];

  snprintf(name, 200, "%s\\*", dir);

  hand = FindFirstFile(name, &finddata);

  if (hand == INVALID_HANDLE_VALUE)
    return -1;

  *namelist = NULL;

  do {
    strncpy(entry.d_name, finddata.cFileName, 199);
    entry.d_name[200] = 0;

    if (select == NULL || (select != NULL && (*select)(&entry)))
    {
      *namelist = (struct dirent **)realloc((void *)(*namelist), (size_t)((i + 1) * sizeof(struct dirent *)));
      if (*namelist == NULL)
        return(-1);
      entrysize = sizeof(struct dirent) - sizeof(entry.d_name) + strlen(entry.d_name) + 1;
      (*namelist)[i] = (struct dirent *)malloc(entrysize);
      if ((*namelist)[i] == NULL)
        return(-1);
      memcpy((*namelist)[i], &entry, entrysize);
      i++;
    }
  } while (FindNextFile(hand, &finddata));

  FindClose(hand);

  if (i == 0)
    return(-1);

  qsort((void *)(*namelist), (size_t)i, sizeof(struct dirent *), sort_by_name);

  return(i);
}

#else

int alpha_scandir(const char *dir, struct dirent ***namelist,
            int (*select)(const struct dirent *)) {
  DIR *d;
  struct dirent *entry;
  int i = 0;
  size_t entrysize;

  if ((d = opendir(dir)) == NULL)
     return(-1);

  *namelist = NULL;
  while ((entry = readdir(d)) != NULL)
  {
    if (select == NULL || (select != NULL && (*select)(entry)))
    {
      *namelist = (struct dirent **)realloc((void *)(*namelist), (size_t)((i + 1) * sizeof(struct dirent *)));
      if (*namelist == NULL)
        return(-1);
      entrysize = sizeof(struct dirent) - sizeof(entry->d_name) + strlen(entry->d_name) + 1;
      (*namelist)[i] = (struct dirent *)malloc(entrysize);
      if ((*namelist)[i] == NULL)
        return(-1);
      memcpy((*namelist)[i], entry, entrysize);
      i++;
    }
  }
  if (closedir(d))
    return(-1);

  if (i == 0)
    return(-1);

  qsort((void *)(*namelist), (size_t)i, sizeof(struct dirent *), sort_by_name);
    
  return(i);
}

#endif

