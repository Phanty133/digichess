#ifndef __LCD_COMMS_H
#define __LCD_COMMS_H

#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include "bitops.h"
#include "drivers/ili9341/lcd_defines.h"

// 8080 MCU 8-bit bus interface Ⅱ

void lcd_set_bus_data(uint8_t data);

void lcd_write_strobe();
void lcd_write_command(uint8_t command);
void lcd_write_data(uint8_t data);
void lcd_write_register(uint8_t command, uint8_t* data, uint32_t dataSize);

void lcd_read_strobe();
void lcd_read_data(uint8_t command);

#endif