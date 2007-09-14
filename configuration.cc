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

#include "configuration.h"
#include <string.h>
#include <stdlib.h>
#include "keyb.h"

static bool
str2bool(char *s) {
  if (s) {
    if (!strcmp("yes", s) || !strcmp("true", s)) return true;
    else return (atoi(s) != 0);
  }
  return false;
}

void configuration::parse(FILE * in) {
  char line[201], param[201];

  while (!feof(in)) {
    if (fscanf(in, "%200s%*[\t ]%200s\n", line, param) == 2) {

      config_data *t = first_data;

      while (t) {
        if (strstr(line, t->cnf_name)) {
          switch (t->cnf_typ) {
          case CT_BOOL:
            *(bool *)t->cnf_var = str2bool(param);
            break;
          case CT_STRING:
            if (strlen(param) > 1) {
              param[strlen(param)-1] = '\0';
              strncpy((char *)t->cnf_var, param+1, t->maxlen);
            }
            break;
          case CT_INT:
            *(int *)t->cnf_var = atoi(param);
            break;
          case CT_KEY:
            if (atoi(param) > 0)
              key_redefine((ttkey)t->maxlen, (SDLKey)atoi(param));
            break;
          default: assert_msg(0, "Unknown config data type.");
          }
          break;
        }
        t = t->next;
      }
    }
  }
}

void configuration::register_entry(char *cnf_name, cnf_type  cnf_typ, void *cnf_var, long maxlen) {
  config_data *t = new config_data;

  t->next = first_data;
  first_data = t;

  t->cnf_name = cnf_name;
  t->cnf_typ = cnf_typ;
  t->cnf_var = cnf_var;
  t->maxlen = maxlen;
}

#define CNF_BOOL(a,b) register_entry(a, CT_BOOL, b, 0)
#define CNF_CHAR(a,b,c) register_entry(a, CT_STRING, b, c)
#define CNF_INT(a,b) register_entry(a, CT_INT, b, 0)
#define CNF_KEY(a,b) register_entry(a, CT_KEY, NULL, b)

configuration::configuration(FILE *glob, FILE *local) {

  i_fullscreen = false;
  i_nosound  = false;
  i_use_water = true;
  i_use_alpha_sprites = false;
  i_use_alpha_layers = false;
  i_use_alpha_font = false;
  i_use_alpha_darkening = false;
  i_use_full_scroller = true;
  i_waves_type = waves_nonreflecting;
  i_status_top = true;  /* is status line top or bottom of screen? */
  i_editor_towerpagesize = -1;
  i_editor_towerstarthei = -5;
  i_curr_password[0] = 0;
  i_start_lives = 3;
  i_editor_towername[0] = 0;
  i_debug_level = 0;
  i_game_speed = DEFAULT_GAME_SPEED;
  i_nobonus = false;

  first_data = 0;
  need_save = (local == 0);

  CNF_BOOL( "fullscreen",          &i_fullscreen );
  CNF_BOOL( "nosound",             &i_nosound );
  CNF_BOOL( "nomusic",             &i_nomusic );
  CNF_CHAR( "editor_towername",    &i_editor_towername, TOWERNAMELEN );
  CNF_BOOL( "use_alpha_sprites",   &i_use_alpha_sprites );
  CNF_BOOL( "use_alpha_font",      &i_use_alpha_font );
  CNF_BOOL( "use_alpha_layers",    &i_use_alpha_layers );
  CNF_BOOL( "use_alpha_darkening", &i_use_alpha_darkening );
  CNF_BOOL( "use_full_scroller",   &i_use_full_scroller );
  CNF_BOOL( "status_top",          &i_status_top );
  CNF_INT(  "editor_pagesize",     &i_editor_towerpagesize );
  CNF_INT(  "editor_towerstarthei",&i_editor_towerstarthei );
  CNF_INT(  "waves_type",          &i_waves_type );
  CNF_KEY(  "key_fire",             fire_key );
  CNF_KEY(  "key_up",               up_key );
  CNF_KEY(  "key_down",             down_key );
  CNF_KEY(  "key_left",             left_key );
  CNF_KEY(  "key_right",            right_key );
  CNF_CHAR( "password",            &i_curr_password, PASSWORD_LEN );
  CNF_INT(  "start_lives",         &i_start_lives );
  CNF_INT(  "game_speed",          &i_game_speed);
  CNF_BOOL( "nobonus",             &i_nobonus);

  if (glob) {
    parse(glob);
    fclose(glob);
  }

  f = local;
  if (f) parse(f);

  if (i_start_lives < 1) i_start_lives = 1;
  else if (i_start_lives > 3) i_start_lives = 3;

  if (i_game_speed < 0) i_game_speed = 0;
  else if (i_game_speed > MAX_GAME_SPEED) i_game_speed = MAX_GAME_SPEED;
}

configuration::~configuration(void) {

  if (need_save) {

    if (!f) f = create_local_config_file(".toppler.rc");

    fseek(f, 0, SEEK_SET);

    config_data *t = first_data;

    while(t) {
      fprintf(f, "%s: ", t->cnf_name);

      switch (t->cnf_typ) {
      case CT_BOOL:
        fprintf(f, "%s", (*(bool *)t->cnf_var)?("yes"):("no"));
        break;
      case CT_STRING:
        fprintf(f, "\"%s\"", (char *)(t->cnf_var));
        break;
      case CT_INT:
        fprintf(f, "%i", *(int *)t->cnf_var);
        break;
      case CT_KEY:
        fprintf(f, "%i", (int)key_conv2sdlkey((ttkey)t->maxlen, true));
        break;
      default: assert_msg(0, "Unknown config data type.");
      }

      fprintf(f, "\n");

      t = t->next;
    }
  }
  fclose(f);

  config_data *t = first_data;

  while (t) {
    t = t->next;
    delete first_data;
    first_data = t;
  }
}

void configuration::curr_password(char pwd[PASSWORD_LEN+1]) {
  need_save = true;
  strncpy(i_curr_password, pwd, PASSWORD_LEN);
  i_curr_password[PASSWORD_LEN] = 0;
}

void configuration::editor_towername(char name[TOWERNAMELEN+1]) {
  need_save = true;
  strncpy(i_editor_towername, name, TOWERNAMELEN);
  i_editor_towername[TOWERNAMELEN] = 0;
}

configuration config(open_local_config_file(".toppler.rc"), open_local_config_file(".toppler.rc"));
