#include "uart.h"

void uart_begin(uint32_t baudrate) {
	// Set baudrate
	U1BRG = PBCLK_FREQ / (16 * baudrate) - 1;
	U1STASET = __UART_TXEN_MASK + __UART_RXEN_MASK;
	U1MODESET = __UART_ON_MASK;
}

void uart_end() {
	U1MODECLR = __UART_ON_MASK;
}

void uart_write(const char* data) {
	while (*data != '\0') {
		// Wait until transmit buffer empty
		// i.e. U1STA.UTXBF = 0
		while (U1STA & (1 << 9));

		U1TXREG = *data;
		++data;
	}
}

void uart_write_num(uint32_t num, uint8_t terminate_line) {
	char buf[16];
	num2char(num, buf, 16);

	if (terminate_line) {
		uart_write_line(buf);
	} else {
		uart_write(buf);
	}
}

void uart_write_line(const char* data) {
	uart_write(data);
	uart_write("\r\n");
}

bool uart_read_available() {
	return U1STA & __UART_DATAAVAIL_MASK;
}

char uart_read_byte() {
	if (!uart_read_available()) return '\0';

	return U1RXREG;
}
