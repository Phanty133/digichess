#include "bitmap.h"

void bitmap_clear(Bitmap8* bitmap) {
	memory_set(bitmap->data, 0, bitmap->height * bitmap->width);
}

void bitmap_combine(Bitmap8* dest, Bitmap8* src, uint32_t offset_x, uint32_t offset_y) {
	for (int y = 0; y < src->height; y++) {
		for (int x = 0; x < src->width; x++) {
			int src_index = y * src->width + x;
			int dest_index = (y + offset_y) * dest->width + x + offset_x;

			dest->data[dest_index] = src->data[src_index];
		}
	}
}

uint8_t bitmap8_get_pixel(Bitmap8* bitmap, uint16_t x, uint16_t y) {
	if ((x < 0 || x >= bitmap->width)
		|| (y < 0 || y >= bitmap->height)
	) return 0;

	return bitmap->data[y * bitmap->width + x];
}

void bitmap8_set_pixel(Bitmap8* bitmap, uint16_t x, uint16_t y, uint8_t value) {
	if ((x < 0 || x >= bitmap->width)
		|| (y < 0 || y >= bitmap->height)
	) return;

	bitmap->data[y * bitmap->width + x] = value;
}

void bitmap_rotate90(Bitmap8* dest, Bitmap8* src) {
	for (uint16_t y = 0; y < src->height; y++) {
		for (uint16_t x = 0; x < src->width; x++) {
			// x becomes y in the dest
			// y becomes x in the dest and counted in reverse

			dest->data[x * dest->width + (dest->width - y)] = src->data[y * src->width + x];
		}
	}
}
