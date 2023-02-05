#include "drivers/ili9341/lcd_controls.h"

void lcd_select() {
	// CS - LOW
	PORTBCLR = CS_MASK;
}

void lcd_deselect() {
	// CS - HIGH
	PORTBSET = CS_MASK;
}

void lcd_hw_reset() {
	PORTBCLR = RST_MASK;
	PORTBSET = RST_MASK;
	delay_milli(150);
}

void lcd_sw_reset() {
	lcd_write_command(ILI9341_RESET);
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
