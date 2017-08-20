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
 * @date    January 2017
 * @version 0.1
 *
 * Implementation for a Game utility.
 *
 **************************************************************************************************/

#include "../include/Game.h"

using namespace cxbase;

Game::Game(const PlayerList& p_players, const GameBoardSPtr p_gameboard, int p_inARow):
           m_players{p_players}, m_gameboard{p_gameboard}, m_inARow{p_inARow}
{
    PRECONDITION(p_players.size() >= 2);
    PRECONDITION(p_inARow >= 2);
    PRECONDITION(p_inARow < std::min(p_gameboard->nbColumns(), p_gameboard->nbRows()));

    INVARIANTS();
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
    m_turn = (m_turn + 1) % static_cast<int>(m_players.size()); // Cast is OK because this vector is always small.

}

void Game::checkInvariant() const
{
    INVARIANT(m_inARow >= 2);
    INVARIANT(m_inARow < std::min(m_gameboard->nbColumns(), m_gameboard->nbRows()));

    INVARIANT(m_nbTurns >= 0);
    INVARIANT(m_nbTurns < m_gameboard->nbPositions());

    INVARIANT(m_turn >= 0);
    INVARIANT(static_cast<unsigned int>(m_turn) < m_players.size());
}
