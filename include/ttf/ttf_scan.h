/// @file ttf_scan.h
/// @brief TTF Scan converter

#ifndef __TTF_SCAN_H
#define __TTF_SCAN_H

#include "memory.h"
#include "math.h"
#include "bitmap.h"
#include "ttf/ttf_funcs.h"
#include "ttf/ttf_structs.h"

/// @brief Generates a character on a bitmap
/// @param bitmap Bitmap to draw in. Must be allocated large enough for the character (ttf_get_char_dims())
/// @param font Font's TTF data to use
/// @param charcode Character to draw
/// @param scale FUnit to pixel scaling factor (ttf_get_scale())
/// @param bitmap_offset_x X offset in the bitmap
/// @param bitmap_offset_y Y offset in the bitmap
void gen_char_fill(
	Bitmap8* bitmap,
	const uint8_t* font,
	char charcode,
	float scale,
	int bitmap_offset_x,
	int bitmap_offset_y
);

/// @brief Marks a character's on-curve and control points on a bitmap
/// @param bitmap Bitmap to draw in. Must be allocated large enough for the character (ttf_get_char_dims())
/// @param font Font's TTF data to use
/// @param charcode Character to draw
/// @param scale FUnit to pixel scaling factor (ttf_get_scale())
/// @param bitmap_offset_x X offset in the bitmap
/// @param bitmap_offset_y Y offset in the bitmap
void gen_char_outline(
	Bitmap8* bitmap,
	const uint8_t* font,
	char charcode,
	float scale,
	int bitmap_offset_x,
	int bitmap_offset_y
);

#endif