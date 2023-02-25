#include <pic32mx.h>
#include <stdint.h>
#include "uart.h"
#include "delay.h"
#include "sys_defines.h"

// #define DEBUG_BOARD
// #define DEBUG_LCD
#define DEBUG_BUZZER

#ifdef DEBUG_BOARD
#include "grid.h"
#include "drivers/ws2812b/ws2812b.h"
#endif

#ifdef DEBUG_LCD
#include "drivers/ili9341/lcd_setup.h"
#include "drivers/ili9341/lcd_tests.h"
#endif

#ifdef DEBUG_BUZZER
#include "buzzer.h"
#endif

uint8_t power_mask = (1 << 1);

void setup() {
	uart_begin(115200);

#ifdef DEBUG_BUZZER
	buzzer_init();

	buzzer_on();
	delay_milli(500);
	buzzer_off();
	delay_milli(500);
	buzzer_on();
	delay_milli(500);
	buzzer_off();
#endif
	
#ifdef DEBUG_LCD
	lcd_init();
	lcd_select();
	// lcd_test_all();
	lcd_draw_test();
#endif

#ifdef DEBUG_BOARD
	grid_init();

	TRISFCLR = power_mask;
	LATFCLR = power_mask;

	led_display(grid_get_led_data(), GRID_LED_COUNT);
#endif
}

void loop() {
#ifdef DEBUG_BOARD
	LATFCLR = power_mask;
	delay_milli(2750);
	LATFSET = power_mask;
	delay_milli(50);

	for (int r = 0; r < 2; r++) {
		for (int c = 0; c < 8; c++) {
			uint32_t color = !grid_read_square(r, c) ? 0x000088 : 0x80000;

			if (c == 7) {
				uart_write_num(color, 1);
			}

			grid_set_color(r, c, color, 0);
		}
	}

	led_display(grid_get_led_data(), GRID_LED_COUNT);
#endif
}

int main() {
	setup();
	while (1) loop();

	return 0;
}
