#ifndef __LCD_DRAW_H
#define __LCD_DRAW_H

#include <pic32mx.h>
#include <stdint.h>
#include "drivers/ili9341/lcd_defines.h"
#include "drivers/ili9341/lcd_comms.h"

void lcd_set_address_window(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h);
void lcd_fill(uint16_t color, uint16_t w, uint16_t h);

#endif