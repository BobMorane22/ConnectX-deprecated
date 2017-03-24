/***************************************************************************************************
 * 
 * Copyright (C) 2016 Connect X team
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
 * @file    test_Color.cpp
 * @author  Eric Poirier
 * @date    September 2016
 * @version 0.1
 *
 * Unit tests for a the Color class.
 *
 **************************************************************************************************/

#include <publicAPI/Color.h>

#include <gtest/gtest.h>


USING_NAMESPACE_CXBASE

const Name              NO_COLOR              {"No color"};
const AsciiColorCode    NO_COLOR_ASCII_CODE   {' '};

const Name              RED                   {"Red"};
const AsciiColorCode    RED_ASCII_CODE        {'R'};


class ColorTests: public::testing::Test
{
public:

    Color t_color;
};

TEST(Color, Constructor_Default_NoColor)
{
    Color t_colorNone;

    ASSERT_EQ(t_colorNone.name(), NO_COLOR);
    ASSERT_EQ(t_colorNone.asciiColorCode(), NO_COLOR_ASCII_CODE);
}

TEST(Color, Constructor_Red_RedColor)
{
    Color t_color{RED, RED_ASCII_CODE};

    ASSERT_EQ(t_color.name(), RED);
    ASSERT_EQ(t_color.asciiColorCode(), RED_ASCII_CODE);
}

TEST(Color, Constructor_AsciiColorCodeLowerCase_CustomColor)
{
    Color t_color{Name{"test"}, AsciiColorCode{'t'}};

    ASSERT_EQ(t_color.name(), Name{"test"});
    ASSERT_EQ(t_color.asciiColorCode(), AsciiColorCode{'t'});
}

TEST(Color, Constructor_AsciiColorCodeUpperCase_CustomColor)
{
    Color t_color{Name{"test"}, AsciiColorCode{'T'}};

    ASSERT_EQ(t_color.name(), Name{"test"});
    ASSERT_EQ(t_color.asciiColorCode(), AsciiColorCode{'T'});
}

TEST_F(ColorTests, NameAccessor_Default_ReturnsNoColor)
{
    ASSERT_EQ(NO_COLOR, t_color.name());
}

TEST_F(ColorTests, AsciiColorCodeAccessor_Default_ReturnsNoColor)
{
    ASSERT_EQ(NO_COLOR_ASCII_CODE, t_color.asciiColorCode());
}

TEST_F(ColorTests, EqualOperator_TwoDefaultColors_ReturnsTrue)
{
    Color t_colorByDefault;

    ASSERT_TRUE(t_colorByDefault == t_color);
}

TEST_F(ColorTests, EqualOperator_TwoDifferentNamesButSameASCIICode_ReturnsFalse)
{
    Color t_colorRed{RED, NO_COLOR_ASCII_CODE};

    ASSERT_FALSE(t_colorRed == t_color);
}

TEST_F(ColorTests, EqualOperator_TwoNamesEqualButDifferentASCIICode_ReturnsTrue)
{
    Color t_colorNone{NO_COLOR, RED_ASCII_CODE};

    ASSERT_TRUE(t_colorNone == t_color);
}

TEST_F(ColorTests, NotEqualOperator_TwoDefaultColors_ReturnsFalse)
{
    Color t_colorByDefault;

    ASSERT_FALSE(t_colorByDefault != t_color);
}

TEST_F(ColorTests, NotEqualOperator_DifferentNames_ReturnsTrue)
{
    Color t_colorRed{RED, NO_COLOR_ASCII_CODE};

    ASSERT_TRUE(t_colorRed != t_color);
}

TEST_F(ColorTests, NotEqualOperator_SameNamesButDifferentASCIICode_ReturnsFalse)
{
    Color t_colorNone{NO_COLOR, RED_ASCII_CODE};

    ASSERT_FALSE(t_colorNone != t_color);
}
