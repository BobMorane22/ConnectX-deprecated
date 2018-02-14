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
 * @file    GameBoard.h
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Interface for a Connect X GUI game board utility.
 *
 **************************************************************************************************/

#ifndef GAMEBOARD_H_243D9911_CDCC_4CD8_B2A5_14BE544ED80C
#define GAMEBOARD_H_243D9911_CDCC_4CD8_B2A5_14BE544ED80C

#include <gtkmm/grid.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/paned.h>

#include "../include/GBDisc.h"
#include "../include/NDADisc.h"

namespace cx
{

/**********************************************************************************************//**
 *
 *
 *************************************************************************************************/
class GameBoard : public Gtk::Paned
{

public:

    /******************************************************************************************//**
     *
     *
     *********************************************************************************************/
    GameBoard();


    /******************************************************************************************//**
     *
     *
     *********************************************************************************************/
    virtual ~GameBoard();


private:

    Gtk::Grid m_nextDiscArea;    ///<
    Gtk::Grid m_gameBoardGrid;   ///<

};

} // namespace cx

#endif // GAMEBOARD_H_243D9911_CDCC_4CD8_B2A5_14BE544ED80C

