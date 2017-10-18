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
 * @file    test_GameBoard.cpp
 * @author  Eric Poirier
 * @date    December 2016
 * @version 1.0
 *
 * Unit tests for a the GameBoard class.
 *
 **************************************************************************************************/

#include <gtest/gtest.h>

#include <include/GameBoard.h>


using namespace std;
using namespace cxbase;


class GameBoardTests: public::testing::Test
{

public:
    GameBoardTests() {}

    int   NB_COLUMNS_MAX    {64};
    int   NB_ROWS_MAX       {64};
    int   NB_COLUMNS_MIN    {7};
    int   NB_ROWS_MIN       {6};

    GameBoard t_gameBoard;
    GameBoard t_gameBoard10x10 {10, 10};
};



TEST_F(GameBoardTests, Constructor_Default_CreatesStandardAndEmptyC4Board)
{
    ASSERT_EQ(t_gameBoard.nbRows(), NB_ROWS_MIN);
    ASSERT_EQ(t_gameBoard.nbColumns(), NB_COLUMNS_MIN);

    for (auto& row : t_gameBoard.grid())
    {
        for (auto& disc : row)
        {
            ASSERT_EQ(disc, Disc::Disc::NO_DISC);
        }
    }
}


TEST_F(GameBoardTests, Constructor_TwoValidParameters_NoExceptionThrown)
{

    ASSERT_EQ(t_gameBoard10x10.nbColumns(), 10);
    ASSERT_EQ(t_gameBoard10x10.nbRows(), 10);

    for (auto& row : t_gameBoard10x10.grid())
    {
        for (auto& disc : row)
        {
            ASSERT_EQ(disc, Disc::Disc::NO_DISC);
        }
    }
}


TEST(GameBoard, Constructor_ColumnParameterTooSmall_ExceptionThrown)
{
    ASSERT_THROW((GameBoard{10, 6}), PreconditionException);
}


TEST(GameBoard, Constructor_ColumnParameterTooLarge_ExceptionThrown)
{
    ASSERT_THROW((GameBoard{10, 65}), PreconditionException);
}


TEST(GameBoard, Constructor_RowParameterTooSmall_ExceptionThrown)
{
    ASSERT_THROW((GameBoard{5, 10}), PreconditionException);
}


TEST(GameBoard, Constructor_RowParameterTooLarge_ExceptionThrown)
{
    ASSERT_THROW((GameBoard{65, 10}), PreconditionException);
}


TEST_F(GameBoardTests, GridAccessor_ValidGameBoard_ReturnsGrid)
{
    std::vector < std::vector < Disc > > t_defaultGrid(NB_ROWS_MIN, std::vector<Disc>(NB_COLUMNS_MIN, Disc::NO_DISC));

    ASSERT_EQ(t_defaultGrid, t_gameBoard.grid());
}


TEST_F(GameBoardTests, NbRowsAccessor_ValidGameBoard_ReturnsNbRows)
{
    ASSERT_EQ(NB_ROWS_MIN, t_gameBoard.nbRows());
}


TEST_F(GameBoardTests, NbColumnsAccessor_ValidGameBoard_ReturnsNbColumns)
{
    ASSERT_EQ(NB_COLUMNS_MIN, t_gameBoard.nbColumns());
}


TEST_F(GameBoardTests, NbPositionsAccessor_ValidGameBoard_ReturnsNbPositions)
{
    ASSERT_EQ(NB_ROWS_MIN * NB_COLUMNS_MIN, t_gameBoard.nbPositions());
}


TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboard)
{
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);

    ASSERT_EQ(t_gameBoard(Position{Row{0}, Column{0}}), Disc::RED_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{1}, Column{0}}), Disc::NO_DISC);
}


TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious)
{
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);

    ASSERT_EQ(t_gameBoard(Position{Row{0}, Column{0}}), Disc::RED_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{1}, Column{0}}), Disc::BLACK_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{2}, Column{0}}), Disc::NO_DISC);
}


TEST_F(GameBoardTests, PlaceDisc_InvalidDiscAsParameter_ExceptionThrown)
{   
    ASSERT_THROW(t_gameBoard.placeDisc(Column{0}, Disc::NO_DISC), PreconditionException);
}


TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious2)
{
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);

    ASSERT_EQ(t_gameBoard(Position{Row{0}, Column{0}}), Disc::RED_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{1}, Column{0}}), Disc::BLACK_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{2}, Column{0}}), Disc::RED_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{3}, Column{0}}), Disc::NO_DISC);
}


TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious3)
{
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);

    ASSERT_EQ(t_gameBoard(Position{Row{0}, Column{0}}), Disc::RED_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{1}, Column{0}}), Disc::BLACK_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{2}, Column{0}}), Disc::RED_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{3}, Column{0}}), Disc::BLACK_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{4}, Column{0}}), Disc::NO_DISC);
}


TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious4)
{
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);

    ASSERT_EQ(t_gameBoard(Position{Row{0}, Column{0}}), Disc::RED_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{1}, Column{0}}), Disc::BLACK_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{2}, Column{0}}), Disc::RED_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{3}, Column{0}}), Disc::BLACK_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{4}, Column{0}}), Disc::RED_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{5}, Column{0}}), Disc::NO_DISC);
}


TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious5)
{
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);

    ASSERT_EQ(t_gameBoard(Position{Row{0}, Column{0}}), Disc::RED_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{1}, Column{0}}), Disc::BLACK_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{2}, Column{0}}), Disc::RED_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{3}, Column{0}}), Disc::BLACK_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{4}, Column{0}}), Disc::RED_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{5}, Column{0}}), Disc::BLACK_DISC);
}


TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious6)
{
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);

    // An extra disc:
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);

    ASSERT_EQ(t_gameBoard(Position{Row{0}, Column{0}}), Disc::RED_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{1}, Column{0}}), Disc::BLACK_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{2}, Column{0}}), Disc::RED_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{3}, Column{0}}), Disc::BLACK_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{4}, Column{0}}), Disc::RED_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{5}, Column{0}}), Disc::BLACK_DISC);
}


TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious7)
{
    t_gameBoard.placeDisc(Column{NB_COLUMNS_MIN - 1}, Disc::RED_DISC);

    ASSERT_EQ(t_gameBoard(Position{Row{0}, Column{NB_COLUMNS_MIN - 1}}), Disc::RED_DISC);
    ASSERT_EQ(t_gameBoard(Position{Row{1}, Column{NB_COLUMNS_MIN - 1}}), Disc::NO_DISC);
}


TEST_F(GameBoardTests, PlaceDisc_PlaceDisc_ColumnTooSmallAsParameter_ExceptionThrown)
{
    ASSERT_THROW(t_gameBoard.placeDisc(Column{-1}, Disc::RED_DISC), PreconditionException);
}


TEST_F(GameBoardTests, PlaceDisc_PlaceDisc_ColumnTooLargeAsParameter_ExceptionThrown)
{
    ASSERT_THROW(t_gameBoard.placeDisc(Column{NB_COLUMNS_MIN}, Disc::RED_DISC), PreconditionException);
}


TEST_F(GameBoardTests, IsColumFull_AFullColumnAsParameter_ReturnsTrue)
{
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);

    ASSERT_TRUE(t_gameBoard.isColumnFull(Column{0}));
}


TEST_F(GameBoardTests, IsColumFull_ANotFullColumnAsParameter_ReturnsFalse)
{
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, Disc::RED_DISC);

    ASSERT_FALSE(t_gameBoard.isColumnFull(Column{0}));
}


TEST_F(GameBoardTests, IsColumnFull_ColumnTooSmallAsParameter_ExceptionThrown)
{
    ASSERT_THROW(t_gameBoard.isColumnFull(Column{-1}), PreconditionException);
}


TEST_F(GameBoardTests, IsColumnFull_ColumnTooLargeAsParameter_ExceptionThrown)
{
    ASSERT_THROW(t_gameBoard.isColumnFull(Column{NB_COLUMNS_MIN}), PreconditionException);
}


TEST_F(GameBoardTests, EqualToOperator_TwoEqualGameBoardsAsParameters_ReturnsTrue)
{
    GameBoard t_gameBoard2;

    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{3}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{5}, Disc::RED_DISC);

    t_gameBoard2.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard2.placeDisc(Column{3}, Disc::RED_DISC);
    t_gameBoard2.placeDisc(Column{1}, Disc::BLACK_DISC);
    t_gameBoard2.placeDisc(Column{5}, Disc::RED_DISC);

    ASSERT_TRUE(t_gameBoard == t_gameBoard2);

}


TEST_F(GameBoardTests, EqualToOperator_TwoDifferentGameBoardsAsParameters_ReturnsFalse)
{
    GameBoard t_gameBoard2;

    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{3}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{5}, Disc::RED_DISC);

    t_gameBoard2.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard2.placeDisc(Column{3}, Disc::RED_DISC);
    t_gameBoard2.placeDisc(Column{1}, Disc::BLACK_DISC);

    // Different:
    t_gameBoard2.placeDisc(Column{4}, Disc::RED_DISC);

    ASSERT_FALSE(t_gameBoard == t_gameBoard2);
}


TEST_F(GameBoardTests, EqualToOperator_TwoDifferentSizeGameBoardsAsParameters_ExceptionThrown)
{
    GameBoard t_gameBoard2{8, 8};

    ASSERT_THROW(t_gameBoard == t_gameBoard2, PreconditionException);
}


TEST_F(GameBoardTests, NoEqualToOperator_TwoDifferentGameBoardsAsParameters_ReturnsTrue)
{
    GameBoard t_gameBoard2;

    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{3}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{5}, Disc::RED_DISC);

    t_gameBoard2.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard2.placeDisc(Column{3}, Disc::RED_DISC);
    t_gameBoard2.placeDisc(Column{1}, Disc::BLACK_DISC);

    // Different:
    t_gameBoard2.placeDisc(Column{5}, Disc::BLACK_DISC);

    ASSERT_NE(t_gameBoard, t_gameBoard2);
}


TEST_F(GameBoardTests, NoEqualToOperator_TwoEqualGameBoardsAsParameters_ReturnsFalse)
{
    GameBoard t_gameBoard2;

    t_gameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{3}, Disc::RED_DISC);
    t_gameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);
    t_gameBoard.placeDisc(Column{5}, Disc::RED_DISC);

    t_gameBoard2.placeDisc(Column{0}, Disc::BLACK_DISC);
    t_gameBoard2.placeDisc(Column{3}, Disc::RED_DISC);
    t_gameBoard2.placeDisc(Column{1}, Disc::BLACK_DISC);
    t_gameBoard2.placeDisc(Column{5}, Disc::RED_DISC);

    ASSERT_FALSE(t_gameBoard != t_gameBoard2);
}


TEST_F(GameBoardTests, NoEqualToOperator_TwoDifferentSizeGameBoardsAsParameters_ExceptionThrown)
{
    GameBoard t_gameBoard2{8,8};

    ASSERT_THROW(t_gameBoard != t_gameBoard2, PreconditionException);
}


TEST_F(GameBoardTests, FunctionOperator_ExistingPositionAsParameter_ReturnsPosition)
{
    Position thisPosition{Row{0}, Column{2}};

    t_gameBoard.placeDisc(Column{2}, Disc::BLACK_DISC);

    ASSERT_EQ(Disc::BLACK_DISC, t_gameBoard(thisPosition));
}


TEST_F(GameBoardTests, FunctionOperator_RowTooLargeInPositionParameter_ExceptionThrown)
{
    Position invalidPosition{Row{NB_ROWS_MAX + 1}, Column{4}};

    ASSERT_THROW(t_gameBoard(invalidPosition), PreconditionException);
}


TEST_F(GameBoardTests, FunctionOperator_ColumnTooLargeInPositionParameter_ExceptionThrown)
{
    Position invalidPosition{Row{4}, Column{NB_ROWS_MAX + 1}};

    ASSERT_THROW(t_gameBoard(invalidPosition), PreconditionException);
}


TEST_F(GameBoardTests, FunctionOperator_RowTooSmallInPositionParameter_ExceptionThrown)
{
    Position invalidPosition{Row{-1}, Column{4}};

    ASSERT_THROW(t_gameBoard(invalidPosition), PreconditionException);
}


TEST_F(GameBoardTests, FunctionOperator_ColumnTooSmallInPositionParameter_ExceptionThrown)
{
    Position invalidPosition{Row{5}, Column{-1}};

    ASSERT_THROW(t_gameBoard(invalidPosition), PreconditionException);
}


TEST_F(GameBoardTests, StreamInsertionOperator_StandardGameBoardAsParameter_PrintsCorrectFormat)
{
    std::ostringstream t_gameBoard1;

    for(int row{0}; row < t_gameBoard.nbRows(); ++row)
    {
        for(int column{0}; column < t_gameBoard.nbColumns(); ++column)
        {
            t_gameBoard.placeDisc(Column{column}, Disc::BLACK_DISC);
        }
    }

    t_gameBoard1 << t_gameBoard;

    std::ostringstream t_gameBoard2;
    t_gameBoard2 << "5  | K | K | K | K | K | K | K |" << endl
                 << "4  | K | K | K | K | K | K | K |" << endl
                 << "3  | K | K | K | K | K | K | K |" << endl
                 << "2  | K | K | K | K | K | K | K |" << endl
                 << "1  | K | K | K | K | K | K | K |" << endl
                 << "0  | K | K | K | K | K | K | K |" << endl
                 << "     0   1   2   3   4   5   6" << endl;

    ASSERT_EQ(t_gameBoard1.str(), t_gameBoard2.str());
}


TEST(GameBoard, StreamInsertionOperator_12x14GameBoardAsParameter_PrintsCorrectFormat)
{
    GameBoard t_gameBoard {12,14};

    ostringstream t_gameBoard1;

    for(int row{0}; row < t_gameBoard.nbRows(); ++row)
    {
        for(int column{0}; column < t_gameBoard.nbColumns(); ++column)
        {
            t_gameBoard.placeDisc(Column{column}, Disc::BLACK_DISC);
        }
    }

    t_gameBoard1 << t_gameBoard;

    ostringstream t_gameBoard2;
    t_gameBoard2 << "11 | K | K | K | K | K | K | K | K | K | K | K  | K  | K  | K  |" << endl
                 << "10 | K | K | K | K | K | K | K | K | K | K | K  | K  | K  | K  |" << endl
                 << "9  | K | K | K | K | K | K | K | K | K | K | K  | K  | K  | K  |" << endl
                 << "8  | K | K | K | K | K | K | K | K | K | K | K  | K  | K  | K  |" << endl
                 << "7  | K | K | K | K | K | K | K | K | K | K | K  | K  | K  | K  |" << endl
                 << "6  | K | K | K | K | K | K | K | K | K | K | K  | K  | K  | K  |" << endl
                 << "5  | K | K | K | K | K | K | K | K | K | K | K  | K  | K  | K  |" << endl
                 << "4  | K | K | K | K | K | K | K | K | K | K | K  | K  | K  | K  |" << endl
                 << "3  | K | K | K | K | K | K | K | K | K | K | K  | K  | K  | K  |" << endl
                 << "2  | K | K | K | K | K | K | K | K | K | K | K  | K  | K  | K  |" << endl
                 << "1  | K | K | K | K | K | K | K | K | K | K | K  | K  | K  | K  |" << endl
                 << "0  | K | K | K | K | K | K | K | K | K | K | K  | K  | K  | K  |" << endl
                 << "     0   1   2   3   4   5   6   7   8   9   10   11   12   13" << endl;

    ASSERT_EQ(t_gameBoard1.str(), t_gameBoard2.str());
}


TEST_F(GameBoardTests, IsWinner_RowUnderLimit_ExceptionThrown)
{
    Position rowUnderLimit{Row{-1}, Column{0}};

    ASSERT_THROW(t_gameBoard.isWinner(rowUnderLimit, GameBoard::CONNECT_FOUR), PreconditionException);
}


TEST_F(GameBoardTests, IsWinner_RowOverLimit_ExceptionThrown)
{
    Position rowOverLimit{Row{t_gameBoard.nbRows() + 1}, Column{0}};

    ASSERT_THROW(t_gameBoard.isWinner(rowOverLimit, GameBoard::CONNECT_FOUR), PreconditionException);
}


TEST_F(GameBoardTests, IsWinner_ColumnUnderLimit_ExceptionThrown)
{
    Position columnUnderLimit{Row{0}, Column{-1}};

    ASSERT_THROW(t_gameBoard.isWinner(columnUnderLimit, GameBoard::CONNECT_FOUR), PreconditionException);
}


TEST_F(GameBoardTests, IsWinner_ColumnOverLimit_ExceptionThrown)
{
    Position columnOverLimit{Row{0}, Column{t_gameBoard.nbColumns() + 1}};

    ASSERT_THROW(t_gameBoard.isWinner(columnOverLimit, GameBoard::CONNECT_FOUR), PreconditionException);
}


class ValidHorizontalGameBoardTests : public GameBoardTests
{
public:
    ValidHorizontalGameBoardTests(): GameBoardTests()
    {
        initialize();
    }

    GameBoard t_horizontalValidGameBoard{NB_ROWS_MIN, 15};

    void initialize()
    {
        // Left section:
        t_horizontalValidGameBoard.placeDisc(Column{0}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{0}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{0}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{1}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{1}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{1}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{2}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{2}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{2}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{2}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{2}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{2}, Disc::BLACK_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{3}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{3}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{3}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{3}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{3}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{3}, Disc::BLACK_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{4}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{4}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{4}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{4}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{4}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{4}, Disc::BLACK_DISC);

        // Center section:
        t_horizontalValidGameBoard.placeDisc(Column{5}, Disc::YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{5}, Disc::GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{5}, Disc::YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{5}, Disc::GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{5}, Disc::YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{5}, Disc::GREEN_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{6}, Disc::YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{6}, Disc::GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{6}, Disc::YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{6}, Disc::GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{6}, Disc::YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{6}, Disc::GREEN_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{7}, Disc::YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{7}, Disc::GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{7}, Disc::YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{7}, Disc::GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{7}, Disc::YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{7}, Disc::GREEN_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{8}, Disc::YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{8}, Disc::GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{8}, Disc::YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{8}, Disc::GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{8}, Disc::YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{8}, Disc::GREEN_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{9}, Disc::YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{9}, Disc::GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{9}, Disc::YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{9}, Disc::GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{9}, Disc::YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{9}, Disc::GREEN_DISC);

        // Right section:
        t_horizontalValidGameBoard.placeDisc(Column{10}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{10}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{10}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{10}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{10}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{10}, Disc::BLACK_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{11}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{11}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{11}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{11}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{11}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{11}, Disc::BLACK_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{12}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{12}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{12}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{12}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{12}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{12}, Disc::BLACK_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{13}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{13}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{13}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{13}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{13}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{13}, Disc::BLACK_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{14}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{14}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{14}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{14}, Disc::BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{14}, Disc::RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{14}, Disc::BLACK_DISC);

    }

};


TEST_F(ValidHorizontalGameBoardTests, IsWinner_InARowIs4_BordersChecked)
{
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{0}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{14}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{14}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{14}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{14}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{14}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{14}}, GameBoard::CONNECT_FOUR));
}


TEST_F(ValidHorizontalGameBoardTests, IsWinner_InARowIs5_BordersChecked)
{
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{0}}, GameBoard::CONNECT_FIVE));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{14}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{14}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{14}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{14}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{14}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{14}}, GameBoard::CONNECT_FIVE));
}


TEST_F(ValidHorizontalGameBoardTests, IsWinner_InARowIs6_BordersChecked)
{
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{0}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{14}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{14}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{14}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{14}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{14}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{14}}, GameBoard::CONNECT_SIX));
}


TEST_F(ValidHorizontalGameBoardTests, IsWinner_InARowIs4_GridInternalsChecked)
{
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, GameBoard::CONNECT_FOUR));
}


TEST_F(ValidHorizontalGameBoardTests, IsWinner_InARowIs5_GridInternalsChecked)
{
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, GameBoard::CONNECT_FIVE));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_FIVE));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, GameBoard::CONNECT_FIVE));
}


TEST_F(ValidHorizontalGameBoardTests, IsWinner_InARowIs6_GridInternalsChecked)
{
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, GameBoard::CONNECT_SIX));
}


TEST_F(ValidHorizontalGameBoardTests, IsWinner_InARowIs4_GridInternalBordersChecked)
{
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{4}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{4}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{4}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{4}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{4}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{4}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{5}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{5}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{5}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{5}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{5}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{5}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{9}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{9}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{9}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{9}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{9}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{9}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{10}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{10}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{10}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{10}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{10}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{10}}, GameBoard::CONNECT_FOUR));
}


TEST_F(ValidHorizontalGameBoardTests, IsWinner_InARowIs5_GridInternalBordersChecked)
{
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{4}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{4}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{4}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{4}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{4}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{4}}, GameBoard::CONNECT_FIVE));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{5}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{5}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{5}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{5}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{5}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{5}}, GameBoard::CONNECT_FIVE));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{9}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{9}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{9}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{9}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{9}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{9}}, GameBoard::CONNECT_FIVE));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{10}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{10}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{10}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{10}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{10}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{10}}, GameBoard::CONNECT_FIVE));
}


TEST_F(ValidHorizontalGameBoardTests, IsWinner_InARowIs6_GridInternalBordersChecked)
{
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{4}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{4}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{4}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{4}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{4}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{4}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{5}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{5}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{5}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{5}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{5}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{5}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{9}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{9}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{9}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{9}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{9}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{9}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{10}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{10}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{10}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{10}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{10}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{10}}, GameBoard::CONNECT_SIX));
}


class VerticalValidGameBoardTests : public GameBoardTests
{
public:
    VerticalValidGameBoardTests(): GameBoardTests()
    {
        initialize();
    }

    GameBoard t_verticalValidGameBoard{15, NB_COLUMNS_MIN};

    void initialize()
    {
        t_verticalValidGameBoard.placeDisc(Column{0}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, Disc::RED_DISC);

        t_verticalValidGameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, Disc::GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, Disc::GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, Disc::GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, Disc::GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, Disc::GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);

        t_verticalValidGameBoard.placeDisc(Column{2}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, Disc::RED_DISC);

        t_verticalValidGameBoard.placeDisc(Column{3}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, Disc::GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, Disc::GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, Disc::GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, Disc::GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, Disc::GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, Disc::BLACK_DISC);

        t_verticalValidGameBoard.placeDisc(Column{4}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, Disc::RED_DISC);

        t_verticalValidGameBoard.placeDisc(Column{5}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, Disc::GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, Disc::GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, Disc::GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, Disc::GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, Disc::GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, Disc::BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, Disc::BLACK_DISC);

        t_verticalValidGameBoard.placeDisc(Column{6}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, Disc::YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, Disc::RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, Disc::RED_DISC);
    }
};


TEST_F(VerticalValidGameBoardTests, IsWinner_InARowIs4_BordersChecked)
{
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{1}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{2}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{3}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{4}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{5}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{6}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{1}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{2}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{3}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{4}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{5}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{6}}, GameBoard::CONNECT_FOUR));
}


TEST_F(VerticalValidGameBoardTests, IsWinner_InARowIs5_BordersChecked)
{
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{1}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{2}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{3}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{4}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{5}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{6}}, GameBoard::CONNECT_FIVE));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{1}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{2}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{3}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{4}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{5}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{6}}, GameBoard::CONNECT_FIVE));
}


TEST_F(VerticalValidGameBoardTests, IsWinner_InARowIs6_BordersChecked)
{
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{1}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{2}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{3}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{4}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{5}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{6}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{1}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{2}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{3}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{4}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{5}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{6}}, GameBoard::CONNECT_SIX));
}


TEST_F(VerticalValidGameBoardTests, IsWinner_InARowIs4_GridInternalsChecked)
{
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{1}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{2}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{3}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{4}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{5}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{6}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{1}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{2}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{3}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{4}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{5}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{6}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{1}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{2}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{3}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{4}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{5}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{6}}, GameBoard::CONNECT_FOUR));
}


TEST_F(VerticalValidGameBoardTests, IsWinner_InARowIs5_GridInternalsChecked)
{
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{1}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{2}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{3}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{4}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{5}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{6}}, GameBoard::CONNECT_FIVE));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{1}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{2}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{3}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{4}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{5}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{6}}, GameBoard::CONNECT_FIVE));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{1}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{2}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{3}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{4}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{5}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{6}}, GameBoard::CONNECT_FIVE));
}


TEST_F(VerticalValidGameBoardTests, IsWinner_InARowIs6_GridInternalsChecked)
{
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{1}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{2}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{3}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{4}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{5}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{6}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{1}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{2}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{3}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{4}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{5}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{6}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{1}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{2}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{3}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{4}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{5}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{6}}, GameBoard::CONNECT_SIX));
}


TEST_F(VerticalValidGameBoardTests, IsWinner_InARowIs4_InternalBordersChecked)
{
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_FOUR));
}


TEST_F(VerticalValidGameBoardTests, IsWinner_InARowIs5_InternalBordersChecked)
{
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_FIVE));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_FIVE));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_FIVE));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_FIVE));
}


TEST_F(VerticalValidGameBoardTests, IsWinner_InARowIs6_InternalBordersChecked)
{
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_SIX));
}


class UpwardValidGameBoardTests : public GameBoardTests
{
public:

    UpwardValidGameBoardTests(): GameBoardTests()
    {
        initialize();
    }

    GameBoard t_upwardValidGameBoard{12, 11};

    void initialize()
    {
        t_upwardValidGameBoard.placeDisc(Column{0}, Disc::RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, Disc::RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, Disc::RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, Disc::RED_DISC);

        t_upwardValidGameBoard.placeDisc(Column{1}, Disc::WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, Disc::RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, Disc::RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);

        t_upwardValidGameBoard.placeDisc(Column{2}, Disc::BLUE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, Disc::BLUE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, Disc::RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, Disc::BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, Disc::RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, Disc::BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, Disc::GREEN_DISC);

        t_upwardValidGameBoard.placeDisc(Column{3}, Disc::WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, Disc::WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, Disc::WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, Disc::RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, Disc::BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, Disc::RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, Disc::BLUE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, Disc::BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, Disc::YELLOW_DISC);

        t_upwardValidGameBoard.placeDisc(Column{4}, Disc::BLUE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{4}, Disc::WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{4}, Disc::BLUE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{4}, Disc::WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{4}, Disc::RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{4}, Disc::BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{4}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{4}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{4}, Disc::RED_DISC);

        t_upwardValidGameBoard.placeDisc(Column{5}, Disc::BLUE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{5}, Disc::WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{5}, Disc::BLUE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{5}, Disc::WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{5}, Disc::BLUE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{5}, Disc::WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{5}, Disc::BLUE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{5}, Disc::WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{5}, Disc::BLUE_DISC);

        t_upwardValidGameBoard.placeDisc(Column{6}, Disc::RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{6}, Disc::BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{6}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{6}, Disc::GREEN_DISC);

        t_upwardValidGameBoard.placeDisc(Column{7}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{7}, Disc::RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{7}, Disc::BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{7}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{7}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{7}, Disc::YELLOW_DISC);

        t_upwardValidGameBoard.placeDisc(Column{8}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{8}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{8}, Disc::RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{8}, Disc::BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{8}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{8}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{8}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{8}, Disc::GREEN_DISC);

        t_upwardValidGameBoard.placeDisc(Column{9}, Disc::BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{9}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{9}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{9}, Disc::RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{9}, Disc::BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{9}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{9}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{9}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{9}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{9}, Disc::BLACK_DISC);

        t_upwardValidGameBoard.placeDisc(Column{10}, Disc::RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, Disc::BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, Disc::RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, Disc::BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, Disc::YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, Disc::GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, Disc::BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, Disc::RED_DISC);
    }
};


TEST_F(UpwardValidGameBoardTests, IsWinner_InARowIs4_CornersChecked)
{

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{0}}, GameBoard::CONNECT_FOUR));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{1}}, GameBoard::CONNECT_FOUR));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{1}}, GameBoard::CONNECT_FOUR));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{2}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{2}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{3}}, GameBoard::CONNECT_FOUR));



    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{10}}, GameBoard::CONNECT_FOUR));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{9}}, GameBoard::CONNECT_FOUR));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{10}}, GameBoard::CONNECT_FOUR));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{8}}, GameBoard::CONNECT_FOUR));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{8}, Column{9}}, GameBoard::CONNECT_FOUR));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{10}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{8}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{8}, Column{10}}, GameBoard::CONNECT_FOUR));



    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{10}}, GameBoard::CONNECT_FOUR));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{9}}, GameBoard::CONNECT_FOUR));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{10}}, GameBoard::CONNECT_FOUR));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{8}}, GameBoard::CONNECT_FOUR));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{9}}, GameBoard::CONNECT_FOUR));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{10}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{7}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{9}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{10}}, GameBoard::CONNECT_FOUR));
}


TEST_F(UpwardValidGameBoardTests, IsWinner_InARowIs5_CornersChecked)
{

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{0}}, GameBoard::CONNECT_FIVE));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{1}}, GameBoard::CONNECT_FIVE));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{1}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{2}}, GameBoard::CONNECT_FIVE));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{2}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{3}}, GameBoard::CONNECT_FIVE));



    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{10}}, GameBoard::CONNECT_FIVE));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{9}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{10}}, GameBoard::CONNECT_FIVE));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{8}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{8}, Column{9}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{10}}, GameBoard::CONNECT_FIVE));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{8}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{8}, Column{10}}, GameBoard::CONNECT_FIVE));



    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{10}}, GameBoard::CONNECT_FIVE));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{9}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{10}}, GameBoard::CONNECT_FIVE));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{8}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{9}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{10}}, GameBoard::CONNECT_FIVE));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{7}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{9}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{10}}, GameBoard::CONNECT_FIVE));
}


TEST_F(UpwardValidGameBoardTests, IsWinner_InARowIs6_CornersChecked)
{

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{0}}, GameBoard::CONNECT_SIX));

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{0}}, GameBoard::CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{1}}, GameBoard::CONNECT_SIX));

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{0}}, GameBoard::CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{1}}, GameBoard::CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{2}}, GameBoard::CONNECT_SIX));

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{0}}, GameBoard::CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{2}}, GameBoard::CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{3}}, GameBoard::CONNECT_SIX));



        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{10}}, GameBoard::CONNECT_SIX));

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{9}}, GameBoard::CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{10}}, GameBoard::CONNECT_SIX));

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{8}}, GameBoard::CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{8}, Column{9}}, GameBoard::CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{10}}, GameBoard::CONNECT_SIX));

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{7}}, GameBoard::CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{8}}, GameBoard::CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{8}, Column{10}}, GameBoard::CONNECT_SIX));



        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{10}}, GameBoard::CONNECT_SIX));

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{9}}, GameBoard::CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{10}}, GameBoard::CONNECT_SIX));

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{8}}, GameBoard::CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{9}}, GameBoard::CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{10}}, GameBoard::CONNECT_SIX));

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{7}}, GameBoard::CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{9}}, GameBoard::CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{10}}, GameBoard::CONNECT_SIX));
}


TEST_F(UpwardValidGameBoardTests, IsWinner_InARowIs4_BordersChecked)
{

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{2}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{4}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{2}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{4}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{2}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{4}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{2}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{4}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{2}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{8}, Column{4}}, GameBoard::CONNECT_FOUR));



    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{8}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{10}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{8}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{10}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{8}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{10}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{8}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{10}}, GameBoard::CONNECT_FOUR));
}


TEST_F(UpwardValidGameBoardTests, IsWinner_InARowIs5_BordersChecked)
{

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{2}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{4}}, GameBoard::CONNECT_FIVE));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{2}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{4}}, GameBoard::CONNECT_FIVE));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{2}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{4}}, GameBoard::CONNECT_FIVE));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{2}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{4}}, GameBoard::CONNECT_FIVE));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{2}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{8}, Column{4}}, GameBoard::CONNECT_FIVE));



    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{8}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{10}}, GameBoard::CONNECT_FIVE));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{8}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{10}}, GameBoard::CONNECT_FIVE));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{8}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{10}}, GameBoard::CONNECT_FIVE));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{8}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{10}}, GameBoard::CONNECT_FIVE));
}


TEST_F(UpwardValidGameBoardTests, IsWinner_InARowIs6_BordersChecked)
{

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{2}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{4}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{2}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{4}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{2}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{4}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{2}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{4}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{2}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{8}, Column{4}}, GameBoard::CONNECT_SIX));



    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{8}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{10}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{8}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{10}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{8}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{10}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{8}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{10}}, GameBoard::CONNECT_SIX));
}


class DownwardValidGameBoardTests : public GameBoardTests
{
public:

    DownwardValidGameBoardTests(): GameBoardTests()
    {
        initialize();
    }

    GameBoard t_downwardValidGameBoard{12, 11};

    void initialize()
    {
        t_downwardValidGameBoard.placeDisc(Column{0}, Disc::RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, Disc::GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, Disc::GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, Disc::BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, Disc::BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, Disc::BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, Disc::GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, Disc::BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, Disc::RED_DISC);

        t_downwardValidGameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, Disc::GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, Disc::GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, Disc::WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, Disc::WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, Disc::WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, Disc::GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, Disc::BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, Disc::RED_DISC);

        t_downwardValidGameBoard.placeDisc(Column{2}, Disc::GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{2}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{2}, Disc::GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{2}, Disc::BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{2}, Disc::BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{2}, Disc::BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{2}, Disc::GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{2}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{2}, Disc::BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{2}, Disc::RED_DISC);

        t_downwardValidGameBoard.placeDisc(Column{3}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{3}, Disc::GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{3}, Disc::WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{3}, Disc::WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{3}, Disc::WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{3}, Disc::GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{3}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{3}, Disc::BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{3}, Disc::RED_DISC);

        t_downwardValidGameBoard.placeDisc(Column{4}, Disc::GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{4}, Disc::BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{4}, Disc::BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{4}, Disc::BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{4}, Disc::GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{4}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{4}, Disc::BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{4}, Disc::RED_DISC);

        t_downwardValidGameBoard.placeDisc(Column{5}, Disc::BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{5}, Disc::WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{5}, Disc::BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{5}, Disc::WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{5}, Disc::BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{5}, Disc::WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{5}, Disc::BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{5}, Disc::WHITE_DISC);

        t_downwardValidGameBoard.placeDisc(Column{6}, Disc::WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, Disc::GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, Disc::BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, Disc::RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, Disc::WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, Disc::WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, Disc::WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, Disc::BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, Disc::RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, Disc::YELLOW_DISC);

        t_downwardValidGameBoard.placeDisc(Column{7}, Disc::GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, Disc::BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, Disc::RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, Disc::BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, Disc::BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, Disc::BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, Disc::BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, Disc::RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, Disc::GREEN_DISC);

        t_downwardValidGameBoard.placeDisc(Column{8}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, Disc::BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, Disc::RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, Disc::WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, Disc::WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, Disc::WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, Disc::BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, Disc::RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, Disc::GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, Disc::YELLOW_DISC);

        t_downwardValidGameBoard.placeDisc(Column{9}, Disc::BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, Disc::RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, Disc::BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, Disc::BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, Disc::BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, Disc::BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, Disc::RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, Disc::GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, Disc::BLACK_DISC);

        t_downwardValidGameBoard.placeDisc(Column{10}, Disc::RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, Disc::WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, Disc::WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, Disc::WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, Disc::BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, Disc::RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, Disc::GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, Disc::YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, Disc::BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, Disc::RED_DISC);
    }
};


TEST_F(DownwardValidGameBoardTests, IsWinner_InARowIs4_CornersChecked)
{

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{0}}, GameBoard::CONNECT_FOUR));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{1}}, GameBoard::CONNECT_FOUR));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{1}}, GameBoard::CONNECT_FOUR));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{2}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{3}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{1}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{3}}, GameBoard::CONNECT_FOUR));


    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{7}}, GameBoard::CONNECT_FOUR));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{7}}, GameBoard::CONNECT_FOUR));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{8}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{3}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{7}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{8}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{9}}, GameBoard::CONNECT_FOUR));


    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{10}}, GameBoard::CONNECT_FOUR));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{9}}, GameBoard::CONNECT_FOUR));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{10}}, GameBoard::CONNECT_FOUR));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{8}}, GameBoard::CONNECT_FOUR));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{9}}, GameBoard::CONNECT_FOUR));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{10}}, GameBoard::CONNECT_FOUR));

    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{7}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{9}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{10}}, GameBoard::CONNECT_FOUR));
}


TEST_F(DownwardValidGameBoardTests, IsWinner_InARowIs5_CornersChecked)
{

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{0}}, GameBoard::CONNECT_FIVE));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{1}}, GameBoard::CONNECT_FIVE));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{1}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{2}}, GameBoard::CONNECT_FIVE));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{3}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{1}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{3}}, GameBoard::CONNECT_FIVE));


    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{7}}, GameBoard::CONNECT_FIVE));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{7}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{8}}, GameBoard::CONNECT_FIVE));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{3}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{7}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{8}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{9}}, GameBoard::CONNECT_FIVE));


    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{10}}, GameBoard::CONNECT_FIVE));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{9}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{10}}, GameBoard::CONNECT_FIVE));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{8}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{9}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{10}}, GameBoard::CONNECT_FIVE));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{7}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{9}}, GameBoard::CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{10}}, GameBoard::CONNECT_FIVE));
}


TEST_F(DownwardValidGameBoardTests, IsWinner_InARowIs6_CornersChecked)
{

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{0}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{1}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{1}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{2}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{3}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{1}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{3}}, GameBoard::CONNECT_SIX));


    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{7}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{7}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{8}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{3}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{7}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{8}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{9}}, GameBoard::CONNECT_SIX));


    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{10}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{9}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{10}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{8}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{9}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{10}}, GameBoard::CONNECT_SIX));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{7}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{9}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{10}}, GameBoard::CONNECT_SIX));
}


TEST_F(DownwardValidGameBoardTests, IsWinner_InARowIs4_BordersChecked)
{

    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{2}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{4}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{2}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{4}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{2}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{5}, Column{4}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{2}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{4}, Column{4}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{4}, Column{0}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{2}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{4}}, GameBoard::CONNECT_FOUR));


    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{8}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{10}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{8}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{10}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{8}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{5}, Column{10}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{6}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{8}}, GameBoard::CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{4}, Column{10}}, GameBoard::CONNECT_FOUR));
}


TEST_F(DownwardValidGameBoardTests, IsWinner_InARowIs5_BordersChecked)
{

    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{2}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{4}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{2}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{4}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{2}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{5}, Column{4}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{2}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{4}, Column{4}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{4}, Column{0}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{2}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{4}}, GameBoard::CONNECT_FIVE));


    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{8}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{10}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{8}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{10}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{8}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{5}, Column{10}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{6}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{8}}, GameBoard::CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{4}, Column{10}}, GameBoard::CONNECT_FIVE));
}


TEST_F(DownwardValidGameBoardTests, IsWinner_InARowIs6_BordersChecked)
{

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{2}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{4}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{2}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{4}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{2}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{5}, Column{4}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{2}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{4}, Column{4}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{4}, Column{0}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{2}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{4}}, GameBoard::CONNECT_SIX));


    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{8}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{10}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{8}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{10}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{8}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{5}, Column{10}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{6}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{8}}, GameBoard::CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{4}, Column{10}}, GameBoard::CONNECT_SIX));
}
