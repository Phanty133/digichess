#include "bmp/bmp_decode.h"

static uint8_t bpp_mask(uint8_t bpp, uint8_t shift) {
	switch (bpp) {
		case 1:
			return (0x01 << shift);
		case 2:
			return (0x03 << shift);
		case 4:
			return (0x0F << shift);
		case 8:
			return 0xFF;
	}
}

static void decode_uncompressed(
	const uint8_t* file,
	void pixel_callback(uint32_t x, uint32_t y, BMP_Color color, void* context),
	void* callback_context
) {
	const BMP_InfoHeader* info = bmp_get_info(file);
	uint8_t bpp = info->bpp;

	if (bpp >= 16) {
		// printf("Uncompressed bitmaps with bpp > 8 unsupported");
		return;
	}

	const BMP_Color* color_table = bmp_get_color_table(file);
	const uint16_t color_table_size = bmp_get_color_table_size(file);
	const uint8_t* img_data = bmp_get_image_data(file);
	const uint32_t row_size = bmp_get_row_size(file);

	uint8_t pixels_per_byte = 8 / bpp;
	int w = info->width;
	int h = info->height;

	// Images are stored bottom-to-top, left-to-right
	// Start in the bottom-left corner
	uint32_t cur_byte_index = row_size * (h - 1);

	for (int y = h - 1; y >= 0; y--) {
		uint8_t cur_byte = 0;

		for (int x = 0; x < w; x++) {
			uint8_t cur_byte_fraction = x % pixels_per_byte;

			if (cur_byte_fraction == 0) {
				cur_byte = img_data[cur_byte_index++];
			}

			uint8_t shift = bpp * (pixels_per_byte - cur_byte_fraction - 1);
			uint8_t mask = bpp_mask(bpp, shift);
			uint8_t pixel_index = ((cur_byte & mask) >> shift);

			pixel_callback(x, y, color_table[pixel_index], callback_context);
		}

		uint8_t row_padding = row_size - cur_byte_index % row_size;
		cur_byte_index += row_padding;
		cur_byte_index -= row_size * 2;
	}
}

static void decode_rle4(
	const uint8_t* file,
	void pixel_callback(uint32_t x, uint32_t y, BMP_Color color, void* context),
	void* callback_context
) {

}

static void decode_rle8(
	const uint8_t* file,
	void pixel_callback(uint32_t x, uint32_t y, BMP_Color color, void* context),
	void* callback_context
) {

}

void bmp_decode(
	const uint8_t* file,
	void pixel_callback(uint32_t x, uint32_t y, BMP_Color color, void* context),
	void* callback_context
) {
	const BMP_InfoHeader* info = bmp_get_info(file);

	switch (info->compression) {
		case UNCOMPRESSED:
			decode_uncompressed(file, pixel_callback, callback_context);
			break;
		case RLE_4BIT:
			decode_rle4(file, pixel_callback, callback_context);
			break;
		case RLE_8BIT:
			decode_rle8(file, pixel_callback, callback_context);
			break;
	}
}
