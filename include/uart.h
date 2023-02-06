/// @file uart.h
/// @brief UART functions and utilities

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

/// @brief Initializes UART1
/// @param baudrate UART baudrate (Default: 115200)
void uart_begin(uint32_t baudrate);

/// @brief Stops UART1
void uart_end();

/// @brief Writes raw data to UART1
/// @param data Data to be written 
void uart_write(const char* data);

/// @brief Writes raw data to UART1 and terminates with a CRLF
/// @param data Data to be written
void uart_write_line(const char* data);

/// @brief If available, reads a byte from UART1
/// @return First byte from UART1
char uart_read_byte();

/// @brief Check whether data is available on UART1
/// @return True if data is available
bool uart_read_available();

/// @brief Converts num to char*. Here only because I couldn't get sprintf to compile
/// @param num Number to convert
/// @param buf Buffer to write to
/// @param bufsize Buffer size
void num2char(uint32_t num, char* buf, const uint32_t bufsize);

#endif