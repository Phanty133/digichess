#include <pic32mx.h>
#include <stdint.h>
#include "uart.h"
#include "drivers/ili9341/lcd_setup.h"
#include "drivers/ili9341/lcd_tests.h"
#include "delay.h"

void setup() {
	uart_begin(115200);
	lcd_init();
	lcd_select();

	lcd_test_all();
}

void loop() {
	uart_write_line("Hello world!");
	delay_milli(1000);
}

int main() {
	setup();
	while (1) loop();

	return 0;
}
