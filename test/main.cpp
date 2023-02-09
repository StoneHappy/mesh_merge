#include <gtest/gtest.h>
#include "tests/index.h"
TEST(ZIPPER, EAT_EDGE)
{
	EXPECT_NO_THROW(eat_edge());
}

TEST(ZIPPER, EAT_EDGE_MM)
{
	EXPECT_NO_THROW(eat_edge_mm());
}


TEST(ZIPPER, EAT_EDGE_V_MM)
{
	EXPECT_NO_THROW(eat_edge_v_mm());
}

TEST(ZIPPER, MERGEMESH)
{
	EXPECT_NO_THROW(merge());
}

TEST(ZIPPER, RECONSTRUCTION)
{
	EXPECT_NO_THROW(reconstruction());
}

TEST(ZIPPER, GET_BORDER_V)
{
	EXPECT_NO_THROW(get_border_v());
}

TEST(ZIPPER, ALL)
{
	EXPECT_NO_THROW(all());
}