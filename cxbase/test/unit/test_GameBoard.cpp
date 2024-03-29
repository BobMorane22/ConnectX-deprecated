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

    for(int row{0}; row < t_gameBoard.nbRows(); ++row)
    {
        for(int column{0}; column < t_gameBoard.nbColumns(); ++column)
        {
            ASSERT_EQ(t_gameBoard(Position{Row{row}, Column{column}}), Disc::noDisc());
        }
    }
}


TEST_F(GameBoardTests, Constructor_TwoValidParameters_NoExceptionThrown)
{

    ASSERT_EQ(t_gameBoard10x10.nbColumns(), 10);
    ASSERT_EQ(t_gameBoard10x10.nbRows(), 10);

    for(int row{0}; row < t_gameBoard.nbRows(); ++row)
    {
        for(int column{0}; column < t_gameBoard.nbColumns(); ++column)
        {
            ASSERT_EQ(t_gameBoard10x10(Position{Row{row}, Column{column}}), Disc::noDisc());
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
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());

    ASSERT_EQ(t_gameBoard(Position{Row{0}, Column{0}}), Disc::redDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{1}, Column{0}}), Disc::noDisc());
}


TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious)
{
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());

    ASSERT_EQ(t_gameBoard(Position{Row{0}, Column{0}}), Disc::redDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{1}, Column{0}}), Disc::blackDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{2}, Column{0}}), Disc::noDisc());
}


TEST_F(GameBoardTests, PlaceDisc_InvalidDiscAsParameter_ExceptionThrown)
{   
    ASSERT_THROW(t_gameBoard.placeDisc(Column{0}, Disc::noDisc()), PreconditionException);
}


TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious2)
{
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());

    ASSERT_EQ(t_gameBoard(Position{Row{0}, Column{0}}), Disc::redDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{1}, Column{0}}), Disc::blackDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{2}, Column{0}}), Disc::redDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{3}, Column{0}}), Disc::noDisc());
}


TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious3)
{
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());

    ASSERT_EQ(t_gameBoard(Position{Row{0}, Column{0}}), Disc::redDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{1}, Column{0}}), Disc::blackDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{2}, Column{0}}), Disc::redDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{3}, Column{0}}), Disc::blackDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{4}, Column{0}}), Disc::noDisc());
}


TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious4)
{
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());

    ASSERT_EQ(t_gameBoard(Position{Row{0}, Column{0}}), Disc::redDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{1}, Column{0}}), Disc::blackDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{2}, Column{0}}), Disc::redDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{3}, Column{0}}), Disc::blackDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{4}, Column{0}}), Disc::redDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{5}, Column{0}}), Disc::noDisc());
}


TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious5)
{
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());

    ASSERT_EQ(t_gameBoard(Position{Row{0}, Column{0}}), Disc::redDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{1}, Column{0}}), Disc::blackDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{2}, Column{0}}), Disc::redDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{3}, Column{0}}), Disc::blackDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{4}, Column{0}}), Disc::redDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{5}, Column{0}}), Disc::blackDisc());
}


TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious6)
{
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());

    // An extra disc:
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());

    ASSERT_EQ(t_gameBoard(Position{Row{0}, Column{0}}), Disc::redDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{1}, Column{0}}), Disc::blackDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{2}, Column{0}}), Disc::redDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{3}, Column{0}}), Disc::blackDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{4}, Column{0}}), Disc::redDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{5}, Column{0}}), Disc::blackDisc());
}


TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious7)
{
    t_gameBoard.placeDisc(Column{NB_COLUMNS_MIN - 1}, Disc::redDisc());

    ASSERT_EQ(t_gameBoard(Position{Row{0}, Column{NB_COLUMNS_MIN - 1}}), Disc::redDisc());
    ASSERT_EQ(t_gameBoard(Position{Row{1}, Column{NB_COLUMNS_MIN - 1}}), Disc::noDisc());
}


TEST_F(GameBoardTests, PlaceDisc_PlaceDisc_ColumnTooSmallAsParameter_ExceptionThrown)
{
    ASSERT_THROW(t_gameBoard.placeDisc(Column{-1}, Disc::redDisc()), PreconditionException);
}


TEST_F(GameBoardTests, PlaceDisc_PlaceDisc_ColumnTooLargeAsParameter_ExceptionThrown)
{
    ASSERT_THROW(t_gameBoard.placeDisc(Column{NB_COLUMNS_MIN}, Disc::redDisc()), PreconditionException);
}


TEST_F(GameBoardTests, IsColumFull_AFullColumnAsParameter_ReturnsTrue)
{
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());

    ASSERT_TRUE(t_gameBoard.isColumnFull(Column{0}));
}


TEST_F(GameBoardTests, IsColumFull_ANotFullColumnAsParameter_ReturnsFalse)
{
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{0}, Disc::redDisc());

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

    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{3}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{1}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{5}, Disc::redDisc());

    t_gameBoard2.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard2.placeDisc(Column{3}, Disc::redDisc());
    t_gameBoard2.placeDisc(Column{1}, Disc::blackDisc());
    t_gameBoard2.placeDisc(Column{5}, Disc::redDisc());

    ASSERT_TRUE(t_gameBoard == t_gameBoard2);

}


TEST_F(GameBoardTests, EqualToOperator_TwoDifferentGameBoardsAsParameters_ReturnsFalse)
{
    GameBoard t_gameBoard2;

    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{3}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{1}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{5}, Disc::redDisc());

    t_gameBoard2.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard2.placeDisc(Column{3}, Disc::redDisc());
    t_gameBoard2.placeDisc(Column{1}, Disc::blackDisc());

    // Different:
    t_gameBoard2.placeDisc(Column{4}, Disc::redDisc());

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

    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{3}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{1}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{5}, Disc::redDisc());

    t_gameBoard2.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard2.placeDisc(Column{3}, Disc::redDisc());
    t_gameBoard2.placeDisc(Column{1}, Disc::blackDisc());

    // Different:
    t_gameBoard2.placeDisc(Column{5}, Disc::blackDisc());

    ASSERT_NE(t_gameBoard, t_gameBoard2);
}


TEST_F(GameBoardTests, NoEqualToOperator_TwoEqualGameBoardsAsParameters_ReturnsFalse)
{
    GameBoard t_gameBoard2;

    t_gameBoard.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{3}, Disc::redDisc());
    t_gameBoard.placeDisc(Column{1}, Disc::blackDisc());
    t_gameBoard.placeDisc(Column{5}, Disc::redDisc());

    t_gameBoard2.placeDisc(Column{0}, Disc::blackDisc());
    t_gameBoard2.placeDisc(Column{3}, Disc::redDisc());
    t_gameBoard2.placeDisc(Column{1}, Disc::blackDisc());
    t_gameBoard2.placeDisc(Column{5}, Disc::redDisc());

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

    t_gameBoard.placeDisc(Column{2}, Disc::blackDisc());

    ASSERT_EQ(Disc::blackDisc(), t_gameBoard(thisPosition));
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


