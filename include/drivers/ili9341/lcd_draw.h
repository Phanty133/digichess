/// @file lcd_draw.h
/// @brief LCD drawing utilities

#ifndef __LCD_DRAW_H
#define __LCD_DRAW_H

#include <pic32mx.h>
#include <stdint.h>
#include "drivers/ili9341/lcd_defines.h"
#include "drivers/ili9341/lcd_comms.h"
#include "drivers/ili9341/lcd_utils.h"

/// @brief Sets the addresses that get written to when drawing
/// @param x0 Start X address
/// @param y0 Start Y address
/// @param w Window width
/// @param h Window height
void lcd_set_address_window(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h);

/// @brief Fill a section of the screen starting at the address window's x0 and y0. 
/// @param color 16 bit 5-6-5 RGB color
/// @param w Width of the address window
/// @param h Height of the address window
void lcd_fill(uint16_t color, uint16_t w, uint16_t h);

/// @brief Shows coordinate calibration marks. Corners: red (0,0); green (w, 0); blue (0, h); black (w, h)
/// @param direction The direction of the display set in MADCTL. 0 - horizontal; 1 - vertical
void lcd_calibrate(uint8_t direction);

#endif