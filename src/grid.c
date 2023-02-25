#include "grid.h"

uint32_t LED_DATA[GRID_LED_COUNT * ELS_PER_LED] = {};

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

	uint16_t cur_latd = LATD;

	uint16_t mux_state =
		(r0 << MUX_R0_PIN)
		| (r1 << MUX_R1_PIN)
		| (r2 << MUX_R2_PIN)
		| (c0 << MUX_C0_PIN)
		| (c1 << MUX_C1_PIN)
		| (c2 << MUX_C2_PIN);

	// TODO rewrite to not overwrite other D pins
	LATD = mux_state;

	return ((PORTB & MUX_OUT_MASK) >> MUX_OUT_PIN);
}

void grid_set_color(uint8_t row, uint8_t col, uint32_t color, uint8_t display) {
	uint16_t led_start_index = (row * 8 + col) * GRID_LEDS_PER_SQUARE;
	uint16_t led_end_index = led_start_index + GRID_LEDS_PER_SQUARE;

	for (int i = led_start_index; i < led_end_index; i++) {
		led_set(LED_DATA, i, color);
	}

	if (display) led_display(LED_DATA, GRID_LED_COUNT);
}

uint32_t* grid_get_led_data() {
	return LED_DATA;
}
