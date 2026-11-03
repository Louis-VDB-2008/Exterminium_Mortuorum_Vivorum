#include "pch.h"
#include <gtest/gtest.h>

TEST(FirstTest, Addition)
{
    int result = 2 + 3;

    EXPECT_EQ(result, 5);
}