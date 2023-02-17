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
		uart_write_line("[WARNING] Uncompressed bitmaps with bpp > 8 unsupported");
		return;
	}

	const BMP_Color* color_table = bmp_get_color_table(file);
	const uint16_t color_table_size = bmp_get_color_table_size(file);
	const uint8_t* img_data = bmp_get_image_data(file);
	const uint32_t row_size = bmp_get_row_size(file);

	uint8_t pixels_per_byte = 8 / bpp;
	int w = info->width;
	int h = info->height;

	uint32_t cur_byte_index = 0;

	for (int y = 0; y < h; y++) {
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
	}
}

static void decode_rle(
	const uint8_t* file,
	void pixel_callback(uint32_t x, uint32_t y, BMP_Color color, void* context),
	void* callback_context
) {
	const BMP_InfoHeader* info = bmp_get_info(file);
	uint8_t bpp = info->bpp;
	BMP_Compression compression = bmp_get_compression(file);

	const BMP_Color* color_table = bmp_get_color_table(file);
	const uint16_t color_table_size = bmp_get_color_table_size(file);
	const uint8_t* img_data = bmp_get_image_data(file);
	const uint32_t row_size = bmp_get_row_size(file);

	int w = info->width;
	int h = info->height;
	int imgsize = info->image_size;

	uint8_t control_byte = 0;
	uint8_t param_byte = 0;

	// Not the prettiest code, but it seems to work fine, so ¯\_(ツ)_/¯

	for (int i = 0; i < imgsize; i += 2) {
		control_byte = img_data[i];
		param_byte = img_data[i + 1];

		if (control_byte == 0) {
			if (param_byte == 1) {
				// A goto outside of ASM. Dear god.
				goto end_of_bitmap;
			} else if (param_byte == 2) {
				// The position change command has 2 extra bytes
				i += 2;
			} else if (param_byte >= 3) {
				// Absolute mode

				uint32_t bytes_parsed;

				if (compression == RLE_4BIT) {
					for (int j = i + 2; j < i + 2 + param_byte / 2; j++) {
						uint8_t msb = (img_data[j] >> 4);
						uint8_t lsb = (img_data[j] & 0x0F);

						pixel_callback(0, 0, color_table[msb], callback_context);
						pixel_callback(0, 0, color_table[lsb], callback_context);
					}

					bytes_parsed = param_byte / 2;
				} else {
					for (int j = i + 2; j < i + 2 + param_byte; j++) {
						pixel_callback(0, 0, color_table[img_data[j]], callback_context);
					}

					bytes_parsed = param_byte;
				}

				// The absolute command is zero-padded to a 16-bit boundary
				uint8_t padding = bytes_parsed % 2;
				i += bytes_parsed + padding;
			}

			continue;
		}

		// Repeat index in param_byte

		if (compression == RLE_4BIT) {
			uint8_t msb = (param_byte >> 4);
			uint8_t lsb = (param_byte & 0x0F);

			for (int j = 0; j < control_byte; j++) {
				pixel_callback(0, 0, color_table[j % 2 == 0 ? msb : lsb], callback_context);
			}
		} else {
			for (int j = 0; j < control_byte; j++) {
				pixel_callback(0, 0, color_table[param_byte], callback_context);
			}
		}
	}
end_of_bitmap:
	return;
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
		case RLE_8BIT:
			decode_rle(file, pixel_callback, callback_context);
			break;
		default:
			uart_write_line("[WARNING] Unsupported BMP compression");
			break;
	}
}
