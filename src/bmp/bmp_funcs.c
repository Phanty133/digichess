#include "bmp/bmp_funcs.h"

const BMP_Header* bmp_get_header(const uint8_t* file) {
	return (BMP_Header*)file;
}

const BMP_InfoHeader* bmp_get_info(const uint8_t* file) {
	return (BMP_InfoHeader*)(file + sizeof(BMP_Header));
}

const uint32_t bmp_get_info_header_size(const uint8_t* file) {
	return bmp_get_info(file)->header_size;
}

const BMP_Color* bmp_get_color_table(const uint8_t* file) {
	return (BMP_Color*)(file + sizeof(BMP_Header) + bmp_get_info_header_size(file));
}

const uint16_t bmp_get_color_table_size(const uint8_t* file) {
	const BMP_InfoHeader* info = bmp_get_info(file);

	return info->num_colors == 0 ? powi(2, info->bpp) : info->num_colors;
}

const BMP_Compression bmp_get_compression(const uint8_t* file) {
	return bmp_get_info(file)->compression;
}

const uint32_t bmp_get_row_size(const uint8_t* file) {
	const BMP_InfoHeader* info = bmp_get_info(file);

	// The / 32 and * 4 are separate to make sure the inner fraction is floored correctly
	return ((info->bpp * info->width + 31) / 32) * 4;
}

const uint8_t* bmp_get_image_data(const uint8_t* file) {
	const BMP_Header* header = bmp_get_header(file);
	return file + header->data_offset;
}
