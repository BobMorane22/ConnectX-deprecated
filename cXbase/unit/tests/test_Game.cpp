/***********************************************************************************************//**
 * @file    test_Game.cpp
 * @author  Eric Poirier
 * @date    January 2017
 * @version 0.1
 *
 * Unit tests for a the Game class.
 *
 **************************************************************************************************/

#include <publicAPI/Game.h>

#include <gtest/gtest.h>

USING_NAMESPACE_STD
USING_NAMESPACE_CXBASE

class GameTests: public::testing::Test
{

public:

    GameTests() {};

    int   NB_COLUMNS_MAX                    {64};
    int   NB_ROWS_MAX                       {64};
    int   NB_COLUMNS_MIN                    {7};
    int   NB_ROWS_MIN                       {6};

    Disc NO_DISC                            {Color{Name{"No color"},    AsciiColorCode{' '}}};
    Disc BLACK_DISC                         {Color{Name{"Black"},       AsciiColorCode{'B'}}};
    Disc RED_DISC                           {Color{Name{"Red"},         AsciiColorCode{'R'}}};
    Disc YELLOW_DISC                        {Color{Name{"Yellow"},      AsciiColorCode{'Y'}}};

    shared_ptr<Player> FIRST_PLAYER         {new Player{Name{"First Player"},      BLACK_DISC}};
    shared_ptr<Player> SECOND_PLAYER        {new Player{Name{"Second Player"},     RED_DISC}};
    shared_ptr<Player> THIRD_PLAYER         {new Player{Name{"Third Player"},      YELLOW_DISC}};

    shared_ptr<GameBoard> CLASSIC_GAMEBOARD {new GameBoard};
    int CONNECT_FOUR                        {4};

};


TEST_F(GameTests, Constructor_ValidArguments_CreatesValidGame)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    ASSERT_NO_THROW((Game {players, CLASSIC_GAMEBOARD, CONNECT_FOUR}));

    Game t_game3 {players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

    ASSERT_EQ(t_game3.inARowValue(), CONNECT_FOUR);

}

TEST_F(GameTests, Constructor_NotEnoughPlayers_ExceptionThrown)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));

    ASSERT_THROW((Game {players, CLASSIC_GAMEBOARD, CONNECT_FOUR}), PreconditionException);
}

TEST_F(GameTests, Constructor_InARowTooSmall_ExceptionThrown)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    ASSERT_THROW((Game {players, CLASSIC_GAMEBOARD, 1}), PreconditionException);
}

TEST_F(GameTests, Constructor_InARowTooLarge_ExceptionThrown)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    int InARowTooLarge {min(CLASSIC_GAMEBOARD->nbRows(), CLASSIC_GAMEBOARD->nbColumns()) + 1};

    ASSERT_THROW((Game {players, CLASSIC_GAMEBOARD, InARowTooLarge}), PreconditionException);
}

TEST_F(GameTests, ActivePlayerAccessor_ThreePlayerGameAndNoTurn_ReturnsFirstPlayer)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

    // Need to create new Player object because FISRT_PLAYER was std::moved.
    Player PLAYER1{Name{"First Player"},      BLACK_DISC};

    ASSERT_EQ(t_game.activePlayer(), PLAYER1);
}

TEST_F(GameTests, ActivePlayerAccessor_ThreePlayerGameAndTwoTurns_ReturnsThirdPlayer)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

    // Need to create new Player object because FISRT_PLAYER was std::moved.
    Player PLAYER3{Name{"Third Player"}, YELLOW_DISC};

    t_game.nextTurn();
    t_game.nextTurn();

    ASSERT_EQ(t_game.activePlayer(), PLAYER3);
}

TEST_F(GameTests, ActivePlayerAccessor_ThreePlayerGameAndThreeTurns_ReturnsFirstPlayer)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

    // Need to create new Player object because FISRT_PLAYER was std::moved.
    Player PLAYER1{Name{"First Player"}, BLACK_DISC};

    t_game.nextTurn();
    t_game.nextTurn();
    t_game.nextTurn();

    ASSERT_EQ(t_game.activePlayer(), PLAYER1);
}

TEST_F(GameTests, InARowValueAccessor_ValidObject_ReturnsInARowValue)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

    ASSERT_EQ(t_game.inARowValue(), 4);
}

TEST_F(GameTests, NbOfTurnsPlayedAccessor_ValidObject_ReturnsNbOfTurnsPlayed)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

    t_game.nextTurn();
    t_game.nextTurn();
    t_game.nextTurn();
    t_game.nextTurn();

    ASSERT_EQ(t_game.nbOfTurnsPlayed(), 4);
}

TEST_F(GameTests, CurrentTurnAccessor_ValidObject_ReturnsCurrentTurn)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

    ASSERT_EQ(t_game.currentTurn(), 0);
}

TEST_F(GameTests, IsDraw_FirstTurn_ReturnsFalse)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

    ASSERT_FALSE(t_game.isDraw());
}

TEST_F(GameTests, IsDraw_AllTurnsPlayedPlusOne_ReturnsTrue)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

    for(int i{0}; i < CLASSIC_GAMEBOARD->nbPositions(); ++i)
    {
        t_game.nextTurn(); // 43 turns for a classic GameBoard.
    }

    ASSERT_TRUE(t_game.isDraw());
}

TEST_F(GameTests, NextTurn_ToFirstTurn_TurnIsOneActivePlayerIsTwo)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

    t_game.nextTurn();

    Player t_player{Name{"Second Player"}, RED_DISC};

    ASSERT_EQ(t_game.currentTurn(), 1);
    ASSERT_EQ(t_game.activePlayer(), t_player);
}

TEST_F(GameTests, NextTurn_AllTurns_TurnIs42ActivePlayerIsFirst)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

    for(int i{0}; i < CLASSIC_GAMEBOARD->nbPositions() - 1; ++i)
    {
        t_game.nextTurn(); // 42 turns for a classic GameBoard.
    }

    Player t_player{Name{"Third Player"}, YELLOW_DISC};

    ASSERT_EQ(t_game.nbOfTurnsPlayed(), CLASSIC_GAMEBOARD->nbPositions() - 1);
    ASSERT_EQ(t_game.activePlayer(), t_player);
}

TEST_F(GameTests, NextTurn_ExceedsAllTurns_TurnIs43)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

    for(int i{0}; i < CLASSIC_GAMEBOARD->nbPositions(); ++i)
    {
        t_game.nextTurn(); // 43 turns for a classic GameBoard.
    }

    ASSERT_EQ(t_game.nbOfTurnsPlayed(), CLASSIC_GAMEBOARD->nbPositions());

    t_game.nextTurn();

    ASSERT_EQ(t_game.nbOfTurnsPlayed(), CLASSIC_GAMEBOARD->nbPositions());
}

TEST_F(GameTests, IsWon_HorizontalWinner_ReturnsTrue)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

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
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

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
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

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
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

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
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

    ASSERT_FALSE(t_game.isWon());
}

TEST_F(GameTests, PlayTurn_ValidAndEmptyColumn_ReturnsTrue)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

    ASSERT_TRUE(t_game.playTurn(Column{0}));
}

TEST_F(GameTests, PlayTurn_ValidAndFullColumn_ReturnsFalse)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

    for(int i{0}; i < CLASSIC_GAMEBOARD->nbColumns(); ++i)
    {
        t_game.playTurn(Column{0});
    }

    // Column is filled...

    ASSERT_FALSE(t_game.playTurn(Column{0}));
}

TEST_F(GameTests, PlayTurn_ColumnValueTooSmall_ExceptionThrown)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

    ASSERT_THROW(t_game.playTurn(Column{-1}), PreconditionException);
}

TEST_F(GameTests, PlayTurn_ColumnValueTooLarge_ExceptionThrown)
{
    vector<shared_ptr<Player>> players;
    players.push_back(move(FIRST_PLAYER));
    players.push_back(move(SECOND_PLAYER));
    players.push_back(move(THIRD_PLAYER));

    Game t_game{players, CLASSIC_GAMEBOARD, CONNECT_FOUR};

    ASSERT_THROW(t_game.playTurn(Column{CLASSIC_GAMEBOARD->nbColumns()}), PreconditionException);
}