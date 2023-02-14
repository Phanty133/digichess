#ifndef __MATH_H
#define __MATH_H

#include <stdint.h>

/// @brief Returns an integer absolute value
/// @param x
/// @return |x|
int abs(int x);

/// @brief Returns a float absolute value
/// @param x 
/// @return |x|
float absf(float x);

/// @brief Floors the x float value
/// @param x 
/// @return Floored x as integer
int floor(float x);

/// @brief Ceils the x float value
/// @param x 
/// @return Ceiled x as integer
int ceil(float x);

/// @brief Use a lookup table to get the square root of an integer up to 32767 (including)
/// @param x 
/// @return sqrt(x) if 0 <= x <= 32767. NaN otherwise
float sqrtf_16b(int16_t x);

#endif