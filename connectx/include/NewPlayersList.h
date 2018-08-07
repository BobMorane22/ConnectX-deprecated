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
 *
 **************************************************************************************************/
class NewPlayersList : public Gtk::ListBox
{

public:
    NewPlayersList();
    ~NewPlayersList();

private:
    std::vector<NewPlayerRow> m_newPlayersList;

};

} // namespace ui

} // namespace cx

#endif // NEWPLAYERSLIST_H_A39DED7C_43CD_419E_A4AA_4E6A61C46E63
