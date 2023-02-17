/// @file lcd_utils.h
/// @brief Miscellaneous LCD utility functions

#ifndef __LCD_UTILS_H
#define __LCD_UTILS_H

#include <stdint.h>

/// @brief Converts 24 bit RGB to 5R-6G-5B 16 bit RGB
/// @param rgb 24 bit RGB color 0xRRGGBB
/// @return 16 bit RGB color
uint16_t rgb_24b_to_16b(uint32_t rgb);

/// @brief Converts 24 bit RGB to 5R-6G-5B 16 bit RGB
/// @param r 8-bit red color value
/// @param g 8-bit green color value
/// @param b 8-bit blue color value
/// @return 16 bit RGB color
uint16_t rgbarr_24b_to_16b(uint8_t r, uint8_t g, uint8_t b);

#endif