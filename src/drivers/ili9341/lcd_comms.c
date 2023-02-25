#include "drivers/ili9341/lcd_comms.h"

void lcd_write_command(uint8_t command) {
	lcd_wait_available();
	
	lcd_set_command_mode();
	PMDIN = command;
}

void lcd_write_data(uint8_t data) {
	lcd_wait_available();

	lcd_set_data_mode();
	PMDIN = data;
}

void lcd_write_register(uint8_t command, uint8_t* data, uint32_t dataSize) {
	lcd_write_command(command);

	for (int i = 0; i < dataSize; i++) {
		lcd_write_data(data[i]);
	}
}

void lcd_read_data(uint8_t command) {
	// D/C - HIGH
	// WR - HIGH
	// LATBSET = __LCD_DC_MASK + __LCD_WR_MASK;

	// TODO: Implement data reading
}

void lcd_set_command_mode() {
	// D/C - LOW
	// RD - HIGH
	
	// LATDSET = __LCD_RD_MASK;
	LATBCLR = __LCD_DC_MASK;
}

void lcd_set_data_mode() {
	// D/C - HIGH
	// RD - HIGH

	LATBSET = __LCD_DC_MASK;
}

void lcd_wait_available() {
	int i = 0;

	while(PMMODE & 0x8000); // Wait until the busy flag is not set
}
