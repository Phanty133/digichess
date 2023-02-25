/* stubs.c
 * This file written 2015 by Axel Isaksson
 * This copyright notice added 2015 by F Lundevall

 * For copyright and licensing, see file COPYING */

#include <pic32mx.h>
#include "uart.h"

/* Non-Maskable Interrupt; something bad likely happened, so hang */
void _nmi_handler() {
	// volatile int cause;
	// __asm__ volatile("mfc0 %0, $13" : "=r"(cause));

	// char buf[32];
	// num2char(cause, buf, 32);

	// uart_write("EXCEPTION CAUSE: ");
	// uart_write_line(buf);

	for(;;);
}

/* This function is called upon reset, before .data and .bss is set up */
void _on_reset() {
	
}

/* This function is called before main() is called, you can do setup here */
void _on_bootstrap() {
	
}
