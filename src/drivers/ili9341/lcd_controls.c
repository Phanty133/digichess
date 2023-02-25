#include "drivers/ili9341/lcd_controls.h"

void lcd_select() {
	// CS - LOW
	LATBCLR = __LCD_CS_MASK;
}

void lcd_deselect() {
	// CS - HIGH
	LATBSET = __LCD_CS_MASK;
}

void lcd_hw_reset() {
	LATDCLR = __LCD_RST_MASK;
	delay_milli(150);
	LATDSET = __LCD_RST_MASK;
	delay_milli(150);
}

void lcd_sw_reset() {
	lcd_write_command(ILI9341_RESET);
	delay_milli(100);
}

void lcd_sleep_on() {
	lcd_write_command(ILI9341_SLPIN);
}

void lcd_sleep_off() {
	lcd_write_command(ILI9341_SLPOUT);
}

void lcd_display_on() {
	lcd_write_command(ILI9341_DISPON);
}

void lcd_display_off() {
	lcd_write_command(ILI9341_DISPOFF);
}

void lcd_set_orientation(uint8_t x, uint8_t y) {
	uint8_t yBit = y >= 1 ? 1 : 0;
	uint8_t xBit = x >= 1 ? 1 : 0;
	uint8_t colorFormatBit = 1;

	uint8_t data[] = {
		(yBit << 7) + (xBit << 6) + (colorFormatBit << 3)
	};

	lcd_write_register(ILI9341_MADCTL, data, 1);
}
