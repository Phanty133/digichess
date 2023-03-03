#ifndef __MENU_MODE_H
#define __MENU_MODE_H

#include "drivers/ili9341/lcd_draw.h"
#include "files/fonts/ComicSansMS.ttf.h"
#include "gui/menu_defines.h"
#include "gui/gui.h"
#include "game_logic.h"

void menu_mode_setup();
void menu_mode_draw();
uint8_t menu_mode_update();

#endif