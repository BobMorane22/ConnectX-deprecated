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
 * Implementation for the widget containing a new player's information.
 *
 **************************************************************************************************/

#include <sstream>

#include <cxutil/include/Assertion.h>
#include <cxutil/include/narrow_cast.h>

#include "../include/NewPlayerRow.h"
#include "../include/util.h"


cx::ui::NewPlayerRow::NewPlayerRow(const std::string& p_playerName, const cxutil::Color& p_playerDiscColor)
{
    m_playerName.set_text(p_playerName);

    // Add color to the button:
    Gdk::RGBA btnColor{cx::ui::convertToGdkRGBA(p_playerDiscColor)};
    m_playerDiscColor.set_rgba(btnColor);

    // Populate the row layout for the ListView:
    m_gridLayout.add(m_playerName);
    m_gridLayout.add(m_playerDiscColor);

    add(m_gridLayout);
}


void cx::ui::NewPlayerRow::update(const std::string& p_playerNewName, const cxutil::Color& p_playerNewDiscColor)
{
    (void)p_playerNewName;
    (void)p_playerNewDiscColor;
}


std::string cx::ui::NewPlayerRow::playerName() const
{
    return m_playerName.get_text();
}


cxutil::Color cx::ui::NewPlayerRow::playerDiscColor() const
{
    return cx::ui::deprecated::convertToLocalColor(m_playerDiscColor.get_color());
}
