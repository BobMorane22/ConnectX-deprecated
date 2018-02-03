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
 * @version 1.0
 * @sa https://www.w3schools.com/cssref/css_colors.asp
 *
 * Unit tests for a the Color class.
 *
 **************************************************************************************************/

#include <gtest/gtest.h>

#include <cxutil/include/Color.h>


using namespace cxutil;


class ColorTests: public::testing::Test
{
public:

    Color t_defaultColor;

    Color t_colorRed         {255, 0, 0, 255};
    Color t_transparentColor {Color::transparent()};
};


TEST_F(ColorTests, Constructor_Default_Black)
{
    Color defaultColor {0, 0, 0, 255};
    ASSERT_EQ(t_defaultColor, defaultColor);
}


TEST_F(ColorTests, ConstructorParam_Red_RedColor)
{
    Color red {255, 0, 0, 255};
    ASSERT_EQ(t_colorRed, red);
}


TEST(Color, ConstructorParam_RedNegative_ThrowsException)
{
    ASSERT_THROW((Color{-1, 128, 128, 128}), PreconditionException);
}


TEST(Color, ConstructorParam_RedOver255_ThrowsException)
{
    ASSERT_THROW((Color{256, 128, 128, 128}), PreconditionException);
}


TEST(Color, ConstructorParam_GreenNegative_ThrowsException)
{
    ASSERT_THROW((Color{128, -1, 128, 128}), PreconditionException);
}


TEST(Color, ConstructorParam_GreenOver255_ThrowsException)
{
    ASSERT_THROW((Color{128, 256, 128, 128}), PreconditionException);
}


TEST(Color, ConstructorParam_BlueNegative_ThrowsException)
{
    ASSERT_THROW((Color{128, 128, -1, 128}), PreconditionException);
}


TEST(Color, ConstructorParam_BlueOver255_ThrowsException)
{
    ASSERT_THROW((Color{128, 128, 256, 128}), PreconditionException);
}


TEST(Color, ConstructorParam_AlphaNegative_ThrowsException)
{
    ASSERT_THROW((Color{128, 128, 128, -1}), PreconditionException);
}


TEST(Color, ConstructorParam_AlphaOver255_ThrowsException)
{
    ASSERT_THROW((Color{128, 128, 128, 256}), PreconditionException);
}


TEST_F(ColorTests, RedAccessor_Default_ReturnsRedComponent)
{
    ASSERT_EQ(255, t_colorRed.r());
}


TEST_F(ColorTests, GreenAccessor_Default_ReturnsGreenComponent)
{
    ASSERT_EQ(0, t_colorRed.g());
}


TEST_F(ColorTests, BlueAccessor_Default_ReturnsBlueComponent)
{
    ASSERT_EQ(0, t_colorRed.b());
}


TEST_F(ColorTests, AlphaAccessor_Default_ReturnsAlphaComponent)
{
    ASSERT_EQ(255, t_colorRed.a());
}


TEST_F(ColorTests, EqualOperator_SameColors_ReturnsTrue)
{
    Color t_colorOther {255, 0, 0, 255};
    ASSERT_TRUE(t_colorRed == t_colorOther);
}


TEST_F(ColorTests, EqualOperator_DifferentRedElementOnly_ReturnsFalse)
{
    Color t_colorOther {254, 0, 0, 255};
    ASSERT_FALSE(t_colorRed == t_colorOther);
}

TEST_F(ColorTests, EqualOperator_DifferentGreenElementOnly_ReturnsFalse)
{
    Color t_colorOther {255, 1, 0, 255};
    ASSERT_FALSE(t_colorRed == t_colorOther);
}

TEST_F(ColorTests, EqualOperator_DifferentBlueElementOnly_ReturnsFalse)
{
    Color t_colorOther {255, 0, 1, 255};
    ASSERT_FALSE(t_colorRed == t_colorOther);
}

TEST_F(ColorTests, EqualOperator_DifferentAlphaElementOnly_ReturnsFalse)
{
    Color t_colorOther {255, 0, 0, 254};
    ASSERT_FALSE(t_colorRed == t_colorOther);
}

TEST_F(ColorTests, EqualOperator_DifferentAsciiColorCodeOnly_ReturnsTrue)
{
    Color t_colorOther {255, 0, 0, 255};
    ASSERT_TRUE(t_colorRed == t_colorOther);
}

TEST_F(ColorTests, NotEqualOperator_SameColors_ReturnsFalse)
{
    Color t_colorOther {255, 0, 0, 255};
    ASSERT_FALSE(t_colorRed != t_colorOther);
}

TEST_F(ColorTests, NotEqualOperator_DifferentRedElementOnly_ReturnsTrue)
{
    Color t_colorOther {254, 0, 0, 255};
    ASSERT_TRUE(t_colorRed != t_colorOther);
}


TEST_F(ColorTests, NotEqualOperator_DifferentGreenElementOnly_ReturnsTrue)
{
    Color t_colorOther {255, 1, 0, 255};
    ASSERT_TRUE(t_colorRed != t_colorOther);
}


TEST_F(ColorTests, NotEqualOperator_DifferentBlueElementOnly_ReturnsTrue)
{
    Color t_colorOther {255, 0, 1, 255};
    ASSERT_TRUE(t_colorRed != t_colorOther);
}


TEST_F(ColorTests, NotEqualOperator_DifferentAlphaElementOnly_ReturnsTrue)
{
    Color t_colorOther {255, 0, 0, 254};
    ASSERT_TRUE(t_colorRed != t_colorOther);
}


TEST(Color, Normalize_SemiTransparentGrey_RGBAOneHalf)
{
    const double t_rWanted{127.0 / 255.0};
    const double t_gWanted{127.0 / 255.0};
    const double t_bWanted{127.0 / 255.0};
    const double t_aWanted{127.0 / 255.0};

    const Color semiTransparentGrey{127, 127, 127, 127};

    double t_rResult, t_gResult, t_bResult, t_aResult;

    normalize(semiTransparentGrey, t_rResult, t_gResult, t_bResult, t_aResult);

    ASSERT_EQ(t_rWanted, t_rResult);
    ASSERT_EQ(t_gWanted, t_gResult);
    ASSERT_EQ(t_bWanted, t_bResult);
    ASSERT_EQ(t_aWanted, t_aResult);
}


TEST(Color, Normalize_OpaqueBlack_RGBOneAndAZero)
{
    const double t_rWanted{1.0};
    const double t_gWanted{1.0};
    const double t_bWanted{1.0};
    const double t_aWanted{0.0};

    const Color opaqueBlack{255, 255, 255, 0};

    double t_rResult, t_gResult, t_bResult, t_aResult;

    normalize(opaqueBlack, t_rResult, t_gResult, t_bResult, t_aResult);

    ASSERT_EQ(t_rWanted, t_rResult);
    ASSERT_EQ(t_gWanted, t_gResult);
    ASSERT_EQ(t_bWanted, t_bResult);
    ASSERT_EQ(t_aWanted, t_aResult);
}
