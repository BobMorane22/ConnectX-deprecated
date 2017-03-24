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

#include <publicAPI/Disc.h>

#include<gtest/gtest.h>

#include <sstream>


USING_NAMESPACE_CXBASE

const Name NO_COLOR     {"No color"};
const Name RED          {"Red"};
const Name BLACK        {"Black"};

const AsciiColorCode NO_COLOR_ASCII_CODE  {' '};
const AsciiColorCode RED_ASCII_CODE       {'R'};
const AsciiColorCode BLACK_ASCII_CODE     {'B'};


TEST(Disc, Constructor_Default_SetsNoColor)
{
    Disc t_disc;

    ASSERT_EQ(t_disc.color().name(), NO_COLOR);
    ASSERT_EQ(t_disc.asciiColorCode(), NO_COLOR_ASCII_CODE);
}

TEST(Disc, Constructor_RedColor_RedNameAndASCIICode)
{
    Color t_red{RED, RED_ASCII_CODE};
    Disc t_disc{t_red};

    ASSERT_EQ(t_disc.color().name(), RED);
    ASSERT_EQ(t_disc.asciiColorCode(), RED_ASCII_CODE);
}

TEST(Disc, ColorAccessor_NoColor_GetsNoColor)
{
    Color t_colorNone{NO_COLOR, NO_COLOR_ASCII_CODE};
    Disc t_disc;

    ASSERT_EQ(t_disc.color(), t_colorNone);
}

TEST(Disc, AsciiColorCodeAccessor_NoColor_GetsNoColorASCII)
{
    Disc t_disc;

    ASSERT_EQ(t_disc.asciiColorCode(), NO_COLOR_ASCII_CODE);
}

TEST(Disc, EqualOperator_TwoEqualDiscs_ReturnsTrue)
{
    Color t_red1{RED, RED_ASCII_CODE};
    Color t_red2{RED, RED_ASCII_CODE};

    Disc t_disc1{t_red1};
    Disc t_disc2{t_red2};

    ASSERT_TRUE(t_disc1 == t_disc2);
}

TEST(Disc, EqualOperator_TwoDifferentASCIICodes_ReturnsFalse)
{
    Color t_red1{RED, RED_ASCII_CODE};
    Color t_red2{RED, AsciiColorCode{'x'}};

    Disc t_disc1(t_red1);
    Disc t_disc2(t_red2);

    ASSERT_FALSE(t_disc1 == t_disc2);
}

TEST(Disc, EqualOperator_TwoDifferentColorAndASCIICode_ReturnsFalse)
{

    Color t_red1{RED, RED_ASCII_CODE};
    Color t_red2{BLACK, BLACK_ASCII_CODE};

    Disc t_disc1{t_red1};
    Disc t_disc2{t_red2};

    ASSERT_FALSE(t_disc1 == t_disc2);
}

TEST(Disc, OperatorNotEqual_TwoDifferentDiscs_ReturnTrue)
{
    Color t_red1{RED, RED_ASCII_CODE};
    Color t_red2{BLACK, BLACK_ASCII_CODE};

    Disc t_disc1{t_red1};
    Disc t_disc2{t_red2};

    ASSERT_TRUE(t_disc1 != t_disc2);
}

TEST(Disc, OperatorNotEqual_TwoEqualColorsButDifferentASCIICode_ReturnTrue)
{
    Color t_red1{RED, RED_ASCII_CODE};
    Color t_red2{RED, AsciiColorCode{'x'}};

    Disc t_disc1{t_red1};
    Disc t_disc2{t_red2};

    ASSERT_TRUE(t_disc1 != t_disc2);
}

TEST(Disc, OperatorNotEqual_TwoEqualDiscs_ReturnFalse)
{
    Color t_red1{RED, RED_ASCII_CODE};
    Color t_red2{RED, RED_ASCII_CODE};

    Disc t_disc1{t_red1};
    Disc t_disc2{t_red2};

    ASSERT_FALSE(t_disc1 != t_disc2);
}

TEST(Disc, StreamInsertionOperator_StandardDisc_PrintsRightString)
{
    std::ostringstream t_flux;
    std::ostringstream t_asciiRepresentation;

    Color t_red{RED, RED_ASCII_CODE};
    Disc t_disc{t_red};

    t_flux << t_disc;
    t_asciiRepresentation << " " << RED_ASCII_CODE << " ";

    ASSERT_EQ(t_flux.str(), t_asciiRepresentation.str());
}
