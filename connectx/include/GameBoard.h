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

namespace ui
{

/**********************************************************************************************//**
 * @brief A Connect X game board.
 *
 * A Connect X game board emulates a standard Four-In-A-Row game board in a scalable way. It
 * consists of two important and distinct areas: the game board area and the next disc area.
 *
 * The game board area is the area where the discs that have already been dropped by the
 * different players lie. In a Four-In-A-Row game, it represents the vertical plastic rack where
 * the discs are piled up vertically after each move.
 *
 * The next disc area is the area where the next disc that is about to be dropped in the game
 * board area is displayed. In a Four-In-A-Row game, it represents the disc in the active
 * player's hand, that is, the next disc to be dropped in the vertical plastic rack.
 *
 * Visually, the Connect X game board is displayed like this:
 *
 *   @verbatim
 *
 *     |--------------------------|
 *     |                          |
 *     |      Next disc area      |  <-- Next disc to be played is displayed here!
 *     |                          |
 *     |--------------------------|
 *     |                          |
 *     |                          |
 *     |                          |
 *     |     Game board area      | <-- All discs that have been played are piled up here.
 *     |                          |
 *     |                          |
 *     |                          |
 *     |                          |
 *     |--------------------------|
 *
 *   @endverbatim
 *
 * The Connect X game board class also offers many services that allow to perform actions on
 * sets of discs on the game board in a simplified way.
 *
 *************************************************************************************************/
class GameBoard : public Gtk::Paned
{

public:

    /******************************************************************************************//**
     * @brief Default constructor.
     *
     * Constructs a GameBoard with hidden discs in the next disc area and empty (i.e. black)
     * discs in the game board area. So in essence, it constructs an empty Connect X game board.
     *
     *********************************************************************************************/
    GameBoard();


    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    virtual ~GameBoard();


private:

    Gtk::Grid m_nextDiscArea;    ///< The next disc area layout.
    Gtk::Grid m_gameBoardGrid;   ///< The game board layout.

};

} // namespace ui

} // namespace cx

#endif // GAMEBOARD_H_243D9911_CDCC_4CD8_B2A5_14BE544ED80C

