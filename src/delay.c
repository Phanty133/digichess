#include "delay.h"

static uint32_t read_core_timer() {
	volatile uint32_t timer;

	__asm__ volatile("mfc0 %0,$9" : "=r"(timer));

	return timer;
}

void delay_milli(uint32_t ms) {
	uint32_t startTimer = read_core_timer();
	uint32_t waitCnt = ms * __SCALE_ms;

	while(read_core_timer() - startTimer < waitCnt);
}

void delay_micro(uint32_t us) {
	uint32_t startTimer = read_core_timer();
	uint32_t waitCnt = us * __SCALE_us;

	while(read_core_timer() - startTimer < waitCnt);
}
