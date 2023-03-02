#ifndef __MENU_SPLASH_H
#define __MENU_SPLASH_H

#include "drivers/ili9341/lcd_draw.h"
#include "files/images/logo.bmp.h"
#include "delay.h"
#include "gui/gui.h"

void menu_splash_setup();
void menu_splash_draw();
uint8_t menu_splash_update();

#endif