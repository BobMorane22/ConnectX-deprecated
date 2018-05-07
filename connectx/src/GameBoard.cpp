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
 * @file    GameBoard.cpp
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Implementation for a Connect X GUI game board utility.
 *
 **************************************************************************************************/


#include <cxbase/include/GameBoard.h>

#include "../include/GameBoard.h"


namespace
{


} // unnamed namespace

cx::ui::GameBoard::GameBoard(const std::shared_ptr<cxbase::GameBoard>& p_gameBoard) : m_gameBoard{p_gameBoard}
{
    set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);

    const int nbRows    {m_gameBoard->nbRows()   };
    const int nbColumns {m_gameBoard->nbColumns()};

    // Setting up the next disc area:
    m_nextDiscArea.set_row_homogeneous(true);
    m_nextDiscArea.set_column_homogeneous(true);

    for(int col{0}; col < nbColumns; ++col)
    {
        NDADisc* noDisc{Gtk::manage(new NDADisc)};
        noDisc->set_size_request(40, 40);
        m_nextDiscArea.attach(*noDisc, col, 0, 1, 1);
    }

    // Then, the game board area:
    m_gameBoardGrid.set_row_homogeneous(true);
    m_gameBoardGrid.set_column_homogeneous(true);

    for(int row{0}; row < nbRows; ++row)
    {
        for(int col{0}; col < nbColumns; ++col)
        {
            GBDisc* noDisc{Gtk::manage(new GBDisc)};
            noDisc->set_size_request(40, 40);
            m_gameBoardGrid.attach(*noDisc, col, row, 1, 1);
        }
    }

    // Layout setup:
    pack1(m_nextDiscArea, true, false);
    pack2(m_gameBoardGrid, true, false);
}



// Memory management: https:   https://developer.gnome.org/gtkmm-tutorial/stable/sec-memory-widgets.html.en
// Why std tools are not used: https://softwareengineering.stackexchange.com/questions/206223/gtkmm-manage-add-vs-smart-pointers
cx::ui::GameBoard::~GameBoard() = default;
