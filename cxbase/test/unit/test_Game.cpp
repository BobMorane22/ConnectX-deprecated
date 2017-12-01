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
 * @file    test_Game.cpp
 * @author  Eric Poirier
 * @date    January 2017
 * @version 0.1
 *
 * Unit tests for a the Game class.
 *
 **************************************************************************************************/

#include <gtest/gtest.h>

#include <include/Game.h>


using namespace cxbase;


class GameTests: public::testing::Test
{

public:

    GameTests() {};

    const int                                   NB_COLUMNS_MAX    {64};
    const int                                   NB_ROWS_MAX       {64};
    const int                                   NB_COLUMNS_MIN    {7 };
    const int                                   NB_ROWS_MIN       {6 };

    const std::shared_ptr<Player>               FIRST_PLAYER      {std::make_shared<Player>(cxutil::Name{"First Player" } ,  Disc::BLACK_DISC ) };
    const std::shared_ptr<Player>               SECOND_PLAYER     {std::make_shared<Player>(cxutil::Name{"Second Player"} ,  Disc::RED_DISC   ) };
    const std::shared_ptr<Player>               THIRD_PLAYER      {std::make_shared<Player>(cxutil::Name{"Third Player" } ,  Disc::YELLOW_DISC) };

    const std::vector<std::shared_ptr<Player>>  TWO_PLAYERS       {FIRST_PLAYER, SECOND_PLAYER              };
    const std::vector<std::shared_ptr<Player>>  THREE_PLAYERS     {FIRST_PLAYER, SECOND_PLAYER, THIRD_PLAYER};

    const std::shared_ptr<GameBoard>            CLASSIC_GAMEBOARD  {std::make_shared<GameBoard>()                                                };
    const std::shared_ptr<GameBoard>            A_9_BY_9_GAMEBOARD {std::make_shared<GameBoard>(9, 9)};                                          };


TEST_F(GameTests, Constructor_ValidArguments_NoExceptionThrown)
{
    ASSERT_NO_THROW((Game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR}));

    Game t_game3 {THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    ASSERT_EQ(t_game3.inARowValue(), GameBoard::CONNECT_FOUR);
}


TEST_F(GameTests, Constructor_NotEnoughPlayers_ExceptionThrown)
{
    std::vector<std::shared_ptr<Player>> t_players;
    t_players.push_back(FIRST_PLAYER);

    ASSERT_THROW((Game{t_players, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR}), PreconditionException);
}


TEST_F(GameTests, Constructor_TooManyPlayers_ExceptionThrown)
{
    std::vector<std::shared_ptr<Player>> t_players;
    t_players.push_back(FIRST_PLAYER);
    t_players.push_back(SECOND_PLAYER);
    t_players.push_back(THIRD_PLAYER);
    t_players.push_back(std::make_shared<Player>(cxutil::Name{"Fourth Player"   } ,  Disc::YELLOW_DISC));
    t_players.push_back(std::make_shared<Player>(cxutil::Name{"Fifth Player"    } ,  Disc::YELLOW_DISC));
    t_players.push_back(std::make_shared<Player>(cxutil::Name{"Sixth Player"    } ,  Disc::YELLOW_DISC));
    t_players.push_back(std::make_shared<Player>(cxutil::Name{"Seventh Player"  } ,  Disc::YELLOW_DISC));
    t_players.push_back(std::make_shared<Player>(cxutil::Name{"Eight Player"    } ,  Disc::YELLOW_DISC));
    t_players.push_back(std::make_shared<Player>(cxutil::Name{"Ninth Player"    } ,  Disc::YELLOW_DISC));
    t_players.push_back(std::make_shared<Player>(cxutil::Name{"Tenth Player"    } ,  Disc::YELLOW_DISC));
    t_players.push_back(std::make_shared<Player>(cxutil::Name{"Eleventh Player" } ,  Disc::YELLOW_DISC));

    ASSERT_THROW((Game{t_players, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR}), PreconditionException);
}


TEST_F(GameTests, Constructor_InARowTooSmall_ExceptionThrown)
{
    ASSERT_THROW((Game{THREE_PLAYERS, CLASSIC_GAMEBOARD, 1}), PreconditionException);
}


TEST_F(GameTests, Constructor_InARowTooLarge_ExceptionThrown)
{
    const int InARowTooLarge {std::min(CLASSIC_GAMEBOARD->nbRows(), CLASSIC_GAMEBOARD->nbColumns()) + 1};

    ASSERT_THROW((Game{THREE_PLAYERS, CLASSIC_GAMEBOARD, InARowTooLarge}), PreconditionException);
}


TEST_F(GameTests, Constructor_InvalidPlayerAddress_ExceptionThrown)
{
    std::vector<std::shared_ptr<Player>> t_players;
    t_players.push_back(FIRST_PLAYER);
    t_players.push_back(nullptr);
    t_players.push_back(THIRD_PLAYER);

    ASSERT_THROW((Game{t_players, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR}), PreconditionException);
}


TEST_F(GameTests, Constructor_InvalidGameboardAddress_ExceptionThrown)
{
    std::shared_ptr<GameBoard> gameboard{std::make_shared<GameBoard>()};
    gameboard.reset();

    ASSERT_THROW((Game{THREE_PLAYERS, gameboard, GameBoard::CONNECT_FOUR}), PreconditionException);
}


TEST_F(GameTests, ActivePlayerAccessor_ThreePlayerGameAndNoTurn_ReturnsFirstPlayer)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    ASSERT_EQ(t_game.activePlayer(), *FIRST_PLAYER);
}


TEST_F(GameTests, ActivePlayerAccessor_ThreePlayerGameAndTwoTurns_ReturnsThirdPlayer)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    t_game.nextTurn();
    t_game.nextTurn();

    ASSERT_EQ(t_game.activePlayer(), *THIRD_PLAYER);
}


TEST_F(GameTests, ActivePlayerAccessor_ThreePlayerGameAndThreeTurns_ReturnsFirstPlayer)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    t_game.nextTurn();
    t_game.nextTurn();
    t_game.nextTurn();

    ASSERT_EQ(t_game.activePlayer(), *FIRST_PLAYER);
}


TEST_F(GameTests, InARowValueAccessor_ValidObject_ReturnsInARowValue)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    ASSERT_EQ(t_game.inARowValue(), 4);
}


TEST_F(GameTests, NbOfTurnsPlayedAccessor_ValidObject_ReturnsNbOfTurnsPlayed)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    t_game.nextTurn();
    t_game.nextTurn();
    t_game.nextTurn();
    t_game.nextTurn();

    ASSERT_EQ(t_game.nbOfTurnsPlayed(), 4);
}


TEST_F(GameTests, CurrentTurnAccessor_ValidObject_ReturnsCurrentTurn)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    ASSERT_EQ(t_game.currentTurn(), 0);
}


TEST_F(GameTests, IsDraw_FirstTurn_ReturnsFalse)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    ASSERT_FALSE(t_game.isDraw());
}


TEST_F(GameTests, IsDraw_AllTurnsPlayedPlusOne_ReturnsTrue)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    for(int i{0}; i < CLASSIC_GAMEBOARD->nbPositions(); ++i)
    {
        t_game.nextTurn(); // 43 turns for a classic GameBoard.
    }

    ASSERT_TRUE(t_game.isDraw());
}


TEST_F(GameTests, NextTurn_ToFirstTurn_TurnIsOneActivePlayerIsTwo)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    t_game.nextTurn();

    Player t_player{cxutil::Name{"Second Player"}, Disc::RED_DISC};

    ASSERT_EQ(t_game.currentTurn(), 1);
    ASSERT_EQ(t_game.activePlayer(), t_player);
}


TEST_F(GameTests, NextTurn_AllTurns_TurnIs42ActivePlayerIsFirst)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    for(int i{0}; i < CLASSIC_GAMEBOARD->nbPositions() - 1; ++i)
    {
        t_game.nextTurn(); // 42 turns for a classic GameBoard.
    }

    Player t_player{cxutil::Name{"Third Player"}, Disc::YELLOW_DISC};

    ASSERT_EQ(t_game.nbOfTurnsPlayed(), CLASSIC_GAMEBOARD->nbPositions() - 1);
    ASSERT_EQ(t_game.activePlayer(), t_player);
}


TEST_F(GameTests, NextTurn_ExceedsAllTurns_TurnIs43)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    for(int i{0}; i < CLASSIC_GAMEBOARD->nbPositions(); ++i)
    {
        t_game.nextTurn(); // 43 turns for a classic GameBoard.
    }

    ASSERT_EQ(t_game.nbOfTurnsPlayed(), CLASSIC_GAMEBOARD->nbPositions());

    t_game.nextTurn();

    ASSERT_EQ(t_game.nbOfTurnsPlayed(), CLASSIC_GAMEBOARD->nbPositions());
}


TEST_F(GameTests, IsDraw_TieClassicGameBoardEmpty_ReturnsFalse)
{
    Game t_game{TWO_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    ASSERT_FALSE(t_game.isTie());
}


TEST_F(GameTests, IsDraw_TieClassicGameBoardEdgeCaseHorizontal_ReturnsTrue)
{
    Game t_game{TWO_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_FALSE(t_game.isTie());

    // Form this point on, the game should report a tie on every move, until completion:
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    // All these ties should lead to a draw upon game completion:
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isDraw());
}


TEST_F(GameTests, IsDraw_Tie9by8GameBoardConnect7ThreePlayersEdgeCaseHorizontal_ReturnsTrue)
{
    const std::shared_ptr<GameBoard> t_8by9Gameboard{std::make_shared<GameBoard>(9, 8)};

    Game t_game{THREE_PLAYERS, t_8by9Gameboard, GameBoard::CONNECT_SEVEN};

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_FALSE(t_game.isTie());

    // Form this point on, the game should report a tie on every move, until completion:
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    // All these ties should lead to a draw upon game completion:
    ASSERT_TRUE(t_game.isDraw());
}


// This test may not be such an edge case... Enhancement seems possible.
TEST_F(GameTests, IsDraw_TieClassicGameBoardEdgeCaseVertical_ReturnsTrue)
{
    Game t_game{TWO_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_FALSE(t_game.isTie());

    // Form this point on, the game should report a tie on every move, until completion:
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    // All these ties should lead to a draw upon game completion:
    ASSERT_TRUE(t_game.isDraw());
}


TEST_F(GameTests, IsDraw_Tie9by8GameBoardConnect7ThreePlayersEdgeCaseVertical_ReturnsTrue)
{
    const std::shared_ptr<GameBoard> t_8by9Gameboard{std::make_shared<GameBoard>(9, 8)};

    Game t_game{THREE_PLAYERS, t_8by9Gameboard, GameBoard::CONNECT_SEVEN};

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_FALSE(t_game.isTie());

    // Form this point on, the game should report a tie on every move, until completion:
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    // All these ties should lead to a draw upon game completion:
    ASSERT_TRUE(t_game.isDraw());
}


TEST_F(GameTests, IsDraw_TieClassicGameBoardEdgeCaseDiagonalUpward_ReturnsTrue)
{
    Game t_game{TWO_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_FALSE(t_game.isTie());

    // Form this point on, the game should report a tie on every move, until completion:
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    // All these ties should lead to a draw upon game completion:
    ASSERT_TRUE(t_game.isDraw());
}


TEST_F(GameTests, IsDraw_Tie9by8GameBoardConnect7ThreePlayersEdgeCaseDiagonalUpward_ReturnsTrue)
{
    const std::shared_ptr<GameBoard> t_8by9Gameboard{std::make_shared<GameBoard>(9, 8)};

    Game t_game{THREE_PLAYERS, t_8by9Gameboard, GameBoard::CONNECT_SEVEN};

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_FALSE(t_game.isTie());

    // Form this point on, the game should report a tie on every move, until completion:
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    // All these ties should lead to a draw upon game completion:
    ASSERT_TRUE(t_game.isDraw());
}


TEST_F(GameTests, IsDraw_TieClassicGameBoardEdgeCaseDiagonalDownward_ReturnsTrue)
{
    Game t_game{TWO_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_FALSE(t_game.isTie());

    // Form this point on, the game should report a tie on every move, until completion:
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    // All these ties should lead to a draw upon game completion:
    ASSERT_TRUE(t_game.isDraw());
}


TEST_F(GameTests, IsDraw_Tie9by8GameBoardConnect7ThreePlayersEdgeCaseDiagonalDownward_ReturnsTrue)
{
    const std::shared_ptr<GameBoard> t_8by9Gameboard{std::make_shared<GameBoard>(9, 8)};

    Game t_game{THREE_PLAYERS, t_8by9Gameboard, GameBoard::CONNECT_SEVEN};

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{7});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{6});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_FALSE(t_game.isTie());

    // Form this point on, the game should report a tie on every move, until completion:
    t_game.playTurn(Column{2});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{5});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{4});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{3});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{1});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    t_game.playTurn(Column{0});     t_game.nextTurn();     ASSERT_FALSE(t_game.isWon());
    ASSERT_TRUE(t_game.isTie());

    // All these ties should lead to a draw upon game completion:
    ASSERT_TRUE(t_game.isDraw());
}


TEST_F(GameTests, IsWon_HorizontalWinner_ReturnsTrue)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    // Always same player:
    t_game.playTurn(Column{0});
    t_game.playTurn(Column{1});
    t_game.playTurn(Column{2});

    ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});

    ASSERT_TRUE(t_game.isWon());
}


TEST_F(GameTests, IsWon_VerticalWinner_ReturnsTrue)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    // Always same player:
    t_game.playTurn(Column{0});
    t_game.playTurn(Column{0});
    t_game.playTurn(Column{0});

    ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});

    ASSERT_TRUE(t_game.isWon());
}


TEST_F(GameTests, IsWon_ObliqueUpwardWinner_ReturnsTrue)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    t_game.playTurn(Column{0}); // Player 1
    t_game.nextTurn();

    t_game.playTurn(Column{1});
    t_game.nextTurn();

    t_game.playTurn(Column{2});
    t_game.nextTurn();

    t_game.playTurn(Column{1}); // Player 1
    t_game.nextTurn();

    t_game.playTurn(Column{3});
    t_game.nextTurn();

    t_game.playTurn(Column{2});
    t_game.nextTurn();

    t_game.playTurn(Column{2}); // Player 1
    t_game.nextTurn();

    ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{3});
    t_game.nextTurn();

    t_game.playTurn(Column{3});
    t_game.nextTurn();

    t_game.playTurn(Column{3}); // Player 1
    t_game.nextTurn();

    ASSERT_TRUE(t_game.isWon());
}


TEST_F(GameTests, IsWon_ObliqueDownwardWinner_ReturnsTrue)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    t_game.playTurn(Column{3}); // Player 1
    t_game.nextTurn();

    t_game.playTurn(Column{2});
    t_game.nextTurn();

    t_game.playTurn(Column{1});
    t_game.nextTurn();

    t_game.playTurn(Column{2}); // Player 1
    t_game.nextTurn();

    t_game.playTurn(Column{0});
    t_game.nextTurn();

    t_game.playTurn(Column{1});
    t_game.nextTurn();

    t_game.playTurn(Column{1}); // Player 1
    t_game.nextTurn();

    ASSERT_FALSE(t_game.isWon());

    t_game.playTurn(Column{0});
    t_game.nextTurn();

    t_game.playTurn(Column{0});
    t_game.nextTurn();

    t_game.playTurn(Column{0}); // Player 1
    t_game.nextTurn();

    ASSERT_TRUE(t_game.isWon());
}


TEST_F(GameTests, IsWon_NoWinner_ReturnsFalse)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    ASSERT_FALSE(t_game.isWon());
}


TEST_F(GameTests, PlayTurn_ValidAndEmptyColumn_ReturnsTrue)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    ASSERT_TRUE(t_game.playTurn(Column{0}));
}


TEST_F(GameTests, PlayTurn_ValidAndFullColumn_ReturnsFalse)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    for(int i{0}; i < CLASSIC_GAMEBOARD->nbColumns(); ++i)
    {
        t_game.playTurn(Column{0});
    }

    // Column is filled...

    ASSERT_FALSE(t_game.playTurn(Column{0}));
}


TEST_F(GameTests, PlayTurn_ColumnValueTooSmall_ExceptionThrown)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    ASSERT_THROW(t_game.playTurn(Column{-1}), PreconditionException);
}


TEST_F(GameTests, PlayTurn_ColumnValueTooLarge_ExceptionThrown)
{
    Game t_game{THREE_PLAYERS, CLASSIC_GAMEBOARD, GameBoard::CONNECT_FOUR};

    ASSERT_THROW(t_game.playTurn(Column{CLASSIC_GAMEBOARD->nbColumns()}), PreconditionException);
}

