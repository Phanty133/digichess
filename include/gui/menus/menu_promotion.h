#ifndef __MENU_TEST_H
#define __MENU_TEST_h

#include <stdint.h>
#include "gui/gui.h"
#include "drivers/ili9341/lcd_draw.h"

void menu_promotion_setup();
void menu_promotion_draw();
uint8_t menu_promotion_update();

#endif