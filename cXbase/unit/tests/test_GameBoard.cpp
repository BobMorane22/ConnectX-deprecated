/***********************************************************************************************//**
 * @file    test_GameBoard.cpp
 * @author  Eric Poirier
 * @date    December 2016
 * @version 0.1
 *
 * Unit tests for a the GameBoard class.
 *
 **************************************************************************************************/

#include <publicAPI/GameBoard.h>

#include <gtest/gtest.h>

USING_NAMESPACE_STD
USING_NAMESPACE_CXBASE


class GameBoardTests: public::testing::Test
{

public:
    GameBoardTests() {}

    int   NB_COLUMNS_MAX    {64};
    int   NB_ROWS_MAX       {64};
    int   NB_COLUMNS_MIN    {7};
    int   NB_ROWS_MIN       {6};

    Disc NO_DISC        {Color{Name{"No color"},    AsciiColorCode{' '}}};
    Disc BLACK_DISC     {Color{Name{"Black"},       AsciiColorCode{'B'}}};
    Disc RED_DISC       {Color{Name{"Red"},         AsciiColorCode{'R'}}};
    Disc YELLOW_DISC    {Color{Name{"Yellow"},      AsciiColorCode{'Y'}}};
    Disc GREEN_DISC     {Color{Name{"Green"},       AsciiColorCode{'G'}}};
    Disc WHITE_DISC     {Color{Name{"White"},       AsciiColorCode{'W'}}};
    Disc BLUE_DISC      {Color{Name{"Blue"},        AsciiColorCode{'b'}}};

    int CONNECT_FOUR    {4};
    int CONNECT_FIVE    {5};
    int CONNECT_SIX     {6};

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
            ASSERT_EQ(disc, NO_DISC);
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
            ASSERT_EQ(disc, NO_DISC);
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
    std::vector < std::vector < Disc > > t_defaultGrid(NB_ROWS_MIN, std::vector<Disc>(NB_COLUMNS_MIN, NO_DISC));

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

TEST_F(GameBoardTests, SpecificPositionAccessor_ExistingPositionAsParameter_ReturnsPosition)
{
    Position thisPosition{Row{0}, Column{2}};

    t_gameBoard.placeDisc(Column{2}, BLACK_DISC);

    ASSERT_EQ(BLACK_DISC, t_gameBoard.discAtPosition(thisPosition));
}

TEST_F(GameBoardTests, SpecificPositionAccessor_RowTooLargeInPositionParameter_ExceptionThrown)
{
    Position invalidPosition{Row{NB_ROWS_MAX + 1}, Column{4}};

    ASSERT_THROW(t_gameBoard.discAtPosition(invalidPosition), PreconditionException);
}

TEST_F(GameBoardTests, SpecificPositionAccessor_ColumnTooLargeInPositionParameter_ExceptionThrown)
{
    Position invalidPosition{Row{4}, Column{NB_ROWS_MAX + 1}};

    ASSERT_THROW(t_gameBoard.discAtPosition(invalidPosition), PreconditionException);
}

TEST_F(GameBoardTests, SpecificPositionAccessor_RowTooSmallInPositionParameter_ExceptionThrown)
{
    Position invalidPosition{Row{-1}, Column{4}};

    ASSERT_THROW(t_gameBoard.discAtPosition(invalidPosition), PreconditionException);
}

TEST_F(GameBoardTests, SpecificPositionAccessor_ColumnTooSmallInPositionParameter_ExceptionThrown)
{
    Position invalidPosition{Row{5}, Column{-1}};

    ASSERT_THROW(t_gameBoard.discAtPosition(invalidPosition), PreconditionException);
}

TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboard)
{
    t_gameBoard.placeDisc(Column{0}, RED_DISC);

    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{0}, Column{0}}), RED_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{1}, Column{0}}), NO_DISC);
}

TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious)
{
    t_gameBoard.placeDisc(Column{0}, RED_DISC);
    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);

    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{0}, Column{0}}), RED_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{1}, Column{0}}), BLACK_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{2}, Column{0}}), NO_DISC);
}

TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious2)
{
    t_gameBoard.placeDisc(Column{0}, RED_DISC);
    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, RED_DISC);

    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{0}, Column{0}}), RED_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{1}, Column{0}}), BLACK_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{2}, Column{0}}), RED_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{3}, Column{0}}), NO_DISC);
}

TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious3)
{
    t_gameBoard.placeDisc(Column{0}, RED_DISC);
    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, RED_DISC);
    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);

    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{0}, Column{0}}), RED_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{1}, Column{0}}), BLACK_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{2}, Column{0}}), RED_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{3}, Column{0}}), BLACK_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{4}, Column{0}}), NO_DISC);
}

TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious4)
{
    t_gameBoard.placeDisc(Column{0}, RED_DISC);
    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, RED_DISC);
    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, RED_DISC);

    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{0}, Column{0}}), RED_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{1}, Column{0}}), BLACK_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{2}, Column{0}}), RED_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{3}, Column{0}}), BLACK_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{4}, Column{0}}), RED_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{5}, Column{0}}), NO_DISC);
}

TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious5)
{
    t_gameBoard.placeDisc(Column{0}, RED_DISC);
    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, RED_DISC);
    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, RED_DISC);
    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);

    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{0}, Column{0}}), RED_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{1}, Column{0}}), BLACK_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{2}, Column{0}}), RED_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{3}, Column{0}}), BLACK_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{4}, Column{0}}), RED_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{5}, Column{0}}), BLACK_DISC);
}

TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious6)
{
    t_gameBoard.placeDisc(Column{0}, RED_DISC);
    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, RED_DISC);
    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, RED_DISC);
    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);

    // An extra disc:
    t_gameBoard.placeDisc(Column{0}, RED_DISC);

    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{0}, Column{0}}), RED_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{1}, Column{0}}), BLACK_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{2}, Column{0}}), RED_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{3}, Column{0}}), BLACK_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{4}, Column{0}}), RED_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{5}, Column{0}}), BLACK_DISC);
}

TEST_F(GameBoardTests, PlaceDisc_ValidDiscAsParameter_DiscInsertedInGameboardOverPrevious7)
{
    t_gameBoard.placeDisc(Column{NB_COLUMNS_MIN - 1}, RED_DISC);

    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{0}, Column{NB_COLUMNS_MIN - 1}}), RED_DISC);
    ASSERT_EQ(t_gameBoard.discAtPosition(Position{Row{1}, Column{NB_COLUMNS_MIN - 1}}), NO_DISC);
}

TEST_F(GameBoardTests, PlaceDisc_PlaceDisc_ColumnTooSmallAsParameter_ExceptionThrown)
{
    ASSERT_THROW(t_gameBoard.placeDisc(Column{-1}, RED_DISC), PreconditionException);
}

TEST_F(GameBoardTests, PlaceDisc_PlaceDisc_ColumnTooLargeAsParameter_ExceptionThrown)
{
    ASSERT_THROW(t_gameBoard.placeDisc(Column{NB_COLUMNS_MIN}, RED_DISC), PreconditionException);
}

TEST_F(GameBoardTests, IsColumFull_AFullColumnAsParameter_ReturnsTrue)
{
    t_gameBoard.placeDisc(Column{0}, RED_DISC);
    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, RED_DISC);
    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, RED_DISC);
    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);

    ASSERT_TRUE(t_gameBoard.isColumnFull(Column{0}));
}

TEST_F(GameBoardTests, IsColumFull_ANotFullColumnAsParameter_ReturnsFalse)
{
    t_gameBoard.placeDisc(Column{0}, RED_DISC);
    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, RED_DISC);
    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{0}, RED_DISC);

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

    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{3}, RED_DISC);
    t_gameBoard.placeDisc(Column{1}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{5}, RED_DISC);

    t_gameBoard2.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard2.placeDisc(Column{3}, RED_DISC);
    t_gameBoard2.placeDisc(Column{1}, BLACK_DISC);
    t_gameBoard2.placeDisc(Column{5}, RED_DISC);

    ASSERT_TRUE(t_gameBoard == t_gameBoard2);

}

TEST_F(GameBoardTests, EqualToOperator_TwoDifferentGameBoardsAsParameters_ReturnsFalse)
{
    GameBoard t_gameBoard2;

    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{3}, RED_DISC);
    t_gameBoard.placeDisc(Column{1}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{5}, RED_DISC);

    t_gameBoard2.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard2.placeDisc(Column{3}, RED_DISC);
    t_gameBoard2.placeDisc(Column{1}, BLACK_DISC);

    // Different:
    t_gameBoard2.placeDisc(Column{4}, RED_DISC);

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

    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{3}, RED_DISC);
    t_gameBoard.placeDisc(Column{1}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{5}, RED_DISC);

    t_gameBoard2.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard2.placeDisc(Column{3}, RED_DISC);
    t_gameBoard2.placeDisc(Column{1}, BLACK_DISC);

    // Different:
    t_gameBoard2.placeDisc(Column{5}, BLACK_DISC);

    ASSERT_NE(t_gameBoard, t_gameBoard2);
}

TEST_F(GameBoardTests, NoEqualToOperator_TwoEqualGameBoardsAsParameters_ReturnsFalse)
{
    GameBoard t_gameBoard2;

    t_gameBoard.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{3}, RED_DISC);
    t_gameBoard.placeDisc(Column{1}, BLACK_DISC);
    t_gameBoard.placeDisc(Column{5}, RED_DISC);

    t_gameBoard2.placeDisc(Column{0}, BLACK_DISC);
    t_gameBoard2.placeDisc(Column{3}, RED_DISC);
    t_gameBoard2.placeDisc(Column{1}, BLACK_DISC);
    t_gameBoard2.placeDisc(Column{5}, RED_DISC);

    ASSERT_FALSE(t_gameBoard != t_gameBoard2);
}

TEST_F(GameBoardTests, NoEqualToOperator_TwoDifferentSizeGameBoardsAsParameters_ExceptionThrown)
{
    GameBoard t_gameBoard2{8,8};

    ASSERT_THROW(t_gameBoard != t_gameBoard2, PreconditionException);
}

TEST_F(GameBoardTests, StreamInsertionOperator_StandardGameBoardAsParameter_PrintsCorrectFormat)
{
    std::ostringstream t_gameBoard1;

    for(int row{0}; row < t_gameBoard.nbRows(); ++row)
    {
        for(int column{0}; column < t_gameBoard.nbColumns(); ++column)
        {
            t_gameBoard.placeDisc(Column{column}, BLACK_DISC);
        }
    }

    t_gameBoard1 << t_gameBoard;

    std::ostringstream t_gameBoard2;
    t_gameBoard2 << "5  | B | B | B | B | B | B | B |" << endl
                 << "4  | B | B | B | B | B | B | B |" << endl
                 << "3  | B | B | B | B | B | B | B |" << endl
                 << "2  | B | B | B | B | B | B | B |" << endl
                 << "1  | B | B | B | B | B | B | B |" << endl
                 << "0  | B | B | B | B | B | B | B |" << endl
                 << "     0   1   2   3   4   5   6" << endl;

    ASSERT_EQ(t_gameBoard1.str(), t_gameBoard2.str());
}

TEST(GameBoard, StreamInsertionOperator_12x14GameBoardAsParameter_PrintsCorrectFormat)
{
    Disc BLACK_DISC {Color{Name{"Black"},   AsciiColorCode{'B'}}};

    GameBoard t_gameBoard {12,14};

    ostringstream t_gameBoard1;

    for(int row{0}; row < t_gameBoard.nbRows(); ++row)
    {
        for(int column{0}; column < t_gameBoard.nbColumns(); ++column)
        {
            t_gameBoard.placeDisc(Column{column}, BLACK_DISC);
        }
    }

    t_gameBoard1 << t_gameBoard;

    ostringstream t_gameBoard2;
    t_gameBoard2 << "11 | B | B | B | B | B | B | B | B | B | B | B  | B  | B  | B  |" << endl
                 << "10 | B | B | B | B | B | B | B | B | B | B | B  | B  | B  | B  |" << endl
                 << "9  | B | B | B | B | B | B | B | B | B | B | B  | B  | B  | B  |" << endl
                 << "8  | B | B | B | B | B | B | B | B | B | B | B  | B  | B  | B  |" << endl
                 << "7  | B | B | B | B | B | B | B | B | B | B | B  | B  | B  | B  |" << endl
                 << "6  | B | B | B | B | B | B | B | B | B | B | B  | B  | B  | B  |" << endl
                 << "5  | B | B | B | B | B | B | B | B | B | B | B  | B  | B  | B  |" << endl
                 << "4  | B | B | B | B | B | B | B | B | B | B | B  | B  | B  | B  |" << endl
                 << "3  | B | B | B | B | B | B | B | B | B | B | B  | B  | B  | B  |" << endl
                 << "2  | B | B | B | B | B | B | B | B | B | B | B  | B  | B  | B  |" << endl
                 << "1  | B | B | B | B | B | B | B | B | B | B | B  | B  | B  | B  |" << endl
                 << "0  | B | B | B | B | B | B | B | B | B | B | B  | B  | B  | B  |" << endl
                 << "     0   1   2   3   4   5   6   7   8   9   10   11   12   13" << endl;

    ASSERT_EQ(t_gameBoard1.str(), t_gameBoard2.str());
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
        t_horizontalValidGameBoard.placeDisc(Column{0}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{0}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{0}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{0}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{0}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{0}, BLACK_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{1}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{1}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{1}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{1}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{1}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{1}, BLACK_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{2}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{2}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{2}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{2}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{2}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{2}, BLACK_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{3}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{3}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{3}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{3}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{3}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{3}, BLACK_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{4}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{4}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{4}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{4}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{4}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{4}, BLACK_DISC);

        // Center section:
        t_horizontalValidGameBoard.placeDisc(Column{5}, YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{5}, GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{5}, YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{5}, GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{5}, YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{5}, GREEN_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{6}, YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{6}, GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{6}, YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{6}, GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{6}, YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{6}, GREEN_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{7}, YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{7}, GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{7}, YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{7}, GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{7}, YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{7}, GREEN_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{8}, YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{8}, GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{8}, YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{8}, GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{8}, YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{8}, GREEN_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{9}, YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{9}, GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{9}, YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{9}, GREEN_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{9}, YELLOW_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{9}, GREEN_DISC);

        // Right section:
        t_horizontalValidGameBoard.placeDisc(Column{10}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{10}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{10}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{10}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{10}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{10}, BLACK_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{11}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{11}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{11}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{11}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{11}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{11}, BLACK_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{12}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{12}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{12}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{12}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{12}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{12}, BLACK_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{13}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{13}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{13}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{13}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{13}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{13}, BLACK_DISC);

        t_horizontalValidGameBoard.placeDisc(Column{14}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{14}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{14}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{14}, BLACK_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{14}, RED_DISC);
        t_horizontalValidGameBoard.placeDisc(Column{14}, BLACK_DISC);

    }

};

TEST_F(ValidHorizontalGameBoardTests, IsWinner_InARowIs4_BordersChecked)
{
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{0}}, CONNECT_FOUR));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{14}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{14}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{14}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{14}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{14}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{14}}, CONNECT_FOUR));
}

TEST_F(ValidHorizontalGameBoardTests, IsWinner_InARowIs5_BordersChecked)
{
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{0}}, CONNECT_FIVE));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{14}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{14}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{14}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{14}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{14}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{14}}, CONNECT_FIVE));
}

TEST_F(ValidHorizontalGameBoardTests, IsWinner_InARowIs6_BordersChecked)
{
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{0}}, CONNECT_SIX));

    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{14}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{14}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{14}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{14}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{14}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{14}}, CONNECT_SIX));
}

TEST_F(ValidHorizontalGameBoardTests, IsWinner_InARowIs4_GridInternalsChecked)
{
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, CONNECT_FOUR));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_FOUR));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, CONNECT_FOUR));
}

TEST_F(ValidHorizontalGameBoardTests, IsWinner_InARowIs5_GridInternalsChecked)
{
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, CONNECT_FIVE));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_FIVE));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, CONNECT_FIVE));
}

TEST_F(ValidHorizontalGameBoardTests, IsWinner_InARowIs6_GridInternalsChecked)
{
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{1}}, CONNECT_SIX));

    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_SIX));

    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{13}}, CONNECT_SIX));
}

TEST_F(ValidHorizontalGameBoardTests, IsWinner_InARowIs4_GridInternalBordersChecked)
{
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{4}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{4}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{4}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{4}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{4}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{4}}, CONNECT_FOUR));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{5}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{5}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{5}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{5}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{5}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{5}}, CONNECT_FOUR));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{9}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{9}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{9}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{9}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{9}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{9}}, CONNECT_FOUR));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{10}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{10}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{10}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{10}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{10}}, CONNECT_FOUR));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{10}}, CONNECT_FOUR));
}

TEST_F(ValidHorizontalGameBoardTests, IsWinner_InARowIs5_GridInternalBordersChecked)
{
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{4}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{4}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{4}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{4}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{4}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{4}}, CONNECT_FIVE));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{5}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{5}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{5}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{5}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{5}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{5}}, CONNECT_FIVE));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{9}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{9}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{9}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{9}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{9}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{9}}, CONNECT_FIVE));

    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{10}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{10}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{10}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{10}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{10}}, CONNECT_FIVE));
    ASSERT_TRUE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{10}}, CONNECT_FIVE));
}

TEST_F(ValidHorizontalGameBoardTests, IsWinner_InARowIs6_GridInternalBordersChecked)
{
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{4}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{4}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{4}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{4}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{4}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{4}}, CONNECT_SIX));

    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{5}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{5}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{5}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{5}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{5}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{5}}, CONNECT_SIX));

    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{9}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{9}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{9}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{9}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{9}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{9}}, CONNECT_SIX));

    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{0}, Column{10}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{1}, Column{10}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{2}, Column{10}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{3}, Column{10}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{4}, Column{10}}, CONNECT_SIX));
    ASSERT_FALSE(t_horizontalValidGameBoard.isWinner(Position{Row{5}, Column{10}}, CONNECT_SIX));
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
        t_verticalValidGameBoard.placeDisc(Column{0}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{0}, RED_DISC);

        t_verticalValidGameBoard.placeDisc(Column{1}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{1}, BLACK_DISC);

        t_verticalValidGameBoard.placeDisc(Column{2}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{2}, RED_DISC);

        t_verticalValidGameBoard.placeDisc(Column{3}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{3}, BLACK_DISC);

        t_verticalValidGameBoard.placeDisc(Column{4}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{4}, RED_DISC);

        t_verticalValidGameBoard.placeDisc(Column{5}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, GREEN_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, BLACK_DISC);
        t_verticalValidGameBoard.placeDisc(Column{5}, BLACK_DISC);

        t_verticalValidGameBoard.placeDisc(Column{6}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, YELLOW_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, RED_DISC);
        t_verticalValidGameBoard.placeDisc(Column{6}, RED_DISC);
    }
};

TEST_F(VerticalValidGameBoardTests, IsWinner_InARowIs4_BordersChecked)
{
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{1}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{2}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{3}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{4}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{5}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{6}}, CONNECT_FOUR));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{1}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{2}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{3}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{4}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{5}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{6}}, CONNECT_FOUR));
}

TEST_F(VerticalValidGameBoardTests, IsWinner_InARowIs5_BordersChecked)
{
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{1}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{2}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{3}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{4}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{5}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{6}}, CONNECT_FIVE));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{1}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{2}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{3}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{4}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{5}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{6}}, CONNECT_FIVE));
}

TEST_F(VerticalValidGameBoardTests, IsWinner_InARowIs6_BordersChecked)
{
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{1}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{2}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{3}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{4}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{5}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{0}, Column{6}}, CONNECT_SIX));

    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{1}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{2}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{3}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{4}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{5}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{14}, Column{6}}, CONNECT_SIX));
}

TEST_F(VerticalValidGameBoardTests, IsWinner_InARowIs4_GridInternalsChecked)
{
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{1}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{2}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{3}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{4}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{5}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{6}}, CONNECT_FOUR));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{1}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{2}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{3}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{4}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{5}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{6}}, CONNECT_FOUR));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{1}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{2}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{3}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{4}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{5}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{6}}, CONNECT_FOUR));
}

TEST_F(VerticalValidGameBoardTests, IsWinner_InARowIs5_GridInternalsChecked)
{
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{1}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{2}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{3}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{4}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{5}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{6}}, CONNECT_FIVE));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{1}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{2}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{3}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{4}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{5}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{6}}, CONNECT_FIVE));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{1}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{2}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{3}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{4}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{5}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{6}}, CONNECT_FIVE));
}

TEST_F(VerticalValidGameBoardTests, IsWinner_InARowIs6_GridInternalsChecked)
{
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{1}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{2}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{3}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{4}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{5}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{1}, Column{6}}, CONNECT_SIX));

    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{1}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{2}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{3}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{4}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{5}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{7}, Column{6}}, CONNECT_SIX));

    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{1}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{2}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{3}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{4}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{5}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{13}, Column{6}}, CONNECT_SIX));
}

TEST_F(VerticalValidGameBoardTests, IsWinner_InARowIs4_InternalBordersChecked)
{
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_FOUR));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_FOUR));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_FOUR));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_FOUR));
}

TEST_F(VerticalValidGameBoardTests, IsWinner_InARowIs5_InternalBordersChecked)
{
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_FIVE));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_FIVE));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_FIVE));

    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_FIVE));
}

TEST_F(VerticalValidGameBoardTests, IsWinner_InARowIs6_InternalBordersChecked)
{
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{4}, Column{6}}, CONNECT_SIX));

    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{5}, Column{6}}, CONNECT_SIX));

    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_SIX));

    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_verticalValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_SIX));
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
        t_upwardValidGameBoard.placeDisc(Column{0}, RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{0}, RED_DISC);

        t_upwardValidGameBoard.placeDisc(Column{1}, WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{1}, BLACK_DISC);

        t_upwardValidGameBoard.placeDisc(Column{2}, BLUE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, BLUE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{2}, GREEN_DISC);

        t_upwardValidGameBoard.placeDisc(Column{3}, WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, BLUE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{3}, YELLOW_DISC);

        t_upwardValidGameBoard.placeDisc(Column{4}, BLUE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{4}, WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{4}, BLUE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{4}, WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{4}, RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{4}, BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{4}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{4}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{4}, RED_DISC);

        t_upwardValidGameBoard.placeDisc(Column{5}, BLUE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{5}, WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{5}, BLUE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{5}, WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{5}, BLUE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{5}, WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{5}, BLUE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{5}, WHITE_DISC);
        t_upwardValidGameBoard.placeDisc(Column{5}, BLUE_DISC);

        t_upwardValidGameBoard.placeDisc(Column{6}, RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{6}, BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{6}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{6}, GREEN_DISC);

        t_upwardValidGameBoard.placeDisc(Column{7}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{7}, RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{7}, BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{7}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{7}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{7}, YELLOW_DISC);

        t_upwardValidGameBoard.placeDisc(Column{8}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{8}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{8}, RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{8}, BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{8}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{8}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{8}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{8}, GREEN_DISC);

        t_upwardValidGameBoard.placeDisc(Column{9}, BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{9}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{9}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{9}, RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{9}, BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{9}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{9}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{9}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{9}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{9}, BLACK_DISC);

        t_upwardValidGameBoard.placeDisc(Column{10}, RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, RED_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, YELLOW_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, GREEN_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, BLACK_DISC);
        t_upwardValidGameBoard.placeDisc(Column{10}, RED_DISC);
    }
};

TEST_F(UpwardValidGameBoardTests, IsWinner_InARowIs4_CornersChecked)
{

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{0}}, CONNECT_FOUR));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{0}}, CONNECT_FOUR));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{1}}, CONNECT_FOUR));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{0}}, CONNECT_FOUR));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{1}}, CONNECT_FOUR));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{2}}, CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{2}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{3}}, CONNECT_FOUR));



    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{10}}, CONNECT_FOUR));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{9}}, CONNECT_FOUR));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{10}}, CONNECT_FOUR));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{8}}, CONNECT_FOUR));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{8}, Column{9}}, CONNECT_FOUR));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{10}}, CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{8}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{8}, Column{10}}, CONNECT_FOUR));



    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{10}}, CONNECT_FOUR));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{9}}, CONNECT_FOUR));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{10}}, CONNECT_FOUR));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{8}}, CONNECT_FOUR));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{9}}, CONNECT_FOUR));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{10}}, CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{7}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{9}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{10}}, CONNECT_FOUR));
}

TEST_F(UpwardValidGameBoardTests, IsWinner_InARowIs5_CornersChecked)
{

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{0}}, CONNECT_FIVE));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{0}}, CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{1}}, CONNECT_FIVE));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{0}}, CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{1}}, CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{2}}, CONNECT_FIVE));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{0}}, CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{2}}, CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{3}}, CONNECT_FIVE));



    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{10}}, CONNECT_FIVE));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{9}}, CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{10}}, CONNECT_FIVE));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{8}}, CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{8}, Column{9}}, CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{10}}, CONNECT_FIVE));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{8}}, CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{8}, Column{10}}, CONNECT_FIVE));



    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{10}}, CONNECT_FIVE));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{9}}, CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{10}}, CONNECT_FIVE));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{8}}, CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{9}}, CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{10}}, CONNECT_FIVE));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{7}}, CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{9}}, CONNECT_FIVE));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{10}}, CONNECT_FIVE));
}

TEST_F(UpwardValidGameBoardTests, IsWinner_InARowIs6_CornersChecked)
{

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{0}}, CONNECT_SIX));

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{0}}, CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{1}}, CONNECT_SIX));

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{0}}, CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{1}}, CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{2}}, CONNECT_SIX));

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{0}}, CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{2}}, CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{3}}, CONNECT_SIX));



        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{11}, Column{10}}, CONNECT_SIX));

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{9}}, CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{10}, Column{10}}, CONNECT_SIX));

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{8}}, CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{8}, Column{9}}, CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{9}, Column{10}}, CONNECT_SIX));

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{7}}, CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{8}}, CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{8}, Column{10}}, CONNECT_SIX));



        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{10}}, CONNECT_SIX));

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{9}}, CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{10}}, CONNECT_SIX));

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{8}}, CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{9}}, CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{10}}, CONNECT_SIX));

        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{7}}, CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{9}}, CONNECT_SIX));
        ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{10}}, CONNECT_SIX));
}

TEST_F(UpwardValidGameBoardTests, IsWinner_InARowIs4_BordersChecked)
{

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{2}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{4}}, CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{2}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{4}}, CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{2}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{4}}, CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{2}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{4}}, CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{2}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{8}, Column{4}}, CONNECT_FOUR));



    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{8}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{10}}, CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{8}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{10}}, CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{8}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{10}}, CONNECT_FOUR));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{8}}, CONNECT_FOUR));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{10}}, CONNECT_FOUR));
}

TEST_F(UpwardValidGameBoardTests, IsWinner_InARowIs5_BordersChecked)
{

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{2}}, CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{4}}, CONNECT_FIVE));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{2}}, CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{4}}, CONNECT_FIVE));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{2}}, CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{4}}, CONNECT_FIVE));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{2}}, CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{4}}, CONNECT_FIVE));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{2}}, CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{8}, Column{4}}, CONNECT_FIVE));



    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{8}}, CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{10}}, CONNECT_FIVE));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{8}}, CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{10}}, CONNECT_FIVE));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{8}}, CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{10}}, CONNECT_FIVE));

    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{8}}, CONNECT_FIVE));
    ASSERT_TRUE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{10}}, CONNECT_FIVE));
}

TEST_F(UpwardValidGameBoardTests, IsWinner_InARowIs6_BordersChecked)
{

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{2}}, CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{4}}, CONNECT_SIX));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{2}}, CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{4}}, CONNECT_SIX));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{2}}, CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{4}}, CONNECT_SIX));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{2}}, CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{4}}, CONNECT_SIX));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{2}}, CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{8}, Column{4}}, CONNECT_SIX));



    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{0}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{8}}, CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{10}}, CONNECT_SIX));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{1}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{8}}, CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{10}}, CONNECT_SIX));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{2}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{4}, Column{8}}, CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{6}, Column{10}}, CONNECT_SIX));

    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{3}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{5}, Column{8}}, CONNECT_SIX));
    ASSERT_FALSE(t_upwardValidGameBoard.isWinner(Position{Row{7}, Column{10}}, CONNECT_SIX));
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
        t_downwardValidGameBoard.placeDisc(Column{0}, RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{0}, RED_DISC);

        t_downwardValidGameBoard.placeDisc(Column{1}, BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{1}, RED_DISC);

        t_downwardValidGameBoard.placeDisc(Column{2}, GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{2}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{2}, GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{2}, BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{2}, BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{2}, BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{2}, GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{2}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{2}, BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{2}, RED_DISC);

        t_downwardValidGameBoard.placeDisc(Column{3}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{3}, GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{3}, WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{3}, WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{3}, WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{3}, GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{3}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{3}, BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{3}, RED_DISC);

        t_downwardValidGameBoard.placeDisc(Column{4}, GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{4}, BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{4}, BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{4}, BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{4}, GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{4}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{4}, BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{4}, RED_DISC);

        t_downwardValidGameBoard.placeDisc(Column{5}, BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{5}, WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{5}, BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{5}, WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{5}, BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{5}, WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{5}, BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{5}, WHITE_DISC);

        t_downwardValidGameBoard.placeDisc(Column{6}, WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{6}, YELLOW_DISC);

        t_downwardValidGameBoard.placeDisc(Column{7}, GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{7}, GREEN_DISC);

        t_downwardValidGameBoard.placeDisc(Column{8}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{8}, YELLOW_DISC);

        t_downwardValidGameBoard.placeDisc(Column{9}, BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, BLUE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{9}, BLACK_DISC);

        t_downwardValidGameBoard.placeDisc(Column{10}, RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, WHITE_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, RED_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, GREEN_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, YELLOW_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, BLACK_DISC);
        t_downwardValidGameBoard.placeDisc(Column{10}, RED_DISC);
    }
};

TEST_F(DownwardValidGameBoardTests, IsWinner_InARowIs4_CornersChecked)
{

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{0}}, CONNECT_FOUR));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{0}}, CONNECT_FOUR));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{1}}, CONNECT_FOUR));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{0}}, CONNECT_FOUR));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{1}}, CONNECT_FOUR));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{2}}, CONNECT_FOUR));

    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{3}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{1}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{3}}, CONNECT_FOUR));


    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{6}}, CONNECT_FOUR));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{7}}, CONNECT_FOUR));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{6}}, CONNECT_FOUR));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{7}}, CONNECT_FOUR));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{8}}, CONNECT_FOUR));

    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{3}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{7}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{8}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{9}}, CONNECT_FOUR));


    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{10}}, CONNECT_FOUR));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{9}}, CONNECT_FOUR));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{10}}, CONNECT_FOUR));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{8}}, CONNECT_FOUR));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{9}}, CONNECT_FOUR));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{10}}, CONNECT_FOUR));

    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{7}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{9}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{10}}, CONNECT_FOUR));
}

TEST_F(DownwardValidGameBoardTests, IsWinner_InARowIs5_CornersChecked)
{

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{0}}, CONNECT_FIVE));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{0}}, CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{1}}, CONNECT_FIVE));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{0}}, CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{1}}, CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{2}}, CONNECT_FIVE));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{3}, Column{0}}, CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{1}}, CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{3}}, CONNECT_FIVE));


    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{6}}, CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{7}}, CONNECT_FIVE));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{6}}, CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{7}}, CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{8}}, CONNECT_FIVE));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{3}, Column{6}}, CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{7}}, CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{8}}, CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{9}}, CONNECT_FIVE));


    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{10}}, CONNECT_FIVE));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{9}}, CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{10}}, CONNECT_FIVE));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{8}}, CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{9}}, CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{10}}, CONNECT_FIVE));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{7}}, CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{9}}, CONNECT_FIVE));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{10}}, CONNECT_FIVE));
}

TEST_F(DownwardValidGameBoardTests, IsWinner_InARowIs6_CornersChecked)
{

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{0}}, CONNECT_SIX));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{1}}, CONNECT_SIX));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{1}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{2}}, CONNECT_SIX));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{3}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{1}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{3}}, CONNECT_SIX));


    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{7}}, CONNECT_SIX));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{7}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{8}}, CONNECT_SIX));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{3}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{7}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{1}, Column{8}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{9}}, CONNECT_SIX));


    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{10}}, CONNECT_SIX));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{9}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{10}}, CONNECT_SIX));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{8}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{9}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{10}}, CONNECT_SIX));

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{7}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{9}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{10}}, CONNECT_SIX));
}

TEST_F(DownwardValidGameBoardTests, IsWinner_InARowIs4_BordersChecked)
{

    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{2}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{4}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{2}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{4}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{2}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{5}, Column{4}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{2}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{4}, Column{4}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{4}, Column{0}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{2}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{4}}, CONNECT_FOUR));


    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{8}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{10}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{8}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{10}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{8}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{5}, Column{10}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{6}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{8}}, CONNECT_FOUR));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{4}, Column{10}}, CONNECT_FOUR));
}

TEST_F(DownwardValidGameBoardTests, IsWinner_InARowIs5_BordersChecked)
{

    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{2}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{4}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{2}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{4}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{2}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{5}, Column{4}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{2}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{4}, Column{4}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{4}, Column{0}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{2}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{4}}, CONNECT_FIVE));


    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{8}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{10}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{8}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{10}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{8}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{5}, Column{10}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{6}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{8}}, CONNECT_FIVE));
    ASSERT_TRUE(t_downwardValidGameBoard.isWinner(Position{Row{4}, Column{10}}, CONNECT_FIVE));
}

TEST_F(DownwardValidGameBoardTests, IsWinner_InARowIs6_BordersChecked)
{

    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{2}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{4}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{2}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{4}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{2}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{5}, Column{4}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{2}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{4}, Column{4}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{4}, Column{0}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{2}, Column{2}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{0}, Column{4}}, CONNECT_SIX));


    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{11}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{8}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{10}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{10}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{8}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{10}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{9}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{7}, Column{8}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{5}, Column{10}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{8}, Column{6}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{6}, Column{8}}, CONNECT_SIX));
    ASSERT_FALSE(t_downwardValidGameBoard.isWinner(Position{Row{4}, Column{10}}, CONNECT_SIX));
}
