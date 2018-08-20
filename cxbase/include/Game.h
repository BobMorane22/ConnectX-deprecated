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
 * @file    Game.h
 * @author  Eric Poirier
 * @date    September 2017
 * @version 1.0
 *
 * Interface for a Game utility.
 *
 **************************************************************************************************/

#ifndef GAME_H_2D56E7FC_5FA9_4841_B204_05ADCF2DCE07
#define GAME_H_2D56E7FC_5FA9_4841_B204_05ADCF2DCE07

#include <cxutil/include/ContractException.h>

#include "GameBoard.h"
#include "Player.h"


namespace cxbase
{

/***********************************************************************************************//**
 * @class Game
 *
 * @brief Connect X game.
 *
 * Gives access to several higher level features to construct Connect X games.
 *
 * @invariant The Gameboard address is valid.
 *
 * @invariant All Player addresses are valid.
 *
 * @invariant The number of Players is always at least two (2) and at most the number of Positions
 *            in the GameBoard divided by the @a inARow value.
 *
 * @invariant The @a inARow value must be bigger or equal to two (2) and smaller or equal to the
 *            minimum between the grid width and length.
 *
 * @invariant The current number of completed moves is always between 0 (GameBoard is empty) and
 *            the total number of positions in the grid plus one (1).
 *
 * @invariant The current turn is always between 0 and the total numbers of Players minus one.
 *
 * @invariant The chosen GameBoard must allow every Player to have the same number of moves
 *            during the Game.
 *
 **************************************************************************************************/
class Game
{

public:

///@{ @name Object construction and destruction

    /*******************************************************************************************//**
     * Default destructor.
     *
     **********************************************************************************************/
    virtual ~Game();


    /*******************************************************************************************//**
     * Constructor with parameters.
     *
     * @param[in] p_players     A list of Players.
     * @param[in] p_gameboard   The GameBoard for the Game.
     * @param[in] p_inARow      The @a inARow value, i.e. the number of equal Discs that must be
     *                          adjacent to consider a combination a win.
     *
     * @pre The Gameboard address passed as an argument is valid.
     * @pre All Player addresses passed as arguments (contained in a @c std::vector) are valid.
     * @pre The number of Players is always at least two (2) and at most the number of Positions
     *      in the GameBoard divided by the @a inARow value.
     * @pre @c p_inARow is bigger than two (2) and smaller than the minimum between the Grid
     *      width and length.
     * @pre The chosen GameBoard must allow every Player to have the same number of moves
     *      during the Game.
     *
     **********************************************************************************************/
    Game(const std::vector<std::shared_ptr<Player>>& p_players, const std::shared_ptr<GameBoard>& p_gameboard, int p_inARow);

///@}


///@{ @name Data access

    /*******************************************************************************************//**
     * Active Player accessor.
     *
     * Gives access to the Player whose current turn it is to make a move.
     *
     * @return The active player.
     *
     **********************************************************************************************/
    Player activePlayer() const;


    /*******************************************************************************************//**
     * @a inARow value accessor.
     *
     * @return The Game's @a inARow value.
     *
     **********************************************************************************************/
    int inARowValue() const {return m_inARow;}


    /*******************************************************************************************//**
     * Current turn accessor.
     *
     * @return The current Player turn.
     *
     **********************************************************************************************/
    int currentTurn() const {return m_turn;}


    /*******************************************************************************************//**
     * Number of completed moves accessor.
     *
     * @return The current number of completed moves for the Game.
     *
     **********************************************************************************************/
    int nbOfCompletedMoves() const {return m_nbOfCompletedMoves;}

///@}

///@{ @name Game utilities

    /*******************************************************************************************//**
     * Checks if the Game can be considered an early draw.
     *
     * An early draw occurs when, for any chosen Player, the possibility of winning the Game no
     * longer exists. As opposed to the @c isDraw() method, which requires a GameBoard to be
     * completely filled with Discs before deciding anything, the @c isEarlyDraw() method can make
     * a decision at any point in the Game, even if the Game is not finished yet. Note that no
     * check is run as to wether the GameBoard is exempt of a winning combination. It is the user's
     * responsability to call the @c isWon() method to make sure of it.
     *
     * @return A boolean indicating if the Game will eventually be a draw.
     *
     * @see isWon()
     * @see isDraw()
     *
     **********************************************************************************************/
     bool isEarlyDraw() const;


    /*******************************************************************************************//**
     * Checks if a Game is a draw.
     *
     * A Game is considered a draw if the number of completed moves for the Game exceeds by one
     * (1) the total number of positions in the grid. Note that no check is run as to wether the
     * GameBoard is exempt of a winning combination. It is the user's responsability to call the
     * @c isWon() method to make sure of it.
     *
     * @return A boolean indicating if the Game is a draw.
     *
     * @see isWon()
     * @see isEarlyDraw()
     *
     **********************************************************************************************/
    bool isDraw() const;


    /*******************************************************************************************//**
     * Checks if a Game is won.
     *
     * A Game is considered won if it contains a @a inARow number of adjacent equal Discs. This
     * string of equal Discs can be either horizontal, vertical or diagonal.
     *
     * This method checks, <em> for the current Position only, </em> if such a winning string of
     * adjacent Discs exists. Here is an example where a Disc with AsciiColorCode @c R,
     * represents the current Position, i.e. the Position where the last active Player dropped a
     * Disc. The Positions considered for the winner check by this method (other than the
     * active one) are shown with the ASCII code @c x. Note that this example uses an
     * @a inARow value of four (4).
     *
     *   @verbatim
     *      5 |   |   |   | x |   | x |   |
     *      4 |   |   |   |   | x | x | x |
     *      3 |   |   | x | x | x | R | x |
     *      2 |   |   |   |   | x | x | x |
     *      1 |   |   |   | x |   | x |   |
     *      0 |   |   | x |   |   | x |   |
     *          0   1   2   3   4   5   6
     *   @endverbatim
     *
     * In other words, all Positions that are not marked by either @c R or @c x in this example are
     * not taken into account by this method.
     *
     * Note that this method does not check for [early] draws. It is the user's responsability to
     * check for those using the @c isEarlyDraw() and @c isDraw() methods.
     *
     * @return A boolean indicating if a winning string of Discs has been found from the
     *         current Position.
     *
     * @see isEarlyDraw()
     * @see isDraw()
     *
     **********************************************************************************************/
    bool isWon() const;


    /*******************************************************************************************//**
     * Make a move.
     *
     * If possible, places a Disc at the specified Column for the active Player, otherwise,
     * does nothing. The active Player must try again until a successfull move occurs. Most of
     * the time, a move will fail because the chosen Column is already full.
     *
     * @param p_column The Column where to place the active Player's Disc.
     *
     * @pre p_column is inside the grid.
     *
     * @return @true if the Disc has been placed successfully, @c false otherwise.
     *
     **********************************************************************************************/
    bool makeMove(const Column& p_column);


///@}

///@{ @name Predefined values

    static const int& connectThree();
    static const int& connectFour();
    static const int& connectFive();
    static const int& connectSix();
    static const int& connectSeven();
    static const int& connectEight();
    static const int& connectNine();

///@}

protected:

    void checkInvariant() const;

///{ @name private data

    std::vector<std::shared_ptr<Player>>  m_players;    ///< List of Players for the Game.
    std::shared_ptr<GameBoard>            m_gameboard;  ///< The GameGoard used.

///}

private:

    bool     isPlayerInGame(const Player& p_player) const;

    Player   previousPlayer() const;
    Position positionOfLastSuccessFullMove() const;

///@{ @name isEarlyDraw implementation

    bool canPlayerWinHorizontal              (const Player& p_player                             ) const;
    bool canPlayerWinVertical                (const Player& p_player                             ) const;
    bool canPlayerWinDiagonalUpward          (const Player& p_player                             ) const;
    bool canPlayerWinDiagonalDownward        (const Player& p_player                             ) const;

    int  nbRemainingMoves                    (const Player& p_player, const int p_nbOfTurnsPlayed) const;
    int  nbRemainingMoves                    (const Player& p_player                             ) const;
    int  maxVerticalPositionForPlayerInColumn(const Player& p_player, const Column& p_column     ) const;
    int  nbOfMovesSinceLastPlay              (const Player& p_player                             ) const;
    bool isPlayerPresentInColumn             (const Player& p_player, const Column& p_column     ) const;
    int  playerTurn                          (const Player& p_player                             ) const;

///@}

///{ @name isWon implementation

    enum class GridValidationType: int
    {
        Straight,
        Horizontal,
        Vertical,
        Oblique,
        DiagonalUpward,
        DiagonalDownward
    };

    int leftValidationLimit (GridValidationType validationType = GridValidationType::Straight) const;
    int rightValidationLimit(GridValidationType validationType = GridValidationType::Straight) const;
    int upperValidationLimit(GridValidationType validationType = GridValidationType::Straight) const;
    int lowerValidationLimit(GridValidationType validationType = GridValidationType::Straight) const;

    int nbOfValidations(int p_minValidationLimit, int p_maxValidationLimit) const;

    int horizontalNbOfAdjacentDiscs() const;
    int verticalNbOfAdjacentDiscs  () const;
    int upwardNbOfAdjacentDiscs    () const;
    int downwardNbOfAdjacentDiscs  () const;

    bool checkHorizontalWinner() const;
    bool checkVerticalWinner  () const;
    bool checkUpwardWinner    () const;
    bool checkDownwardWinner  () const;

///{ @name private data

    int                   m_inARow;                       ///< The @a inARow for the Game.
    int                   m_turn                    {0};  ///< The current turn (first turn is 0).
    int                   m_nbOfCompletedMoves      {0};  ///< The total number of completed moves.
    std::vector<Position> m_completedMovePositions;       ///< A list of all Positions successfully used.
                                                          ///< by the Players to complete a move.

///}

};

} // namespace cxbase

#endif /* GAME_H_2D56E7FC_5FA9_4841_B204_05ADCF2DCE07_ */
