#include "drivers/ili9341/lcd_comms.h"

void lcd_set_bus_data(uint8_t data) {
	const int busSize = 8;
	bool bits[busSize];

	for (int i = 0; i < busSize; i++) {
		bits[i] = get_bit(data, i);
	}

	uint16_t port1 = PORTD;

	// TODO: make more efficient
	port1 = set_bit(port1, 10, bits[0]);
	port1 = set_bit(port1, 3, bits[1]);
	port1 = set_bit(port1, 8, bits[2]);
	port1 = set_bit(port1, 0, bits[3]);
	port1 = set_bit(port1, 1, bits[5]);
	port1 = set_bit(port1, 2, bits[6]);
	port1 = set_bit(port1, 9, bits[7]);

	PORTD = port1;
	PORTF = set_bit(PORTF, 1, bits[4]);

}

void lcd_write_strobe() {
	PORTBSET = WR_MASK;
	PORTBCLR = WR_MASK;
}

void lcd_write_command(uint8_t command) {
	// D/C - LOW
	// RD - HIGH
	PORTBSET = RD_MASK;
	PORTBCLR = DC_MASK;

	lcd_set_bus_data(command);
	lcd_write_strobe();
}

void lcd_write_data(uint8_t data) {
	// D/C - HIGH
	// RD - HIGH
	PORTBSET = DC_MASK + RD_MASK;

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
	PORTBSET = RD_MASK;
	PORTBCLR = RD_MASK;
}

void lcd_read_data(uint8_t command) {
	// D/C - HIGH
	// WR - HIGH
	PORTBSET = DC_MASK + WR_MASK;

	// TODO: Implement data reading
}