#include "tests.h"

void debug_board_setup() {
	grid_init();

	led_display(grid_get_led_data(), GRID_LED_COUNT);
}

void debug_board_loop() {
	grid_loop_update();
	uint8_t (*grid_state)[8] = (uint8_t (*)[8])grid_get_state();

	for (int r = 0; r < GRID_ROWS; r++) {
		for (int c = 0; c < GRID_COLS; c++) {
			uint32_t color = grid_state[r][c] ? 0x000010 : 0x100000;

			grid_set_color(r, c, color, 0);
		}
	}

	led_display(grid_get_led_data(), GRID_LED_COUNT);
}

void debug_board_grid_setup() {
	grid_init();

	TRISFCLR = GRID_POWER_MASK;
	LATFCLR = GRID_POWER_MASK;

	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			uint8_t col_flip = 0;
			uint32_t color = 0xAA6600;

			if (c % 2) col_flip = 1;

			if (col_flip) color = 0x0066AA;

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
	lcd_touch_init_postdraw();

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
