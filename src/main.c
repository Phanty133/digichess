#include <pic32mx.h>
#include <stdint.h>
#include "drivers/ili9341/lcd_setup.h"
#include "drivers/ili9341/lcd_draw.h"
#include "drivers/ili9341/lcd_utils.h"
#include "drivers/ili9341/lcd_touch.h"
#include <stdbool.h>

int clamp(int val, int min, int max) {
	if (val <= min) return min;
	if (val >= max) return max;
	return val;
}

int main(void) {
	uart_begin(115200);

	lcd_init();
	lcd_touch_init();

	// Fill screen with white
	lcd_set_address_window(0, 0, 240, 320);
	lcd_fill(rgb_24b_to_16b(0xFFFFFF), 240, 320);

	// Setup pixel drawing
	int radius = 2;
	int dia = radius * 2;

	uint16_t touchX, touchY;

	while (1) {
		lcd_deselect();
		// lcd_touch_debug_raw();
		bool isTouching = lcd_touch_read_coords(
			ILI9341_TFTWIDTH,
			ILI9341_TFTHEIGHT,
			&touchX,
			&touchY,
			true
		);
		lcd_select();

		if (!isTouching) continue;
		if (
			touchX < radius || touchX > ILI9341_TFTWIDTH - radius
			|| touchY < radius || touchY > ILI9341_TFTHEIGHT - radius
		) continue;

		lcd_set_address_window(
			clamp(touchX - radius, 0, ILI9341_TFTWIDTH),
			clamp(touchY - radius, 0, ILI9341_TFTHEIGHT),
			dia,
			dia
		);
		lcd_fill(rgb_24b_to_16b(0xFF0000), dia, dia);

		delay_milli(10);
	}

	return 0;
}
