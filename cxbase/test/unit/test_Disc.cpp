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
 * @version 1.0
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
    ASSERT_EQ(t_disc.color(), Color::transparent());
}


TEST(Disc, Constructor_RedColor_SetsRedComponents)
{
    Disc t_disc{Color::red()};
    ASSERT_EQ(t_disc.color(), Color::red());
}


TEST(Disc, ColorAccessor_Transparent_GetsTransparent)
{
    Disc t_disc;
    ASSERT_EQ(t_disc.color(), Color::transparent());
}


TEST(Disc, EqualOperator_TwoEqualDiscs_ReturnsTrue)
{
    Disc t_disc1{Color::red()};
    Disc t_disc2{Color::red()};

    ASSERT_TRUE(t_disc1 == t_disc2);
}


TEST(Disc, OperatorNotEqual_TwoEqualDiscs_ReturnFalse)
{
    Disc t_disc1{Color::red()};
    Disc t_disc2{Color::red()};

    ASSERT_FALSE(t_disc1 != t_disc2);
}

