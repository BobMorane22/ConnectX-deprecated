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
 * @file    test_Disc.cpp
 * @author  Eric Poirier
 * @date    October 2016
 * @version 0.1
 *
 * Unit tests for a the Disc class.
 *
 **************************************************************************************************/

#include <sstream>

#include <gtest/gtest.h>

#include <include/Disc.h>


using namespace cxbase;


TEST(Disc, Constructor_Default_SetsNoColor)
{
    Disc t_disc;
    ASSERT_EQ(t_disc.color(), Color::TRANSPARENT);
}

TEST(Disc, Constructor_RedColor_SetsRedComponentsAndRedAsciiColorCode)
{
    Disc t_disc{Color::RED};
    ASSERT_EQ(t_disc.color(), Color::RED);
}

TEST(Disc, ColorAccessor_Transparent_GetsTransparent)
{
    Disc t_disc;
    ASSERT_EQ(t_disc.color(), Color::TRANSPARENT);
}

TEST(Disc, EqualOperator_TwoEqualDiscs_ReturnsTrue)
{
    Disc t_disc1{Color::RED};
    Disc t_disc2{Color::RED};

    ASSERT_TRUE(t_disc1 == t_disc2);
}

TEST(Disc, EqualOperator_TwoDifferentAsciiColorCodes_ReturnsFalse)
{
    Color t_red1{Color::RED};
    Color t_red2{255, 0, 0, 255, AsciiColorCode{'r'}};

    Disc t_disc1{t_red1};
    Disc t_disc2{t_red2};

    ASSERT_FALSE(t_disc1 == t_disc2);
}

TEST(Disc, EqualOperator_TwoDifferentColorAndAsciiColorCode_ReturnsFalse)
{
    Disc t_discRed   {Color::RED};
    Disc t_discBlack {Color::BLACK};

    ASSERT_FALSE(t_discRed == t_discBlack);
}

TEST(Disc, OperatorNotEqual_TwoDifferentColorAndAsciiColorCode_ReturnTrue)
{
    Disc t_discRed   {Color::RED};
    Disc t_discBlack {Color::BLACK};

    ASSERT_TRUE(t_discRed != t_discBlack);
}

TEST(Disc, OperatorNotEqual_TwoEqualColorsButDifferentASCIICode_ReturnTrue)
{
    Color t_red1{Color::RED};
    Color t_red2{255, 0, 0, 255, AsciiColorCode{'r'}};

    Disc t_disc1{t_red1};
    Disc t_disc2{t_red2};

    ASSERT_TRUE(t_disc1 != t_disc2);
}

TEST(Disc, OperatorNotEqual_TwoEqualDiscs_ReturnFalse)
{
    Disc t_disc1{Color::RED};
    Disc t_disc2{Color::RED};

    ASSERT_FALSE(t_disc1 != t_disc2);
}

TEST(Disc, StreamInsertionOperator_StandardDisc_PrintsRightString)
{
    std::ostringstream t_flux;
    std::ostringstream t_asciiRepresentation;

    Disc t_disc{Color::RED};

    t_flux << t_disc;
    t_asciiRepresentation << " " << 'R' << " ";

    ASSERT_EQ(t_flux.str(), t_asciiRepresentation.str());
}
