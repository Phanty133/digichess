/// @file bmp_decode.h
/// @brief Functions for decoding BMP image data

#ifndef __BMP_DECODE_H
#define __BMP_DECODE_H

#include <stdint.h>
#include "bmp_structs.h"
#include "bmp_funcs.h"

void bmp_decode(
	const uint8_t* file,
	void pixel_callback(uint32_t x, uint32_t y, BMP_Color color, void* context),
	void* callback_context
);

#endif
