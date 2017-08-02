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
 * @file    GameBoard.h
 * @author  Eric Poirier
 * @date    December 2016
 * @version 0.1
 *
 * Interface for a GameBoard utility.
 *
 **************************************************************************************************/

#ifndef GAMEBOARD_H_59F7D710_94EA_491A_9C14_94AE5C014E9A
#define GAMEBOARD_H_59F7D710_94EA_491A_9C14_94AE5C014E9A

#include <string>
#include <vector>

#include <cxutil/include/ICliObject.h>
#include <cxutil/include/IEnforceContract.h>

#include "Disc.h"
#include "Position.h"


BEGIN_CXBASE_NAMESPACE

/***********************************************************************************************//**
 * class GameBoard
 *
 * Connect X GameBoard.
 *
 * A Connect X GameBoard consists mainly of a Grid, or a 2D Disc array and dimensionnal information
 * about the grid. In this document, grid and GameBoard will be used interchangeably. The GameBoard
 * also support features to check itself for a winner if additionnal information is supplied
 * (like the <em> in a row </em> value for the game).
 *
 * @invariant The number of rows exceeds the minimal number of rows: 6
 * @invariant The number of rows is less than the maximal number of rows: 64
 * @invariant The number of columns exceeds the minimal number of columns: 7
 * @invariant The number of columns is less than the maximal number of columns: 64
 *
 * @note If you want dimensions smaller than 6 by 7 or larger than 64 by 64, you must recompile
 * the cXbase library after having modified the values for private data members @c NB_ROWS_MIN,
 * @c NB_COLUMNS_MIN, @c NB_ROWS_MAX and @c NB_COLUMNS_MAX to your needs. Note that the library
 * has only been officially tested for default values.
 *
 * @note 3D GameBoards are not supported.
 *
 **************************************************************************************************/
class GameBoard : public CXUTIL::IEnforceContract, public CXUTIL::ICliObject
{

private:

    typedef std::vector< std::vector<Disc> > Grid;

public:

///@{ @name Object construction and destruction
    virtual ~GameBoard() = default;


    /*******************************************************************************************//**
     * Constructor by default.
     *
     * Constructs a classic six (6) by seven (7) Connect 4 GameBoard.
     *
     **********************************************************************************************/
    GameBoard();


    /*******************************************************************************************//**
     * Constructor with parameters.
     *
     * Constructs a parametrized Connect X GameBoard.
     *
     * @param[in] p_nbRows      The wanted number of rows for the GameBoard.
     * @param[in] p_nbColumns   The wanted number of columns for the GameBoard.
     *
     * @pre The number of rows exceeds the minimal number of rows: 6
     * @pre The number of rows is less than the maximal number of rows: 64
     * @pre The number of columns exceeds the minimal number of columns: 7
     * @pre The number of columns is less than the maximal number of columns: 64
     *
     **********************************************************************************************/
    GameBoard(int p_nbRows, int p_nbColumns);
///@}


///@{ @name Data access
    /*******************************************************************************************//**
     * Accessor for the grid.
     *
     * @return The Gameboard grid.
     * @todo This in soly used as a mean to iterate over the grid... Make an iterator instead!
     *
     **********************************************************************************************/
    Grid grid() const;


    /*******************************************************************************************//**
     * Accessor for the number of rows in the Gameboard.
     *
     * @return The number of rows in the GameBoard.
     *
     **********************************************************************************************/
    int  nbRows() const;


    /*******************************************************************************************//**
     * Accessor for the number of columns in the Gameboard.
     *
     * @return The number of columns in the GameBoard.
     *
     **********************************************************************************************/
    int  nbColumns() const;


    /*******************************************************************************************//**
     * Accessor for the number of positions total in the GameBoard.
     *
     * @return The number of positions (total) in the GameBoard.
     *
     **********************************************************************************************/
    int  nbPositions() const;


    /*******************************************************************************************//**
     * Accessor for a specific Disc in the GameBoard.
     *
     * Returns the Disc located at a specific Position in the GameBoard
     *
     * @param[in] p_position The position of the seeked Disc.
     * @pre The position passed as an argument exists on the GameBoard, i.e. both Coordinates
     * respect the dimensions.
     *
     **********************************************************************************************/
    Disc discAtPosition(const Position& p_position) const;
///@}


///@{ @name Gameboard checks and actions
    /*******************************************************************************************//**
     * Places a Disc in a specific Column.
     *
     * Just like in the classic Connect 4 game, the Disc is inserted in a specific Column and sets
     * to the bottommost available Position in the Column.
     *
     *   @verbatim
     *
     *   Example:
     *
     *      | N | <- Last placed disc (unless already full, see below)
     *      | R |
     *      | N |
     *      | R |
     *      | N |
     *      | R | <- First placed Disc.
     *
     *   @endverbatim
     *
     * If the Column is already full, the action is ignored (the disc is not placed!) ad the top
     * most position is returned. It is a good idea to use the isColumnFull() method before
     * trying to place a Disc.
     *
     * @param[in] p_column  The Column where to insert the Disc.
     * @param[in] p_disc    The Disc to insert.
     *
     * @return The Position where the Disc has been placed, if the Column specified as an argument
     *         is not full, or the Column's top most Position otherwise.
     *
     * @pre The Column number is between 0 and the maximum Column number for the GameBoard.
     * @pre The Disc that is placed has a ColorAsciiCode other than the space character (@c ' ').
     *
     * @todo Remove possibility for "no disc" Disc insertion (add as PRECONDITION) and test.
     * @todo Test the return value.
     *
     **********************************************************************************************/
    Position placeDisc(const Column& p_column, const Disc& p_disc);


    /*******************************************************************************************//**
     * Checks if a specific Column is full.
     *
     * If Discs (other than the @c Disc::NO_DISC specifier) are stacked all the way up to the last
     * Column's position, the Column is considered full. Concretely:
     *
     *   @verbatim
     *
     *   Example:
     *
     *      |   | <- Not full, no Disc here...
     *      |   |
     *      |   |
     *      |   |
     *      |   |
     *      | R |
     *
     *
     *      |   | <- Not full yet, still no Disc here...
     *      | R |
     *      | N |
     *      | R |
     *      | B |
     *      | R |
     *
     *
     *      | N | <- Now you got it! The Column is full.
     *      | R |
     *      | N |
     *      | R |
     *      | B |
     *      | R |
     *
     *   @endverbatim
     *
     * @param[in] p_column  The Column where to insert the Disc.
     * @pre The Column number is between 0 and the maximum Column number for the GameBoard.
     *
     * @return @c true if the Column passed as an argument is full, @c false otherwise.
     *
     **********************************************************************************************/
    bool isColumnFull(const Column& p_column) const;


    /*******************************************************************************************//**
     * Checks for a win at a specified Position.
     *
     * Checks from the specified Position if a combination of @c p_inARow consecutive Discs
     * matching the Disc at @c p_positionLastDiscPlaced ispresent either horizontally, vertically
     * or diagonally. Be aware that it is @b NOT the responsablity of this method to know who
     * won. In other words, it only checks if @a someone won.
     *
     * @param[in] p_positionLastDiscPlaced  Position from which to look for a winner combination
     *                                      (usually where the last Player placed a Disc).
     *
     * @param[in] p_inARow                  Number of consecutive equal Discs neccessary to win
     *                                      the game.
     *
     * @pre The position passed as an argument exists on the GameBoard, i.e. both Coordinates
     * respect the dimensions.
     *
     * @return @c true if someone won, @c false otherwise.
     *
     * @todo Add unit tests for PRECONDITION checks!
     * @todo The methods works fine, but could be optimized. See implementation for details.
     *
     **********************************************************************************************/
    bool isWinner(const Position& p_positionLastDiscPlaced, int p_inARow) const;
///@}


///@{ @name Operators
    /*******************************************************************************************//**
     * Equal operator.
     *
     * Two GameBoards are considered equal <em> if and only if </em> both their grids and
     * dimension information are the same.
     *
     * @param[in] p_gameBoard The GameBoard with which to compare.
     *
     **********************************************************************************************/
    bool operator==(const GameBoard &p_gameBoard) const;


    /*******************************************************************************************//**
     * Not equal operator.
     *
     * Two GameBoards are considered @b NOT equal <em> if and only if </em> their grids or
     * dimension information (or both) are @b NOT the same.
     *
     * @param[in] p_gameBoard The GameBoard with which to compare.
     *
     **********************************************************************************************/
    bool operator!=(const GameBoard &p_gameBoard) const;
///@}

///@{ @name Predefined values
    static const int CONNECT_THREE;
    static const int CONNECT_FOUR;
    static const int CONNECT_FIVE;
    static const int CONNECT_SIX;
    static const int CONNECT_SEVEN;
    static const int CONNECT_EIGHT;
    static const int CONNECT_NINE;
///@}

protected:

    /*******************************************************************************************//**
     * Insert text into stream.
     *
     * A GameBoard can be inserted into a stream to text-mode using this method. Only the grid 
     * and its underlying Discs are printed with Row and Column numbers. The character "|" is used
     * to separate different columns.
     *
     * For example:
     *
     *   @code{.cpp}
     *
     *      // A disc, red in this case:
     *      Disc        RED_DISC{Color::RED};
     *
     *      // A classic Connect 4 board:
     *      GameBoard   aBoard;
     *
     *      // Fill first Column:
     *      aBoard.placeDisc(Column{0}, Disc::RED_DISC);
     *      aBoard.placeDisc(Column{0}, Disc::RED_DISC);
     *      aBoard.placeDisc(Column{0}, Disc::RED_DISC);
     *      aBoard.placeDisc(Column{0}, Disc::RED_DISC);
     *      aBoard.placeDisc(Column{0}, Disc::RED_DISC);
     *      aBoard.placeDisc(Column{0}, Disc::RED_DISC);
     *      aBoard.placeDisc(Column{0}, Disc::RED_DISC); // Oops! No effect: already full!
     *
     *      // Put three Discs in second:
     *      aBoard.placeDisc(Column{1}, Disc::RED_DISC);
     *      aBoard.placeDisc(Column{1}, Disc::RED_DISC);
     *      aBoard.placeDisc(Column{1}, Disc::RED_DISC);
     *
     *      // Print it to console:
     *      std::cout << aBoard;
     *
     *   @endcode
     *
     *   will result in the following text string inserted:
     *
     *     @verbatim
     *
     *       5 | R |   |   |   |   |   |   |
     *       4 | R |   |   |   |   |   |   |
     *       3 | R |   |   |   |   |   |   |
     *       2 | R | R |   |   |   |   |   |
     *       1 | R | R |   |   |   |   |   |
     *       0 | R | R |   |   |   |   |   |
     *           0   1   2   3   4   5   6
     *
     *     @endverbatim
     *
     * @param[in] p_stream        The stream in which to insert.
     *
     **********************************************************************************************/
    virtual void print(std::ostream& p_stream) const override;


    virtual void checkInvariant() const override;

private:

    static const int   NB_COLUMNS_MAX   {64};
    static const int   NB_ROWS_MAX      {64};
    static const int   NB_COLUMNS_MIN   {7};
    static const int   NB_ROWS_MIN      {6};

    enum class GridValidationType: int
    {
        Straight,
        Horizontal,
        Vertical,
        Oblique,
        ObliqueIncreasing,
        ObliqueDecreasing
    };

    Grid      m_grid;       ///< The GameBoard's grid.
    int       m_nbRows;     ///< The GameBoard grid's number of rows.
    int       m_nbColumns;  ///< The GameBoard grid's number of columns.


    int leftValidationLimit  (Position p_positionLastPlacedDisc, int p_inARow, GridValidationType validationType = GridValidationType::Straight) const;
    int rightValidationLimit (Position p_positionLastPlacedDisc, int p_inARow, GridValidationType validationType = GridValidationType::Straight) const;
    int upperValidationLimit (Position p_positionLastPlacedDisc, int p_inARow, GridValidationType validationType = GridValidationType::Straight) const;
    int lowerValidationLimit (Position p_positionLastPlacedDisc, int p_inARow, GridValidationType validationType = GridValidationType::Straight) const;

    int nbOfValidations(int p_minValidationLimit, int p_maxValidationLimit, int p_inARow) const;

    int horizontalNbOfAdjacentDiscs  (Position p_positionLastPlacedDisc, int p_inARow) const;
    int verticalNbOfAdjacentDiscs    (Position p_positionLastPlacedDisc, int p_inARow) const;
    int upwardNbOfAdjacentDiscs      (Position p_positionLastPlacedDisc, int p_inARow) const;
    int downwardNbOfAdjacentDiscs    (Position p_positionLastPlacedDisc, int p_inARow) const;

    bool checkHorizontalWinner (Position p_positionLastPlacedDisc, int p_inARow) const;
    bool checkVerticalWinner   (Position p_positionLastPlacedDisc, int p_inARow) const;
    bool checkUpwardWinner     (Position p_positionLastPlacedDisc, int p_inARow) const;
    bool checkDownwardWinner   (Position p_positionLastPlacedDisc, int p_inARow) const;

};

END_CXBASE_NAMESPACE

#endif /* GAMEBOARD_H_59F7D710_94EA_491A_9C14_94AE5C014E9A */
