/// @file lcd_draw.h
/// @brief LCD drawing utilities

#ifndef __LCD_DRAW_H
#define __LCD_DRAW_H

#include <pic32mx.h>
#include <stdint.h>
#include "math.h"
#include "drivers/ili9341/lcd_defines.h"
#include "drivers/ili9341/lcd_comms.h"
#include "drivers/ili9341/lcd_utils.h"

typedef struct {
	uint16_t x;
	uint16_t y;
} Point;

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

/// @brief Draws a horizontal line
/// @param x0 Line start X coordinatae
/// @param x1 Line end X coordinate
/// @param y Line Y coordinate
/// @param color Line color in 5-6-5 RGB format
/// @param thickness Line thickness in pixels
void lcd_draw_line_h(
	uint16_t x0,
	uint16_t x1,
	uint16_t y,
	uint16_t color,
	uint16_t thickness
);

/// @brief Draws a vertical line
/// @param x Line X coordinate
/// @param y0 Line start Y coordinate
/// @param y1 Line end Y coordinate
/// @param color Line color in 5-6-5 RGB format
/// @param thickness Line thickness in pixels
void lcd_draw_line_v(
	uint16_t x,
	uint16_t y0,
	uint16_t y1,
	uint16_t color,
	uint16_t thickness
);

/// @brief Draws a square with a side length of thickness
/// @param Point Center point
/// @param color Color in 5-6-5 RGB format
/// @param thickness Square side length
void lcd_draw_pixel(
	Point p,
	uint16_t color,
	uint16_t thickness
);

/// @brief Draws a rectangular outline
/// @param p0 Top-left point
/// @param p1 Bottom-right point
/// @param color Color in 5-6-5 RGB format
/// @param thickness Outline thickness
void lcd_draw_rect(
	Point p0,
	Point p1,
	uint16_t color,
	uint16_t thickness
);

/// @brief Draws a filled rectangle
/// @param p0 Top-left point
/// @param p1 Bottom-right point
/// @param color Color in 5-6-5 RGB format
void lcd_draw_rect_filled(
	Point p0,
	Point p1,
	uint16_t color
);

/// @brief Draws a generic line
/// @param p0 Line start point
/// @param p1 Line end point
/// @param color Line color in 5-6-5 RGB format
/// @param thickness Line thickness in pixels
void lcd_draw_line(
	Point p0,
	Point p1,
	uint16_t color,
	uint16_t thickness
);

/// @brief Draws a circular outline
/// @param p Center point
/// @param r Radius
/// @param color Color in 5-6-5 RGB format
/// @param thickness Outline thickness in pixels
void lcd_draw_circle(
	Point p,
	uint16_t r,
	uint16_t color,
	uint16_t thickness
);

/// @brief Draws a filled circle
/// @param p Center point
/// @param r Radius
/// @param color Color in 5-6-5 RGB format
void lcd_draw_circle_filled(
	Point p,
	uint16_t r,
	uint16_t color
);

/// @brief Draws a quadratic bezier curve
/// @param p0 Start point
/// @param p1 Control point
/// @param p2 End point
/// @param color Color in 5-6-5 RGB format
/// @param thickness Line thickness in pixels
void lcd_draw_bezier_quadratic(
	Point p0,
	Point p1,
	Point p2,
	uint16_t color,
	uint16_t thickness
);

#endif