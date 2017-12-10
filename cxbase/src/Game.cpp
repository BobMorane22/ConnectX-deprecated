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


const int Game::CONNECT_THREE  {3};
const int Game::CONNECT_FOUR   {4};
const int Game::CONNECT_FIVE   {5};
const int Game::CONNECT_SIX    {6};
const int Game::CONNECT_SEVEN  {7};
const int Game::CONNECT_EIGHT  {8};
const int Game::CONNECT_NINE   {9};


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
    PRECONDITION((p_gameboard->nbColumns() * p_gameboard->nbRows()) % m_players.size() == 0);

    INVARIANTS();
}

// Source: https://stackoverflow.com/questions/46921528/detect-early-tie-in-connect-4/46928055#46928055
bool Game::isEarlyDraw() const
{
    bool validPlaysAreStillAvailable{false};

    for(auto& player : m_players)
    {
        validPlaysAreStillAvailable |= canPlayerWinHorizontal(*player);

        if(!validPlaysAreStillAvailable)
        {
            validPlaysAreStillAvailable |= canPlayerWinVertical(*player);
        }

        if(!validPlaysAreStillAvailable)
        {
            validPlaysAreStillAvailable |= canPlayerWinDiagonalUpward(*player);
        }
        
        if(!validPlaysAreStillAvailable)
        {
            validPlaysAreStillAvailable |= canPlayerWinDiagonalDownward(*player);
        }
    }

    return !validPlaysAreStillAvailable;
}


bool Game::isWon() const
{
    bool isWinner{false};

    if(checkHorizontalWinner() || checkVerticalWinner() || checkUpwardWinner()|| checkDownwardWinner())
    {
        isWinner = true;
    }

    return isWinner;
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

    INVARIANT((m_gameboard->nbColumns() * m_gameboard->nbRows()) % m_players.size() == 0);
}


/***********************************************************************************************//**
 * Checks wether the specified Player is part of the current Game or not.
 *
 * @param[in] p_player The Player we wich to check for.
 *
 * @return    @c true is the Player is part of the current Game, @c false otherwise.
 *
 **************************************************************************************************/
bool Game::isPlayerInGame(const Player& p_player) const
{
    const auto player{std::find(m_players.begin(), m_players.end(), std::make_shared<Player>(p_player))};
    
    return player != m_players.end();
}


/***********************************************************************************************//**
 * Calculates the remaining possible moves number for a Player from the numbers of moves already
 * consluded in the Game. 
 *
 * @pre The Player specified as an argument is registered in the Game.
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


/***********************************************************************************************//**
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
 * @pre The Player specified as an argument is registered in the Game.
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


/***********************************************************************************************//**
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


/***********************************************************************************************//**
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


/***********************************************************************************************//**
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


/***********************************************************************************************//**
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
    int maxPosition{0};

    for(int rowIndex{0}; rowIndex < m_gameboard->nbRows(); ++rowIndex)
    {
        if((*m_gameboard)(Position{Row{rowIndex}, p_column}) == p_player.disc())
        {
            maxPosition = rowIndex;
        }
    }

    return maxPosition;
}


/***********************************************************************************************//**
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
                              (*m_gameboard)(Position{Row{rowIndex}, Column{columnIndex + offset}}) == Disc::noDisc();

                // If the space is free, we record it for later checks:
                if((*m_gameboard)(Position{Row{rowIndex}, Column{columnIndex + offset}}) == Disc::noDisc())
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


/***********************************************************************************************//**
 * This method checks for any remaining winnable vertical combinations for a Player on a 
 * GameBoard. For example, consider this GameBoard, where Player B just made a move:
 *
 * @verbatim
 *
 *                           |
 *                           v
 *   5 | B | A | B | B |   |   |   |
 *   4 | A | B | A | A | B |   |   |
 *   3 | B | A | B | B | A | B |   |
 *   2 | A | B | A | A | B | A | A |
 *   1 | B | A | B | B | A | B | B |
 *   0 | A | B | A | A | B | A | A |
 *       0   1   2   3   4   5   6
 *
 * @endverbatim
 *
 * If you call this method on Player B, it will return @c false because there are no more 
 * vertical winner moves for B. If you call it for Player A though, the method will return 
 * @c true because A can still win vertically like so:
 *
 * @verbatim
 *
 *   5 | B | A | B | B | B |   | A | ***
 *   4 | A | B | A | A | B | B | A | WIN
 *   3 | B | A | B | B | A | B | A |
 *   2 | A | B | A | A | B | A | A | ***
 *   1 | B | A | B | B | A | B | B |
 *   0 | A | B | A | A | B | A | A |
 *       0   1   2   3   4   5   6
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
                              (*m_gameboard)(Position{Row{rowIndex + offset}, Column{columnIndex}}) == Disc::noDisc();
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


/***********************************************************************************************//**
 * This method checks for any remaining winnable upward diagonal combinations for a Player on a 
 * GameBoard. For example, consider this GameBoard, where Player A just made a move:
 *
 * @verbatim
 *
 *                                |
 *                                v
 *    5 | B | B | A | B |   |   |   |
 *    4 | A | A | B | A | A | B | A |
 *    3 | B | B | A | B | B | B | A |
 *    2 | A | A | B | A | A | A | B |
 *    1 | B | B | A | B | B | B | A |
 *    0 | A | A | B | A | A | B | A |
 *        0   1   2   3   4   5   6
 *
 * @endverbatim
 *
 * If you call this method on Player B, it will return @c false since Player B has no more 
 * upward diagonal and winnable moves ahead. However, if you call it in Player A, it will return 
 * @c true since Player A has one last possibility for a win:
 *
 * @verbatim
 *
 *          ***   WIN    ***
 *    5 | B | B | A | B | A | B |   |
 *    4 | A | A | B | A | A | B | A |
 *    3 | B | B | A | B | B | B | A |
 *    2 | A | A | B | A | A | A | B |
 *    1 | B | B | A | B | B | B | A |
 *    0 | A | A | B | A | A | B | A |
 *        0   1   2   3   4   5   6
 *
 * @endverbatim
 *
 * @param[in] p_player The Player we want to know if he/she can still win upward diagonally.
 *
 * @return @c true if the player can still win upward diagonally, @c false otherwise.
 *
 **************************************************************************************************/
bool Game::canPlayerWinDiagonalUpward(const Player& p_player) const
{
    bool canPlayerWin{false};

    // Row to check:
    for(int rowIndex{0}; rowIndex < (m_gameboard->nbRows() - m_inARow) + 1; ++rowIndex)
    {
        // Use these columns for starting point of the checks:
        for(int columnIndex{0}; columnIndex < (m_gameboard->nbColumns() - m_inARow) + 1; ++columnIndex)
        {
            bool isPlayFree{true};
            int nbOfEmptyDiscsInDiagonal{0};

            // Check only for the good inARow value:
            for(int offset{0}; offset < m_inARow; ++offset)
            {
                isPlayFree &= (*m_gameboard)(Position{Row{rowIndex + offset}, Column{columnIndex + offset}}) == p_player.disc() ||
                              (*m_gameboard)(Position{Row{rowIndex + offset}, Column{columnIndex + offset}}) == Disc::noDisc();

                // If the space is free, we record it for later checks:
                if((*m_gameboard)(Position{Row{rowIndex + offset}, Column{columnIndex + offset}}) == Disc::noDisc())
                {
                    ++nbOfEmptyDiscsInDiagonal;
                }
            }

            // Make sure there is enough space left for the current player to win:
            isPlayFree &= (nbOfEmptyDiscsInDiagonal <= nbRemainingMoves(p_player));

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


/***********************************************************************************************//**
 * This method checks for any remaining winnable downward diagonal combinations for a Player on a 
 * GameBoard. For example, consider this GameBoard, where Player A just made a move:
 *
 * @verbatim
 *
 *        |
 *        v
 *    5 |   |   |   | B | A | B | B |
 *    4 | A | B | A | A | B | A | A |
 *    3 | A | B | B | B | A | B | B |
 *    2 | B | A | A | A | B | A | A |
 *    1 | A | B | B | B | A | B | B |
 *    0 | A | B | A | A | B | A | A |
 *        0   1   2   3   4   5   6
 *
 * @endverbatim
 *
 * If you call this method on Player B, it will return @c false since Player B has no more 
 * downward diagonal and winnable moves ahead. However, if you call it in Player A, it will return 
 * @c true since Player A has one last possibility for a win:
 *
 * @verbatim
 *
 *              ***   WIN    ***
 *    5 |   | B | A | B | A | B | B |
 *    4 | A | B | A | A | B | A | A |
 *    3 | A | B | B | B | A | B | B |
 *    2 | B | A | A | A | B | A | A |
 *    1 | A | B | B | B | A | B | B |
 *    0 | A | B | A | A | B | A | A |
 *        0   1   2   3   4   5   6
 *
 * @endverbatim
 *
 * @param[in] p_player The Player we want to know if he/she can still win downward diagonally.
 *
 * @return @c true if the player can still win downward diagonally @c false otherwise.
 *
 **************************************************************************************************/
bool Game::canPlayerWinDiagonalDownward(const Player& p_player) const
{
    bool canPlayerWin{false};

    // Row to check:
    for(int rowIndex{0}; rowIndex < (m_gameboard->nbRows()) - (m_inARow - 1); ++rowIndex)
    {
        // Use these columns for starting point of the checks:
        for(int columnIndex{m_inARow - 1}; columnIndex < m_gameboard->nbColumns() - 1; ++columnIndex)
        {
            bool isPlayFree{true};
            int nbOfEmptyDiscsInDiagonal{0};

            // Check only for the good inARow value:
            for(int offset{0}; offset < m_inARow; ++offset)
            {
                isPlayFree &= (*m_gameboard)(Position{Row{rowIndex + offset}, Column{columnIndex - offset}}) == p_player.disc() ||
                              (*m_gameboard)(Position{Row{rowIndex + offset}, Column{columnIndex - offset}}) == Disc::noDisc();

                // If the space is free, we record it for later checks:
                if((*m_gameboard)(Position{Row{rowIndex + offset}, Column{columnIndex - offset}}) == Disc::noDisc())
                {
                    ++nbOfEmptyDiscsInDiagonal;
                }
            }

            // Make sure there is enough space left for the current player to win:
            isPlayFree &= (nbOfEmptyDiscsInDiagonal <= nbRemainingMoves(p_player));

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


/***********************************************************************************************//**
 * Computes the left-most limit needed for validation.
 *
 * @param[in] p_validationType The type of validation.
 *
 * @return The index of the left-most column to consider in the validation.
 *
 **************************************************************************************************/
int Game::leftValidationLimit(GridValidationType p_validationType) const
{
    const int lastPlayedRow{m_currentPosition.rowValue()};
    const int lastPlayedColumn{m_currentPosition.columnValue()};

    int leftSubscript{lastPlayedColumn - (m_inARow - 1)};
    leftSubscript = std::max(leftSubscript, 0);

    if(p_validationType == GridValidationType::DiagonalDownward)
    {
        int lowerSubscript{lastPlayedRow + (m_inARow - 1)};
        lowerSubscript = std::min(m_gameboard->nbRows() - 1, lowerSubscript);

        if(lastPlayedColumn - leftSubscript > lowerSubscript - lastPlayedRow)
        {
            leftSubscript = lastPlayedColumn - (lowerSubscript - lastPlayedRow);
        }
    }
    else if(p_validationType == GridValidationType::DiagonalUpward)
    {
        int upperSubscript{lastPlayedRow - (m_inARow - 1)};
        upperSubscript = std::max(0, upperSubscript);

        if(lastPlayedColumn - leftSubscript > lastPlayedRow - upperSubscript)
        {
            leftSubscript = lastPlayedColumn - (lastPlayedRow - upperSubscript);
        }
    }

    return leftSubscript;
}


/***********************************************************************************************//**
 * Computes the right-most limit needed for validation.
 *
 * @param[in] p_validationType The type of validation.
 *
 * @return The index of the right-most column to consider in the validation.
 *
 **************************************************************************************************/
int Game::rightValidationLimit(GridValidationType p_validationType) const

{
    const int lastPlayedRow{m_currentPosition.rowValue()};
    const int lastPlayedColumn{m_currentPosition.columnValue()};

    int rightSubscript{lastPlayedColumn + (m_inARow - 1)};
    rightSubscript = std::min(rightSubscript, m_gameboard->nbColumns() - 1);

    if(p_validationType == GridValidationType::DiagonalDownward)
    {
        int upperSubscript{(lastPlayedRow) - (m_inARow - 1)};
        upperSubscript = std::max(0, upperSubscript);

        if(rightSubscript - lastPlayedColumn > lastPlayedRow - upperSubscript)
        {
            rightSubscript = lastPlayedColumn + (lastPlayedRow - upperSubscript);
        }
    }
    else if(p_validationType == GridValidationType::DiagonalUpward)
    {
        int lowerSubscript{lastPlayedRow + (m_inARow - 1)};
        lowerSubscript = std::min(m_gameboard->nbRows() - 1, lowerSubscript);

        if(rightSubscript - lastPlayedColumn > lowerSubscript - lastPlayedRow)
        {
            rightSubscript = lastPlayedColumn + (lowerSubscript - lastPlayedRow);
        }
    }

    return rightSubscript;
}


/***********************************************************************************************//**
 * Computes the upper-most limit needed for validation.
 *
 * @param[in] p_validationType The type of validation.
 *
 * @return The index of the upper-most row to consider in the validation.
 *
 **************************************************************************************************/
int Game::upperValidationLimit(GridValidationType p_validationType) const
{
    const int lastPlayedRow{m_currentPosition.rowValue()};
    const int lastPlayedColumn{m_currentPosition.columnValue()};

    int upperSubscript{lastPlayedRow + (m_inARow - 1)};
    upperSubscript = std::min(m_gameboard->nbRows() - 1, upperSubscript);

    if(p_validationType == GridValidationType::DiagonalDownward)
    {
        int leftSubscript{lastPlayedColumn - (m_inARow - 1)};
        leftSubscript = std::max(leftSubscript, 0);

        if(upperSubscript - lastPlayedRow > lastPlayedColumn - leftSubscript)
        {
            upperSubscript = lastPlayedRow + (lastPlayedColumn - leftSubscript);
        }
    }
    else if(p_validationType == GridValidationType::DiagonalUpward)
    {
        int rightSubscript{lastPlayedColumn + (m_inARow - 1)};
        rightSubscript = std::min(rightSubscript, m_gameboard->nbColumns() - 1);

        if(upperSubscript - lastPlayedRow > rightSubscript - lastPlayedColumn)
        {
            upperSubscript = lastPlayedRow + (rightSubscript - lastPlayedColumn);
        }
    }

    return upperSubscript;
}


/***********************************************************************************************//**
 * Computes the lower-most limit needed for validation.
 *
 * @param[in] p_validationType The type of validation.
 *
 * @return The index of the lower-most row to consider in the validation.
 *
 **************************************************************************************************/
int Game::lowerValidationLimit(GridValidationType p_validationType) const
{
    const int lastPlayedRow{m_currentPosition.rowValue()};
    const int lastPlayedColumn{m_currentPosition.columnValue()};

    int lowerSubscript{lastPlayedRow - (m_inARow - 1)};
    lowerSubscript = std::max(0, lowerSubscript);

    if(p_validationType == GridValidationType::DiagonalDownward)
    {
        int rightSubscript{lastPlayedColumn + (m_inARow - 1)};
        rightSubscript = std::min(rightSubscript, m_gameboard->nbColumns() - 1);

        if(lastPlayedRow - lowerSubscript > rightSubscript - lastPlayedColumn)
        {
            lowerSubscript = lastPlayedRow - (rightSubscript - lastPlayedColumn);
        }
    }
    else if(p_validationType == GridValidationType::DiagonalUpward)
    {
        int leftSubscript = lastPlayedColumn - (m_inARow - 1);
        leftSubscript = std::max(leftSubscript, 0);

        if(lastPlayedRow - lowerSubscript > lastPlayedColumn - leftSubscript)
        {
            lowerSubscript = lastPlayedRow - (lastPlayedColumn - leftSubscript);
        }
    }

    return lowerSubscript;
}


/***********************************************************************************************//**
 * Computes the number of <em> in a row </em> Positions to check.
 *
 * @param[in] p_minValidationLimit The minimum index to check.
 * @param[in] p_maxValidationLimit The maximum index to check.
 *
 * @return The number of Positions to check.
 *
 **************************************************************************************************/
int Game::nbOfValidations(int p_minValidationLimit, int p_maxValidationLimit) const
{
    int nbCombinationsToCheck{abs(p_maxValidationLimit - p_minValidationLimit) + 1};
    nbCombinationsToCheck = nbCombinationsToCheck - (m_inARow - 1);

    return nbCombinationsToCheck;
}


/***********************************************************************************************//**
 * Computes the number of adjacent, identical Discs that are horizontally alligned from the 
 * current Position. The bounds for the computation are determined by the GameBoard geometry 
 * and the <em> in a row </em> value for the Game. Note that the method filters empty Discs
 * from the computation, as Players are not allow to use them.
 *
 * @return The number of adjacent, identical Discs that are horizontally alligned from the current
 *         Position.
 *
 **************************************************************************************************/
int Game::horizontalNbOfAdjacentDiscs() const
{

    const int leftLimit{leftValidationLimit()};
    const int rightLimit{rightValidationLimit()};
    const int nbValidations{nbOfValidations(leftLimit, rightLimit)};

    int pairIdenticalDiscs{0};
    int nbIdenticalDiscs{0};

    Row rowLastPlacedDisc{m_currentPosition.row()};

    for(int i{leftLimit}; i < leftLimit + nbValidations; ++i)
    {
        for(int j{0}; j < m_inARow - 1; ++j)
        {
            if(((*m_gameboard)(Position{rowLastPlacedDisc, Column{i + j}}) != Disc::noDisc()) &&
               ((*m_gameboard)(Position{rowLastPlacedDisc, Column{i + j}}) == (*m_gameboard)(Position{rowLastPlacedDisc, Column{i + j + 1}})))
            {
                pairIdenticalDiscs++;
            }
        }

        if(pairIdenticalDiscs == m_inARow - 1)
        {
            nbIdenticalDiscs = pairIdenticalDiscs + 1;

            break;
        }
        else
        {
            pairIdenticalDiscs = 0;
        }
    }

    return nbIdenticalDiscs;
}


/***********************************************************************************************//**
 * Computes the number of adjacent, identical Discs that are vertically alligned from the 
 * current Position. The bounds for the computation are determined by the GameBoard geometry 
 * and the <em> in a row </em> value for the Game. Note that the method filters empty Discs
 * from the computation, as Players are not allow to use them.
 *
 * @return The number of adjacent, identical Discs that are vertically alligned from the current
 *         Position.
 *
 **************************************************************************************************/
int Game::verticalNbOfAdjacentDiscs() const
{
    const int lowerLimit{lowerValidationLimit()};
    const int upperLimit{upperValidationLimit()};
    const int nbValidations{nbOfValidations(lowerLimit, upperLimit)};

    int pairIdenticalDiscs{0};
    int nbIdenticalDiscs{0};

    Column columnLastPlacedDisc{m_currentPosition.column()};

    for(int i{lowerLimit}; i < lowerLimit + nbValidations; ++i)
    {
        for(int j{0}; j < m_inARow - 1; ++j)
        {
            if(((*m_gameboard)(Position{Row{i + j}, columnLastPlacedDisc}) != Disc::noDisc()) &&
               ((*m_gameboard)(Position{Row{i + j}, columnLastPlacedDisc}) == (*m_gameboard)(Position{Row{i + j + 1}, columnLastPlacedDisc})))
            {
                pairIdenticalDiscs++;
            }
        }

        if(pairIdenticalDiscs == m_inARow - 1)
        {
            nbIdenticalDiscs = pairIdenticalDiscs + 1;

            break;
        }
        else
        {
            pairIdenticalDiscs = 0;
        }
    }

    return nbIdenticalDiscs;
}


/***********************************************************************************************//**
 * Computes the number of adjacent, identical Discs that are diagonally upward alligned from the 
 * current Position. The bounds for the computation are determined by the GameBoard geometry 
 * and the <em> in a row </em> value for the Game. Note that the method filters empty Discs
 * from the computation, as Players are not allow to use them.
 *
 * @return The number of adjacent, identical Discs that are diagonally upward alligned from the 
 *         current Position.
 *
 **************************************************************************************************/
int Game::upwardNbOfAdjacentDiscs() const
{
    const int lowerLimit{lowerValidationLimit(GridValidationType::DiagonalUpward)};
    const int leftLimit{leftValidationLimit(GridValidationType::DiagonalUpward)};
    const int rightLimit{rightValidationLimit(GridValidationType::DiagonalUpward)};
    const int nbValidations{nbOfValidations(leftLimit, rightLimit)};

    int pairIdenticalDiscs{0};
    int nbIdenticalDiscs{0};
    int counter{0};

    for(int i{leftLimit}; i < leftLimit + nbValidations; ++i)
    {
        int k{lowerLimit + counter};

        for(int j{0}; j < m_inARow - 1; ++j)
        {
            if(((*m_gameboard)(Position{Row{k}, Column{i + j}}) != Disc::noDisc()) &&
               ((*m_gameboard)(Position{Row{k}, Column{i + j}}) == (*m_gameboard)(Position{Row{k + 1}, Column{i + j + 1}})))
            {
                pairIdenticalDiscs++;
            }

            ++k;
        }

        if(pairIdenticalDiscs == m_inARow - 1)
        {
            nbIdenticalDiscs = pairIdenticalDiscs + 1;

            break;
        }

        pairIdenticalDiscs = 0;
        ++counter;
    }

    return nbIdenticalDiscs;
}


/***********************************************************************************************//**
 * Computes the number of adjacent, identical Discs that are diagonally downward alligned from the 
 * current Position. The bounds for the computation are determined by the GameBoard geometry 
 * and the <em> in a row </em> value for the Game. Note that the method filters empty Discs
 * from the computation, as Players are not allow to use them.
 *
 * @return The number of adjacent, identical Discs that are diagonally downward alligned from 
 *         the current Position.
 *
 **************************************************************************************************/
int Game::downwardNbOfAdjacentDiscs() const
{
    const int upperLimit{upperValidationLimit(GridValidationType::DiagonalDownward)};
    const int leftLimit{leftValidationLimit(GridValidationType::DiagonalDownward)};
    const int rightLimit{rightValidationLimit(GridValidationType::DiagonalDownward)};
    const int nbValidations{nbOfValidations(leftLimit, rightLimit)};

    int pairIdenticalDiscs{0};
    int nbIdenticalDiscs{0};
    int counter{0};

    for(int i{leftLimit}; i < leftLimit + nbValidations; ++i)
    {
        int k{upperLimit - counter};

        for(int j{0}; j < m_inARow - 1; ++j)
        {
            if(((*m_gameboard)(Position{Row{k}, Column{i + j}}) != Disc::noDisc()) &&
               ((*m_gameboard)(Position{Row{k}, Column{i + j}}) == (*m_gameboard)(Position{Row{k - 1}, Column{i + j + 1}})))
            {
                ++pairIdenticalDiscs;
            }

            --k;
        }

        if(pairIdenticalDiscs == m_inARow - 1)
        {
            nbIdenticalDiscs = pairIdenticalDiscs + 1;

            break;
        }

        pairIdenticalDiscs = 0;
        ++counter;
    }

    return nbIdenticalDiscs;
}


/***********************************************************************************************//**
 * Checks in the number of adjacent, horizontally aligned Discs, is equal to the required 
 * number of adjacent Discs for a win.
 *
 * @return @c true if the number of adjacent, horizontally aligned Discs, is equal to the required 
 *         number of adjacent Discs for a win, @c false otherwhise.
 *
 **************************************************************************************************/
bool Game::checkHorizontalWinner() const
{
    const int nbAdjacentIdenticalDiscs{horizontalNbOfAdjacentDiscs()};

    return nbAdjacentIdenticalDiscs == m_inARow;
}


/***********************************************************************************************//**
 * Checks in the number of adjacent, vertically aligned Discs, is equal to the required 
 * number of adjacent Discs for a win.
 *
 * @return @c true if the number of adjacent, vertically aligned Discs, is equal to the required 
 *         number of adjacent Discs for a win, @c false otherwhise.
 *
 **************************************************************************************************/
bool Game::checkVerticalWinner() const
{
    const int nbAdjacentIdenticalDiscs{verticalNbOfAdjacentDiscs()};

    return nbAdjacentIdenticalDiscs == m_inARow;
}


/***********************************************************************************************//**
 * Checks in the number of adjacent, diagonally upward aligned Discs, is equal to the required 
 * number of adjacent Discs for a win.
 *
 * @return @c true if the number of adjacent, diagonally upward aligned Discs, is equal to the 
 *         required number of adjacent Discs for a win, @c false otherwhise.
 *
 **************************************************************************************************/
bool Game::checkUpwardWinner() const
{
    const int nbAdjacentIdenticalDiscs{upwardNbOfAdjacentDiscs()};

    return nbAdjacentIdenticalDiscs == m_inARow;
}


/***********************************************************************************************//**
 * Checks in the number of adjacent, diagonally downward aligned Discs, is equal to the required 
 * number of adjacent Discs for a win.
 *
 * @return @c true if the number of adjacent, diagonally downward aligned Discs, is equal to the 
 *         required number of adjacent Discs for a win, @c false otherwhise.
 *
 **************************************************************************************************/
bool Game::checkDownwardWinner() const
{
    const int nbAdjacentIdenticalDiscs{downwardNbOfAdjacentDiscs()};

    return nbAdjacentIdenticalDiscs == m_inARow;
}
