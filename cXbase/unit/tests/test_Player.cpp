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
 * @file    test_Player.cpp
 * @author  Eric Poirier
 * @date    November 2016
 * @version 0.1
 *
 * Unit tests for a the Player class.
 *
 **************************************************************************************************/

#include<gtest/gtest.h>

#include <sstream>

#include <publicAPI/Player.h>


USING_NAMESPACE_STD
USING_NAMESPACE_CXBASE

class PlayerTests : public ::testing::Test
{

public:

    const Name              JOHN_DOE              {"John Doe"};
    const Name              JOHNNY_DOE            {"Johnny Doe"};
    const Name              RED                   {"Red"};
    const Name              BLACK                 {"Black"};

    const AsciiColorCode    ASCII_CODE_RED        {'R'};
    const AsciiColorCode    ASCII_CODE_BLACK      {'B'};

    const Color             COLOR_RED             {RED, ASCII_CODE_RED};
    const Color             COLOR_BLACK           {BLACK, ASCII_CODE_BLACK};

    const Disc              RED_DISC              {COLOR_RED};
    const Disc              BLACK_DISC            {COLOR_BLACK};


    Player                  t_player1             {JOHN_DOE, RED_DISC};
    Player                  t_player2             {JOHNNY_DOE, BLACK_DISC};

};

TEST_F(PlayerTests, Constructor_TwoValidParameters_NoExceptionThrown)
{
    Player t_player{JOHN_DOE, RED_DISC};

    ASSERT_EQ(t_player.name(), JOHN_DOE);
    ASSERT_EQ(t_player.disc(), RED_DISC);
}

TEST_F(PlayerTests, Constructor_NoDiscAsParameter_ExceptionThrown)
{
    Disc NO_DISC{Color{Name{"No color"}, AsciiColorCode{' '}}};

    ASSERT_THROW(Player t_player(JOHN_DOE, NO_DISC), InvariantException);
}

TEST_F(PlayerTests, NameAccessor_ValidPlayer_ReturnsName)
{
    ASSERT_EQ(t_player1.name(), JOHN_DOE);
}

TEST_F(PlayerTests, DiscAccessor_ValidPlayer_ReturnsDisc)
{
    ASSERT_EQ(t_player1.disc(), RED_DISC);
}

TEST_F(PlayerTests, EqualOperator_TwoEqualPlayers_ReturnsTrue)
{
    Name sameName{JOHN_DOE};
    Disc sameDisc{RED_DISC};
    Player t_player3{sameName, sameDisc};

    ASSERT_TRUE(t_player1 == t_player3);
}

TEST_F(PlayerTests, EqualOperator_TwoDifferentPlayers_ReturnsFalse)
{
    ASSERT_FALSE(t_player1 == t_player2);
}

TEST_F(PlayerTests, EqualOperator_TwoEqualNamesButDifferentDiscs_ReturnsFalse)
{
    Player t_player3{JOHN_DOE, RED_DISC};
    Player t_player4{JOHN_DOE, BLACK_DISC};

    ASSERT_FALSE(t_player3 == t_player4);
}

TEST_F(PlayerTests, EqualOperator_TwoDifferentNamesButEqualDiscs_ReturnsFalse)
{
    Player t_player3{JOHN_DOE, RED_DISC};
    Player t_player4{JOHNNY_DOE, RED_DISC};

    ASSERT_FALSE(t_player1 == t_player2);
}

TEST_F(PlayerTests, NotEqualOperator_TwoDifferentPlayers_ReturnsTrue)
{
    ASSERT_TRUE(t_player1 != t_player2);
}

TEST_F(PlayerTests, NotEqualOperator_TwoEqualNamesButDifferentDiscs_ReturnsTrue)
{
    Player t_player3(JOHN_DOE, RED_DISC);
    Player t_player4(JOHN_DOE, BLACK_DISC);

    ASSERT_TRUE(t_player3 != t_player4);
}

TEST_F(PlayerTests, NotEqualOperator_TwoDifferentNamesButEqualDiscs_ReturnsTrue)
{
    Player t_player3(JOHN_DOE, RED_DISC);
    Player t_player4(JOHNNY_DOE, RED_DISC);

    ASSERT_TRUE(t_player3 != t_player4);
}

TEST_F(PlayerTests, NotEqualOperator_TwoEqualPlayers_ReturnsFalse)
{
    Player t_player3(JOHN_DOE, RED_DISC);

    ASSERT_FALSE(t_player1 != t_player3);
}

TEST_F(PlayerTests, StreamInsertionOperator_ValidPlayerAsParameter_InsertsName)
{
    std::ostringstream flux;

    flux << t_player1;

    ASSERT_EQ(flux.str(), "John Doe");
}
