#ifndef __TTF_SCAN_H
#define __TTF_SCAN_H

#include "memory.h"
#include "math.h"
#include "bitmap.h"
#include "ttf/ttf_funcs.h"
#include "ttf/ttf_structs.h"

void gen_char_fill(
	Bitmap8* bitmap,
	const uint8_t* font,
	char charcode,
	float scale,
	int bitmap_offset_x,
	int bitmap_offset_y
);

void gen_char_outline(
	Bitmap8* bitmap,
	const uint8_t* font,
	char charcode,
	float scale,
	int bitmap_offset_x,
	int bitmap_offset_y
);

#endif