#include "grid.h"

uint8_t LED_DATA[GRID_LED_COUNT * ELS_PER_LED] = {};

void grid_init() {
	led_init(LED_DATA, led_get_arr_size(GRID_LED_COUNT));

	uint16_t mux_select_mask =
		MUX_R0_MASK
		| MUX_R1_MASK
		| MUX_R2_MASK
		| MUX_C0_MASK
		| MUX_C1_MASK
		| MUX_C2_MASK;

	TRISBSET = MUX_OUT_MASK;
	TRISDCLR = mux_select_mask;
	LATDCLR = mux_select_mask;
}

uint8_t grid_read_square(uint8_t row, uint8_t col) {
	uint8_t r0 = get_bit(row, 0);
	uint8_t r1 = get_bit(row, 1);
	uint8_t r2 = get_bit(row, 2);

	uint8_t c0 = get_bit(col, 0);
	uint8_t c1 = get_bit(col, 1);
	uint8_t c2 = get_bit(col, 2);

	uint16_t cur_latd = PORTD;

	cur_latd = set_bit(cur_latd, MUX_R0_PIN, r0);
	cur_latd = set_bit(cur_latd, MUX_R1_PIN, r1);
	cur_latd = set_bit(cur_latd, MUX_R2_PIN, r2);
	cur_latd = set_bit(cur_latd, MUX_C0_PIN, c0);
	cur_latd = set_bit(cur_latd, MUX_C1_PIN, c1);
	cur_latd = set_bit(cur_latd, MUX_C2_PIN, c2);

	LATD = cur_latd;

	return get_bit(PORTB, MUX_OUT_PIN);
}

void grid_set_color(uint8_t row, uint8_t col, uint32_t color, uint8_t display) {
	uint16_t led_start_index = (row * 8 + col) * GRID_LEDS_PER_SQUARE;
	uint16_t led_end_index = led_start_index + GRID_LEDS_PER_SQUARE;

	for (int i = led_start_index; i < led_end_index; i++) {
		led_set(LED_DATA, i, color);
	}

	if (display) led_display(LED_DATA, GRID_LED_COUNT);
}

uint8_t* grid_get_led_data() {
	return LED_DATA;
}

void grid_reset_sensors() {
	LATFCLR = GRID_POWER_MASK;
	delay_milli(2750);
	LATFSET = GRID_POWER_MASK;
	delay_milli(50);
}
