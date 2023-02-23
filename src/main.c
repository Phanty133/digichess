#include <pic32mx.h>
#include <stdint.h>
#include "uart.h"
// #include "drivers/ili9341/lcd_setup.h"
// #include "drivers/ili9341/lcd_tests.h"
#include "delay.h"
#include "grid.h"

void setup() {
	uart_begin(115200);
	// lcd_init();
	// lcd_select();

	grid_init();

	// lcd_test_all();
}

void loop() {
	for (int i = 0; i < 8; i++) {
		uint32_t color = grid_read_square(0, i) ? 0x880000 : 0;

		if (i == 0) {
			uart_write_num(color, 1);
		}

		grid_set_color(0, i, color, 1);
	}

	delay_milli(10);
}

int main() {
	setup();
	while (1) loop();

	return 0;
}
