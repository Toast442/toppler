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

#include "menusys.h"

#include "string.h"
#include "screen.h"
#include "sprites.h"
#include "configuration.h"
#include "keyb.h"

#include <ctype.h>

static menubg_callback_proc menu_background_proc = NULL;

void set_men_bgproc(menubg_callback_proc proc) {
  menu_background_proc = proc;
}

_menusystem *new_menu_system(const char *title, menuopt_callback_proc pr, int molen, int ystart)
{
  _menusystem *ms = new _menusystem;

  if (ms) {
    memset(ms->title, '\0', MENUTITLELEN);
    if (title) {
      memcpy(ms->title, title, (strlen(title) < MENUTITLELEN) ? strlen(title) + 1 : (MENUTITLELEN-1));
    }

    ms->numoptions = 0;
    ms->moption = NULL;
    ms->mstate = 0;
    ms->mproc = pr;
    ms->maxoptlen = molen;
    ms->exitmenu = false;
    ms->wraparound = false;
    ms->curr_mtime = ms->hilited = 0;
    ms->ystart = ystart;
    ms->key = SDLK_UNKNOWN;
    ms->mtime = ms->yhilitpos = ms->opt_steal_control = -1;
    ms->timeproc = NULL;
  }

  return ms;
}

_menusystem *
add_menu_option(_menusystem *ms,
                const char *name,
                menuopt_callback_proc pr,
                SDL_Keycode quickkey,
                menuoptflags flags,
                int state) {
  _menuoption *tmp;
  int olen = 0;

  if (!ms) return ms;

  tmp = new _menuoption[ms->numoptions+1];

  if (!tmp) return ms;

  memcpy(tmp, ms->moption, sizeof(_menuoption)*ms->numoptions);
  delete [] ms->moption;

  memset(tmp[ms->numoptions].oname, '\0', MENUOPTIONLEN);

  /* if no name, but has callback proc, query name from it. */
  if (!name && pr) name = (*pr) (NULL);

  if (name) {
    olen = (int)strlen(name);
    memcpy(tmp[ms->numoptions].oname, name, (olen < MENUOPTIONLEN) ? olen + 1 : (MENUOPTIONLEN-1));
  }

  tmp[ms->numoptions].oproc = pr;
  tmp[ms->numoptions].ostate = state;
  tmp[ms->numoptions].oflags = flags;
  tmp[ms->numoptions].quickkey = quickkey;

  ms->moption = tmp;
  ms->numoptions++;
  if (name)
    olen = scr_textlength(name);
  else
    olen = 0;
  if (ms->maxoptlen < olen) ms->maxoptlen = olen;

  return ms;
}

void
free_menu_system(_menusystem *ms)
{
  if (!ms) return;

  delete [] ms->moption;
  ms->numoptions = 0;
  ms->mstate = 0;
  ms->mproc = NULL;
  delete ms;
}

static void draw_background(_menusystem *ms)
{
  while (!ms->mproc && ms->parent) ms = ms->parent;

  if (ms->mproc)
    (*ms->mproc)(ms);
  else if (menu_background_proc)
    (*menu_background_proc) ();
}


void
draw_menu_system(_menusystem *ms, Uint16 dx, Uint16 dy)
{
  static int color_r = 0, color_g = 20, color_b = 70;

  if (!ms) return;

  int y, offs = 0, len, realy, minx, miny, maxx, maxy, scrlen,
    newhilite = -1, yz, titlehei;
  bool has_title = (ms->title[0]) && (strlen(ms->title) != 0);

  if (ms->wraparound) {
    if (ms->hilited < 0)
      ms->hilited = ms->numoptions - 1;
    else if (ms->hilited >= ms->numoptions)
      ms->hilited = 0;
  } else {
    if (ms->hilited < 0)
      ms->hilited = 0;
    else if (ms->hilited >= ms->numoptions)
      ms->hilited = ms->numoptions - 1;
  }

  draw_background(ms);

  titlehei = 0;

  if (has_title) {
    int pos = 0;
    int start = 0;
    int len = (int)strlen(ms->title);

    while (pos <= len) {

      if ((ms->title[pos] == '\n') || (ms->title[pos] == 0)) {

        bool end = ms->title[pos] == 0;

        ms->title[pos] = 0;
        scr_writetext_center(ms->ystart + titlehei * FONTHEI, ms->title + start);
        titlehei ++;

        if (!end)
          ms->title[pos] = '\n';

        start = pos + 1;
      }
      pos++;
    }

    titlehei++;
  }



  /* TODO: Calculate offs from ms->hilited.
   * TODO: Put slider if more options than fits in screen.
   */

  yz = ms->ystart + (titlehei) * FONTHEI;

  for (y = 0; (yz+y+1 < SCREENHEI) && (y+offs < ms->numoptions); y++) {
    realy = yz + y * FONTHEI;
    len = (int)strlen(ms->moption[y+offs].oname);
    scrlen = scr_textlength(ms->moption[y+offs].oname, len);
    minx = (SCREENWID - scrlen) / 2;
    miny = realy;
    maxx = (SCREENWID + scrlen) / 2;
    maxy = realy + FONTHEI;
    if (len) {
      if (dx >= minx && dx <= maxx && dy >= miny && dy <= maxy) {
        newhilite = y + offs;
        ms->curr_mtime = 0;
      }
      if (y + offs == ms->hilited) {
        if (ms->yhilitpos == -1) {
          ms->yhilitpos = miny;
        } else {
          if (ms->yhilitpos < miny) {
            ms->yhilitpos += ((miny - ms->yhilitpos + 3) / 4)+1;
            if (ms->yhilitpos > miny) ms->yhilitpos = miny;
          } else if (ms->yhilitpos > miny) {
            ms->yhilitpos -= ((ms->yhilitpos - miny + 3) / 4)+1;
            if (ms->yhilitpos < miny) ms->yhilitpos = miny;
          }
        }
        scr_putbar((SCREENWID - ms->maxoptlen - 8) / 2, ms->yhilitpos - 3,
                   ms->maxoptlen + 8, FONTHEI + 3,
                   color_r, color_g, color_b, (config.use_alpha_darkening())?128:255);
      }
    }
  }

  maxy = y;

  for (y = 0; y < maxy; y++) {
    if (strlen(ms->moption[y+offs].oname)) {
      miny = ms->ystart + (y + titlehei)*FONTHEI;
      if ((ms->moption[y+offs].oflags & MOF_LEFT))
        scr_writetext((SCREENWID - ms->maxoptlen) / 2 + 4, miny,
                      ms->moption[y+offs].oname);
      else
        if ((ms->moption[y+offs].oflags & MOF_RIGHT))
          scr_writetext((SCREENWID + ms->maxoptlen) / 2 - 4
                        - scr_textlength(ms->moption[y+offs].oname), miny,
                        ms->moption[y+offs].oname);
        else
          scr_writetext_center(miny, ms->moption[y+offs].oname);
    }
  }

  if (newhilite >= 0) ms->hilited = newhilite;

  scr_color_ramp(&color_r, &color_g, &color_b);

  scr_swap();
  dcl_wait();
}

void
menu_system_caller(_menusystem *ms)
{
  const char *tmpbuf = (*ms->moption[ms->hilited].oproc) (ms);
  if (tmpbuf) {
    int olen = (int) strlen(tmpbuf);
    memset(ms->moption[ms->hilited].oname, '\0', MENUOPTIONLEN);
    memcpy(ms->moption[ms->hilited].oname, tmpbuf,
           (olen < MENUOPTIONLEN) ? olen + 1 : (MENUOPTIONLEN-1));
    olen = scr_textlength(tmpbuf);
    if (ms->maxoptlen < olen) ms->maxoptlen = olen;
    ms->key = SDLK_UNKNOWN;
  }
}


_menusystem *
run_menu_system(_menusystem *ms, _menusystem *parent)
{
  Uint16 x,y;
  ttkey bttn;
  bool stolen = false;

  if (!ms) return ms;

  ms->parent = parent;

  /* find the first option with text */
  if (!strlen(ms->moption[ms->hilited].oname))
    do {
      ms->hilited = (ms->hilited + 1) % ms->numoptions;
    } while (!strlen(ms->moption[ms->hilited].oname));

  (void)key_sdlkey();

  do {

    stolen = false;
    bttn = no_key;
    x = y = 0;

    ms->key = SDLK_UNKNOWN;

    if ((ms->curr_mtime++ >= ms->mtime) && ms->timeproc) {
      (void) (*ms->timeproc) (ms);
      ms->curr_mtime = 0;
    }

    if ((ms->opt_steal_control >= 0) &&
        (ms->opt_steal_control < ms->numoptions) &&
        ms->moption[ms->opt_steal_control].oproc) {
      ms->key = key_sdlkey();
      ms->hilited = ms->opt_steal_control;
      stolen = true;
    } else {
      if (!config.fullscreen() && !key_mouse(&x, &y, &bttn) && bttn)
        ms->key = key_conv2sdlkey(bttn, false);
      else ms->key = key_sdlkey();
    }

    draw_menu_system(ms, x, y);

    if ((ms->key != SDLK_UNKNOWN) || stolen) {

      if (!stolen) {
        ms->curr_mtime = 0;
        for (int tmpz = 0; tmpz < ms->numoptions; tmpz++)
          if (ms->moption[tmpz].quickkey == ms->key) {
            ms->hilited = tmpz;
            ms->key = SDLK_UNKNOWN;
            break;
          }
      }

      if ((((ms->moption[ms->hilited].oflags & MOF_PASSKEYS)) || stolen) &&
          (ms->moption[ms->hilited].oproc) && ((ms->key != SDLK_UNKNOWN) || stolen)) {
        menu_system_caller(ms);
      }
      if (!stolen) {
        switch (key_sdlkey2conv(ms->key, false)) {
        case down_key:
          if (ms->wraparound) {
            do {
              ms->hilited = (ms->hilited + 1) % ms->numoptions;
            } while (!strlen(ms->moption[ms->hilited].oname));
          } else {
            if (ms->hilited < ms->numoptions) {
              ms->hilited++;
              if (!strlen(ms->moption[ms->hilited].oname)) ms->hilited++;
            }
          }
          break;
        case up_key:
          if (ms->wraparound) {
            do {
              ms->hilited--;
              if (ms->hilited < 0) ms->hilited = ms->numoptions - 1;
            } while (!strlen(ms->moption[ms->hilited].oname));
          } else {
            int tmpz = ms->hilited;
            if (ms->hilited > 0) {
              do {
                if (ms->hilited < 0) {
                  ms->hilited = tmpz;
                  break;
                }
                ms->hilited--;
              } while (!strlen(ms->moption[ms->hilited].oname));
            }
          }
          break;
        case fire_key:
          if ((ms->hilited >= 0) && (ms->hilited < ms->numoptions) &&
              ms->moption[ms->hilited].oproc) {
            const char *tmpbuf = (*ms->moption[ms->hilited].oproc) (ms);
            if (tmpbuf) {
              int olen = (int)strlen(tmpbuf);
              memset(ms->moption[ms->hilited].oname, '\0', MENUOPTIONLEN);
              memcpy(ms->moption[ms->hilited].oname, tmpbuf,
                     (olen < MENUOPTIONLEN) ? olen + 1 : (MENUOPTIONLEN-1));
              olen = scr_textlength(tmpbuf);
              if (ms->maxoptlen < olen) ms->maxoptlen = olen;
            }
            break;
          }
        case break_key : ms->exitmenu = true; break;
        default:
          break;
        }
      }
    }
  } while (!ms->exitmenu);
  return ms;
}

void men_info(const char *s, long timeout, int fire) {
  bool ende = false;
  do {
    if (menu_background_proc) (*menu_background_proc) ();
    scr_writetext_center((SCREENHEI / 5), s);
    if (fire)
      scr_writetext_center((SCREENHEI / 5) + 2 * FONTHEI, (fire == 1) ? _("Press fire") : _("Press space"));
    scr_swap();
    dcl_wait();
    if (timeout > 0) timeout--;
    if (!timeout) ende = true;
    else if ((fire == 2) && (key_chartyped() == ' ')) ende = true;
    else if ((fire != 2) && key_keypressed(fire_key)) ende = true;
  } while (!ende);
  (void)key_sdlkey();
}

static int input_box_cursor_state = 0;

void
draw_input_box(int x, int y, int len, int cursor, char *txt)
{
  static int col_r = 0, col_g = 200, col_b = 120;
  int nlen = len, slen = len;
  int arrows = 0;

  if ((len+3)*FONTMAXWID > SCREENWID)
    nlen = (SCREENWID / FONTMAXWID) - 3;

  if (x < 0) x = (SCREENWID / 2) - nlen * (FONTMAXWID / 2);
  if (x < 0) x = 0;
  if (y < 0) y = (SCREENHEI / 2) - (FONTHEI / 2);

  scr_putbar(x, y, nlen * FONTMAXWID, FONTHEI, 0, 0, 0, (config.use_alpha_darkening())?128:255);

  if (scr_textlength(txt) >= nlen*FONTMAXWID) {
    while ((cursor >= 0) &&
           (scr_textlength(txt, cursor+(nlen/2)) >= (nlen)*FONTMAXWID)) {
      cursor--;
      txt++;
      arrows = 1;
    }
  }
  if (scr_textlength(txt) >= nlen*FONTMAXWID) {
    arrows |= 2;
    while ((slen > 0) && (scr_textlength(txt, slen) >= nlen*FONTMAXWID)) slen--;
  }

  scr_writetext(x+1,y, txt, slen);

  if ((input_box_cursor_state & 4) && (cursor >= 0))
    scr_putbar(x + scr_textlength(txt, cursor) + 1, y, FONTMINWID, FONTHEI,
               col_r, col_g, col_b, (config.use_alpha_darkening())?128:255);
  scr_putrect(x,y, nlen * FONTMAXWID, FONTHEI, col_r, col_g, col_b, 255);

  if ((arrows & 1)) scr_writetext(x-FONTMAXWID,y, "\x08"); //fontptrright
  if ((arrows & 2)) scr_writetext(x+(nlen*FONTMAXWID),y, "\x06"); //fontptrleft

  input_box_cursor_state++;

  scr_color_ramp(&col_r, &col_g, &col_b);
}

bool men_input(char *origs, int max_len, int xpos, int ypos, const char *allowed) {
  SDL_Keycode sdlinp;
  char inpc;
  ttkey inptt;
  static int pos = (int) strlen(origs);
  int ztmp;
  static char s[256];
  static bool copy_origs = true;
  bool restore_origs = false;
  bool ende = false;

  if ((strlen(origs) >= 256)) return true;

  if (copy_origs) {
    strcpy(s, origs);
    copy_origs = false;
    pos = (int)strlen(origs);
  }

  (void)key_readkey();

  if (menu_background_proc) (*menu_background_proc) ();

  draw_input_box(xpos,ypos, max_len, pos, s);
  scr_swap();
  dcl_wait();

  key_keydatas(sdlinp, inptt, inpc);

  switch (sdlinp) {
  case SDLK_RIGHT: if ((unsigned)pos < strlen(s)) pos++; break;
  case SDLK_LEFT: if (pos > 0) pos--; break;
  case SDLK_ESCAPE:if (strlen(s)) {
    s[0] = '\0';
    pos = 0;
    restore_origs = false;
  } else {
    restore_origs = true;
    ende = true;
  }
  break;
  case SDLK_RETURN: restore_origs = false; copy_origs = true; ende = true;
  break;
  case SDLK_DELETE:
    if (strlen(s) >= (unsigned)pos) {
      for (ztmp = pos; ztmp < max_len-1; ztmp++) s[ztmp] = s[ztmp+1];
      s[ztmp] = '\0';
    }
    break;
  case SDLK_BACKSPACE:
    if (pos > 0) {
      if (pos <= max_len) {
        for (ztmp = pos-1; ztmp < max_len-1; ztmp++) s[ztmp] = s[ztmp+1];
        s[ztmp] = '\0';
      }
      pos--;
    }
    break;
  default:
    if (pos >= max_len || (inpc < ' ')) break;
    if (allowed) {
      if (!strchr(allowed, inpc)) {
        if (strchr(allowed, toupper(inpc))) inpc = toupper(inpc);
        else
          if (strchr(allowed, tolower(inpc))) inpc = tolower(inpc);
          else break;
      }
    } else {
      if (inpc < ' ' || inpc > 'z') break;
    }
    if ((strlen(s) >= (unsigned)pos) &&
        (strlen(s) < (unsigned)max_len)) {
      for (ztmp = max_len-1; ztmp >= pos; ztmp--) s[ztmp+1] = s[ztmp];
      s[pos] = inpc;
      s[max_len] = '\0';
      pos++;
    }
    break;
  }
  if (ende) {
    if (!restore_origs) strcpy(origs, s);
    s[0] = 0;
    copy_origs = true;
  } else {
    copy_origs = false;
  }
  return ende;
}

_menusystem *
set_menu_system_timeproc(_menusystem *ms, long t, menuopt_callback_proc pr)
{
  if (!ms) return ms;

  ms->timeproc = pr;
  ms->mtime = t;

  return ms;
}

static const char *
men_yn_option_yes(_menusystem *ms)
{
  if (ms) {
    ms->mstate = 1;
    ms->exitmenu = true;
    return NULL;
  } else return _("Yes");
}

static const char *
men_yn_option_no(_menusystem *ms)
{
  if (ms) {
    ms->mstate = 0;
    ms->exitmenu = true;
    return NULL;
  } else return _("No");
}

unsigned char men_yn(const char *s, bool defchoice, menuopt_callback_proc pr) {
  _menusystem *ms = new_menu_system(s, pr, 0, SCREENHEI / 5);

  bool doquit = false;

  if (!ms) return defchoice;

  ms = add_menu_option(ms, NULL, men_yn_option_no, SDLK_n);
  ms = add_menu_option(ms, NULL, men_yn_option_yes, SDLK_y);

  ms->mstate = defchoice ? 1 : 0;

  ms = run_menu_system(ms, 0);

  doquit = (ms->mstate != 0);

  free_menu_system(ms);

  return ((doquit == 0) ? 0 : 1);
}

