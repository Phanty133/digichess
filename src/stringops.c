#include "stringops.h"

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