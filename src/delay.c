#include "delay.h"

static uint32_t readCoreTimer() {
	volatile uint32_t timer;

	__asm__ volatile("mfc0 %0,$9" : "=r"(timer));

	return timer;
}

void delay_milli(uint32_t ms) {
	uint32_t startTimer = readCoreTimer();
	uint32_t waitCnt = ms * __SCALE_ms;

	while(readCoreTimer() - startTimer < waitCnt);
}

void delay_micro(uint32_t us) {
	uint32_t startTimer = readCoreTimer();
	uint32_t waitCnt = us * __SCALE_us;

	while(readCoreTimer() - startTimer < waitCnt);
}

void delay_100_nano(uint32_t ns){
	uint32_t startTimer = readCoreTimer();
	uint32_t waitCnt = ns * __SCALE_ns;

	while(readCoreTimer() - startTimer < waitCnt);
}
