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

#include "highscore.h"
#include "decl.h"
#include "screen.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef __QNXNTO__
   #include <strings.h>
#endif // __QNXNTO__

#define NUMHISCORES 10

#define SCOREFNAME "toppler.hsc"

/* the group ids of the game */
static gid_t UserGroupID, GameGroupID;

/* true, if we use the global highscore table, false if not */
static bool globalHighscore;

/* the name of the highscore table we use the name because the
 * file might change any time and so it's better to close and reopen
 * every time we need access
 */
static char highscoreName[200];

typedef struct {
  Uint32 points;
  char name[SCORENAMELEN+1];
  Sint16 tower; /* tower reached, -1 = mission finished */
} _scores;

static _scores scores[NUMHISCORES];

/* this is the name of the surrenlty selected mission */
static char missionname[100];

#ifdef WIN32
#define setegid(x)
#endif

static void savescores(FILE *f) {

  unsigned char len;
  char mname[256];

  while (!feof(f)) {

    if ((fread(&len, 1, 1, f) == 1) &&
        (fread(mname, 1, len, f) == len)) {
      mname[len] = 0;
      if (strcasecmp(mname, missionname) == 0) {

        // this is necessary because some system can not switch
        // on the fly from reading to writing
        fseek(f, ftell(f), SEEK_SET);

        fwrite(scores, sizeof(_scores)*NUMHISCORES, 1, f);
        return;
      }
    } else
      break;

    fseek(f, ftell(f) + sizeof(_scores)*NUMHISCORES, SEEK_SET);
  }

  unsigned char tmp = strlen(missionname);

  fwrite(&tmp, 1, 1, f);
  fwrite(missionname, 1, tmp, f);
  fwrite(scores, sizeof(_scores)*NUMHISCORES, 1, f);
}

static void loadscores(FILE *f) {

  unsigned char len;
  char mname[256];

  while (f && !feof(f)) {

    if ((fread(&len, 1, 1, f) == 1) &&
        (fread(mname, 1, len, f) == len) &&
        (fread(scores, 1, sizeof(_scores) * NUMHISCORES, f) == sizeof(_scores) * NUMHISCORES)) {
      mname[len] = 0;
      if (strcasecmp(mname, missionname) == 0)
        return;
    }
  }

  for (int t = 0; t < NUMHISCORES; t++) {
    scores[t].points = 0;
    scores[t].name[0] = 0;
  }
}

static bool hsc_lock(void) {

#ifndef WIN32

  if (globalHighscore) {

    setegid(GameGroupID);
    int lockfd;

    while ((lockfd = open(HISCOREDIR "/" SCOREFNAME ".lck", O_CREAT | O_RDWR | O_EXCL, S_IRUSR | S_IWUSR)) == -1) {
      dcl_wait();
      scr_swap();
    }
    close(lockfd);
    setegid(UserGroupID);
  }

#endif

  if (globalHighscore) setegid(GameGroupID);
  FILE *f = fopen(highscoreName, "rb");
  if (globalHighscore) setegid(UserGroupID);

  loadscores(f);

  if (f) fclose(f);

  return true;
}

static void hsc_unlock(void) {

#ifndef WIN32

  if (globalHighscore) {
    setegid(GameGroupID);
    unlink(HISCOREDIR "/" SCOREFNAME ".lck");
    setegid(UserGroupID);
  }

#endif
}

void hsc_init(void) {

  for (int t = 0; t < NUMHISCORES; t++) {
    scores[t].points = 0;
    scores[t].name[0] = 0;
    scores[t].tower = 0;
  }

#ifndef WIN32

  /* fine at first save the group ids and drom group privileges */
  UserGroupID = getgid ();
  GameGroupID = getegid ();

  setegid(UserGroupID);

  /* asume we use local highscore table */
  globalHighscore = false;
  snprintf(highscoreName, 199, "%s/.toppler/%s", homedir(), SCOREFNAME);

  /* now check if we have access to a global highscore table */

#ifdef HISCOREDIR

  /* ok the dir is given, we need to be able to do 2 things: */

  /* 1. get read and write access to the file */

  char fname[200];
  snprintf(fname, 200, HISCOREDIR "/" SCOREFNAME);

  setegid(GameGroupID);
  FILE * f = fopen(fname, "r+");
  setegid(UserGroupID);

  if (f) {

    fclose(f);

    /* 2. get write access to the directory to create the lock file
     * to check this we try to chreate a file with a random name
     */
    snprintf(fname, 200, HISCOREDIR "/" SCOREFNAME "%i", rand());

    setegid(GameGroupID);
    f = fopen(fname, "w+");
    setegid(UserGroupID);

    if (f) {

      fclose(f);
      setegid(GameGroupID);
      unlink(fname);
      setegid(UserGroupID);

      /* ok, we've got all the rights we need */
      snprintf(highscoreName, 200, HISCOREDIR "/" SCOREFNAME);
      globalHighscore = true;
    }
  }

#endif

  /* no dir to the global highscore table -> not global highscore table */

  if (globalHighscore)
    debugprintf(2, "using global highscore at %s\n", highscoreName);
  else
    debugprintf(2, "using local highscore at %s\n", highscoreName);

#else // ifdef WIN32

  /* for non unix systems we use only local highscore tables */
  globalHighscore = false;
  snprintf(highscoreName, 200, SCOREFNAME);

#endif

}

void hsc_select(const char * mission) {
  strncpy(missionname, mission, 100);

  if (globalHighscore) setegid(GameGroupID);
  FILE *f = fopen(highscoreName, "rb");
  if (globalHighscore) setegid(UserGroupID);

  loadscores(f);

  if (f) fclose(f);
}

Uint8 hsc_entries(void) { return NUMHISCORES; }

void hsc_entry(Uint8 nr, char *name, Uint32 *points, Uint8 *tower) {

  if (nr < NUMHISCORES) {
    if (name) strncpy(name, scores[nr].name, SCORENAMELEN);
    if (points) *points = scores[nr].points;
    if (tower) *tower = scores[nr].tower;
  } else {
    if (name) name[0] = 0;
    if (points) *points = 0;
    if (tower) *tower = 0;
  }
}

bool hsc_canEnter(Uint32 points) {
  return points > scores[NUMHISCORES-1].points;
}

Uint8 hsc_enter(Uint32 points, Uint8 tower, char *name) {

  if (hsc_lock()) {

    int t = NUMHISCORES;

    while ((t > 0) && (points > scores[t-1].points)) {
      if (t < NUMHISCORES)
        scores[t] = scores[t-1];
      t--;
    }

    if (t < NUMHISCORES) {

      strncpy(scores[t].name, name, SCORENAMELEN);
      scores[t].points = points;
      scores[t].tower = tower;

      FILE *f;

      if (globalHighscore) {
        if (globalHighscore) setegid(GameGroupID);
        f = fopen(highscoreName, "r+b");
        if (globalHighscore) setegid(UserGroupID);
      } else {

        /* local highscore: this one might require creating the file */
        fclose(fopen(highscoreName, "a+"));
        f = fopen(highscoreName, "r+b");
      }

      savescores(f);
      fclose(f);

      hsc_unlock();

      return t;
    }

    hsc_unlock();
  }

  return 0xff;
}

