#ifndef __UART_H
#define __UART_H

#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include "sys_defines.h"
#include "delay.h"

#define __UART_ON_MASK (1 << 15)
#define __UART_TXEN_MASK (1 << 10)
#define __UART_RXEN_MASK (1 << 12)

#define __UART_DATAAVAIL_MASK (1)

void uart_begin(uint32_t baudrate);
void uart_end();

void uart_write(const char* data);
void uart_write_line(const char* data);

char uart_read_byte();
bool uart_read_available();

// a very shitty int to char* function
// here only because i couldnt get sprintf to compile
void num2char(uint32_t num, char* buf, const uint32_t bufsize);

#endif