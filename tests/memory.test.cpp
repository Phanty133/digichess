#include "gtest/gtest.h"

extern "C" {
	#include "../include/memory.h"
}

TEST(Memory, memory_set) {
	int a = 69;

	memory_set(&a, 0, sizeof(int));

	EXPECT_EQ(a, 0);
}

TEST(Memory, memory_copy) {
	int a = 69;
	int b = 0;

	memory_copy(&b, &a, sizeof(int));

	EXPECT_EQ(b, a);
}
