#include "gtest/gtest.h"

extern "C" {
	#include "../include/stringops.h"
}

TEST(Stringops, num2char_0) {
	int num = 0;
	char buf[16];

	num2char(num, buf, 16);

	EXPECT_STREQ(buf, "0");
}

TEST(Stringops, num2char_1337) {
	int num = 1337;
	char buf[16];

	num2char(num, buf, 16);

	EXPECT_STREQ(buf, "1337");
}
