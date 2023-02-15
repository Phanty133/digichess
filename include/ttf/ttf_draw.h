/// @file ttf_draw.h
/// @brief End-user TTF drawing functions

#ifndef __TTF_DRAW_H
#define __TTF_DRAW_H

#include <stdio.h>
#include "ttf/ttf_scan.h"
#include "ttf/ttf_structs.h"
#include "ttf/ttf_funcs.h"
#include "ttf/ttf_cache.h"

/// @brief Generates the bitmap for a character
/// @param bitmap Bitmap to draw to. Must be allocated large enough for the character
/// @param font The TTF font to use
/// @param charcode The character to generate
/// @param font_size_pt Font size to generate, in pt
/// @param display_ppi Display's pixel density in pixels per inch (dpi)
void ttf_draw_char_bitmap(
	Bitmap8* bitmap,
	const uint8_t* font,
	char charcode,
	uint16_t font_size_pt,
	uint16_t display_ppi
);

/// @brief Retrieves the bitmap for a character from cache.
/// @brief If the character doesn't exist in cache, but memory is allocated
/// @brief for the font size, generates the bitmap and stores it in cache
/// @param bitmap Bitmap to draw to. Must be allocated large enough.
/// @param font The TTF font to use
/// @param cache The TTF cache for the font
/// @param charcode The character to generate
/// @param font_size_pt The font size to generate, in pt
/// @param display_ppi Display's pixel density in pixels per inch (dpi)
void ttf_get_char_bitmap_cached(
	Bitmap8* bitmap,
	const uint8_t* font,
	TTF_Cache* cache,
	char charcode,
	uint16_t font_size_pt,
	uint16_t display_ppi
);

/// @brief Draws text onto a bitmap
/// @param bitmap Bitmap to draw to. Must be allocated large enough.
/// @param font The TTF font to use
/// @param cache The TTF cache for the font
/// @param string String to write
/// @param font_size_pt The font size to generate, in pt
/// @param display_ppi Display's pixel density in pixels per inch (dpi)
void ttf_draw_text(
	Bitmap8* bitmap,
	const uint8_t* font,
	// TTF_Cache* cache,
	char* string,
	uint16_t font_size_pt,
	uint16_t display_ppi
);

#endif