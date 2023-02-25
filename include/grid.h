/// @file grid.h
/// @brief Chessboard grid functions

#ifndef __GRID_H
#define __GRID_H

#define MUX_R0_PIN (10)
#define MUX_R1_PIN (9)
#define MUX_R2_PIN (2)
#define MUX_C0_PIN (1)
#define MUX_C1_PIN (3)
#define MUX_C2_PIN (8)

#define MUX_R0_MASK (1 << MUX_R0_PIN)
#define MUX_R1_MASK (1 << MUX_R1_PIN)
#define MUX_R2_MASK (1 << MUX_R2_PIN)
#define MUX_C0_MASK (1 << MUX_C0_PIN)
#define MUX_C1_MASK (1 << MUX_C1_PIN)
#define MUX_C2_MASK (1 << MUX_C2_PIN)

#define MUX_OUT_PIN (1)
#define MUX_OUT_MASK (1 << MUX_OUT_PIN)

#define GRID_LEDS_PER_SQUARE (3)
#define GRID_LED_COUNT (16 * GRID_LEDS_PER_SQUARE)
#define GRID_LED_PIN 69 // TODO: Make it actually use this pin

#include <pic32mx.h>
#include <stdint.h>
#include "bitops.h"
#include "drivers/ws2812b/ws2812b.h"

/// @brief Initializes the grid square sensors, muxes, and LEDs
void grid_init();

/// @brief Read a grid square
/// @param row Grid row (0-indexed)
/// @param col Grid column (0-indexed)
/// @return 1 if a magnet is on the square, 0 otherwise
uint8_t grid_read_square(uint8_t row, uint8_t col);

/// @brief Sets the LED color of a square
/// @param row Grid row (0-indexed)
/// @param col Grid column (0-indexed)
/// @param color 24bit RGB color
/// @param display If 1, updates the LEDs immediately
void grid_set_color(uint8_t row, uint8_t col, uint32_t color, uint8_t display);

uint8_t* grid_get_led_data();

#endif