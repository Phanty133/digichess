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
void draw_char_fill(
	Bitmap8* bitmap,
	const uint8_t* font,
	char charcode,
	float scale,
	int bitmap_offset_x,
	int bitmap_offset_y
);

/// @brief Calculates a character's fill and sends the data to the respective callbacks
/// @param pixel_fg Callback for a foreground pixel
/// @param pixel_bg Callback for a background pixel
/// @param callback_context A pointer that gets passed to the callbacks
/// @param font Font's TTF data to use
/// @param charcode Character to draw
/// @param scale FUnit to pixel scaling factor (ttf_get_scale())
/// @param bitmap_offset_x X offset in the bitmap
/// @param bitmap_offset_y Y offset in the bitmap
void gen_char_fill(
	void pixel_fg(int16_t x, int16_t y, void* context),
	void pixel_bg(int16_t x, int16_t y, void* context),
	void* callback_context,
	const uint8_t* font,
	char charcode,
	float scale
);

/// @brief [Probably broken] Marks a character's on-curve and control points on a bitmap
/// @param bitmap Bitmap to draw in. Must be allocated large enough for the character (ttf_get_char_dims())
/// @param font Font's TTF data to use
/// @param charcode Character to draw
/// @param scale FUnit to pixel scaling factor (ttf_get_scale())
/// @param bitmap_offset_x X offset in the bitmap
/// @param bitmap_offset_y Y offset in the bitmap
void draw_char_outline(
	Bitmap8* bitmap,
	const uint8_t* font,
	char charcode,
	float scale,
	int bitmap_offset_x,
	int bitmap_offset_y
);

#endif