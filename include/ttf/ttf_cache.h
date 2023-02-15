/// @file ttf_cache.h
/// @brief [NYI] TTF glyph caching

#ifndef __TTF_CACHE_H
#define __TTF_CACHE_H

#include <stdint.h>
#include "memory.h"
#include "bitmap.h"

#define CACHE_CHAR_COUNT 94
#define CACHE_ASCII_OFFSET 32

/// @brief A cached bitmap of a single character.
typedef struct {
	uint16_t width; // Bitmap8 width
	uint16_t height; // Bitmap8 height

	// How many additional bits were added to pad the data to a multiple of 8
	uint16_t end_padding;

	// Size of the data byte array.
	uint16_t data_size;

	// Row-wise compressed data of the bitmap.
	// Every bit corresponds to a pixel on/off state, except for the padded bits
	// The data is continuous with padding added at the end to fit to 8 bits
	// If not cached, pointer is null
	uint8_t* data;
} TTF_CachedBitmap;

/// @brief A TTF cache entry corresponding to a single font and font size
typedef struct {
	uint16_t font_size_pt; // The font size corresponding to the cache entry
	uint16_t char_count; // How many characters have memory reserved

	// Offset for ascii charcodes that correspond to indices in the bitmaps array
	uint16_t ascii_offset;

	// An array of cached bitmaps of size char_count
	// If the element corresponding to the charcode is null, then the
	// character hasn't been cached yet
	TTF_CachedBitmap bitmaps[CACHE_CHAR_COUNT];
} TTF_CacheEntry;

typedef struct {
	uint32_t font_size_count;
	TTF_CacheEntry entries[]; // Size of array is font_size_count
} TTF_Cache;

/// @brief Initializes a TTF cache
/// @param font_sizes An array of font sizes to cache
/// @param size_count Number of font sizes in the font_sizes array
/// @return Heap-allocated pointer to the TTF cache
TTF_Cache* ttf_create_cache(uint16_t font_sizes[], uint32_t size_count);

/// @brief Adds a character to the cache
/// @param cache The TTF cache
/// @param charcode Character to add
/// @param font_size Font size of the character
/// @param bitmap Bitmap8 of the character
void ttf_cache_add(
	TTF_Cache* cache,
	char charcode,
	uint16_t font_size,
	Bitmap8* bitmap
);

/// @brief [NYI] Clears the cache
/// @param cache The TTF cache to clear
void ttf_cache_clear(TTF_Cache* cache);

/// @brief Checks if a character bitmap is cached
/// @param charcode Character to check
/// @param font_size Font size to check
/// @return 1 if the character is cached, 0 otherwise
uint8_t ttf_cache_contains(
	TTF_Cache* cache,
	char charcode,
	uint16_t font_size
);

/// @brief Returns the bitmap dimensions of a cached character
/// @param cache The TTF cache
/// @param charcode Character to retrieve
/// @param font_size Character font size to retrieve
/// @param out_width Pointer to write the width to
/// @param out_height Pointer to write the height to
void ttf_cache_get_dims(
	TTF_Cache* cache,
	char charcode,
	uint16_t font_size,
	uint16_t* out_width,
	uint16_t* out_height
);

/// @brief Retrieves the cached bitmap of a character
/// @param cache The TTF cache
/// @param charcode Character to retrieve
/// @param font_size Font size to retrieve
/// @return Bitmap8 of the character
Bitmap8 ttf_cache_get_bitmap(
	TTF_Cache* cache,
	char charcode,
	uint16_t font_size
);

#endif