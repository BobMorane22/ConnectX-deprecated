/***************************************************************************************************
 * 
 * Copyright (C) 2017 Connect X team
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
 * @file    test_ReturnCode.cpp
 * @author  Eric Poirier
 * @date    September 2017
 * @version 1.0
 *
 * Unit tests for a the @c narrow_cast template function.
 *
 **************************************************************************************************/

#include <string>

#include <gtest/gtest.h>

#include <include/narrow_cast.h>


class DataToCast : public testing::Test
{
public:
    const int t_integerPositiveSmall  { 0x01                            };
    const int t_integerPositiveMedium { 0x01 << (7 * sizeof(short))     };
    const int t_integerPositiveHuge   { 0x01 << (7 * sizeof(short) + 1) };
};

TEST_F(DataToCast, NarrowCast_IntToShortWithinBound_NoAssertion)
{
    const short t_int = cxutil::narrow_cast<short>(t_integerPositiveSmall);

    ASSERT_EQ(t_int, t_integerPositiveSmall);
}


TEST_F(DataToCast, NarrowCast_IntToShortOnBoundLimit_NoAssertion)
{
    const short t_int = cxutil::narrow_cast<short>(t_integerPositiveMedium);

    ASSERT_EQ(t_int, t_integerPositiveMedium);
}


TEST_F(DataToCast, NarrowCast_IntToShortOverBoundLimit_Assertion)
{
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";

    // Only the fact that an assertion has been raised and that the assertion
    // message is about narrow_cast is tested. This allows the test to be independant
    // of the assertion message's line number and file location, which will vary in time
    // and depending on the user testing.
    const std::string narrowCastAssertionRegex{".*static_cast<Source>\\(casted\\) == p_toCast.*"};

    ASSERT_DEATH(cxutil::narrow_cast<short>(t_integerPositiveHuge), narrowCastAssertionRegex);
}
