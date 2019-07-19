/***************************************************************************************************
 *
 * Copyright (C) 2019 Connect X team
 *
 * This file is part of Connect X.
 *
 * Connect X is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Connect X is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Connect X.  If not, see <http://www.gnu.org/licenses/>.
 *
 **************************************************************************************************/

/***********************************************************************************************//**
 * @file    test_util.cpp
 * @author  Eric Poirier
 * @date    July 2019
 * @version 1.0
 *
 * Unit tests for math utilities.
 *
 **************************************************************************************************/

#include <gtest/gtest.h>

#include <cxutil/include/util.h>


TEST(MathTests, AreLogicallyEqual_TwoLogicallyEqualDoubles_ReturnsTrue)
{
    const double expectedResult{0.111111111111111};

    const double lhs{0.555555555555555};
    const double rhs{0.444444444444444};

    ASSERT_FALSE(lhs - rhs == expectedResult);
    ASSERT_TRUE(cxutil::math::areLogicallyEqual<double>(lhs - rhs, expectedResult, 3.0));
}


TEST(MathTests, AreLogicallyEqual_TwoLogicallyEqualDoublesNear0_ReturnsTrue)
{
    const double expectedResult{0.0};
    double lhs{0.0};

    for(int i = 0; i < 10; ++i)
    {
        lhs += 0.1;
    }

    const double rhs{1.0};

    ASSERT_FALSE(lhs - rhs == expectedResult);
    ASSERT_TRUE(cxutil::math::areLogicallyEqual<double>(lhs - rhs, expectedResult, 3.0));
}
