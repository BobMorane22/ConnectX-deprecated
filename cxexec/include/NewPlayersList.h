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

#ifndef NEWPLAYERSLIST_H_A39DED7C_43CD_419E_A4AA_4E6A61C46E63
#define NEWPLAYERSLIST_H_A39DED7C_43CD_419E_A4AA_4E6A61C46E63

#include <vector>

#include <gtkmm/listbox.h>
#include <gtkmm/treeview.h>

#include "NewPlayerRow.h"

namespace cx
{

namespace ui
{

/***********************************************************************************************//**
 * Widget containing row of players to be registered for a Connect X game, as well as the color
 * they have chosen for their discs. There can be a minimum of two players and a maximum of ten
 * players listed in this widget.
 *
 * @see cx::ui::NewPlayerRow
 *
 **************************************************************************************************/
class NewPlayersList final : public Gtk::ListBox
{

public:

    /*******************************************************************************************//**
     * Default constructor.
     *
     * Construct a list of two players with different colors. This is the basic Connect X
     * configuration, an is equivalent to the classic Connect 4 requirements.
     *
     **********************************************************************************************/
    NewPlayersList();


    /*******************************************************************************************//**
     * Default destructor.
     *
     **********************************************************************************************/
    ~NewPlayersList();

private:

    const static int MIN_NB_PLAYERS;            ///< Minimum number of players that can be registered
                                                ///< in this widget.

    const static int MAX_NB_PLAYERS;            ///< Maximum number of players that can be registered
                                                ///< in this widget.

    std::vector<NewPlayerRow> m_newPlayersList; ///< List of rows of players for a game. These rows
                                                ///< are vertically concatenated to make the current
                                                ///< widget.

};

} // namespace ui

} // namespace cx

#endif // NEWPLAYERSLIST_H_A39DED7C_43CD_419E_A4AA_4E6A61C46E63
