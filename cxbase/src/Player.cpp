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
 * @file    Player.cpp
 * @author  Eric Poirier
 * @date    November 2016
 * @version 0.1
 *
 * Implementation for a Player utility.
 *
 **************************************************************************************************/

#include <sstream>

#include "../include/Player.h"

using namespace cxbase;

Player::Player(const cxutil::Name& p_name, const Disc& p_disc): m_name{p_name}, m_disc{p_disc}
{
    POSTCONDITION(m_name == p_name);
    POSTCONDITION(m_disc == p_disc);

    INVARIANTS();
}

bool Player::operator==(const Player& p_player) const
{
    bool areEqual{false};

    if(m_name == p_player.name() && m_disc == p_player.disc())
    {
        areEqual = true;
    }

    return areEqual;
}

bool Player::operator!=(const Player& p_player) const
{
    return !(*this == p_player);
}

void Player::print(std::ostream& p_stream) const
{
    p_stream << m_name.toString();
}

void Player::checkInvariant() const
{
    INVARIANT(m_disc != Disc::NO_DISC);
}
