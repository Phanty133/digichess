#include "math.h"

#ifndef DISABLE_FONT_RENDERING
// Including the LUT here because it causes memory issues when 
// included in math.h for some reason
#include "lut/sqrt.lut.h"
#endif

int abs(int x) {
	return x < 0 ? -x : x;
}

float absf(float x) {
	return x < 0 ? -x : x;
}

int floor(float x) {
	int n = (int)x;
	float d = (float)x;

	if (d == x || x >= 0) {
		return d;
	}

	return d - 1;
}

int ceil(float x) {
	return floor(x) + 1;
}

float sqrtf_16b(int16_t x) {
	// Return NaN if x less than 0 or above the max value in the LUT
	if (x < 0 || x > 32767) return 0.0f / 0.0f;

#ifdef DISABLE_FONT_RENDERING
	return 0;
#else
	return SQRT_15BIT[x];
#endif
}

int pow(int x, uint32_t a) {
	if (a == 0) return 1;

	int cur_val = x;

	for (uint32_t i = 0; i < a - 1; i++) {
		cur_val *= x;
	}

	return cur_val;
}
