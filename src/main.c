#include <pic32mx.h>
#include <stdint.h>
#include "drivers/ili9341/lcd_setup.h"
#include "drivers/ili9341/lcd_draw.h"
#include "drivers/ili9341/lcd_utils.h"
#include "uart.h"
#include "delay.h"
#include <stdbool.h>

int main(void) {
	uart_begin(115200);

	char buf[32];
	int c = 0;

	while (1) {
		bool breaknl = false;

		while (uart_read_available()) {
			char b = uart_read_byte();

			if (b == '\n' || b == '\r') {
				breaknl = true;
				break;
			}

			buf[c++] = b;
		}

		if (breaknl || c >= 32) {
			uart_write("You wrote: ");
			uart_write_line(buf);
			break;
		}

		delay_milli(100);
	}


	// lcd_init();
	// lcd_set_address_window(0, 0, 240, 320);
	// lcd_fill(rgb_24b_to_16b(0xFF0000), 240, 320);

	while(1);

	return 0;
}
