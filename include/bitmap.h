#ifndef __BITMAP_H
#define __BITMAP_H

#include <stdint.h>
#include "memory.h"

/// @struct Bitmap8
/// @brief Bitmap with 8 bit pixel data
typedef struct {
	uint16_t width; ///< Pixel width of the bitmap
	uint16_t height; ///< Pixel height of the bitmap

	uint8_t* data; ///< Pixel data array of size width * height
} Bitmap8;

/// @brief Clear a bitmap to zeros
/// @param bitmap Bitmap to clear
void bitmap_clear(Bitmap8* bitmap);

/// @brief Copy bitmap image data from src to dest
/// @param dest Destination
/// @param src Source
/// @param offset_x X offset in destination
/// @param offset_y Y offset in destination
void bitmap_combine(Bitmap8* dest, Bitmap8* src, uint32_t offset_x, uint32_t offset_y);

uint8_t bitmap_get_pixel(Bitmap8* bitmap, uint16_t x, uint16_t y);

/// @brief Rotates the bitmap in src by 90 degrees clockwise and stores it in dest
/// @param src Source
/// @param desr Destination. Must be large enough to store a rotated 90deg src
void bitmap_rotate90(Bitmap8* dest, Bitmap8* src);

#endif