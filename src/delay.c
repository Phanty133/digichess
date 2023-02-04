#include "delay.h"

static uint32_t readCoreTimer() {
	volatile uint32_t timer;

	__asm__ volatile("mfc0 %0,$9" : "=r"(timer));

	return timer;
}

void delayMilli(uint32_t ms) {
	uint32_t startTimer = readCoreTimer();
	uint32_t waitCnt = ms * __SCALE_ms;

	while(readCoreTimer() - startTimer < waitCnt);
}

void delayMicro(uint32_t us) {
	uint32_t startTimer = readCoreTimer();
	uint32_t waitCnt = us * __SCALE_us;

	while(readCoreTimer() - startTimer < waitCnt);
}