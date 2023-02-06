#include "drivers/ili9341/lcd_draw.h"

#include "uart.h"

void lcd_set_address_window(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h) {
	uint16_t x1 = (x0 + w - 1);
	uint16_t y1 = (y0 + h - 1);

	if (x1 >= ILI9341_TFTWIDTH) x1 = ILI9341_TFTWIDTH - 1;
	if (y1 >= ILI9341_TFTHEIGHT) y1 = ILI9341_TFTHEIGHT - 1;

	uint8_t casetData[] = {
		x0 >> 8,
		x0,
		x1 >> 8,
		x1
	};

	uint8_t pasetData[] = {
		y0 >> 8,
		y0,
		y1 >> 8,
		y1
	};

	lcd_write_register(ILI9341_CASET, casetData, 4);
	lcd_write_register(ILI9341_PASET, pasetData, 4);
}

void lcd_fill(uint16_t color, uint16_t w, uint16_t h) {
	lcd_write_command(ILI9341_RAMWR);
	LATBSET = __LCD_DC_MASK;

	uint8_t col_msb = color >> 8;
	uint8_t col_lsb = color;

	for (int i = 0; i < w * h; i++) {
		lcd_set_bus_data(col_msb);
		lcd_write_strobe();

		lcd_set_bus_data(col_lsb);
		lcd_write_strobe();
	}

	lcd_write_command(0x00); // Terminate the fill
}

void lcd_calibrate(uint8_t direction) {
	uint16_t w, h;

	if (direction == 0) {
		w = ILI9341_TFTHEIGHT;
		h = ILI9341_TFTWIDTH;
	} else {
		h = ILI9341_TFTHEIGHT;
		w = ILI9341_TFTWIDTH;
	}

	uint16_t size = 32;

	// Fill screen with white
	lcd_set_address_window(0, 0, 240, 320);
	lcd_fill(rgb_24b_to_16b(0xFFFFFF), 240, 320);

	// Corner top left
	lcd_set_address_window(0, 0, size, size);
	lcd_fill(rgb_24b_to_16b(0xFF0000), size, size);

	// Corner top right
	lcd_set_address_window(w - size, 0, size, size);
	lcd_fill(rgb_24b_to_16b(0x00FF00), size, size);

	// Corner bottom left
	lcd_set_address_window(0, h - size, size, size);
	lcd_fill(rgb_24b_to_16b(0x0000FF), size, size);

	// Corner bottom right
	lcd_set_address_window(w - size, h - size, size, size);
	lcd_fill(rgb_24b_to_16b(0x000000), size, size);
}

void lcd_draw_line_h(
	uint16_t x0,
	uint16_t x1,
	uint16_t y,
	uint16_t color,
	uint16_t thickness
) {
	uint16_t halfThickness = thickness >> 1;
	uint16_t width = x1 - x0;

	lcd_set_address_window(x0, y - halfThickness, width, thickness);
	lcd_fill(color, width, thickness);
}

void lcd_draw_line_v(
	uint16_t x,
	uint16_t y0,
	uint16_t y1,
	uint16_t color,
	uint16_t thickness
) {
	uint16_t halfThickness = thickness >> 1;
	uint16_t height = y1 - y0;

	lcd_set_address_window(x - halfThickness, y0, thickness, height);
	lcd_fill(color, thickness, height);
}

void lcd_draw_pixel(
	Point p,
	uint16_t color,
	uint16_t thickness
) {
	uint16_t halfThickness = thickness >> 1;

	lcd_set_address_window(p.x - halfThickness, p.y - halfThickness, thickness, thickness);
	lcd_fill(color, thickness, thickness);
}

void lcd_draw_rect(
	Point p0,
	Point p1,
	uint16_t color,
	uint16_t thickness
) {
	// Uses horizontal and vertical lines to draw the rectangle
	// Offsets the lines to make sure that the border is inside the border

	uint16_t halfThickness = thickness >> 1;
	uint16_t x0 = p0.x + halfThickness;
	uint16_t x1 = p1.x - halfThickness;
	uint16_t y0 = p0.y + halfThickness;
	uint16_t y1 = p1.y - halfThickness;

	// Use full width x's for horizontal lines to cover the corners
	lcd_draw_line_h(p0.x, p1.x, y0, color, thickness);
	lcd_draw_line_h(p0.x, p1.x, y1, color, thickness);

	lcd_draw_line_v(x0, y0, y1, color, thickness);
	lcd_draw_line_v(x1, y0, y1, color, thickness);
}

void lcd_draw_rect_filled(
	Point p0,
	Point p1,
	uint16_t color
) {
	uint16_t w = p1.x - p0.x;
	uint16_t h = p1.y - p0.y;

	lcd_set_address_window(p0.x, p0.y, w, h);
	lcd_fill(color, w, h);
}

static void lcd_draw_line_low(Point p0, Point p1, uint16_t color, uint16_t thickness) {
	uint16_t dx = p1.x - p0.x;
	uint16_t dy = p1.y - p0.y;
	uint16_t yi = 1;

	if (dy < 0) {
		yi = -1;
		dy = -dy;
	}

	int D = (dy << 1) - dx;
	uint16_t y = p0.y;

	for (uint16_t x = p0.x; x <= p1.x; x++) {
		Point p;
		p.x = x;
		p.y = y;

		lcd_draw_pixel(p, color, thickness);

		if (D > 0) {
			y = y + yi;
			D += ((dy - dx) << 1);
		} else {
			D += (dy << 1);
		}
	}
}

static void lcd_draw_line_high(Point p0, Point p1, uint16_t color, uint16_t thickness) {
	uint16_t dx = p1.x - p0.x;
	uint16_t dy = p1.y - p0.y;
	uint16_t xi = 1;

	if (dx < 0) {
		xi = -1;
		dx = -dx;
	}

	int D = (dx << 1) - dy;
	uint16_t x = p0.x;

	for (uint16_t y = p0.y; y <= p1.y; y++) {
		Point p;
		p.x = x;
		p.y = y;

		lcd_draw_pixel(p, color, thickness);

		if (D > 0) {
			x = x + xi;
			D += ((dx - dy) << 1);
		} else {
			D += (dx << 1);
		}
	}
}

void lcd_draw_line(
	Point p0,
	Point p1,
	uint16_t color,
	uint16_t thickness
) {
	// Implements general line drawing using Bresenham's line algorithm

	// Check if it's a vertical line
	if (p0.x == p1.x) {
		lcd_draw_line_v(p0.x, p0.y, p1.y, color, thickness);
		return;
	}

	// Check if it's a horizontal line
	if (p0.y == p1.y) {
		lcd_draw_line_h(p0.x, p1.x, p0.y, color, thickness);
		return;
	}

	// Adjust the points for the thickness of the line
	uint16_t halfThickness = thickness >> 1;
	p0.x += halfThickness;
	p0.y += halfThickness;
	p1.x -= halfThickness;
	p1.y -= halfThickness;

	// Check for the octant the line is drawn in
	if (abs(p1.y - p0.y) < abs(p1.x - p0.x)) {
		if (p0.x > p1.x) {
			lcd_draw_line_low(p1, p0, color, thickness);
		} else {
			lcd_draw_line_low(p0, p1, color, thickness);
		}
	} else {
		if (p0.y > p1.y) {
			lcd_draw_line_high(p1, p0, color, thickness);
		} else {
			lcd_draw_line_high(p0, p1, color, thickness);
		}
	}
}