#include <pic32mx.h>
#include <stdint.h>
#include "TestStruct.h"

void delay(void);

int main(void) {
	TestStruct led;
	led.pin = 6; // LED4 is on G6
	led.delays = 5;

	// 0b1111 1111 1011 1111
	TRISG = 0xFFFF - (1 << led.pin);

	LATG = 1 << led.pin;

	for (int i = 0; i < led.delays; i++) {
		delay();
	}

	LATGINV = 1 << led.pin;

	return 0;
}

void delay(void) {
	int j;

	for (j=0; j<1000000; j++) {}
}