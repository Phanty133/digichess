#ifndef __LCD_CONTROLS_H
#define __LCD_CONTROLS_H

#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include "drivers/ili9341/lcd_defines.h"
#include "drivers/ili9341/lcd_comms.h"
#include "delay.h"

// Control the CS pin
void lcd_select();
void lcd_deselect();

// Reset
void lcd_hw_reset();
void lcd_sw_reset();

// Sleep
void lcd_sleep_on();
void lcd_sleep_off();

// Display control
void lcd_display_on();
void lcd_display_off();

#endif