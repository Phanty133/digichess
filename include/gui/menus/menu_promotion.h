#ifndef __MENU_TEST_H
#define __MENU_TEST_h

#include <stdint.h>
#include "gui/gui.h"
#include "drivers/ili9341/lcd_draw.h"
#include "gui/menu_defines.h"
#include "files/images/queen.bmp.h"
#include "files/images/knight.bmp.h"
#include "files/images/rook.bmp.h"
#include "files/images/bishop.bmp.h"
#include "uart.h"
#include "game_logic.h"

void menu_promotion_setup();
void menu_promotion_draw();
uint8_t menu_promotion_update();

#endif