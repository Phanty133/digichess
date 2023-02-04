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