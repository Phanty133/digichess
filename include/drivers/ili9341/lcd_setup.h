#ifndef __LCD_SETUP_H
#define __LCD_SETUP_H

#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include "drivers/ili9341/lcd_defines.h"
#include "drivers/ili9341/lcd_controls.h"

/// @brief Configures the display pins
void lcd_init_pins();

/// @brief Performs the power on sequence
void lcd_power_on();

/// @brief Sets the power settings when initializing
void lcd_set_settings();

/// @brief Fully initializes the display
void lcd_init();

#endif