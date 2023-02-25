/// @file lcd_setup.h
/// @brief LCD setup functions - pin configuration and power up

#ifndef __LCD_SETUP_H
#define __LCD_SETUP_H

#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include "drivers/ili9341/lcd_defines.h"
#include "drivers/ili9341/lcd_controls.h"

#define LCD_X_ORIENTATION 1
#define LCD_Y_ORIENTATION 0

/// @brief Configures the display pins
void lcd_init_pins();

/// @brief Configures port B pins
void lcd_init_portb();

/// @brief Configures port D pins
void lcd_init_portd();

/// @brief Performs the power on sequence
void lcd_power_on();

/// @brief Sets the power settings when initializing
void lcd_set_settings();

/// @brief Fully initializes the display. The display must be selected with lcd_select() after initialization.
void lcd_init();

#endif