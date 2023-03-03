#include "grid.h"

static uint8_t LED_DATA[GRID_LED_COUNT * ELS_PER_LED] = {};
static uint8_t grid_state[GRID_ROWS][GRID_COLS] = {};
static uint16_t timer_counter = 0;

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

	TRISFCLR = GRID_POWER_MASK;
	LATFSET = GRID_POWER_MASK;

	for (int r = 0; r < GRID_ROWS; r++) {
		for (int c = 0; c < GRID_COLS; c++) {
			grid_state[r][c] = 0;
		}
	}

	// Set up the grid update timer
	T2CON = 0x0; // Disable timer while setting up
  	TMR2 = 0; // Reset count

	PR2 = 62500; // Makes the period 200ms with a prescale of 1:256 
	T2CONSET = 0x70; // Set prescale value to 1:256
	IFSCLR(0) = T2IF; // Clear the flag at bit 8
	IECSET(0) = T2IF; // Enable interrupt at bit 8

	T2CONSET = 0x8000; // Start timer
}

uint8_t grid_read_square(uint8_t row, uint8_t col) {
	uint8_t r0 = get_bit(row, 0);
	uint8_t r1 = get_bit(row, 1);
	uint8_t r2 = get_bit(row, 2);

	uint8_t c0 = get_bit(col, 0);
	uint8_t c1 = get_bit(col, 1);
	uint8_t c2 = get_bit(col, 2);

	uint16_t cur_latd = LATD;

	cur_latd = set_bit(cur_latd, MUX_R0_PIN, r0);
	cur_latd = set_bit(cur_latd, MUX_R1_PIN, r1);
	cur_latd = set_bit(cur_latd, MUX_R2_PIN, r2);
	cur_latd = set_bit(cur_latd, MUX_C0_PIN, c0);
	cur_latd = set_bit(cur_latd, MUX_C1_PIN, c1);
	cur_latd = set_bit(cur_latd, MUX_C2_PIN, c2);

	LATD = cur_latd;

	return !get_bit(PORTB, MUX_OUT_PIN);
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
	delay_milli(3000);
	LATFSET = GRID_POWER_MASK;
	delay_milli(50);
}

void grid_update_state() {
	for (int r = 0; r < GRID_ROWS; r++) {
		for (int c = 0; c < GRID_COLS; c++) {
			grid_state[r][c] = grid_read_square(r, c);

			if (r == 6) {
				uart_write_num(c, 0);
				uart_write(": ");
				uart_write_num(grid_read_square(r, c), 1);
			}
		}
	}
}

uint8_t* grid_get_state() {
	return grid_state;
}

void grid_loop_update() {
	if (IFS(0) & T2IF) {
		IFSCLR(0) = T2IF;

		if (++timer_counter == __GRID_OFF_PERIODS) {
			timer_counter = 0;

			LATFSET = GRID_POWER_MASK;
			delay_milli(GRID_ON_TIME); // TODO: Rewrite with timer?

			grid_update_state();

			LATFCLR = GRID_POWER_MASK;
		}
	}
}
