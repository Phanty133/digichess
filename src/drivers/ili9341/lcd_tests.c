#include "drivers/ili9341/lcd_tests.h"

void lcd_setup_test() {
	lcd_calibrate(1);
}

void lcd_draw_test() {
	lcd_clear();

	lcd_draw_line_h(105, 220, 103, rgb_24b_to_16b(0xFF0000), 4);
	lcd_draw_line_v(202, 50, 175, rgb_24b_to_16b(0x0000FF), 4);

	LCD_Point p0, p1, p2;
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

void lcd_font_test() {
	lcd_clear();

	uint16_t fontsize = 20;
	LCD_Point p0, p1;
	p0.x = 0;
	p0.y = 0;

	p1.x = 240;
	p1.y = 320;

	lcd_draw_rect_filled(p0, p1, 0xFFFF);

	uint16_t color_fg = rgb_24b_to_16b(0xFF0000);
	uint16_t color_bg = rgb_24b_to_16b(0x0088FF);

	p0.x = 0;
	p0.y = 10;

	lcd_draw_text(
		"abcdefgh",
		COMICSANSMS,
		fontsize,
		p0,
		color_fg,
		color_bg
	);

	p0.x = 0;
	p0.y = 50;

	lcd_draw_text(
		"ijklmnopq",
		COMICSANSMS,
		fontsize,
		p0,
		color_fg,
		color_bg
	);

	p0.x = 0;
	p0.y = 90;

	lcd_draw_text(
		"rstuvwxyz",
		COMICSANSMS,
		fontsize,
		p0,
		color_fg,
		color_bg
	);

	p0.x = 0;
	p0.y = 130;

	lcd_draw_text(
		"ABCDEFGH",
		COMICSANSMS,
		fontsize,
		p0,
		color_fg,
		color_bg
	);

	p0.x = 0;
	p0.y = 170;

	lcd_draw_text(
		"IJKLMNOP",
		COMICSANSMS,
		fontsize,
		p0,
		color_fg,
		color_bg
	);

	p0.x = 0;
	p0.y = 210;

	lcd_draw_text(
		"QRSTUVW",
		COMICSANSMS,
		fontsize,
		p0,
		color_fg,
		color_bg
	);

	p0.x = 0;
	p0.y = 250;

	lcd_draw_text(
		"XYZ",
		COMICSANSMS,
		fontsize,
		p0,
		color_fg,
		color_bg
	);
}

void lcd_image_test() {
	lcd_clear();

	LCD_Point p;
	p.x = 0;
	p.y = 20;

	LCD_Point p0, p1;
	p0.x = 20;
	p0.y = 300;
	p1.x = 200;
	p1.y = 320;

	lcd_draw_image(p, VIEWSONIC_8BIT);
	delay_milli(1000);
	lcd_draw_image(p, VIEWSONIC_4BIT);
	delay_milli(1000);
	lcd_draw_image_1bit(
		p,
		VIEWSONIC_1BIT,
		rgb_24b_to_16b(0xFF0000),
		rgb_24b_to_16b(0xAAFF00)
	);
}

void lcd_touch_test() {
	lcd_clear();
}

void lcd_test_all() {
	const int test_delay_ms = 5000;

	lcd_setup_test();
	delay_milli(test_delay_ms);

	lcd_draw_test();
	delay_milli(test_delay_ms);
	
	lcd_font_test();
	delay_milli(test_delay_ms);

	lcd_image_test();
	delay_milli(test_delay_ms);
	
	lcd_touch_test();
}
