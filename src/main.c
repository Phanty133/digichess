#include <pic32mx.h>
#include <stdint.h>
#include "drivers/ili9341/lcd_setup.h"
#include "drivers/ili9341/lcd_draw.h"
#include "drivers/ili9341/lcd_utils.h"
#include "drivers/ili9341/lcd_touch.h"
#include <stdbool.h>
#include "bitops.h"

int clamp(int val, int min, int max) {
	if (val <= min) return min;
	if (val >= max) return max;
	return val;
}

int main(void) {
	uart_begin(115200);

	lcd_init();
	lcd_touch_init();
	lcd_select();

	// Fill screen with white

	lcd_set_address_window(0, 0, 240, 320);
	lcd_fill(rgb_24b_to_16b(0x00AAFF), 240, 320);
	lcd_write_command(0x00); // terminates the fill

	uint16_t x,y;
	int radius = 4;
	int dia = radius * 2;

	// lcd_touch_debug_coords();

	while (1) {
		bool isTouched = lcd_touch_read_coords(
			ILI9341_TFTWIDTH,
			ILI9341_TFTHEIGHT,
			&x,
			&y,
			true
		);

		delay_milli(5);

		// uart_write("is touch: ");

		// char buf[16];
		// num2char(isTouched, buf, 16);

		// uart_write_line(buf);

		if (!isTouched) continue;

		char buf_x[16];
		num2char(x, buf_x, 16);

		char buf_y[16];
		num2char(y, buf_y, 16);
		
		uart_write("X: ");
		uart_write(buf_x);
		uart_write("; Y: ");
		uart_write_line(buf_y);

		lcd_select();

		lcd_set_address_window(x - radius, y - radius, dia, dia);
		lcd_fill(rgb_24b_to_16b(0xFF0000), dia, dia);
		lcd_write_command(0x00);
		delay_milli(5);
	}

	return 0;
}
