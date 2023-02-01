#include <gtest/gtest.h>
#include "tests/index.h"
TEST(ZIPPER, EAT_EDGE)
{
	EXPECT_NO_THROW(eat_edge());
}