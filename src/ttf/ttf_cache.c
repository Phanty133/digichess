#include "ttf/ttf_cache.h"

// static TTF_CacheEntry create_cache_entry(uint16_t font_size) {
// 	TTF_CacheEntry entry;
// 	entry.font_size_pt = font_size;
// 	entry.char_count = CACHE_CHAR_COUNT;
// 	entry.ascii_offset = CACHE_ASCII_OFFSET;
	
// 	for (int i = 0; i < CACHE_CHAR_COUNT; i++) {
// 		entry.bitmaps[i].data = 0;
// 	}

// 	return entry;
// }

// TODO: Implement binary search?
static TTF_CacheEntry* get_font_size_entry(TTF_Cache* cache, uint16_t font_size) {
	for (int i = 0; i < cache->font_size_count; i++) {
		if (cache->entries[i].font_size_pt == font_size) return &cache->entries[i];
	}

	return 0;
}

// TODO: Implement run-length encoding
// static TTF_CachedBitmap compress_bitmap(Bitmap8* bitmap) {
// 	TTF_CachedBitmap bitmap_entry;
	
// 	int bitmap_size = bitmap->width * bitmap->height;
// 	int size_multiple = bitmap_size % 8;

// 	bitmap_entry.end_padding = size_multiple == 0 ? 0 : 8 - size_multiple;
// 	bitmap_entry.data_size = (bitmap_size + bitmap_entry.end_padding) / 8;
// 	bitmap_entry.data = calloc(bitmap_entry.data_size, 1);

// 	bitmap_entry.width = bitmap->width;
// 	bitmap_entry.height = bitmap->height;

// 	uint8_t cur_byte = 0;
// 	uint8_t cur_bit = 7;
// 	int cur_byte_index = 0;

// 	for (int y = 0; y < bitmap->height; y++) {
// 		for (int x = 0; x < bitmap->width; x++) {
// 			uint8_t pixel = bitmap->data[y * bitmap->width + x];

// 			cur_byte += (pixel << cur_bit);

// 			if (cur_bit-- == 0) {
// 				bitmap_entry.data[cur_byte_index++] = cur_byte;
// 				cur_byte = 0;
// 				cur_bit = 7;
// 			}
// 		}
// 	}

// 	// Add the unfinished byte
// 	if (cur_byte != 0) {
// 		bitmap_entry.data[cur_byte_index] = cur_byte;
// 	}

// 	return bitmap_entry;
// }

// static Bitmap8 decompress_bitmap(TTF_CachedBitmap* cached_bitmap) {
// 	Bitmap8 bitmap;
// 	bitmap.width = cached_bitmap->width;
// 	bitmap.height = cached_bitmap->height;
	
// 	alloc_bitmap(&bitmap);

// 	uint8_t cur_byte = cached_bitmap->data[0];
// 	uint8_t cur_bit = 7;
// 	int cur_byte_index = 0;

// 	for (int y = 0; y < bitmap.height; y++) {
// 		for (int x = 0; x < bitmap.width; x++) {
// 			// TODO: Replace with get_bit from bitops.h when moved to actual project
// 			bitmap.data[y * bitmap.width + x] = ((cur_byte & (1 << cur_bit)) >> cur_bit);

// 			if (cur_bit-- == 0) {
// 				cur_byte = cached_bitmap->data[++cur_byte_index];
// 				cur_bit = 7;
// 			}
// 		}
// 	}

// 	return bitmap;
// }

static uint32_t get_entry_char_index(TTF_CacheEntry* entry, char charcode) {
	return charcode - entry->ascii_offset;
}

static TTF_CachedBitmap* get_cached_char(TTF_Cache* cache, char charcode, uint16_t font_size) {
	TTF_CacheEntry* font_entry = get_font_size_entry(cache, font_size);
	uint32_t char_index = get_entry_char_index(font_entry, charcode);

	return &(font_entry->bitmaps[char_index]);
}

// TTF_Cache* ttf_create_cache(uint16_t font_sizes[], uint32_t size_count) {
// 	TTF_Cache* cache = malloc(sizeof(uint32_t) + sizeof(TTF_CacheEntry) * size_count);
// 	cache->font_size_count = size_count;

// 	for (int i = 0; i < size_count; i++) {
// 		cache->entries[i] = create_cache_entry(font_sizes[i]);
// 	}

// 	return cache;
// }

// void ttf_cache_add(
// 	TTF_Cache* cache,
// 	char charcode,
// 	uint16_t font_size,
// 	Bitmap8* bitmap
// ) {
// 	TTF_CacheEntry* entry = get_font_size_entry(cache, font_size);

// 	// If the font size isn't allocated, don't add the character
// 	if (entry == 0) return;

// 	uint32_t index = get_entry_char_index(entry, charcode);
// 	entry->bitmaps[index] = compress_bitmap(bitmap);
// }

void ttf_cache_clear(TTF_Cache* cache) {
	// TODO: Implement
}

uint8_t ttf_cache_contains(TTF_Cache* cache, char charcode, uint16_t font_size) {
	return get_cached_char(cache, charcode, font_size)->data != 0;
}

void ttf_cache_get_dims(
	TTF_Cache* cache,
	char charcode,
	uint16_t font_size,
	uint16_t* out_width,
	uint16_t* out_height
) {
	TTF_CachedBitmap* cached_char = get_cached_char(cache, charcode, font_size);

	*out_width = cached_char->width;
	*out_height = cached_char->height;
}

// Bitmap8 ttf_cache_get_bitmap(
// 	TTF_Cache* cache,
// 	char charcode,
// 	uint16_t font_size
// ) {
// 	TTF_CachedBitmap* cached_char = get_cached_char(cache, charcode, font_size);
// 	return decompress_bitmap(cached_char);
// }
