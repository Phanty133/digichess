#include "buzzer.h"

void buzzer_init() {
	TRISDCLR = BUZZER_MASK;
}

void buzzer_on() {
	LATDSET = BUZZER_MASK;
}

void buzzer_off() {
	LATDCLR = BUZZER_MASK;
}