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

#define GRID_ROWS (8)
#define GRID_COLS (8)

#define GRID_LEDS_PER_SQUARE (3)
#define GRID_LED_COUNT (GRID_ROWS * GRID_COLS * GRID_LEDS_PER_SQUARE)

#define GRID_POWER_MASK (1 << 1)
#define GRID_OFF_TIME (3000) // Must be a multiple of 200ms
#define GRID_ON_TIME (30)

#define __GRID_OFF_PERIODS (GRID_OFF_TIME / 200)

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

/// @brief Get the raw grid LED data.
/// @return LED data array
uint8_t* grid_get_led_data();

/// @brief Blocking sensor power-cycle.
void grid_reset_sensors();

/// @brief Reads the sensors and updates grid data.
void grid_update_state();

/// @brief Get the grid state as of the last update
/// @return 2D array [Rows][Cols] of grid squares. 1 if magnet on the square, 0 otherwise.
uint8_t* grid_get_state();

/// @brief Should be called every loop cycle
void grid_loop_update();

#endif