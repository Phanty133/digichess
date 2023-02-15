#include "ttf/ttf_draw.h"

void ttf_draw_char_bitmap(
	Bitmap8* bitmap,
	const uint8_t* font,
	char charcode,
	uint16_t font_size_pt,
	uint16_t display_ppi
) {
	float scale = ttf_get_scale(font, font_size_pt, display_ppi);
	TTF_CharDims dims = ttf_get_char_dims_scaled(font, charcode, scale);

	bitmap_clear(bitmap);

	if (charcode != ' ') {
		draw_char_fill(bitmap, font, charcode, scale, 0, dims.y);
	}
}

// Bitmap8 ttf_get_char_bitmap_cached(
// 	const uint8_t* font,
// 	TTF_Cache* cache,
// 	char charcode,
// 	uint16_t font_size_pt,
// 	uint16_t display_ppi
// ) {
// 	Bitmap8 bitmap;

// 	if (ttf_cache_contains(cache, charcode, font_size_pt)) {
// 		bitmap = ttf_cache_get_bitmap(cache, charcode, font_size_pt);
// 	} else {
// 		bitmap = ttf_gen_char_bitmap(font, charcode, font_size_pt, display_ppi);

// 		ttf_cache_add(cache, charcode, font_size_pt, &bitmap);
// 	}

// 	return bitmap;
// }

void ttf_draw_text(
	Bitmap8* bitmap,
	const uint8_t* font,
	// TTF_Cache* cache,
	char* string,
	uint16_t font_size_pt,
	uint16_t display_ppi
) {
	float scale = ttf_get_scale(font, font_size_pt, display_ppi);

	// Count the characters
	int count = 0;
	while (string[count++] != '\0');
	count -= 1;

	TTF_CharDims dims[count];

	int16_t max_y = 0;
	int16_t min_y = 0;

	for (int i = 0; i < count; i++) {
		char c = string[i];
		dims[i] = ttf_get_char_dims_scaled(font, c, scale);

		// string_bitmap.width += dims[i].advance_width;

		// Make sure the bitmap is big enough for the tallest letter
		if (dims[i].y < min_y) min_y = dims[i].y;
		if (dims[i].max_y > max_y) max_y = dims[i].max_y;
	}

	// string_bitmap.height = max_y - min_y;
	int16_t line_offset = max_y;

	int x_offset = 0;

	for (int i = 0; i < count; i++) {
		char c = string[i];

		Bitmap8 char_bitmap;
		char_bitmap.width = dims[i].advance_width;
		char_bitmap.height = dims[i].height;
		
		uint8_t bitmap_data[char_bitmap.width * char_bitmap.height];
		char_bitmap.data = bitmap_data;

		bitmap_clear(&char_bitmap);
		// Bitmap8 char_bitmap = ttf_get_char_bitmap_cached(font, cache, c, font_size_pt, display_ppi);
		ttf_draw_char_bitmap(&char_bitmap, font, c, font_size_pt, display_ppi);

		bitmap_combine(
			bitmap,
			&char_bitmap,
			x_offset,
			line_offset - dims[i].y - dims[i].height
		);

		x_offset += dims[i].advance_width;
	}
}
