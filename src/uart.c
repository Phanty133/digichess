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

void num2char(uint32_t num, char* buf, const uint32_t bufsize) {
	if (num == 0) {
		buf[0] = '0';
		buf[1] = '\0';
		return;
	}
	
	int digit;
	int n = 0;

	char tempbuf[bufsize];

	while (num > 0) {
		digit = num % 10;
		tempbuf[n++] = digit + '0';

		num /= 10;
	}

	for (int i = 0; i < n; i++) {
		buf[i] = tempbuf[n - i - 1];
	}

	buf[n] = '\0';
}
