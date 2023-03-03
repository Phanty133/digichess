#ifndef __MENU_GAME_H
#define __MENU_GAME_H

#include "drivers/ili9341/lcd_draw.h"
#include "files/fonts/ComicSansMS.ttf.h"
#include "gui/menu_defines.h"
#include "gui/gui.h"

void menu_game_setup();
void menu_game_draw();
uint8_t menu_game_update();
void menu_game_change_player();

#endif