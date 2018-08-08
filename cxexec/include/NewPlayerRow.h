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
 * @file    NewPlayerRow.h
 * @author  Eric Poirier
 * @date    July 2018
 * @version 1.0
 *
 * Interface for the widget containing a new player's information.
 *
 **************************************************************************************************/

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
 * @file    NewPlayersList.h
 * @author  Eric Poirier
 * @date    May 2018
 * @version 1.0
 *
 * Interface for the widget containing the list of players to add to a game.
 *
 **************************************************************************************************/

#ifndef NEWPLAYERROW_H_D145FCB0_8682_48C4_B05E_7805685429E6
#define NEWPLAYERROW_H_D145FCB0_8682_48C4_B05E_7805685429E6

#include <gtkmm/listboxrow.h>
#include <gtkmm/entry.h>
#include <gtkmm/grid.h>
#include <gtkmm/liststore.h>
#include <gtkmm/colorbutton.h>

#include <cxutil/include/Color.h>

#include "../include/NDADisc.h"

namespace cx
{

namespace ui
{

/***********************************************************************************************//**
 * https://github.com/GNOME/gtkmm-documentation/tree/master/examples/book/listbox
 **************************************************************************************************/
class NewPlayerRow : public Gtk::ListBoxRow
{

public:

    NewPlayerRow(const std::string& p_playerName, const cxutil::Color& p_playerDiscColor);

    void update(const std::string& p_playerNewName, const cxutil::Color& p_playerNewDiscColor);

    std::string playerName() const;
    cxutil::Color playerDiscColor() const;

private:

    Glib::RefPtr<Gtk::ListStore>    m_listEntry;

    Gtk::Grid        m_gridLayout;
    Gtk::Entry       m_playerName;
    Gtk::ColorButton m_playerDiscColor;
};

} // namespace ui

} // namespace cx

#endif // NEWPLAYERROW_H_D145FCB0_8682_48C4_B05E_7805685429E6
