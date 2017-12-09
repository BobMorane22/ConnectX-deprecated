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
 * @version 1.0
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


namespace cxbase
{

/***********************************************************************************************//**
 * @class GameBoard
 *
 * @brief Connect X GameBoard.
 *
 * A Connect X GameBoard consists mainly of a Grid, or a 2D Disc array, and dimensionnal information
 * about the Grid. In this document, Grid and GameBoard will be used interchangeably. The GameBoard
 * also support features to check itself for a winner if additionnal information is supplied
 * (like the <em> in a row </em> value for the game).
 *
 * @invariant The number of rows exceeds or is equal to the minimal number of rows: 6
 * @invariant The number of rows is less than  or equal to the maximal number of rows: 64
 * @invariant The number of columns exceeds  or is equal to the minimal number of columns: 7
 * @invariant The number of columns is less than  or equal to the maximal number of columns: 64
 *
 * @note If you want dimensions smaller than 6 by 7 or larger than 64 by 64, you must recompile
 * the cxbase library after having modified the values for private data members @c NB_ROWS_MIN,
 * @c NB_COLUMNS_MIN, @c NB_ROWS_MAX and @c NB_COLUMNS_MAX to your needs. Note that the library
 * has only been officially tested for default values.
 *
 * @note 3D GameBoards are not supported.
 *
 **************************************************************************************************/
class GameBoard : public cxutil::IEnforceContract, public cxutil::ICliObject
{

public:

///@{ @name Object construction and destruction

    /*******************************************************************************************//**
     * Default destructor.
     *
     **********************************************************************************************/
    virtual ~GameBoard();


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
     * @pre The number of rows exceeds or is equal to the minimal number of rows: 6
     * @pre The number of rows is less than  or equal to the maximal number of rows: 64
     * @pre The number of columns exceeds  or is equal to the minimal number of columns: 7
     * @pre The number of columns is less than  or equal to the maximal number of columns: 64
     *
     **********************************************************************************************/
    GameBoard(int p_nbRows, int p_nbColumns);

///@}


///@{ @name Data access

    /*******************************************************************************************//**
     * Accessor for the grid.
     *
     * @return The Gameboard grid.
     *
     **********************************************************************************************/
    std::vector<std::vector<Disc>> grid() const;


    /*******************************************************************************************//**
     * Accessor for the number of rows in the Gameboard.
     *
     * @return The number of rows in the GameBoard.
     *
     **********************************************************************************************/
    int nbRows() const;


    /*******************************************************************************************//**
     * Accessor for the number of columns in the GameBoard.
     *
     * @return The number of columns in the GameBoard.
     *
     **********************************************************************************************/
    int nbColumns() const;


    /*******************************************************************************************//**
     * Accessor for the number of positions total in the GameBoard.
     *
     * @return The number of positions (total) in the GameBoard.
     *
     **********************************************************************************************/
    int nbPositions() const;


///@}


///@{ @name Gameboard checks and actions

    /*******************************************************************************************//**
     * Places a Disc in a specific Column.
     *
     * Just like in the classic Connect 4 game, the Disc is inserted in a specific Column and sets
     * to the bottommost available Position in the Column. For example:
     *
     *   @verbatim
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
     * If the Column is already full, the action is ignored (the disc is not placed) and the top
     * most position is returned. It is a good idea to use the @c isColumnFull() method before
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

///@}

///@{ @name Operators

    /*******************************************************************************************//**
     * Equal-to operator.
     *
     * Two GameBoards are considered equal <em> if and only if </em> both their Grids and
     * dimension information are the same.
     *
     * @param[in] p_gameBoard The GameBoard with which to compare.
     *
     **********************************************************************************************/
    bool operator==(const GameBoard &p_gameBoard) const;


    /*******************************************************************************************//**
     * Not-equal-to operator.
     *
     * Two GameBoards are considered @b NOT equal <em> if and only if </em> their Grids or
     * dimension information (or both) are @b NOT the same.
     *
     * @param[in] p_gameBoard The GameBoard with which to compare.
     *
     **********************************************************************************************/
    bool operator!=(const GameBoard &p_gameBoard) const;

    
    /*******************************************************************************************//**
     * Function operator.
     *
     * Gives access to the Disc located at the needed Position on the GameBoard's grid. Positions
     * on the grid follow a cartesian-like convention. The correct way to visualize a grid is as
     * follow:
     *
     * @verbatim
     *
     *    Columns up
     *        ^
     *        |
     *        |
     *    | (0,1) |
     *    | (0,0) | (1,0) | --> Rows up
     *
     * @endverbatim
     *
     * @param[in] p_position The Position at which the needed Disc is located on the grid.
     *
     **********************************************************************************************/
    Disc operator()(const Position& p_position) const;

///@}


protected:

    /*******************************************************************************************//**
     * Insert text into stream.
     *
     * A GameBoard can be inserted into a stream to text-mode using this method. Only the grid 
     * and its underlying Discs are printed with Row and Column numbers. The character @c "|" is 
     * used to separate different columns.
     *
     * For example:
     *
     *   @code{.cpp}
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

    std::vector<std::vector<Disc>>  m_grid;       ///< The GameBoard's grid.
    int                             m_nbRows;     ///< The GameBoard grid's number of rows.
    int                             m_nbColumns;  ///< The GameBoard grid's number of columns.

};

} // namespace cxbase

#endif /* GAMEBOARD_H_59F7D710_94EA_491A_9C14_94AE5C014E9A */
