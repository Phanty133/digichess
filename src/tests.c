#include "tests.h"

void debug_board_setup() {
	grid_init();

	TRISFCLR = GRID_POWER_MASK;
	LATFCLR = GRID_POWER_MASK;

	led_display(grid_get_led_data(), GRID_LED_COUNT);
}

void debug_board_loop() {
	grid_reset_sensors();

	for (int r = 0; r < GRID_ROWS; r++) {
		for (int c = 0; c < GRID_COLS; c++) {
			uint32_t color = !grid_read_square(r, c) ? 0x000088 : 0x80000;

			if (c == 7) {
				uart_write_num(color, 1);
			}

			grid_set_color(r, c, color, 0);
		}
	}

	led_display(grid_get_led_data(), GRID_LED_COUNT);
}

void debug_lcd_setup() {
	lcd_init();
	lcd_select();
	lcd_test_all();
}

void debug_touch_setup() {
	lcd_init();
	lcd_touch_init();
	lcd_select();

	LCD_Point p0, p1;
	p0.x = 0;
	p0.y = 0;
	p1.x = LCD_WIDTH;
	p1.y = LCD_HEIGHT;

	lcd_draw_rect_filled(p0, p1, rgb_24b_to_16b(0x0055AA));

	lcd_wait_available();
	delay_milli(300);

	lcd_touch_debug_raw();
}

void debug_touch_loop() {}

void debug_ui_setup() {
	lcd_init();
	lcd_touch_init();
	lcd_select();

	lcd_clear();

	LCD_Point p0, p1;
	p0.x = 10;
	p0.y = 50;
	p1.x = p0.x + 220;
	p1.y = p0.y + 50;

	uint16_t bg_color = rgb_24b_to_16b(0x0044DD);

	lcd_draw_rect_filled(p0, p1, bg_color);

	p1.x = p0.x + 22;
	p1.y = p0.y + 10;

	lcd_draw_text("Press here", COMICSANSMS(), 18, p1, 0xFFFF, bg_color);

	p1.x = 10;
	p1.y = p0.y + 70;

	lcd_draw_text("You've pressed", COMICSANSMS(), 16, p1, 0x0000, 0xFFFF);

	p1.x = 100;
	p1.y = p1.y + 45;

	lcd_draw_text("0", COMICSANSMS(), 32, p1, 0x0000, 0xFFFF);

	p1.x = 80;
	p1.y = p1.y + 60;

	lcd_draw_text("times", COMICSANSMS(), 16, p1, 0x0000, 0xFFFF);

	lcd_touch_init_postdraw();
}

int touch_counter = 0;
int prev_loop_touched = 0;

void debug_ui_loop() {
	uint16_t touch_x;
	uint16_t touch_y;

	uint8_t touching = lcd_touch_read_coords(&touch_x, &touch_y, 0);

	delay_milli(5);

	if (touching && !prev_loop_touched) {
		prev_loop_touched = 1;

		if (touch_x >= 10 && touch_x <= 230 && touch_y >= 50 && touch_y <= 100) {
			// lcd_touch_reset_pins(); // why does it work better without resets???
			touch_counter++;

			LCD_Point p0, p1;

			p0.x = 10;
			p0.y = 165;
			p1.x = 230;
			p1.y = 220;

			lcd_select();
			lcd_draw_rect_filled(p0, p1, 0xFFFF);

			char buf[8];
			num2char(touch_counter, buf, 8);

			p0.x = 100;
			p0.y = 165;

			lcd_draw_text(buf, COMICSANSMS(), 32, p0, 0, 0xFFFF);
			lcd_touch_init_postdraw();
		}
	} else if (!touching) {
		prev_loop_touched = 0;
	}
}

void debug_buzzer_setup() {
	buzzer_init();

	buzzer_on();
	delay_milli(500);
	buzzer_off();
	delay_milli(500);
	buzzer_on();
	delay_milli(500);
	buzzer_off();
	delay_milli(500);
	buzzer_on();
	delay_milli(500);
	buzzer_off();
}

void debug_chess_setup() {
	// TODO: Move chess test here
}

void debug_chess_loop() {
	// TODO: Move chess test here
}
