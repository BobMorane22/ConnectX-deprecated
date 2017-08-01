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

#include <sstream>

#include<gtest/gtest.h>

#include <include/Player.h>


USING_NAMESPACE_STD
USING_NAMESPACE_CXBASE

class PlayerTests : public ::testing::Test
{

public:

    const CXUTIL::Name  NAME1     {"John Doe"};
    const CXUTIL::Name  NAME2     {"Johnny Doe"};
    Player              t_player1 {NAME1, Disc::RED_DISC};
    Player              t_player2 {NAME2, Disc::BLACK_DISC};

};

TEST_F(PlayerTests, Constructor_TwoValidParameters_NoExceptionThrown)
{
    Player t_player{NAME1, Disc::RED_DISC};

    ASSERT_EQ(t_player.name(), NAME1);
    ASSERT_EQ(t_player.disc(), Disc::RED_DISC);
}

TEST_F(PlayerTests, Constructor_NoDiscAsParameter_ExceptionThrown)
{
    ASSERT_THROW(Player t_player(NAME1, Disc::NO_DISC), InvariantException);
}

TEST_F(PlayerTests, NameAccessor_ValidPlayer_ReturnsName)
{
    ASSERT_EQ(t_player1.name(), NAME1);
}

TEST_F(PlayerTests, DiscAccessor_ValidPlayer_ReturnsDisc)
{
    ASSERT_EQ(t_player1.disc(), Disc::RED_DISC);
}

TEST_F(PlayerTests, EqualOperator_TwoEqualPlayers_ReturnsTrue)
{
    CXUTIL::Name sameName{NAME1};
    Disc sameDisc{Disc::RED_DISC};
    Player t_player3{sameName, sameDisc};

    ASSERT_TRUE(t_player1 == t_player3);
}

TEST_F(PlayerTests, EqualOperator_TwoDifferentPlayers_ReturnsFalse)
{
    ASSERT_FALSE(t_player1 == t_player2);
}

TEST_F(PlayerTests, EqualOperator_TwoEqualNamesButDifferentDiscs_ReturnsFalse)
{
    Player t_player3{NAME1, Disc::RED_DISC};
    Player t_player4{NAME1, Disc::BLACK_DISC};

    ASSERT_FALSE(t_player3 == t_player4);
}

TEST_F(PlayerTests, EqualOperator_TwoDifferentNamesButEqualDiscs_ReturnsFalse)
{
    Player t_player3{NAME1, Disc::RED_DISC};
    Player t_player4{NAME2, Disc::RED_DISC};

    ASSERT_FALSE(t_player1 == t_player2);
}

TEST_F(PlayerTests, NotEqualOperator_TwoDifferentPlayers_ReturnsTrue)
{
    ASSERT_TRUE(t_player1 != t_player2);
}

TEST_F(PlayerTests, NotEqualOperator_TwoEqualNamesButDifferentDiscs_ReturnsTrue)
{
    Player t_player3{NAME1, Disc::RED_DISC};
    Player t_player4{NAME1, Disc::BLACK_DISC};

    ASSERT_TRUE(t_player3 != t_player4);
}

TEST_F(PlayerTests, NotEqualOperator_TwoDifferentNamesButEqualDiscs_ReturnsTrue)
{
    Player t_player3{NAME1, Disc::RED_DISC};
    Player t_player4{NAME2, Disc::RED_DISC};

    ASSERT_TRUE(t_player3 != t_player4);
}

TEST_F(PlayerTests, NotEqualOperator_TwoEqualPlayers_ReturnsFalse)
{
    Player t_player3{NAME1, Disc::RED_DISC};

    ASSERT_FALSE(t_player1 != t_player3);
}

TEST_F(PlayerTests, StreamInsertionOperator_ValidPlayerAsParameter_InsertsName)
{
    std::ostringstream flux;

    flux << t_player1;

    ASSERT_EQ(flux.str(), "John Doe");
}
