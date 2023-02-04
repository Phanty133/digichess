#include "drivers/ili9341/lcd_utils.h"

uint16_t rgb_24b_to_16b(uint32_t rgb) {
	uint8_t r = (rgb & 0xFF0000) >> 16;
	uint8_t g = (rgb & 0x00FF00) >> 8;
	uint8_t b = (rgb & 0x0000FF);

	uint8_t r_5bit = r / 8;
	uint8_t g_6bit = g / 4;
	uint8_t b_5bit = b / 8;

	return (r_5bit << 11) + (g_6bit << 5) + b_5bit;
}
