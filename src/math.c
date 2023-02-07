#include "math.h"

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
