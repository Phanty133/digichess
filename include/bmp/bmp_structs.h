/// @file bmp_structs.h
/// @brief BMP format data structures

#ifndef __BMP_STRUCTS_H
#define __BMP_STRUCTS_H

#include <stdint.h>

typedef enum {
	UNCOMPRESSED,
	RLE_4BIT,
	RLE_8BIT
} BMP_Compression;

typedef struct __attribute__((__packed__)) {
	uint16_t header; ///< Must be BM
	uint32_t file_size;
	uint16_t _reserved1;
	uint16_t _reserved2;
	uint32_t data_offset; ///< Offset to image data
} BMP_Header;

typedef struct __attribute__((__packed__)) {
	uint32_t header_size; ///< Must be 40
	int32_t width; ///< Bitmap width
	int32_t height; ///< Bitmap height
	uint16_t color_planes; ///< Must be 1
	uint16_t bpp; ///< Bits per pixel
	BMP_Compression compression : 32; ///< Compression method used
	uint32_t image_size; ///< Image data size
	int32_t h_res; ///< Horizontal resolution. Pixels per meter
	int32_t v_res; ///< Vertical resolution. Pixels per meter
	uint32_t num_colors; ///< Number of colors in palette. If 0, defaults to 2^bpp
	uint32_t important_colors; ///< Ignored
} BMP_InfoHeader;

typedef struct __attribute__((__packed__)) {
	uint8_t b;
	uint8_t g;
	uint8_t r;
	uint8_t _separator; ///< Always 0x00
} BMP_Color;

#endif