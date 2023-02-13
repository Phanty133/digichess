#include "memory.h"

void* memory_set(void* str, uint8_t c, uint32_t n) {
	for (int i = 0; i < n; i++) {
		*((uint8_t*)str + i) = c;
	}
}

void* memory_copy(void* dest, const void* src, uint32_t n) {
	for (int i = 0; i < n; i++) {
		*((uint8_t*)dest + i) = *((uint8_t*)src + i);
	}
}
