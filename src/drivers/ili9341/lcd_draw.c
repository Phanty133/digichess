#include "drivers/ili9341/lcd_draw.h"

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
	PORTBSET = DC_MASK + RD_MASK;

	uint8_t col_msb = color >> 8;
	uint8_t col_lsb = color;

	for (int i = 0; i < w * h; i++) {
		lcd_set_bus_data(col_msb);
		lcd_write_strobe();

		lcd_set_bus_data(col_lsb);
		lcd_write_strobe();
	}
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
