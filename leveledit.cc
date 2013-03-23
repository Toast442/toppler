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

#include "leveledit.h"

#include "decl.h"
#include "level.h"
#include "screen.h"
#include "keyb.h"
#include "game.h"
#include "sound.h"
#include "robots.h"
#include "snowball.h"
#include "menu.h"
#include "txtsys.h"
#include "configuration.h"

#include <stdlib.h>
#include <string.h>

/* Editor key actions.
 If you add here, change _ed_key_actions[] in leveledit.cc */

typedef enum {
  EDACT_QUIT,
  EDACT_MOVEUP,
  EDACT_MOVEDOWN,
  EDACT_MOVELEFT,
  EDACT_MOVERIGHT,
  EDACT_INSROW,
  EDACT_DELROW,
  EDACT_ROT180,
  EDACT_PUTSPACE,
  EDACT_PUTSTEP,
  EDACT_PUTVANISHER,
  EDACT_PUTSLIDERLEFT,
  EDACT_PUTSLIDERRIGHT,
  EDACT_PUTDOOR,
  EDACT_PUTGOAL,
  EDACT_CHECKTOWER,
  EDACT_PUTROBOT1,
  EDACT_PUTROBOT2,
  EDACT_PUTROBOT3,
  EDACT_PUTROBOT4,
  EDACT_PUTROBOT5,
  EDACT_PUTROBOT6,
  EDACT_PUTROBOT7,
  EDACT_PUTLIFT,
  EDACT_PUTLIFTMID,
  EDACT_PUTLIFTTOP,
  EDACT_PUTSTICK,
  EDACT_PUTBOX,
  EDACT_LOADTOWER,
  EDACT_SAVETOWER,
  EDACT_TESTTOWER,
  EDACT_SETTOWERCOLOR,
  EDACT_INCTIME,
  EDACT_DECTIME,
  EDACT_CREATEMISSION,
  EDACT_MOVEPAGEUP,
  EDACT_MOVEPAGEDOWN,
  EDACT_GOTOSTART,
  EDACT_SHOWKEYHELP,
  EDACT_NAMETOWER,
  EDACT_SETTIME,
  EDACT_REC_DEMO,
  EDACT_PLAY_DEMO,
  EDACT_ADJHEIGHT,
  EDACT_GOTOEND,
  EDACT_CUTROW,
  EDACT_PASTEROW,
  EDACT_TOGGLEROBOT,

  NUMEDITORACTIONS
} key_actions;

struct _ed_key {
   key_actions action;
   SDLKey key;
   char   character;
   Uint16 mod; /* KMOD_NONE|KMOD_SHIFT|KMOD_CTRL|KMOD_ALT */
};

#define TOWERPAGESIZE 5 /* pageup/pagedown moving */
#define TOWERSTARTHEI 4 /* tower starting height */

const char *_ed_key_actions[NUMEDITORACTIONS] = {
   N_("Quit"),          N_("Move up"),        N_("Move down"),       N_("Move left"),
   N_("Move right"),    N_("Insert row"),     N_("Delete row"),      N_("Rotate 180"),
   N_("Put space"),     N_("Put step"),       N_("Put vanisher"),    N_("Put slider left"),
   N_("Put slider right"),
   N_("Put door"),      N_("Put goal"),       N_("Check tower"),     N_("Put rolling ball"),
   N_("Put jumping ball moving"),   N_("Put jumping ball"),    N_("Put robot up down"),     N_("Put robot up down fast"),
   N_("Put robot left right"),   N_("Put robot left right fast"),    N_("Put lift"),        N_("Lift middle stop"),
   N_("Lift top stop"), N_("Put pillar"),     N_("Put box"),         N_("Load tower"),
   N_("Save tower"),    N_("Test tower"),     N_("Set tower color"), N_("Increase time"),
   N_("Decrease time"), N_("Create mission"), N_("Move page up"),    N_("Move page down"),
   N_("Go to start"),   N_("Show this help"), N_("Name the tower"),  N_("Set tower time"),
   N_("Record demo"),   N_("Play demo"),      N_("Adjust tower height"), N_("Go to end"),
   N_("Cut row"),       N_("Paste row"),      N_("Change robot type")
};

const struct _ed_key _ed_keys[] = {
   {EDACT_QUIT,          SDLK_ESCAPE},
   {EDACT_SHOWKEYHELP,   SDLK_F1},
   {EDACT_SHOWKEYHELP,   SDLK_h,     'h'},
   {EDACT_MOVEUP,        SDLK_UP},
   {EDACT_MOVEDOWN,      SDLK_DOWN},
   {EDACT_MOVELEFT,      SDLK_LEFT},
   {EDACT_MOVERIGHT,     SDLK_RIGHT},
   {EDACT_MOVEPAGEUP,    SDLK_PAGEUP},
   {EDACT_MOVEPAGEDOWN,  SDLK_PAGEDOWN},
   {EDACT_GOTOSTART,     SDLK_HOME},
   {EDACT_GOTOEND,       SDLK_END},
   {EDACT_ROT180,        SDLK_y,     'y'},
   {EDACT_INSROW,        SDLK_INSERT},
   {EDACT_DELROW,        SDLK_DELETE},
   {EDACT_CUTROW,        SDLK_MINUS, '-'},
   {EDACT_PASTEROW,      SDLK_PLUS,  '+'},
   {EDACT_PUTSPACE,      SDLK_SPACE, ' '},
   {EDACT_PUTSTEP,       SDLK_w,     'w'},
   {EDACT_PUTVANISHER,   SDLK_s,     's'},
   {EDACT_PUTSLIDERLEFT, SDLK_x,     'x'},
   {EDACT_PUTSLIDERRIGHT,SDLK_x,     'X', KMOD_SHIFT},
   {EDACT_PUTDOOR,       SDLK_i,     'i'},
   {EDACT_PUTGOAL,       SDLK_k,     'k'},
   {EDACT_PUTROBOT1,     SDLK_1,     '1'},
   {EDACT_PUTROBOT2,     SDLK_2,     '2'},
   {EDACT_PUTROBOT3,     SDLK_3,     '3'},
   {EDACT_PUTROBOT4,     SDLK_4,     '4'},
   {EDACT_PUTROBOT5,     SDLK_5,     '5'},
   {EDACT_PUTROBOT6,     SDLK_6,     '6'},
   {EDACT_PUTROBOT7,     SDLK_7,     '7'},
   {EDACT_TOGGLEROBOT,   SDLK_8,     '8'},
   {EDACT_PUTLIFT,       SDLK_c,     'c'},
   {EDACT_PUTLIFTMID,    SDLK_d,     'd'},
   {EDACT_PUTLIFTTOP,    SDLK_e,     'e'},
   {EDACT_PUTSTICK,      SDLK_q,     'q'},
   {EDACT_PUTBOX,        SDLK_a,     'a'},
   {EDACT_CHECKTOWER,    SDLK_z,     'z'},
   {EDACT_LOADTOWER,     SDLK_l,     'l'},
   {EDACT_SAVETOWER,     SDLK_o,     'o'},
   {EDACT_TESTTOWER,     SDLK_p,     'p'},
   {EDACT_SETTOWERCOLOR, SDLK_v,     'v'},
   {EDACT_SETTIME,       SDLK_b,     'b'},
   {EDACT_INCTIME,       SDLK_n,     'n'},
   {EDACT_DECTIME,       SDLK_n,     'N', KMOD_SHIFT},
   {EDACT_CREATEMISSION, SDLK_m,     'm'},
   {EDACT_NAMETOWER,     SDLK_t,     't'},
   {EDACT_REC_DEMO,      SDLK_F10},
   {EDACT_PLAY_DEMO,     SDLK_F11},
   {EDACT_ADJHEIGHT,     SDLK_F8}
};

static int bg_row;
static int bg_col;
static char *bg_text = NULL;
static bool bg_darken = false;

/* men_yn() background drawing callback proc */
static void editor_background_proc(void) {
   scr_drawedit(bg_row * 4, bg_col * 8, false);
   if (bg_darken) scr_darkenscreen();
   if (bg_text) scr_writetext_center(5, bg_text);
}

static const char *editor_background_menu_proc(_menusystem *ms) {
    editor_background_proc();
    return 0;
}

static bool really_quit(int row, int col) {
  bg_darken = true;
  if (men_yn(_("Tower changed, really quit"), false)) {
    return true;
  } else {
    return false;
  }
  bg_darken = false;
}

static bool really_load(int row, int col) {
  bg_darken = true;
  if (men_yn(_("Tower changed, really load"), false)) {
    return true;
  } else {
    return false;
  }
  bg_darken = false;
}

static bool edit_towercolor(int row, int col) {

  int activecol = 0, abg_r = 10, abg_g = 50, abg_b = 120;
  bool ende = false, oldpal = false;
  char cbuf[32];
  int tmpcol, z, tmp;
  int oldc[3], newc[3], curc[3];
  SDLKey c;

  const char *colorname[] = {_("Red"), _("Green"), _("Blue")};

  curc[0] = newc[0] = oldc[0] = lev_towercol_red();
  curc[1] = newc[1] = oldc[1] = lev_towercol_green();
  curc[2] = newc[2] = oldc[2] = lev_towercol_blue();
  bg_darken = false;
  do {

    scr_drawedit(row * 4, col * 8, false);
    scr_writetext_center(22, _("Tower Color"));

    for (tmp = 0 ; tmp < 3; tmp++) {
      scr_color_ramp(&abg_r, &abg_g, &abg_b);
      tmpcol = newc[tmp];
      z = ((SCREENHEI * 2) / 3) + tmp * (FONTHEI + 2);

      if (tmp == activecol) {
        scr_putbar((SCREENWID / 2) - (128 + 8), z, 8, FONTHEI, abg_r, abg_g, abg_b, 255);
        scr_putbar((SCREENWID / 2) + 128 - 1, z, 8, FONTHEI, abg_r, abg_g, abg_b, 255);
      } else {
        scr_putbar((SCREENWID / 2) - (128 + 8), z, 8, FONTHEI, 66, 66, 66, 255);
        scr_putbar((SCREENWID / 2) + 128 - 1, z, 8, FONTHEI, 66, 66, 66, 255);
      }
      scr_putbar((SCREENWID / 2) - 128 + tmpcol, z, 255 - tmpcol, FONTHEI, 0,0,0, 255);
      switch (tmp) {
      default:
      case 0: scr_putbar((SCREENWID / 2) - 128, z, tmpcol, FONTHEI, tmpcol / 3 + 64, 0, 0, 255); break;
      case 1: scr_putbar((SCREENWID / 2) - 128, z, tmpcol, FONTHEI, 0, tmpcol / 3 + 64, 0, 255); break;
      case 2: scr_putbar((SCREENWID / 2) - 128, z, tmpcol, FONTHEI, 0, 0, tmpcol / 3 + 64, 255); break;
      }
      cbuf[0] = '\0';
      snprintf(cbuf, 32, "%5s  %.3d", colorname[tmp], tmpcol);
      scr_writetext_center(z, cbuf);
    }

    scr_swap();
    dcl_wait();

    c = key_sdlkey();

    switch (c) {
    case SDLK_UP: if (activecol > 0) activecol--; break;
    case SDLK_DOWN: if (activecol < 2) activecol++; break;
    case SDLK_LEFT: if (newc[activecol] > 0)   newc[activecol]--; break;
    case SDLK_RIGHT: if (newc[activecol] < 255) newc[activecol]++; break;
    case SDLK_PAGEDOWN: if (newc[activecol] > 10)  newc[activecol] = newc[activecol] - 10;
                                              else newc[activecol] = 0;  break;
    case SDLK_PAGEUP: if (newc[activecol] < 245)  newc[activecol] = newc[activecol] + 10;
                                             else newc[activecol] = 255; break;
    case SDLK_0: case SDLK_1: case SDLK_2: case SDLK_3: case SDLK_4:
    case SDLK_5: case SDLK_6: case SDLK_7: case SDLK_8:
    case SDLK_9: newc[activecol] = (int) ((c - '0') * 256) / 10; break;
    case SDLK_PERIOD: for (tmp = 0; tmp < 3; tmp++) newc[tmp] = rand() % 256; break;
    case SDLK_r: activecol = 0; break;
    case SDLK_g: activecol = 1; break;
    case SDLK_b: activecol = 2; break;
    case SDLK_ESCAPE: ende = true; oldpal = true; break;
    case SDLK_SPACE:
    case SDLK_RETURN: ende = true;
    default: break;
    }

    if ((newc[0] != curc[0]) || (newc[1] != curc[1]) ||
        (newc[2] != curc[2]) || oldpal) {
      if (oldpal)
        lev_set_towercol(oldc[0],oldc[1],oldc[2]);
      else
        lev_set_towercol(newc[0],newc[1],newc[2]);

      scr_settowercolor(lev_towercol_red(),
                        lev_towercol_green(),
                        lev_towercol_blue());

      curc[0] = newc[0];
      curc[1] = newc[1];
      curc[2] = newc[2];
    }

  } while (!ende);

  return (!oldpal && ((curc[0] != oldc[0]) || (curc[1] != oldc[1]) || (curc[2] != oldc[2])));
}

static void edit_checktower(int &row, int &col) {
  int r, c, pr;
  r = row;
  c = -col;

  static char *problemstr[NUM_TPROBLEMS] = {
    _("No problems found"),
    _("No starting step"),
    _("Start is blocked"),
    _("Unknown block"),
    _("No elevator stop"),
    _("Elevator is blocked"),
    _("No opposing doorway"),
    _("Broken doorway"),
    _("No exit"),
    _("Exit is unreachable"),
    _("Not enough time"),
    _("Tower is too short"),
    _("Tower has no name")
  };

  pr = lev_is_consistent(r, c);
  if ((r >= lev_towerrows()) && (lev_towerrows() > 0)) r = lev_towerrows() - 1;
  bg_row = r;
  bg_col = -c;

  bg_text = _("Tower check:");
  bg_darken = true;
  men_info(problemstr[pr % NUM_TPROBLEMS], 50, 2);
  bg_darken = false;
  row = bg_row;
  col = bg_col;
  bg_text = NULL;
}

char *keymod2str(Uint16 kmod) {
    static char buf[256];
    buf[0] = '\0';
    if (kmod != KMOD_NONE) {
        if ((kmod & KMOD_LSHIFT) ||
            (kmod & KMOD_RSHIFT)) snprintf(buf, 256, "shift+");
        if ((kmod & KMOD_LCTRL) ||
            (kmod & KMOD_RCTRL)) snprintf(&buf[strlen(buf)], 256-strlen(buf), "ctrl+");
        if ((kmod & KMOD_LALT) ||
            (kmod & KMOD_RALT)) snprintf(&buf[strlen(buf)], 256-strlen(buf), "alt+");
    }
    return buf;
}

static void createMission(void) {

  scr_drawedit(0, 0, false);
  scr_writetext_center(30, _("Mission creation"));
  scr_writetext_center(80, _("enter mission name"));
  scr_writetext_center(110, _("empty to abort"));

  set_men_bgproc(NULL);

  char missionname[25];
  missionname[0] = 0;
  while (!men_input(missionname, 15)) ;

  if (!missionname[0])
    return;

  if (!lev_mission_new(missionname)) {

    scr_drawedit(0, 0, false);
    scr_writetext_center(30, _("Mission creation"));

    scr_writetext_center(80, _("could not create file"));
    scr_writetext_center(110, _("aborting"));

    scr_swap();

    int inp;

    do {
      inp = key_chartyped();
    } while (!inp);

    return;
  }

  int currenttower = 1;
  char towername[30];

  while (true) {

    scr_drawedit(0, 0, false);
    scr_writetext_center(30, _("Mission creation"));
    scr_writetext_center(80, _("enter name of"));

    char s[30];
    snprintf(s, 30, _("tower no %i"), currenttower);
    scr_writetext_center(110, s);

    towername[0] = 0;
    while (!men_input(towername, 25)) ;

    if (!towername[0]) break;

    lev_mission_addtower(towername);

    currenttower++;
  }

  lev_mission_finish();

  lev_findmissions();
}

static void le_showkeyhelp(int row, int col) {
  int k;
  int maxkeylen = 0;
  textsystem *ts = new textsystem(_("Editor Key Help"), editor_background_menu_proc);
  char tabbuf1[6], tabbuf2[6];

  if (!ts) return;

  for (k = 0; k < SIZE(_ed_keys); k++) {
      char knam[256];
      snprintf(knam, 256, "%s%s", keymod2str(_ed_keys[k].mod), SDL_GetKeyName(_ed_keys[k].key));
      int l = scr_textlength(knam);

      if (l > maxkeylen) maxkeylen = l;
  }

  snprintf(tabbuf1, 6, "%3i", maxkeylen + FONTWID);
  if (tabbuf1[0] < '0') tabbuf1[0] = '0';
  if (tabbuf1[1] < '0') tabbuf1[1] = '0';
  if (tabbuf1[2] < '0') tabbuf1[2] = '0';

  for (k = 0; k < SIZE(_ed_keys); k++) {
      char buf[256];
      char tmpb[256];
      char knam[256];

      snprintf(knam, 256, "%s%s", keymod2str(_ed_keys[k].mod), SDL_GetKeyName(_ed_keys[k].key));

      snprintf(tabbuf2, 6, "%3i", maxkeylen - scr_textlength(knam));
      if (tabbuf2[0] < '0') tabbuf2[0] = '0';
      if (tabbuf2[1] < '0') tabbuf2[1] = '0';
      if (tabbuf2[2] < '0') tabbuf2[2] = '0';

      snprintf(tmpb, 256, "~T%s%%s~T%s%%s", tabbuf2, tabbuf1);
      snprintf(buf, 256, tmpb, knam, _(_ed_key_actions[_ed_keys[k].action]));

      ts->addline(buf);
  }
  bg_darken = true;
  ts->run();
  bg_darken = false;
  delete ts;
}

static int clipboard_rows = 0;
static Uint8 clipboard_tower[256][16];
static bool cursor_moved = false;

void le_tower_cut(int row, int col) {
    if (cursor_moved) clipboard_rows = 0;

    if (clipboard_rows < 255) {
        for (int i = 0; i < 16; i++)
            clipboard_tower[clipboard_rows][i] = lev_tower(row, (col+i) % 16);
        lev_deleterow(row);
        clipboard_rows++;
    }

    cursor_moved = false;
}

void le_tower_paste(int row, int col) {
    if (clipboard_rows > 0) {
        for (int z = 0; z < clipboard_rows; z++) {
            lev_insertrow(row);
            for (int i = 0; i < 16; i++) {
                lev_set_tower(row, (col+i) % 16, clipboard_tower[clipboard_rows - (z + 1)][i]);
            }
        }
    } else lev_insertrow(row);

    cursor_moved = false;
}

void le_edit(void) {

  bool ende = false;
  bool changed = false;
  SDLKey inp = SDLK_UNKNOWN;
  char inp_char;
  Uint16 keymod;
  int row = 0, col = 0;
  int tstep = 0;
  int blink_r = 70, blink_g = 40, blink_b = 10;
  char status[80];
  int towerstarthei;
  int pagesize;

  if (config.editor_towerstarthei() < 0)
      towerstarthei = TOWERSTARTHEI + (rand() % abs(config.editor_towerstarthei()));
  else towerstarthei = TOWERSTARTHEI + config.editor_towerstarthei();

  lev_new(towerstarthei % 256);

  if (config.editor_towerpagesize() < 1) {
    config.editor_towerpagesize(TOWERPAGESIZE);
    pagesize = TOWERPAGESIZE;
  } else pagesize = config.editor_towerpagesize();

  set_men_bgproc(editor_background_proc);

  lev_set_towertime(100 + (rand() % 10) * 50);

  lev_set_towercol(rand() % 256,rand() % 256,rand() % 256);
  scr_settowercolor(lev_towercol_red(),
                    lev_towercol_green(),
                    lev_towercol_blue());

  lev_set_towername("");
  lev_set_towerdemo(0, NULL);

  while (!ende) {

    bg_row = row;
    bg_col = col;
    bg_darken = false;

    scr_drawedit(row * 4, col * 8, true);

    status[0] = '\0';
    snprintf(status, 80, "%c~t050X%d~t150Y%d~t250%s:%d",
             changed ? '*' : ' ', -col & 0xf, row, _("cut#"), clipboard_rows);

    scr_putbar(SCREENWID-8, SCREENHEI-lev_towerrows(), 8, lev_towerrows(),
               lev_towercol_red(), lev_towercol_green(), lev_towercol_blue(), 255);
    scr_putbar(SCREENWID-8, SCREENHEI-row-1, 8, 1, blink_r, blink_g, blink_b, 128);

    scr_color_ramp(&blink_r, &blink_g, &blink_b);

    scr_writeformattext(0, SCREENHEI-FONTHEI, status);

    scr_swap();
    dcl_wait();

    inp_char = key_chartyped();
    inp = key_sdlkey();
    keymod = (SDL_GetModState() & ~(KMOD_NUM|KMOD_CAPS|KMOD_MODE));
    if (keymod & KMOD_SHIFT) keymod |= KMOD_SHIFT;
    if (keymod & KMOD_CTRL) keymod |= KMOD_CTRL;
    if (keymod & KMOD_ALT) keymod |= KMOD_ALT;
    if (keymod & KMOD_META) keymod |= KMOD_META;


    int k, action = -1;

    if (inp_char != 0)
      for (k = 0; k < SIZE(_ed_keys); k++)
        if (_ed_keys[k].character == inp_char) {
          action = _ed_keys[k].action;
          break;
        }

    if ((inp != SDLK_UNKNOWN) && (action == -1))
      for (k = 0; k < SIZE(_ed_keys); k++)
        if (_ed_keys[k].key == inp && _ed_keys[k].mod == keymod) {
          action = _ed_keys[k].action;
          break;
        }

    if ((action != -1) || (inp_char != 0) || (inp != SDLK_UNKNOWN))
      debugprintf(3, _("key: %s, char: %c, action: %i\n"), SDL_GetKeyName(inp), inp_char, action);

    if (action != -1) {

      switch (action) {
      case EDACT_QUIT:
        if (changed) ende = really_quit(row, col);
        else ende = true;
        break;
      case EDACT_MOVEUP:
        if (row + 1 < lev_towerrows()) {
            row++;
            cursor_moved = true;
        }
        break;
      case EDACT_MOVEDOWN:
        if (row > 0) {
            row--;
            cursor_moved = true;
        }
        break;
      case EDACT_MOVELEFT:
        col++;
        cursor_moved = true;
        break;
      case EDACT_MOVERIGHT:
        col--;
        cursor_moved = true;
        break;
      case EDACT_ROT180:
        col += 8;
        cursor_moved = true;
        break;
      case EDACT_INSROW:
        lev_insertrow(row);
        changed = true;
        break;
      case EDACT_DELROW:
        lev_deleterow(row);
        changed = true;
        break;
      case EDACT_PASTEROW:
        le_tower_paste(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_CUTROW:
        le_tower_cut(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_PUTSPACE:
        lev_putspace(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_PUTSTEP:
        lev_putstep(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_PUTVANISHER:
        lev_putvanishingstep(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_PUTSLIDERLEFT:
        lev_putslidingstep_left(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_PUTSLIDERRIGHT:
        lev_putslidingstep_right(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_PUTDOOR:
        lev_putdoor(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_PUTGOAL:
        lev_puttarget(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_CHECKTOWER:
        edit_checktower(row, col);
        break;
      case EDACT_PUTROBOT1:
        lev_putrobot1(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_PUTROBOT2:
        lev_putrobot2(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_PUTROBOT3:
        lev_putrobot3(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_PUTROBOT4:
        lev_putrobot4(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_PUTROBOT5:
        lev_putrobot5(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_PUTROBOT6:
        lev_putrobot6(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_PUTROBOT7:
        lev_putrobot7(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_PUTLIFTTOP:
        lev_puttopstation(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_PUTLIFTMID:
        lev_putmiddlestation(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_PUTLIFT:
        lev_putelevator(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_PUTSTICK:
        lev_putstick(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_PUTBOX:
        lev_putbox(row, -col & 0xf);
        changed = true;
        break;
      case EDACT_LOADTOWER:
        if (changed)
          if (!really_load(row, col))
            break;
        bg_text = _("Load tower:");
        bg_darken = true;
        key_wait_for_none(editor_background_proc);
        {
          char name[TOWERNAMELEN+1];
          strncpy(name, config.editor_towername(), TOWERNAMELEN);
          name[TOWERNAMELEN] = 0;
          while (!men_input(name, TOWERNAMELEN)) ;
          config.editor_towername(name);
        }
        bg_text = NULL;
        if ((strlen(config.editor_towername()) > 0) &&
            lev_loadtower(config.editor_towername())) {
            scr_settowercolor(lev_towercol_red(),
                               lev_towercol_green(),
                               lev_towercol_blue());
            changed = false;
        }
        if (row >= lev_towerrows()) row = lev_towerrows()-1;
        break;
      case EDACT_SAVETOWER:
        bg_text = _("Save tower:");
        bg_darken = true;
        key_wait_for_none(editor_background_proc);
        {
          char name[TOWERNAMELEN+1];
          strncpy(name, config.editor_towername(), TOWERNAMELEN);
          name[TOWERNAMELEN] = 0;
          while (!men_input(name, TOWERNAMELEN)) ;
          config.editor_towername(name);
        }
        bg_text = NULL;
        lev_savetower(config.editor_towername());
        changed = false;
        break;

      case EDACT_REC_DEMO:
        {
            Uint8 dummy1;
            Uint16 dummy2;
            unsigned char *p;
            int demolen = -1;
            Uint16 *demobuf = NULL;
            int speed = dcl_update_speed(config.game_speed());
            lev_set_towerdemo(0, NULL);
            lev_save(p);
            gam_newgame();
            rob_initialize();
            snb_init();
            ttsounds::instance()->startsound(SND_WATER);
            gam_towergame(dummy1, dummy2, demolen, &demobuf);
            ttsounds::instance()->stopsound(SND_WATER);
            lev_restore(p);
            lev_set_towerdemo(demolen, demobuf);
            key_readkey();
            set_men_bgproc(editor_background_proc);
            dcl_update_speed(speed);
        }
        break;
      case EDACT_PLAY_DEMO:
        {
            int demolen = 0;
            Uint16 *demobuf = NULL;
            lev_get_towerdemo(demolen, demobuf);
            if (demolen > 0) {
                Uint8 dummy1;
                Uint16 dummy2;
                unsigned char *p;
                int speed = dcl_update_speed(config.game_speed());
                lev_save(p);
                gam_newgame();
                rob_initialize();
                snb_init();
                ttsounds::instance()->startsound(SND_WATER);
                gam_towergame(dummy1, dummy2, demolen, &demobuf);
                ttsounds::instance()->stopsound(SND_WATER);
                lev_restore(p);
                key_readkey();
                set_men_bgproc(editor_background_proc);
                dcl_update_speed(speed);
            } else {
                bg_darken = true;
                men_info(_("No recorded demo"), 150, 2);
            }
        }
        break;
      case EDACT_TESTTOWER:
        {
          Uint8 dummy1;
          Uint16 dummy2;
          int dummy3 = -2;
          int speed = dcl_update_speed(config.game_speed());
          Uint16 *dummybuf = NULL;
          unsigned char *p;
          lev_save(p);
          gam_newgame();
          rob_initialize();
          snb_init();
          ttsounds::instance()->startsound(SND_WATER);
          gam_towergame(dummy1, dummy2, dummy3, &dummybuf);
          ttsounds::instance()->stopsound(SND_WATER);
          lev_restore(p);
          key_readkey();
          set_men_bgproc(editor_background_proc);
          dcl_update_speed(speed);
        }
        break;
      case EDACT_SETTOWERCOLOR:
        changed |= edit_towercolor(row, col);
        break;
      case EDACT_INCTIME:
        if (tstep <= 0) tstep = 1;
        lev_set_towertime(lev_towertime() + tstep);
        if (tstep < 10) tstep++;
        changed = true;
        break;
      case EDACT_DECTIME:
        if (tstep >= 0) tstep = -1;
        lev_set_towertime(lev_towertime() + tstep);
        if (tstep > -10) tstep--;
        changed = true;
        break;
      case EDACT_SETTIME:
        {
          char buf[64];

          snprintf(buf, 64, "%d", lev_towertime());

          bg_text = _("Enter tower time:");
          bg_darken = true;
          key_wait_for_none(editor_background_proc);
          while (!men_input((char *)buf, 15, -1, -1, "0123456789")) ;
          bg_text = NULL;

          lev_set_towertime(atoi(buf));
        }
        break;
      case EDACT_ADJHEIGHT:
        {
            char buf[64];
            int i;

            snprintf(buf, 64, "0");

            bg_text = _("Adjust tower height:");
            bg_darken = true;
            key_wait_for_none(editor_background_proc);
            while (!men_input((char *)buf, 15, -1, -1, "-+0123456789")) ;
            bg_text = NULL;

            i = atoi(buf);
            if ((i > 0) && (buf[0] == '+')) {
                while (i-- > 0) lev_insertrow(row);
            } else
            if (i < 0) {
                i = abs(i);
                while (i-- > 0) lev_deleterow(row);
            } else
            if (i>0) {
               if (i < lev_towerrows()) {
                    while ((i > 0) && (i < lev_towerrows())) {
                        lev_deleterow(row);
                        if ((row > 0) && (row >= lev_towerrows())) row--;
                    }
                } else {
                    while ((i < 255) && (i > lev_towerrows())) {
                        lev_insertrow(row);
                    }
                }
            }
        }
        break;
      case EDACT_CREATEMISSION:
        createMission();
        break;
      case EDACT_MOVEPAGEUP:
        if (row + pagesize < lev_towerrows())
          row += pagesize;
        else
          row = lev_towerrows() - 1;
        break;
      case EDACT_MOVEPAGEDOWN:
        if (row > pagesize)
          row -= pagesize;
        else
          row = 0;
        break;
      case EDACT_GOTOSTART:
        col = 0;
        row = 1;
        break;
      case EDACT_GOTOEND:
        {
            int trow = row;
            int tcol = col;
            int coladj = 0;
            int rowadj = 0;
            bool ende = false;
            bool skip = lev_is_targetdoor(trow, -tcol & 0xf);

            do {
                tcol++;
                coladj++;

                if (coladj >= 16) {
                    tcol = col;
                    trow = (trow + 1) % lev_towerrows();
                    coladj = 0;
                    rowadj++;
                }

                if (rowadj >= lev_towerrows()) ende = true;
                else if (!skip && lev_is_targetdoor(trow, -tcol & 0xf) &&
                         lev_is_door_upperend(trow, -tcol & 0xf)) ende = true;
                skip = false;
            } while (!ende);

            if (rowadj < lev_towerrows()) {
                row = trow;
                col = tcol;
            }
        }
        break;
      case EDACT_NAMETOWER:
        bg_text = _("Name the tower:");
        bg_darken = true;
        key_wait_for_none(editor_background_proc);
        while (!men_input(lev_towername(), TOWERNAMELEN)) ;
        bg_text = NULL;
        changed = true;
        break;
      case EDACT_SHOWKEYHELP:
        le_showkeyhelp(row, col);
        break;
      case EDACT_TOGGLEROBOT:
        lev_set_robotnr((lev_robotnr() + 1) % scr_numrobots());
        break;
      default: break;
      }
    }
  }
}
