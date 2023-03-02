#include "buzzer.h"

static uint8_t buzzer_counter = 0;

void buzzer_init() {
	TRISDCLR = BUZZER_MASK;

	// Set up the buzzer timer
	T3CON = 0x0; // Disable timer while setting up
  	TMR3 = 0; // Reset count

	PR3 = 31250; // Makes the period 200ms with a prescale of 1:256 
	T3CONSET = 0x70; // Set prescale value to 1:256
	IFSCLR(0) = T3IF; // Clear the flag
	IECSET(0) = T3IF; // Enable interrupt

	T3CONSET = 0x8000; // Start timer
}

void buzzer_on() {
	LATDSET = BUZZER_MASK;
}

void buzzer_off() {
	LATDCLR = BUZZER_MASK;
}

void buzzer_timed(uint32_t time_ms) {
	buzzer_counter = time_ms / 100;
	buzzer_on();
}

void buzzer_loop_update() {
	if (IFS(0) & T3IF) {
		IFSCLR(0) = T3IF;

		if (buzzer_counter > 0) {
			buzzer_counter--;

			if (buzzer_counter == 0) {
				buzzer_off();
				T3CON = 0x0;
			}
		}
	}
}
