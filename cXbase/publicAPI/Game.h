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
 * @date    January 2017
 * @version 0.1
 *
 * Interface for a Game utility.
 *
 **************************************************************************************************/

#ifndef GAME_H_
#define GAME_H_

#include "../source/IEnforceContract.h"
#include "GameBoard.h"
#include "Player.h"

#include <vector>
#include <memory>

BEGIN_CXBASE_NAMESPACE


/***********************************************************************************************//**
 * @class Game
 *
 * Gives access to several higher level features to construct Connect X games.
 *
 * @invariant The @a inARow value must be bigger or equal to two (2) and smaller or equal to the
 *            minimum between the Grid width and length.
 *
 * @invariant The current number of turns is always between 0 (GameBoard is empty) and the total
 *            number of positions in the Grid plus one (1).
 *
 * @invariant The current turn is always between 0 and the total numbers of Players minus one.
 *
 **************************************************************************************************/
class Game : public IEnforceContract
{

public:

    typedef std::vector<std::shared_ptr<Player>>    PlayerList;
    typedef std::shared_ptr<GameBoard>              GameBoardSPtr;

///@{ @name Object construction and destruction
    Game()          = delete;
    virtual ~Game() = default;


    /*******************************************************************************************//**
     * Constructor with parameters.
     *
     * @param[in] p_players     A list of Players.
     * @param[in] p_gameboard   The GameBoard for the Game.
     * @param[in] p_inARow      The @a inARow value, i.e. the number of equal Discs that must be
     *                          adjacent to consider a combination a win.
     *
     * @pre @c p_players has at least two players.
     * @pre @c p_inARow is bigger than two (2) and smaller than the minimum between the Grid
     *      width and length.
     *
     **********************************************************************************************/
    Game(const PlayerList& p_players, const GameBoardSPtr p_gameboard, int p_inARow);
///@}


///@{ @name Data access
    /*******************************************************************************************//**
     * Active Player accessor.
     *
     * Gives access to the Player whose current turn it is.
     *
     * @return The active player.
     *
     **********************************************************************************************/
    Player activePlayer() const {return *(m_players[m_turn]);}


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
     * Number of turns accessor.
     *
     * @return The current number of turn played in the Game.
     *
     **********************************************************************************************/
    int nbOfTurnsPlayed() const {return m_nbTurns;}
///@}

///@{ @name Game utilities
    /*******************************************************************************************//**
     * Checks is a Game is a draw.
     *
     * A Game is considered a draw if the number of turns for the Game exceeds by one (1) the
     * total number of positions in the Grid. Note that no check is run as to wether the GameBoard
     * is exempt of a winning combination. It is the user's responsability to call the isWon()
     * method to make sure of it.
     *
     * @return A boolean indicating if the Game is a draw.
     *
     * @see isWon()
     *
     * @todo If the Game can be declared a draw but not all turns have been played, this method
     *       will miss it. I would be nice for this method to catch the draw as early as possible.
     *       this would include some kind of GameBoard check.
     *
     **********************************************************************************************/
    bool isDraw() const {return (m_nbTurns == m_gameboard->nbPositions());}


    /*******************************************************************************************//**
     * Checks if a Game is won.
     *
     * A Game is considered won if it contains a @a inARow number of adjacent equal Discs. This
     * string of equal Disc can be either horizontal, vertical or diagonal.
     *
     * This method checks, <em> for the current Position only, </em> if such a winning string of
     * adjacent Discs exists. Here is an example where for a Disc with AsciiColorCode @c R,
     * represents the current Position, i.e. the Position where the last activePlayer placed a
     * Disc. The Positions considered for the winner check by this method  (other than the
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
     * Note that this methods does not check for draws. It is the user's responsability to check
     * for those using the isDray() method.
     *
     * @return A boolean indicating if a winning string of Discs has been found from the
     *         current Position.
     *
     * @see isDraw()
     *
     **********************************************************************************************/
    bool isWon() const {return m_gameboard->isWinner(m_currentPosition, m_inARow);}


    /*******************************************************************************************//**
     * Plays a turn.
     *
     * If possible, places a Disc at the specified Column, otherwise, does nothing.
     *
     * @param p_column The Column where to place the active Player's Disc.
     *
     * @pre p_column is inside the Grid.
     *
     * @return A boolean indicating if the Disc has been placed successfully.
     *
     **********************************************************************************************/
    bool playTurn(const Column& p_column);


    /*******************************************************************************************//**
     * Setups the Game's internal data for the next turn.
     *
     * Update the Game's internal data to make the next turn available. This method should be
     * called after a turn is considered done. It will, for example, increment the current turn.
     * If this method is not called at the end of a turn, you can still fill in the GameBoard
     * and check for a winning combination, but the Game will loose track of the current
     * turn information.
     *
     **********************************************************************************************/
    void nextTurn();
///@}

protected:

    virtual void checkInvariant() const;

    PlayerList      m_players;                                    ///< List of Players for the Game.
    GameBoardSPtr   m_gameboard;                                  ///< The GameGoard used.
    int             m_inARow;                                     ///< The @a inARow for the Game.
    int             m_nbTurns             {0};                    ///< Total number of turns for the GameBoard.
    int             m_turn                {0};                    ///< The current turn (first turn is 0).
    Position        m_currentPosition     {Row{0}, Column{0}};    ///< The Position where the active player places a Disc.

};

END_CXBASE_NAMESPACE

#endif /* GAME_H_ */
