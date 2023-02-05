#ifndef __LCD_TOUCH_H
#define __LCD_TOUCH_H

#include <pic32mx.h>
#include <stdint.h>
#include <stdbool.h>
#include "drivers/ili9341/lcd_defines.h"
#include "uart.h"

// Y+ - LCD_CS - A3 - Analog input
// Y- - LCD_D1 - Digital output
// X+ - LCD_D0 - Digital output
// X- - LCD_RS - A2 - Analog input

#define __TOUCH_YP_MASK (1 << 10) // Port B
#define __TOUCH_YM_MASK (1 << 3) // Port D
#define __TOUCH_XP_MASK (1 << 10) // Port D
#define __TOUCH_XM_MASK (1 << 8) // Port B

#define __TOUCH_X_RESISTANCE (348) // Resistance between X- and X+

#define __TOUCH_X_MIN (396)
#define __TOUCH_X_MAX (1010)
#define __TOUCH_X_DELTA (__TOUCH_X_MAX - __TOUCH_X_MIN)

#define __TOUCH_Y_MIN (320)
#define __TOUCH_Y_MAX (930)
#define __TOUCH_Y_DELTA (__TOUCH_Y_MAX - __TOUCH_Y_MIN)

/// @brief Initializes the ADC for reading the touchscreen
void lcd_touch_init();

/// @brief Reset the pin I/O for use with the LCD
void lcd_touch_reset_pins();


bool lcd_touch_read_x(uint16_t* outX);

/// @brief Read the raw Y axis output
/// @return Raw Y output
bool lcd_touch_read_y(uint16_t* outY);

/// @brief Read the pressure applied. Kind of broken. Probably best if not used
/// @return Raw pressure applied
uint16_t lcd_touch_read_pressure(uint16_t x_val);

/// @brief Read the X and Y touch positions on the screen
/// @return True if the screen is touched, False if not touched
bool lcd_touch_read_coords(
	uint16_t screenWidth,
	uint16_t screenHeight,
	uint16_t* outX,
	uint16_t* outY,
	bool resetPins
);

/// @brief Read and write the touchscreen's raw X and Y axis outputs to UART every 100ms
void lcd_touch_debug_raw();

/// @brief Read and write the output of lcd_touch_read_coords to UART every 100ms
void lcd_touch_debug_coords();

#endif