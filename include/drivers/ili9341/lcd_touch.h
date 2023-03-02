/// @file lcd_touch.h
/// @brief LCD Touchscreen functions and constants

#ifndef __LCD_TOUCH_H
#define __LCD_TOUCH_H

#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include "drivers/ili9341/lcd_defines.h"
#include "drivers/ili9341/lcd_comms.h"
#include "drivers/ili9341/lcd_setup.h"
#include "uart.h"

// Y+ - LCD_CS - A3 - Analog input
// Y- - LCD_D1 - Digital output
// X+ - LCD_D0 - Digital output
// X- - LCD_RS - A2 - Analog input

#define __TOUCH_YP_MASK __LCD_CS_MASK // Port B
#define __TOUCH_YM_MASK __LCD_D1_MASK // Port E
#define __TOUCH_XP_MASK __LCD_D0_MASK // Port E
#define __TOUCH_XM_MASK __LCD_DC_MASK // Port B

#define __TOUCH_XM_ADC (5 << 16)
#define __TOUCH_YP_ADC (9 << 16)

#define __TOUCH_X_RESISTANCE (348) // Resistance between X- and X+
#define __TOUCH_READ_DELAY 30 // microseconds
#define __TOUCH_SAMPLE_NOISE 4

#define __TOUCH_X_MIN (405)
#define __TOUCH_X_MAX (1010)
#define __TOUCH_X_DELTA (__TOUCH_X_MAX - __TOUCH_X_MIN)

#define __TOUCH_Y_MIN (325)
#define __TOUCH_Y_MAX (915)
#define __TOUCH_Y_DELTA (__TOUCH_Y_MAX - __TOUCH_Y_MIN)

#define __TOUCH_POLL_DELAY 1000

/// @brief Initializes the ADC for reading the touchscreen
void lcd_touch_init();

/// @brief Reset the pin I/O for use with the LCD
void lcd_touch_reset_pins();

/// @brief Read the raw X axis output
/// @param out_x Address to write the X value to
/// @return True if the X axis has a non-ambiguous value
bool lcd_touch_read_x(uint16_t* out_x);

/// @brief Read the raw Y axis output
/// @param out_y Address to write the Y value to
/// @return True if the Y axis has a non-ambiguous value
bool lcd_touch_read_y(uint16_t* out_y);

/// @brief Read the pressure applied. Kind of broken. Probably best if not used
/// @return Raw pressure applied
uint16_t lcd_touch_read_pressure(uint16_t x_val);

/// @brief Read the X and Y touch positions on the screen.
/// @brief The display must be selected with lcd_select() after read
/// @param out_x Address to write the X value to
/// @param out_y Address to write the Y value to
/// @param reset_pins If true, resets D0, D1, CS, and RS pins for use with the LCD
/// @return True if the screen is touched
bool lcd_touch_read_coords(
	uint16_t* out_x,
	uint16_t* out_y,
	bool reset_pins
);

/// @brief Read and write the touchscreen's raw X and Y axis outputs to UART every 100ms
void lcd_touch_debug_raw();

/// @brief Read and write the output of lcd_touch_read_coords() to UART every 100ms
void lcd_touch_debug_coords();

/// @brief Deselects the LCD after a delay period to make sure the touchscreen doesn't interfere
void lcd_touch_init_postdraw();

#endif