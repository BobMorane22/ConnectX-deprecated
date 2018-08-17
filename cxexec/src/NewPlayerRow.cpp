/***************************************************************************************************
 *
 * Copyright (C) 2018 Connect X team
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
 * @file    NewPlayerRow.cpp
 * @author  Eric Poirier
 * @date    July 2018
 * @version 1.0
 *
 * Implementation for a widget containing the information of a player to add to a game.
 *
 **************************************************************************************************/

#include <sstream>

#include <cxutil/include/Assertion.h>
#include <cxutil/include/narrow_cast.h>
#include <cxutil/include/ContractException.h>

#include "../include/NewPlayerRow.h"
#include "../include/util.h"


cx::ui::NewPlayerRow::NewPlayerRow(const std::string& p_playerName, const cxutil::Color& p_playerDiscColor)
{
    PRECONDITION(!p_playerName.empty());

    m_playerName.set_text(p_playerName);

    // Add color to the button:
    Gdk::RGBA btnColor{cx::ui::convertToGdkRGBA(p_playerDiscColor)};
    m_playerDiscColor.set_rgba(btnColor);

    // Populate the row layout for the ListView:
    m_gridLayout.add(m_playerName);
    m_gridLayout.add(m_playerDiscColor);

    add(m_gridLayout);

    INVARIANTS();
}


void cx::ui::NewPlayerRow::update(const std::string& p_playerNewName, const cxutil::Color& p_playerNewDiscColor)
{
    PRECONDITION(!p_playerNewName.empty());

    // First we update the player's name:
    m_playerName.set_text(p_playerNewName);

    // Then we update the player's color. Usually we could check if the color has changed
    // before updating but here, since two different color types are in play, this
    // operation would not be free, and so we go ahead and skip it:
    m_playerDiscColor.set_color(cx::ui::deprecated::convertToGdkColor(p_playerNewDiscColor));

    INVARIANTS();
}


std::string cx::ui::NewPlayerRow::playerName() const
{
    return m_playerName.get_text();
}


cxutil::Color cx::ui::NewPlayerRow::playerDiscColor() const
{
    return cx::ui::deprecated::convertToLocalColor(m_playerDiscColor.get_color());
}


/***********************************************************************************************//**
 * Checks if all class invariants are respected. Call this method every time a modification is
 * done to the class state to avoid incoherent states. If the invariants are not respected, an
 * exception of the type @c InvariantException is thrown.
 *
 **************************************************************************************************/
void cx::ui::NewPlayerRow::checkInvariant() const
{
    INVARIANT(!m_playerName.get_text().empty());
}
