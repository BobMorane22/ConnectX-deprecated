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

#include <iostream>

#include "../include/GameBoard.h"


cx::GameBoard::GameBoard()
{
    set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);

    const int nbRows{6};
    const int nbColumns{7};

    // Setting up the next disc area first:
    m_nextDiscArea.set_row_homogeneous(true);
    m_nextDiscArea.set_column_homogeneous(true);

    for(int col{0}; col < nbColumns; ++col)
    {
        NDADisc* noDisc{new NDADisc};
        noDisc->set_size_request(40, 40);
        m_nextDiscArea.attach(*noDisc, col, 0, 1, 1);
    }

    // Then the game board:
    m_gameBoardGrid.set_row_homogeneous(true);
    m_gameBoardGrid.set_column_homogeneous(true);

    for(int row{0}; row < nbRows; ++row)
    {
        for(int col{0}; col < nbColumns; ++col)
        {
            GBDisc* noDisc{new GBDisc};
            noDisc->set_size_request(40, 40);
            m_gameBoardGrid.attach(*noDisc, col, row, 1, 1);
        }
    }

    // Layout setup:
    pack1(m_nextDiscArea, true, false);
    pack2(m_gameBoardGrid, true, false);
}


cx::GameBoard::~GameBoard() = default;
