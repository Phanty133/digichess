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

	gui_register_all_menus();
	gui_set_menu(MENU_SPLASH);
}

void debug_ui_loop() {
	gui_update();
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
