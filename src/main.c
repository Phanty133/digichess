#include <pic32mx.h>
#include <stdint.h>
#include "uart.h"
#include "drivers/ili9341/lcd_setup.h"
#include "drivers/ili9341/lcd_tests.h"

int main() {
	uart_begin(115200);
	lcd_init();
	lcd_select();

	lcd_test_all();

	return 0;
}
