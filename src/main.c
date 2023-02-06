#include <pic32mx.h>
#include <stdint.h>
#include "drivers/ili9341/lcd_setup.h"
#include "drivers/ili9341/lcd_draw.h"
#include "drivers/ili9341/lcd_utils.h"
#include "drivers/ili9341/lcd_touch.h"
#include <stdbool.h>

int main(void) {
	uart_begin(115200);

	lcd_init();
	lcd_select();

	// Fill screen with white

	lcd_set_address_window(0, 0, 240, 320);
	lcd_fill(rgb_24b_to_16b(0xFFFFFF), 240, 320);

	lcd_draw_line_h(105, 220, 103, rgb_24b_to_16b(0xFF0000), 4);
	lcd_draw_line_v(202, 50, 175, rgb_24b_to_16b(0x0000FF), 4);

	Point p0, p1;
	p0.x = 100;
	p0.y = 100;

	lcd_draw_pixel(p0, rgb_24b_to_16b(0x00FF00), 10);

	p0.x = 200;
	p0.y = 250;
	
	lcd_draw_pixel(p0, rgb_24b_to_16b(0x00FF00), 10);

	p0.x = 105;
	p0.y = 105;
	p1.x = 200;
	p1.y = 150;

	lcd_draw_rect(p0, p1, rgb_24b_to_16b(0xFFAA00), 4);

	p0.x = 30;
	p0.y = 30;
	p1.x = 95;
	p1.y = 95;

	lcd_draw_rect_filled(p0, p1, rgb_24b_to_16b(0x00AAFF));

	p0.x = 30;
	p0.y = 30;
	p1.x = 195;
	p1.y = 245;

	lcd_draw_line(p0, p1, rgb_24b_to_16b(0xAA00FF), 4);

	return 0;
}
