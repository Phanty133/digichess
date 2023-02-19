#include "gtest/gtest.h"

extern "C" {
	#include "../include/math.h"
}

TEST(Math, absi) {
	EXPECT_EQ(absi(-1), 1);
	EXPECT_EQ(absi(1), 1);
	EXPECT_EQ(absi(0), 0);
	EXPECT_EQ(absi(3.2), 3);
	EXPECT_EQ(absi(-2.1), 2);
}

TEST(Math, absf) {
	EXPECT_EQ(absf(3.2f), 3.2f);
	EXPECT_EQ(absf(-2.1f), 2.1f);
	EXPECT_EQ(absf(0), 0);
	EXPECT_EQ(absf(-1.0f), 1.0f);
	EXPECT_EQ(absf(1.0f), 1.0f);
}

TEST(Math, floori) {
	EXPECT_EQ(floori(1.0f), 1);
	EXPECT_EQ(floori(1.5f), 1);
	EXPECT_EQ(floori(1.9f), 1);
	EXPECT_EQ(floori(0.5f), 0);
	EXPECT_EQ(floori(0.0f), 0);
}

TEST(Math, ceili) {
	EXPECT_EQ(ceili(1.0f), 1);
	EXPECT_EQ(ceili(1.5f), 2);
	EXPECT_EQ(ceili(1.9f), 2);
	EXPECT_EQ(ceili(0.5f), 1);
	EXPECT_EQ(ceili(0.0f), 0);
}

TEST(Math, sqrtf_16b) {
	EXPECT_EQ(sqrtf_16b(0), 0);
	EXPECT_EQ(sqrtf_16b(1), 1);
	EXPECT_EQ(sqrtf_16b(4), 2);
	EXPECT_FLOAT_EQ(sqrtf_16b(5), 2.236067977f);

	// Two NaN's are never equal
	EXPECT_NE(sqrtf_16b(-1), sqrtf_16b(-1));
	EXPECT_NE(sqrtf_16b(32768), sqrtf_16b(32768));
}

TEST(Math, powi) {
	EXPECT_EQ(powi(2, 0), 1);
	EXPECT_EQ(powi(3, 2), 9);
}
