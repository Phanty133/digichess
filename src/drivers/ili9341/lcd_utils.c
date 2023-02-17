#include "drivers/ili9341/lcd_utils.h"

uint16_t rgb_24b_to_16b(uint32_t rgb) {
	return ((rgb & 0xf80000) >> 8) | ((rgb & 0xfc00) >> 5) | ((rgb & 0xf8) >> 3);
}

uint16_t rgbarr_24b_to_16b(uint8_t r, uint8_t g, uint8_t b) {
	return ((r & 0xf8) << 8) | ((g & 0xfc) << 3) | (b >> 3);
}
