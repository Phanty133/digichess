/// @file lcd_comms.h
/// @brief LCD data bus functions

#ifndef __LCD_COMMS_H
#define __LCD_COMMS_H

#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include "bitops.h"
#include "delay.h"
#include "drivers/ili9341/lcd_defines.h"

// 8080 MCU 8-bit bus interface Ⅱ

/// @brief Sets the D0-D7 bits of the LCD bus
/// @param data Data byte
void lcd_set_bus_data(uint8_t data);

/// @brief Pulses the WRX signal
void lcd_write_strobe();

/// @brief Writes a command to the display (D/C LOW)
/// @param command Command byte
void lcd_write_command(uint8_t command);

/// @brief Writes frame data or command paramter to the display (D/C HIGH)
/// @param data Data byte
void lcd_write_data(uint8_t data);

/// @brief Writes a command and parameters to the LCD
/// @param command Command byte
/// @param data Data bytes
/// @param dataSize Number of data bytes
void lcd_write_register(uint8_t command, uint8_t* data, uint32_t dataSize);

/// @brief Pulses the RDX signal
void lcd_read_strobe();

/// @brief [NYI] Reads data from the display
void lcd_read_data(uint8_t command);

#endif