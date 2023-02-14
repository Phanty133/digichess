#include <pic32mx.h>
#include <stdint.h>
#include "drivers/ili9341/lcd_setup.h"
#include "drivers/ili9341/lcd_draw.h"
#include "drivers/ili9341/lcd_utils.h"
#include "drivers/ili9341/lcd_touch.h"
#include "drivers/ili9341/lcd_defines.h"
#include "drivers/ws2812b/ws2812b.h"
#include "fonts/ComicSansMS.ttf.h"
#include "ttf/ttf_draw.h"
#include "ttf/ttf_funcs.h"
#include "bitmap.h"
#include <stdbool.h>

void led_test();
void draw_test();
void font_test();

int main() {
	uart_begin(115200);

	font_test();

	return 0;
}

void led_test(){
	int num_leds = 7;
	uint32_t leds[num_leds];
	led_init(leds, num_leds);
	int counter = 0;

	while(true){
		led_set(leds, counter, 0x0000FF);
		
		if (counter == 0) {
			led_set(leds, num_leds - 1, 0);
		} else {
			led_set(leds, counter - 1, 0);
		}

		counter = (counter + 1) % num_leds;
		led_display(leds, num_leds);

		delay_milli(20);
	}
}

void font_test() {
	lcd_init();
	lcd_select();

	uint16_t fontsize = 64;
	float scale = ttf_get_scale(COMICSANSMS, fontsize, LCD_PPI);

	Bitmap8 bitmap;
	bitmap.width = 100;
	bitmap.height = 120;
	
	uint8_t bitmap_data[bitmap.width * bitmap.height];
	bitmap.data = bitmap_data;
	bitmap_clear(&bitmap);

	ttf_draw_string(&bitmap, COMICSANSMS, "R", fontsize, LCD_PPI);

	// Bitmap8 bitmap90deg;
	// bitmap90deg.height = 300;
	// bitmap90deg.width = 48;

	// uint8_t bitmap90deg_data[bitmap90deg.width * bitmap90deg.height];
	// bitmap90deg.data = bitmap90deg_data;
	// bitmap_clear(&bitmap90deg);

	// bitmap_rotate90(&bitmap90deg, &bitmap);

	Point p0, p1;
	p0.x = 0;
	p0.y = 0;

	p1.x = 240;
	p1.y = 320;

	lcd_draw_rect_filled(p0, p1, 0xFFFF);

	p0.x = 10;
	p0.y = 10;

	lcd_draw_bitmap1(&bitmap, p0, rgb_24b_to_16b(0xFF0000), rgb_24b_to_16b(0x0000FF));
}

void lcd_test() {
	lcd_init();
	lcd_select();

	// Fill screen with white

	lcd_set_address_window(0, 0, 240, 320);
	lcd_fill(rgb_24b_to_16b(0xFFFFFF), 240, 320);

	lcd_draw_line_h(105, 220, 103, rgb_24b_to_16b(0xFF0000), 4);
	lcd_draw_line_v(202, 50, 175, rgb_24b_to_16b(0x0000FF), 4);

	Point p0, p1, p2;
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

	p0.x = 0;
	p0.y = 169;
	p1.x = 100;
	p1.y = 169;

	lcd_draw_line(p0, p1, rgb_24b_to_16b(0x0000FF), 1);

	p0.x = 50;
	p0.y = 200;

	lcd_draw_circle(p0, 30, rgb_24b_to_16b(0xFF0000), 6);
	lcd_draw_circle_filled(p0, 24, rgb_24b_to_16b(0x00AA00));

	p0.x = 100;
	p0.y = 30;
	p1.x = 145;
	p1.y = 15;
	p2.x = 150;
	p2.y = 50;

	lcd_draw_pixel(p0, rgb_24b_to_16b(0x0000FF), 4);
	lcd_draw_pixel(p1, rgb_24b_to_16b(0xFFAA00), 4);
	lcd_draw_pixel(p2, rgb_24b_to_16b(0x0000FF), 4);

	lcd_draw_bezier_quadratic(p0, p1, p2, rgb_24b_to_16b(0xFF0000), 4);
}
