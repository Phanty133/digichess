#include "math.h"

// Including the LUT here because it causes memory issues when 
// included in math.h for some reason
#include "lut/sqrt.lut.h"

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
	// Return NaN if x less than 0
	if (x < 0) return 0.0f / 0.0f;

	return SQRT_15BIT[x];
}
