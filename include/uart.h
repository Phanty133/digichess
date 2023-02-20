/// @file uart.h
/// @brief UART functions and utilities

#ifndef __UART_H
#define __UART_H

#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include "sys_defines.h"
#include "delay.h"
#include "stringops.h"

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

/// @brief Writes an unsigned int to UART1
/// @param num Number to write 
/// @param terminate_line If 1, terminates with a CRLF
void uart_write_num(const uint32_t num, uint8_t terminate_line);

/// @brief Writes raw data to UART1 and terminates with a CRLF
/// @param data Data to be written
void uart_write_line(const char* data);

/// @brief If available, reads a byte from UART1
/// @return First byte from UART1
char uart_read_byte();

/// @brief Check whether data is available on UART1
/// @return True if data is available
bool uart_read_available();

#endif