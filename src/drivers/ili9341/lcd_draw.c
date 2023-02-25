#include "drivers/ili9341/lcd_draw.h"

#include "uart.h"

static void send_pixel(uint8_t col_msb, uint8_t col_lsb) {
	lcd_write_data(col_msb);
	lcd_write_data(col_lsb);
}

static void start_frame_write() {
	lcd_write_command(ILI9341_RAMWR);
	LATBSET = __LCD_DC_MASK;
}

void lcd_set_address_window(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h) {
	uint16_t x1 = x0 + w - 1;
	uint16_t y1 = y0 + h - 1;

	if (x1 >= LCD_WIDTH) x1 = LCD_WIDTH - 1;
	if (y1 >= LCD_HEIGHT) y1 = LCD_HEIGHT - 1;

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
	start_frame_write();

	uint8_t col_msb = color >> 8;
	uint8_t col_lsb = color;

	for (int i = 0; i < w * h; i++) {
		send_pixel(col_msb, col_lsb);
	}

	lcd_write_command(0x00); // Terminate the fill
}

void lcd_clear() {
	lcd_set_address_window(0, 0, LCD_WIDTH, LCD_HEIGHT);
	lcd_fill(0xFFFF, LCD_WIDTH, LCD_HEIGHT);
}

void lcd_calibrate(uint8_t direction) {
	uint16_t w, h;

	if (direction == 0) {
		w = LCD_HEIGHT;
		h = LCD_WIDTH;
	} else {
		h = LCD_HEIGHT;
		w = LCD_WIDTH;
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
	LCD_Point p,
	uint16_t color,
	uint16_t thickness
) {
	uint16_t halfThickness = thickness >> 1;

	lcd_set_address_window(p.x - halfThickness, p.y - halfThickness, thickness, thickness);
	lcd_fill(color, thickness, thickness);
}

void lcd_draw_rect(
	LCD_Point p0,
	LCD_Point p1,
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
	LCD_Point p0,
	LCD_Point p1,
	uint16_t color
) {
	uint16_t w = p1.x - p0.x;
	uint16_t h = p1.y - p0.y;

	lcd_set_address_window(p0.x, p0.y, w, h);
	lcd_fill(color, w, h);
}

static void lcd_draw_line_low(LCD_Point p0, LCD_Point p1, uint16_t color, uint16_t thickness) {
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
		LCD_Point p;
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

static void lcd_draw_line_high(LCD_Point p0, LCD_Point p1, uint16_t color, uint16_t thickness) {
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
		LCD_Point p;
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
	LCD_Point p0,
	LCD_Point p1,
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
	if (absi(p1.y - p0.y) < absi(p1.x - p0.x)) {
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

void lcd_draw_circle(
	LCD_Point p,
	uint16_t r,
	uint16_t color,
	uint16_t thickness
) {
	// Implements circle drawing with the mid-point circle drawing algorithm

	r -= (thickness >> 1); // Adjust for thickness

	int x = r;
	int y = 0;
	int P = 1 - r;

	while (x > y) {
		y++;

		if (P <= 0) {
			P += (y << 1) + 1;
		} else {
			x--;
			P += ((y - x) << 1) + 1;
		}

		if (x < y) break;

		// Draw octant and reflections

		LCD_Point cP;
		cP.x = p.x + x;
		cP.y = p.y + y;
		lcd_draw_pixel(cP, color, thickness);

		cP.x = p.x - x;
		cP.y = p.y + y;
		lcd_draw_pixel(cP, color, thickness);

		cP.x = p.x + x;
		cP.y = p.y - y;
		lcd_draw_pixel(cP, color, thickness);

		cP.x = p.x - x;
		cP.y = p.y - y;
		lcd_draw_pixel(cP, color, thickness);

		if (x == y) continue;

		cP.y = p.y + x;
		cP.x = p.x + y;
		lcd_draw_pixel(cP, color, thickness);

		cP.y = p.y - x;
		cP.x = p.x + y;
		lcd_draw_pixel(cP, color, thickness);

		cP.y = p.y + x;
		cP.x = p.x - y;
		lcd_draw_pixel(cP, color, thickness);

		cP.y = p.y - x;
		cP.x = p.x - y;
		lcd_draw_pixel(cP, color, thickness);
	}
}

void lcd_draw_circle_filled(
	LCD_Point p,
	uint16_t r,
	uint16_t color
) {
	// Implements circle drawing with a modified mid-point circle drawing algorithm
	// Instead of drawing points on an octant and reflecting,
	// I draw horizontal lines from the -x to x points (Reflected around the y axis)
	int x = r;
	int y = 0;
	int P = 1 - r;

	// Start by drawing a line from (-r, 0) to (r, 0)
	lcd_draw_line_h(p.x - x, p.x + x, p.y, color, 1);

	while (x > y) {
		y++;

		if (P <= 0) {
			P += (y << 1) + 1;
		} else {
			x--;
			P += ((y - x) << 1) + 1;
		}

		if (x < y) break;

		// Draw octant and reflections

		lcd_draw_line_h(p.x - x, p.x + x, p.y + y, color, 1);
		lcd_draw_line_h(p.x - x, p.x + x, p.y - y, color, 1);

		if (x == y) continue;

		lcd_draw_line_h(p.x - y, p.x + y, p.y + x, color, 1);
		lcd_draw_line_h(p.x - y, p.x + y, p.y - x, color, 1);
	}
}

static void lcd_draw_bezier_quadratic_segment(
	uint16_t x0,
	uint16_t y0,
	uint16_t x1,
	uint16_t y1,
	uint16_t x2,
	uint16_t y2,
	uint16_t color,
	uint16_t thickness
) {
	// Draws quadratic bezier curve segment with a modified bresenham's algorithm
	// Sign of gradient must not change
	// Based on http://members.chello.at/~easyfilter/bresenham.html

	int sx = x2 - x1;
	int sy = y2 - y1;

	long xx = x0 - x1;
	long yy = y0 - y1;
	long xy;

	long dx, dy, err;
	long cur = xx * sy - yy * sx;

	if (sx * (long)sx + sy * (long)sy > xx * xx + yy * yy) {
		x2 = x0;
		x0 = sx + x1;

		y2 = y0;
		y0 = sy + y1;

		cur = -cur;
	}

	if (cur != 0) {
		xx += sx;
		sx = x0 < x2 ? 1 : -1;
		xx *= sx;

		yy += sy;
		sy = y0 < y2 ? 1 : -1;
		yy *= sy;

		xy = (xx * yy) << 1;
		xx *= xx;
		yy *= yy;

		if (cur * sx * sy < 0) {
			xx = -xx;
			yy = -yy;
			xy = -xy;
			cur = -cur;
		}

		dx = 4 * sy * cur * (x1 - x0) + xx - xy;
		dy = 4 * sx * cur * (y0 - y1) + yy - xy;
		
		xx += xx;
		yy += yy;
		err = dx + dy + xy;

		do {
			LCD_Point p;
			p.x = x0;
			p.y = y0;
			lcd_draw_pixel(p, color, thickness);

			if (x0 == x2 && y0 == y2) return;

			float dblErr = (err << 1);
			y1 = dblErr < dx;

			if (dblErr > dy) {
				x0 += sx;
				dx -= xy;
				err += dy += yy;	
			}

			if (y1) {
				y0 += sy;
				dy -= xy;
				err += dx += xx;
			}
		} while (dy < dx);
	}

	LCD_Point lineP0;
	lineP0.x = x0;
	lineP0.y = y0;

	LCD_Point lineP1;
	lineP1.x = x2;
	lineP1.y = y2;

	lcd_draw_line(lineP0, lineP1, color, thickness);
}

void lcd_draw_bezier_quadratic(
	LCD_Point p0,
	LCD_Point p1,
	LCD_Point p2,
	uint16_t color,
	uint16_t thickness
) {
	// Draws quadratic bezier curve segment with a modified Bresenham's algorithm
	// Based on http://members.chello.at/~easyfilter/bresenham.html
	// The code is an incomprehensible mess, but it's miles ahead of what was given
	// on the website.

	// Adjust for thickness
	uint16_t halfThickness = thickness >> 1;

	uint16_t x0 = p0.x + halfThickness;
	uint16_t y0 = p0.y + halfThickness;
	uint16_t x1 = p1.x;
	uint16_t y1 = p1.y;
	uint16_t x2 = p2.x - halfThickness;
	uint16_t y2 = p2.y - halfThickness;

	int x = x0 - x1;
	int y = y0 - y1;

	float t = x0 - (x1 << 1) + x2;
	float r;

	if ((long)x * (x2 - x1) > 0) {
		if ((long)y * (y2 - y1) > 0) {
			if (absf((y0 - (y1 << 1) + y2) / t * x) > absi(y)) {
				x0 = x2;
				x2 = x + x1;
				y0 = y2;
				y2 = y + y1;
			}
		}

		t = (x0 - x1) / t;
		r = (1 - t) * ((1 - t) * y0 + 2 * t * y1) + t * t * y2;
		t = (x0 * x2 - x1 * x1) * t / (x0 - x1);

		x = floori(t + 0.5);
		y = floori(r + 0.5);

		r = (y1 - y0) * (t - x0) / (x1 - x0) + y0;

		lcd_draw_bezier_quadratic_segment(x0, y0, x, floori(r + 0.5), x, y, color, thickness);

		r = (y1 - y2) * (t - x2) / (x1 - x2) + y2;
		x0 = x1 = x;
		y0 = y;
		y1 = floori(r + 0.5);
	}

	if ((long)(y0 - y1) * (y2 - y1) > 0) {
		t = y0 - (y1 << 1) + y2;
		t = (y0 - y1) / t;

		r = (1 - t) * ((1 - t) * x0 + 2.0 * t * x1) + t * t * x2;
		t = (y0 * y2 - y1 * y1) * t / (y0 - y1);

		x = floori(r + 0.5);
		y = floori(t + 0.5);

		r = (x1 - x0) * (t - y0) / (y1 - y0) + x0;

		lcd_draw_bezier_quadratic_segment(x0, y0, floori(r + 0.5), y, x, y, color, thickness);

		r = (x1 - x2) * (t - y2) / (y1 - y2) + x2;
		x0 = x;
		x1 = floori(r + 0.5);
		y0 = y1 = y;
	}

	lcd_draw_bezier_quadratic_segment(x0, y0, x1, y1, x2, y2, color, thickness);
}

void lcd_draw_bitmap1(
	Bitmap8* bitmap,
	LCD_Point p0,
	uint16_t color_fg,
	uint16_t color_bg
) {
	lcd_set_address_window(p0.x, p0.y, bitmap->width, bitmap->height);

	start_frame_write();

	for (uint16_t y = 0; y < bitmap->height; y++) {
		for (uint16_t x = 0; x < bitmap->width; x++) {
			uint16_t color = bitmap8_get_pixel(bitmap, x, y) ? color_fg : color_bg;
			
			uint8_t col_msb = color >> 8;
			uint8_t col_lsb = color;

			send_pixel(col_msb, col_lsb);
		}
	}

	lcd_write_command(0x00); // Terminate the fill
}

typedef struct {
	uint8_t color_fg_msb;
	uint8_t color_fg_lsb;
	uint8_t color_bg_msb;
	uint8_t color_bg_lsb;
} DrawCharContext;

static void draw_char_fg_callback(int16_t x, int16_t y, void* context) {
	DrawCharContext* draw_context = (DrawCharContext*)context;

	send_pixel(draw_context->color_fg_msb, draw_context->color_fg_lsb);
}

static void draw_char_bg_callback(int16_t x, int16_t y, void* context) {
	DrawCharContext* draw_context = (DrawCharContext*)context;

	send_pixel(draw_context->color_bg_msb, draw_context->color_bg_lsb);
}

void lcd_draw_text(
	const char* text,
	const uint8_t* font,
	uint16_t font_size_pt,
	LCD_Point p0,
	uint16_t color_fg,
	uint16_t color_bg
) {
	float scale = ttf_get_scale(font, font_size_pt, LCD_PPI);

	// Count the characters
	int count = 0;
	while (text[count++] != '\0');
	count -= 1;

	TTF_CharDims dims[count];
	int16_t max_y = 0;
	uint16_t total_width = 0;

	for (int i = 0; i < count; i++) {
		dims[i] = ttf_get_char_dims_scaled(font, text[i], scale);
		total_width += dims[i].advance_width;

		if (dims[i].max_y > max_y) max_y = dims[i].max_y;
	}

	int x_offset = p0.x;
	int16_t line_offset = max_y;

	LCD_Point text_end;
	text_end.x = p0.x + total_width;
	text_end.y = 0;

	// Determine lowest and highest point of the text for drawing a background rect
	for (int i = 0; i < count; i++) {
		// Subtract -y because the glyph dimensions have a flipped Y axis
		// relative to the screen's Y axis.
		uint16_t lowest_point = line_offset - dims[i].y;

		if (text_end.y < lowest_point) text_end.y = lowest_point;
	}

	text_end.y += p0.y;

	lcd_draw_rect_filled(p0, text_end, color_bg);

#ifndef DISABLE_FONT_RENDERING
	DrawCharContext draw_context;
	draw_context.color_fg_msb = color_fg >> 8;
	draw_context.color_fg_lsb = color_fg;
	draw_context.color_bg_msb = color_bg >> 8;
	draw_context.color_bg_lsb = color_bg;

	for (int i = 0; i < count; i++) {
		if (text[i] == ' ') {
			x_offset += dims[i].advance_width;
			continue;
		}

		lcd_set_address_window(
			x_offset + dims[i].x,
			p0.y + line_offset - dims[i].max_y,
			dims[i].width,
			dims[i].height
		);
		start_frame_write();
		
		gen_char_fill(
			draw_char_fg_callback,
			draw_char_bg_callback,
			&draw_context,
			font,
			text[i],
			scale
		);

		x_offset += dims[i].advance_width;
	}

	lcd_write_command(0x00); // Terminate final memory write
#endif
}

static void draw_image_pixel(uint32_t x, uint32_t y, BMP_Color color, void* context) {
	uint16_t color_hex = rgbarr_24b_to_16b(color.r, color.g, color.b);

	uint8_t col_msb = (color_hex >> 8);
	uint8_t col_lsb = (color_hex);

	send_pixel(col_msb, col_lsb);
}

void lcd_draw_image(LCD_Point p0, const uint8_t* image) {
	const BMP_InfoHeader* info = bmp_get_info(image);

	// Flip the y axis because bitmaps are drawn bottom-to-top
	lcd_set_orientation(LCD_X_ORIENTATION, !LCD_Y_ORIENTATION);

	lcd_set_address_window(
		p0.x,
		LCD_HEIGHT - p0.y - info->height,
		info->width,
		info->height
	);
	start_frame_write();

	bmp_decode(image, draw_image_pixel, 0);

	// Reset the y axis
	lcd_set_orientation(LCD_X_ORIENTATION, LCD_Y_ORIENTATION);
}

typedef struct {
	uint8_t color_fg_msb;
	uint8_t color_fg_lsb;
	uint8_t color_bg_msb;
	uint8_t color_bg_lsb;
} DrawImage1BitPixelContext;

static void draw_image_1bit_pixel(uint32_t x, uint32_t y, BMP_Color color, void* context) {
	DrawImage1BitPixelContext* img_context = (DrawImage1BitPixelContext*)context;

	if (color.r == 0) {
		// Foreground
		send_pixel(img_context->color_fg_msb, img_context->color_fg_lsb);
	} else {
		// Background
		send_pixel(img_context->color_bg_msb, img_context->color_bg_lsb);
	}
}

void lcd_draw_image_1bit(
	LCD_Point p0,
	const uint8_t* image,
	uint16_t color_fg,
	uint16_t color_bg
) {
	const BMP_InfoHeader* info = bmp_get_info(image);
	DrawImage1BitPixelContext context;
	context.color_bg_msb = (color_bg >> 8);
	context.color_bg_lsb = color_bg;
	context.color_fg_msb = (color_fg >> 8);
	context.color_fg_lsb = color_fg;

	// Flip the y axis because bitmaps are drawn bottom-to-top
	lcd_set_orientation(LCD_X_ORIENTATION, !LCD_Y_ORIENTATION);

	lcd_set_address_window(
		p0.x,
		LCD_HEIGHT - p0.y - info->height,
		info->width,
		info->height
	);
	start_frame_write();

	bmp_decode(image, draw_image_1bit_pixel, &context);

	// Reset the y axis
	lcd_set_orientation(LCD_X_ORIENTATION, LCD_Y_ORIENTATION);
}
