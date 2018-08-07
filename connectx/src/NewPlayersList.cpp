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
 * @file    NewPlayersList.cpp
 * @author  Eric Poirier
 * @date    May 2018
 * @version 1.0
 *
 * Implementation for the widget containing the list of players to add to a game.
 *
 **************************************************************************************************/


#include "../include/NewPlayersList.h"


cx::ui::NewPlayersList::NewPlayersList()
{
    // Two players are set up. More can manually be added by the users later, if needed:
    m_newPlayersList.push_back(std::move(*Gtk::manage(new NewPlayerRow("-- Player 1 --", cxutil::Color::black()))));
    m_newPlayersList.push_back(std::move(*Gtk::manage(new NewPlayerRow("-- Player 2 --", cxutil::Color::red()  ))));

    for(auto& row : m_newPlayersList)
    {
        append(row);
    }
}


cx::ui::NewPlayersList::~NewPlayersList() = default;
