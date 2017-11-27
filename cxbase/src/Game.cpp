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
 * @file    Game.cpp
 * @author  Eric Poirier
 * @date    September 2017
 * @version 1.0
 *
 * Implementation for a Game utility.
 *
 **************************************************************************************************/

#include <algorithm>

#include <cxutil/include/narrow_cast.h>

#include "../include/Game.h"

using namespace cxbase;


Game::~Game() = default;


Game::Game(const std::vector<std::shared_ptr<Player>>& p_players, const std::shared_ptr<GameBoard>& p_gameboard, int p_inARow):
           m_players{p_players}, m_gameboard{p_gameboard}, m_inARow{p_inARow}
{
    PRECONDITION(p_gameboard != nullptr);

    PRECONDITION(std::none_of(p_players.begin(), p_players.end(), 
                 [](const std::shared_ptr<Player>& player)
                   {
                       return player == nullptr;
                   })
                 );

    PRECONDITION(p_players.size() >= 2);
    PRECONDITION(p_players.size() <= cxutil::narrow_cast<unsigned int>(p_gameboard->nbPositions() / p_inARow));
    PRECONDITION(p_inARow >= 2);
    PRECONDITION(p_inARow < std::min(p_gameboard->nbColumns(), p_gameboard->nbRows()));

    INVARIANTS();
}

// Source: https://stackoverflow.com/questions/46921528/detect-early-tie-in-connect-4/46928055#46928055
bool Game::isTie() const
{
    bool validPlaysAreStillAvailable{false};

    for(auto& player : m_players)
    {
        validPlaysAreStillAvailable |= canPlayerWinHorizontal(*player);
        
        if(!validPlaysAreStillAvailable)
        {
            validPlaysAreStillAvailable |= canPlayerWinVertical(*player);
        }
    }

    return !validPlaysAreStillAvailable;
}


bool Game::playTurn(const Column& p_column)
{
    PRECONDITION(p_column.value() >= 0);
    PRECONDITION(p_column.value() < m_gameboard->nbColumns());

    bool success{false};

    if(!m_gameboard->isColumnFull(p_column))
    {
        m_currentPosition = m_gameboard->placeDisc(p_column, m_players[m_turn]->disc());
        success = true;
    }

    return success;
}


void Game::nextTurn()
{
    // One more turn done:
    if(m_nbTurns < m_gameboard->nbPositions())
    {
        m_nbTurns++;
    }

    // Next Player is up:
    m_turn = (m_turn + 1) % cxutil::narrow_cast<int>(m_players.size()); // Cast is OK because this vector is always small.

}


void Game::checkInvariant() const
{
    INVARIANT(m_gameboard != nullptr);
    INVARIANT(std::none_of(m_players.begin(), m_players.end(), 
              [](const std::shared_ptr<Player>& p_player)
                 {
                     return p_player == nullptr;
                 })
             );

    INVARIANT(m_players.size() >= 2);
    INVARIANT(m_players.size() <= cxutil::narrow_cast<unsigned int>(m_gameboard->nbPositions() / m_inARow));

    INVARIANT(m_inARow >= 2);
    INVARIANT(m_inARow < std::min(m_gameboard->nbColumns(), m_gameboard->nbRows()));

    INVARIANT(m_nbTurns >= 0);
    INVARIANT(m_nbTurns < m_gameboard->nbPositions());

    INVARIANT(m_turn >= 0);
    INVARIANT(cxutil::narrow_cast<unsigned int>(m_turn) < m_players.size());
}


/***************************************************************************************************
 * Calculates the remaining possible moves number for a Player from the numbers of moves already
 * consluded in the Game. 
 *
 * @param[in] p_player          The Player which we want to know the current count of remaining
 *                              actual moves available.
 * @param[in] p_nbOfTurnsPlayed The number of moves completed at the point in the Game for which 
 *                              the number of remaining moves needs to be known.
 *
 * @return The number of actual moves remaining for the Player.
 *
 **************************************************************************************************/
int Game::nbRemainingMoves(const Player& p_player, const int p_nbOfTurnsPlayed) const
{
    // Note: as of now, I assume that nextTurn() is called prior to this. nextTurn()
    // should be encapsulated before next release to make sure the user cannot misuse it
    // and invalidate the algorithms of this class.
    const int nbMovesLeft{m_gameboard->nbPositions() - p_nbOfTurnsPlayed};//
    const int remainingMovesQuotient{nbMovesLeft / cxutil::narrow_cast<int>(m_players.size())};
    const int remainingMovesRest{nbMovesLeft % cxutil::narrow_cast<int>(m_players.size())};

    int nbRemainingMoves{remainingMovesQuotient};

    // Check if process is really necessary: do all players deserve an equal share?
    if(remainingMovesRest != 0)
    {
        // Find position of p_player in the player list:
        const auto playerPosition{std::find(m_players.begin(),
                                            m_players.end(),
                                            std::make_shared<Player>(p_player))};

        // Check all candidate postition for an extra turn and see if the player is there:
        for(int offset{0}; offset < remainingMovesRest; ++offset)
        {
            const int firstTurnWithMoreMoves{currentTurn()};
            const int nextTurnWithMoreMoves{(firstTurnWithMoreMoves + offset) % cxutil::narrow_cast<int>(m_players.size())};

            const auto candidatePosition{m_players.begin() + nextTurnWithMoreMoves};

            if(playerPosition == candidatePosition)
            {
                nbRemainingMoves = remainingMovesQuotient + 1;
            }
            else
            {
                nbRemainingMoves = remainingMovesQuotient;
            }
        }
    }
    else
    {
        nbRemainingMoves = remainingMovesQuotient;
    }
    
    return nbRemainingMoves;
}


/***************************************************************************************************
 * Calculates the remaining possible moves number for a Player from the current configuration. For 
 * example, consider this classic Connect 4 gameboard, where the Player A made the last move:
 *
 * @verbatim
 *
 *           |
 *           v
 *   5 | B | A |   |   |   |   |   |
 *   4 | A | B | A | B | A | B | A |
 *   3 | A | B | A | B | A | B | A |
 *   2 | B | A | B | A | B | A | B |
 *   1 | B | A | B | A | B | A | B |
 *   0 | A | B | A | B | A | B | A |
 *       0   1   2   3   4   5   6
 *
 * @endverbatim
 *
 * In this situation, Player A has at most two more moves.
 *
 * @param[in] p_player The Player which we want to know the current count of remaining actual 
 *                     moves available.
 *
 * @return The number of actual moves remaining for the Player.
 *
 * @see @c isTie()
 * @see @c canPlayerWinHorizontal()
 *
 **************************************************************************************************/
int Game::nbRemainingMoves(const Player& p_player) const
{
    return nbRemainingMoves(p_player, nbOfTurnsPlayed());
}


/***************************************************************************************************
 * Finds the turn of a specific player.
 *
 * @param[in] p_player The Player whose turn is needed.
 *
 * @return The turn of the Player.
 *
 **************************************************************************************************/
int Game::playerTurn(const Player& p_player) const
{
    int playerTurn{0};

    if(p_player == activePlayer())
    {
        playerTurn = currentTurn();
    }
    else
    {
        for(int position{0}; position < cxutil::narrow_cast<int>(m_players.size()); ++position)
        {
            if(*m_players[position] == p_player)
            {
                break;
            }

            ++playerTurn;
        }
    }
    
    return playerTurn;
}


/***************************************************************************************************
 * Finds the number of turns that took place since a Player last successfully placed a disc.
 *
 * param[in] p_player The Player for which the number of turn since last sucessful move is
 *                    needed.
 *
 * return The number of turns since the Player made his last successful move.
 *
 **************************************************************************************************/
int Game::nbOfMovesSinceLastPlay(const Player& p_player) const
{
    int positionCurrent{0};
    
    if(m_turn == 0)
    {
        positionCurrent = cxutil::narrow_cast<int>(m_players.size()) - 1;
    }
    else
    {
        positionCurrent = m_turn - 1;
    }
    const int positionInspected{playerTurn(p_player)};

    // Find the distance between the two Players:
    int nbOfMoves{0};

    if(positionCurrent < positionInspected)
    {
        nbOfMoves = positionCurrent + (cxutil::narrow_cast<int>(m_players.size()) - positionInspected);
    }

    if(positionCurrent > positionInspected)
    {
        nbOfMoves = positionCurrent - positionInspected;
    }

    return nbOfMoves;
}


/***************************************************************************************************
 * Checks if a Column contains at least one Disc from a specific Player.
 *
 * @pre p_column is valid on the GameBoard.
 *
 * @param[in] p_player The Players for which we want to know if at least one of his Disc is 
 *                     present in the specified Column.
 * @param[in] p_column The Column in which to perform the check.
 *
 * return A @c bool indicating if the Column contains at least one Disc from the specified Player.
 *
 **************************************************************************************************/
bool Game::isPlayerPresentInColumn(const Player& p_player, const Column& p_column) const
{
    PRECONDITION(p_column.value() <= m_gameboard->nbColumns());

    bool isPlayerPresent{false};

    for(int rowIndex{0}; rowIndex < m_gameboard->nbRows(); ++rowIndex)
    {
        if((*m_gameboard)(Position{Row{rowIndex}, p_column}) == p_player.disc())
        {
            isPlayerPresent = true;
            break;
        }
    }

    return isPlayerPresent;
}


/***************************************************************************************************
 * Finds the Player' Disc Position that is the furthest away from the bottom of the GameBoard in 
 * the specified column.
 *
 * @pre  The specified Player must have a Disc present in the speficied Column.
 * @post The @c return ed value corresponds to a valid row index.
 *
 * @param[in] p_player The Player whose maximum Position in the specified Column must be known.
 * @param[in] p_column The Column in which to perform the check.
 *
 * @return An integer corresponding to the Row index of the furthest away from the bottom Player's 
 *         Disc Position. If the Player has no Disc in the specified Column, the @c return ed 
 *         integer is zero (0).
 *
 * @see Game::isPlayerPresentInColumn
 *
 **************************************************************************************************/
int Game::maxVerticalPositionForPlayerInColumn(const Player& p_player, const Column& p_column) const
{
    PRECONDITION(isPlayerPresentInColumn(p_player, p_column));

    int maxPosition{0};

    for(int rowIndex{0}; rowIndex < m_gameboard->nbRows(); ++rowIndex)
    {
        if((*m_gameboard)(Position{Row{rowIndex}, p_column}) == p_player.disc())
        {
            maxPosition = rowIndex;
        }
    }

    POSTCONDITION(maxPosition <  m_gameboard->nbRows());
    POSTCONDITION(maxPosition >= 0);

    return maxPosition;
}


/***************************************************************************************************
 * This method checks for any remaining winnable horizontal combinations for a Player on a 
 * GameBoard. For example, consider this GameBoard, where Player A just made a move:
 *
 * @verbatim
 *
 *                               |
 *                               v
 *   5 | B |   |   |   |   |   | A |
 *   4 | A | B | A | B | A | B | A |
 *   3 | A | B | A | B | A | B | A |
 *   2 | B | A | B | A | B | A | B |
 *   1 | B | A | B | A | B | A | B |
 *   0 | A | B | A | B | A | B | A |
 *       0   1   2   3   4   5   6
 *
 * @endverbatim
 *
 * If you call this method on Player A, it will return @c false since Player A has no more 
 * horizontal and winnable moves ahead. However, if you call it in Player B, it will return 
 * @c true since Player B has one last possibility for a win:
 *
 * @verbatim
 *
 *     ***   WIN!   ***
 *   5 | B | B | B | B | A | A | A |
 *   4 | A | B | A | B | A | B | A |
 *   3 | A | B | A | B | A | B | A |
 *   2 | B | A | B | A | B | A | B |
 *   1 | B | A | B | A | B | A | B |
 *   0 | A | B | A | B | A | B | A |
 *       0   1   2   3   4   5   6
 *
 * @endverbatim
 *
 * @param[in] p_player The Player we want to know if he/she can still win horizontally.
 *
 * @return @c true if the player can still win horizontally, @c false otherwise.
 *
 **************************************************************************************************/
bool Game::canPlayerWinHorizontal(const Player& p_player) const
{
    bool canPlayerWin{false};

    // Row to check:
    for(int rowIndex{0}; rowIndex < m_gameboard->nbRows(); ++rowIndex)
    {
        // Use these columns for starting point of the checks:
        for(int columnIndex{0}; columnIndex < (m_gameboard->nbColumns() - m_inARow) + 1; ++columnIndex)
        {
            bool isPlayFree{true};
            int nbOfEmptyDiscsInRow{0};

            // Check only for the good inARow value:
            for(int offset{0}; offset < m_inARow; ++offset)
            {
                isPlayFree &= (*m_gameboard)(Position{Row{rowIndex}, Column{columnIndex + offset}}) == p_player.disc() ||
                              (*m_gameboard)(Position{Row{rowIndex}, Column{columnIndex + offset}}) == Disc::NO_DISC;

                // If the space is free, we record it for later checks:
                if((*m_gameboard)(Position{Row{rowIndex}, Column{columnIndex + offset}}) == Disc::NO_DISC)
                {
                    ++nbOfEmptyDiscsInRow;
                }
            }

            // Make sure there is enough space left for the current player to win:
            isPlayFree &= (nbOfEmptyDiscsInRow <= nbRemainingMoves(p_player));

            // As soon as one play is still free for a win, we record it:
            canPlayerWin |= isPlayFree;

            if(canPlayerWin)
            {
                break;
            }
        }

        if(canPlayerWin)
        {
            break;
        }
    }

    return canPlayerWin;
}


/***************************************************************************************************
 * This method checks for any remaining winnable vertical combinations for a Player on a 
 * GameBoard. For example, consider this GameBoard, where Player B just made a move:
 *
 * @verbatim
 *
 *   5  | B | A | B | B |   |   |   |
 *   4  | A | B | A | A | B |   |   |
 *   3  | B | A | B | B | A | B |   |
 *   2  | A | B | A | A | B | A | A |
 *   1  | B | A | B | B | A | B | B |
 *   0  | A | B | A | A | B | A | A |
 *        0   1   2   3   4   5   6
 *
 * @endverbatim
 *
 * If you call this method on Player B, it will return @c false because there are no more 
 * vertical winner moves for B. If you call it for Player A though, the method will return 
 * @c true because A can still win vertically like so:
 *
 * @verbatim
 *
 *   5  | B | A | B | B |   |   |   |
 *   4  | A | B | A | A | B |   |   |
 *   3  | B | A | B | B | A | B |   |
 *   2  | A | B | A | A | B | A | A |
 *   1  | B | A | B | B | A | B | B |
 *   0  | A | B | A | A | B | A | A |
 *        0   1   2   3   4   5   6
 *
 * @endverbatim
 *
 * @param[in] p_player The Player we want to know if he/she can still win vertically.
 *
 * @return @c true if the player can still win vertically, @c false otherwise.
 *
 **************************************************************************************************/
bool Game::canPlayerWinVertical(const Player& p_player) const
{
    bool canPlayerWin{false};

    // We calculate the number of remaining moves for all the other players:
    int nbRemainingMovesOtherPlayers{0};

    // Find the inspected Player's turn:
    int inspectedPlayerTurn{playerTurn(p_player)};

    for(int playerTurn{0}; playerTurn < cxutil::narrow_cast<int>(m_players.size()); ++playerTurn)
    {
        if(playerTurn != inspectedPlayerTurn)
        {
            const int nbOfTurnsRemainingFromLastMove{nbOfTurnsPlayed() - nbOfMovesSinceLastPlay(*m_players[playerTurn])};
            nbRemainingMovesOtherPlayers += nbRemainingMoves(*m_players[playerTurn], nbOfTurnsRemainingFromLastMove);
        }
    }

    // Then we perform the check on the grid:

    // Column to check:
    for(int columnIndex{0}; columnIndex <  m_gameboard->nbColumns(); ++columnIndex)
    {
        // Use these columns for starting point of the checks:
        for(int rowIndex{0}; rowIndex < m_gameboard->nbRows() - (m_inARow - 1); ++rowIndex)
        {
            bool isPlayFree{true};

            // Check only for the good inARow value:
            for(int offset{0}; offset < m_inARow; ++offset)
            {
                isPlayFree &= (*m_gameboard)(Position{Row{rowIndex + offset}, Column{columnIndex}}) == p_player.disc() ||
                              (*m_gameboard)(Position{Row{rowIndex + offset}, Column{columnIndex}}) == Disc::NO_DISC;
            }

                // The following makes sure that even though a move is seen as free, there is 
                // enough free positions and remaining moves for the current player.
                if(isPlayFree)
                {
                    const int  nbRemainingMovesTotal          {(m_gameboard->nbRows() * m_gameboard->nbColumns()) - nbOfTurnsPlayed()};
                    const bool isPlayerInColumn               {isPlayerPresentInColumn(p_player, Column{columnIndex})};
                    const int  maxVerticalPositionForPlayer   {isPlayerInColumn ? maxVerticalPositionForPlayerInColumn(p_player, Column{columnIndex}): -1};
                    const int  nbRemainingMovesInOtherColumns {nbRemainingMovesTotal - (m_gameboard->nbRows() - (maxVerticalPositionForPlayer + 1))};

                    // There should be enough room elswhere on the board to store all other players'
                    // remaining moves, otherwhise the move will pile up on the critical column and 
                    // a win becomes impossible: the discs will alternate!
                    isPlayFree &= (nbRemainingMovesOtherPlayers <= nbRemainingMovesInOtherColumns);
                }

            // As soon as one play is still free for a win, we record it:
            canPlayerWin |= isPlayFree;
        }
    }

    return canPlayerWin;
}


/***************************************************************************************************
 *
 *
 *
 *
 *
 *
 *
 *
 *
 **************************************************************************************************/
bool Game::canPlayerWinDiagonalUpward(const Player& p_player) const
{
    (void)p_player;
    return false;
}


/***************************************************************************************************
 *
 *
 *
 *
 *
 *
 *
 *
 *
 **************************************************************************************************/
bool Game::canPlayerWinDiagonalDownward(const Player& p_player) const
{
    (void)p_player;
    return false;
}
