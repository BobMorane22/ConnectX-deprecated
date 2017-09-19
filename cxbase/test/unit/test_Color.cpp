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
 * @date    May 2017
 * @version 0.2
 * @sa https://www.w3schools.com/cssref/css_colors.asp
 *
 * Unit tests for a the Color class.
 *
 **************************************************************************************************/

#include <gtest/gtest.h>

#include <include/Color.h>


using namespace cxbase;

class ColorTests: public::testing::Test
{
public:

    Color t_defaultColor;

    Color t_colorRed         {255, 0, 0, 255, AsciiColorCode{'R'}};
    Color t_transparentColor {Color::TRANSPARENT};
};

TEST_F(ColorTests, Constructor_Default_Black)
{
    Color defaultColor {0, 0, 0, 255, AsciiColorCode{'K'}};
    ASSERT_EQ(t_defaultColor, defaultColor);
}

TEST_F(ColorTests, ConstructorParam_Red_RedColor)
{
    Color red {255, 0, 0, 255, AsciiColorCode{'R'}};
    ASSERT_EQ(t_colorRed, red);
}

TEST(Color, ConstructorParam_RedNegative_ThrowsException)
{
    ASSERT_THROW((Color{-1, 128, 128, 128, AsciiColorCode('b')}), PreconditionException);
}

TEST(Color, ConstructorParam_RedOver255_ThrowsException)
{
    ASSERT_THROW((Color{256, 128, 128, 128, AsciiColorCode('b')}), PreconditionException);
}

TEST(Color, ConstructorParam_GreenNegative_ThrowsException)
{
    ASSERT_THROW((Color{128, -1, 128, 128, AsciiColorCode('b')}), PreconditionException);
}

TEST(Color, ConstructorParam_GreenOver255_ThrowsException)
{
    ASSERT_THROW((Color{128, 256, 128, 128, AsciiColorCode('b')}), PreconditionException);
}

TEST(Color, ConstructorParam_BlueNegative_ThrowsException)
{
    ASSERT_THROW((Color{128, 128, -1, 128, AsciiColorCode('b')}), PreconditionException);
}

TEST(Color, ConstructorParam_BlueOver255_ThrowsException)
{
    ASSERT_THROW((Color{128, 128, 256, 128, AsciiColorCode('b')}), PreconditionException);
}

TEST(Color, ConstructorParam_AlphaNegative_ThrowsException)
{
    ASSERT_THROW((Color{128, 128, 128, -1, AsciiColorCode('b')}), PreconditionException);
}

TEST(Color, ConstructorParam_AlphaOver255_ThrowsException)
{
    ASSERT_THROW((Color{128, 128, 128, 256, AsciiColorCode('b')}), PreconditionException);
}

TEST_F(ColorTests, RedAccessor_Default_ReturnsRedComponent)
{
    ASSERT_EQ(255, t_colorRed.red());
}

TEST_F(ColorTests, GreenAccessor_Default_ReturnsGreenComponent)
{
    ASSERT_EQ(0, t_colorRed.green());
}

TEST_F(ColorTests, BlueAccessor_Default_ReturnsBlueComponent)
{
    ASSERT_EQ(0, t_colorRed.blue());
}

TEST_F(ColorTests, AlphaAccessor_Default_ReturnsAlphaComponent)
{
    ASSERT_EQ(255, t_colorRed.alpha());
}

TEST_F(ColorTests, AsciiColorCodeAccessor_Default_ReturnsNoColor)
{
    AsciiColorCode t_redAsciiColorCode{'R'};
    ASSERT_EQ(t_redAsciiColorCode, t_colorRed.asciiColorCode());
}

TEST_F(ColorTests, EqualOperator_SameColors_ReturnsTrue)
{
    Color t_colorOther {255, 0, 0, 255, AsciiColorCode{'R'}};
    ASSERT_TRUE(t_colorRed == t_colorOther);
}

TEST_F(ColorTests, EqualOperator_DifferentRedElementOnly_ReturnsFalse)
{
    Color t_colorOther {254, 0, 0, 255, AsciiColorCode{'R'}};
    ASSERT_FALSE(t_colorRed == t_colorOther);
}

TEST_F(ColorTests, EqualOperator_DifferentGreenElementOnly_ReturnsFalse)
{
    Color t_colorOther {255, 1, 0, 255, AsciiColorCode{'R'}};
    ASSERT_FALSE(t_colorRed == t_colorOther);
}

TEST_F(ColorTests, EqualOperator_DifferentBlueElementOnly_ReturnsFalse)
{
    Color t_colorOther {255, 0, 1, 255, AsciiColorCode{'R'}};
    ASSERT_FALSE(t_colorRed == t_colorOther);
}

TEST_F(ColorTests, EqualOperator_DifferentAlphaElementOnly_ReturnsFalse)
{
    Color t_colorOther {255, 0, 0, 254, AsciiColorCode{'R'}};
    ASSERT_FALSE(t_colorRed == t_colorOther);
}

TEST_F(ColorTests, EqualOperator_DifferentAsciiColorCodeOnly_ReturnsTrue)
{
    Color t_colorOther {255, 0, 0, 255, AsciiColorCode{'r'}};
    ASSERT_TRUE(t_colorRed == t_colorOther);
}

TEST_F(ColorTests, NotEqualOperator_SameColors_ReturnsFalse)
{
    Color t_colorOther {255, 0, 0, 255, AsciiColorCode{'R'}};
    ASSERT_FALSE(t_colorRed != t_colorOther);
}

TEST_F(ColorTests, NotEqualOperator_DifferentRedElementOnly_ReturnsTrue)
{
    Color t_colorOther {254, 0, 0, 255, AsciiColorCode{'R'}};
    ASSERT_TRUE(t_colorRed != t_colorOther);
}

TEST_F(ColorTests, NotEqualOperator_DifferentGreenElementOnly_ReturnsTrue)
{
    Color t_colorOther {255, 1, 0, 255, AsciiColorCode{'R'}};
    ASSERT_TRUE(t_colorRed != t_colorOther);
}

TEST_F(ColorTests, NotEqualOperator_DifferentBlueElementOnly_ReturnsTrue)
{
    Color t_colorOther {255, 0, 1, 255, AsciiColorCode{'R'}};
    ASSERT_TRUE(t_colorRed != t_colorOther);
}

TEST_F(ColorTests, NotEqualOperator_DifferentAlphaElementOnly_ReturnsTrue)
{
    Color t_colorOther {255, 0, 0, 254, AsciiColorCode{'R'}};
    ASSERT_TRUE(t_colorRed != t_colorOther);
}

TEST_F(ColorTests, NotEqualOperator_DifferentAsciiColorCodeOnly_ReturnsFalse)
{
    Color t_colorOther {255, 0, 0, 255, AsciiColorCode{'r'}};
    ASSERT_FALSE(t_colorRed != t_colorOther);
}
