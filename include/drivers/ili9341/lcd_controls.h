/// @file lcd_controls.h
/// @brief LCD control functions

#ifndef __LCD_CONTROLS_H
#define __LCD_CONTROLS_H

#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include "drivers/ili9341/lcd_defines.h"
#include "drivers/ili9341/lcd_comms.h"
#include "delay.h"

/// @brief Pulls the CS pin LOW
void lcd_select();

/// @brief Pulls the CS pin HIGH
void lcd_deselect();

/// @brief Pulses the RST pin
void lcd_hw_reset();

/// @brief Sends a software reset command
void lcd_sw_reset();

/// @brief Enters sleep mode
void lcd_sleep_on();

/// @brief Exits sleep mode
void lcd_sleep_off();

/// @brief Re-enables the display
void lcd_display_on();

/// @brief Blanks the display
void lcd_display_off();

/// @brief Sets the orientation of the display
/// @param x The X draw direction. Values: 0, 1. Default: 1
/// @param y The Y draw direction Values: 0, 1. Default: 0
void lcd_set_orientation(uint8_t x, uint8_t y);

#endif