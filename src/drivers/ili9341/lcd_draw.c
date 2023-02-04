#include "drivers/ili9341/lcd_draw.h"

void lcd_set_address_window(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h) {
	uint16_t x1 = (x0 + w - 1);
	uint16_t y1 = (y0 + h - 1);

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