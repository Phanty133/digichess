#ifndef __MENU_VICTORY_H
#define __MENU_VICTORY_h

#include "drivers/ili9341/lcd_draw.h"
#include "files/fonts/ComicSansMS.ttf.h"
#include "gui/menu_defines.h"
#include "gui/gui.h"
#include "reset.h"

void menu_victory_setup();
void menu_victory_draw();
uint8_t menu_victory_update();

#endif