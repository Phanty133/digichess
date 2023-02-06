#include "drivers/ili9341/lcd_comms.h"

void lcd_set_bus_data(uint8_t data) {
	const int busSize = 8;
	bool bits[busSize];

	for (int i = 0; i < busSize; i++) {
		bits[i] = get_bit(data, i);
	}

	uint16_t port1 = LATD;

	// TODO: make more efficient
	port1 = set_bit(port1, __LCD_D0_NUM, bits[0]);
	port1 = set_bit(port1, __LCD_D1_NUM, bits[1]);
	port1 = set_bit(port1, __LCD_D2_NUM, bits[2]);
	port1 = set_bit(port1, __LCD_D3_NUM, bits[3]);
	port1 = set_bit(port1, __LCD_D5_NUM, bits[5]);
	port1 = set_bit(port1, __LCD_D6_NUM, bits[6]);
	port1 = set_bit(port1, __LCD_D7_NUM, bits[7]);

	LATD = port1;
	LATF = set_bit(LATF, __LCD_D4_NUM, bits[4]);
}

void lcd_write_strobe() {
	LATBSET = __LCD_WR_MASK;
	LATBCLR = __LCD_WR_MASK;
}

void lcd_write_command(uint8_t command) {
	// D/C - LOW
	// RD - HIGH
	LATBSET = __LCD_RD_MASK;
	LATBCLR = __LCD_DC_MASK;

	lcd_set_bus_data(command);

	lcd_write_strobe();
}

void lcd_write_data(uint8_t data) {
	// D/C - HIGH
	// RD - HIGH
	LATBSET = __LCD_DC_MASK;

	lcd_set_bus_data(data);
	lcd_write_strobe();
}

void lcd_write_register(uint8_t command, uint8_t* data, uint32_t dataSize) {
	lcd_write_command(command);

	for (int i = 0; i < dataSize; i++) {
		lcd_write_data(data[i]);
	}
}

void lcd_read_strobe() {
	LATBSET = __LCD_RD_MASK;
	LATBCLR = __LCD_RD_MASK;
}

void lcd_read_data(uint8_t command) {
	// D/C - HIGH
	// WR - HIGH
	LATBSET = __LCD_DC_MASK + __LCD_WR_MASK;

	// TODO: Implement data reading
}