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
 * Interface for a widget containing the information of a player to add to a game.
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
 * @class NewPlayerRow
 *
 * @brief This widget represents the new information needed by the application to register a
 *        new player.
 *
 * The informations needed are:
 *
 * <ul>
 *   <li> The player's name       </li>
 *   <li> The player's disc color </li>
 * </ul>
 *
 * This widget is not intended to be used by itself. Rather, it should be bundled together in
 * some Gtk::ListBox widget with others like it. @c cxexec::NewPlayersList is an example.
 *
 * @invariant The member variable @c m_playerName does not contain an empty string.
 *
 * @see cxexec::NewPlayersList
 *
 **************************************************************************************************/
class NewPlayerRow final : public Gtk::ListBoxRow
{

public:

///@{ @name Object Construction and Destruction

    /*******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_playerName       The name of the player.
     * @param p_playerDiscColor  The color chosen by or for the player's disc.
     *
     **********************************************************************************************/
    NewPlayerRow(const std::string& p_playerName, const cxutil::Color& p_playerDiscColor);


    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    ~NewPlayerRow();

///@}

///@{ @name Mutators

    /*******************************************************************************************//**
     * @brief Updates the player's information. The name and the disc color can be changed.
     *
     * @param p_playerNewName       The new name of the player.
     * @param p_playerNewDiscColor  The new color chosen by or for the player's disc.
     *
     **********************************************************************************************/
    void update(const std::string& p_playerNewName, const cxutil::Color& p_playerNewDiscColor);

///@}

///@{ @name Accessors

    /*******************************************************************************************//**
     * @brief  Accessor for the player's name.
     *
     * @return The player's actual name as a string.
     *
     **********************************************************************************************/
    std::string playerName() const;


    /*******************************************************************************************//**
     * @brief Accessor for the player's disc color.
     *
     * @return The player's actual disc color.
     *
     **********************************************************************************************/
    cxutil::Color playerDiscColor() const;

///@}


private:

    void checkInvariant() const;


///@{ @name Data members

    Gtk::Grid                     m_gridLayout;       ///< The widget's layout.

    Gtk::Entry                    m_playerName;       ///< The edit box in which the player's name
                                                      ///< typed.

    Gtk::ColorButton              m_playerDiscColor;  ///< The button repsonsible to present the
                                                      ///< player with a color choice for his disc.

///@}

};


///@{ @name Operators

/***********************************************************************************************//**
 * @brief Equality operator.
 *
 * Checks if two @c NewPlayerRow are equal. Two @c NewPlayerRow are equal <em>if and only if</em>
 * they share the same player name and the same player disc color.
 *
 * @param p_lhs The first @NewPlayerRow object to compare against.
 * @param p_rhs The second @NewPlayerRow object to compare against.
 *
 * @return @c true if both objects are considered equal @c false otherwise.
 *
 **************************************************************************************************/
bool operator==(const NewPlayerRow& p_lhs, const NewPlayerRow& p_rhs);


/***********************************************************************************************//**
 * @brief Non-equality operator.
 *
 * Checks if two @c NewPlayerRow are NOT equal. Two @c NewPlayerRow are NOT equal if they differ
 * in their player names and/or in their player disc colors.
 *
 * @param p_lhs The first @NewPlayerRow object to compare against.
 * @param p_rhs The second @NewPlayerRow object to compare against.
 *
 * @return @return @c true if both objects are considered NOT equal @c false otherwise.
 *
 **************************************************************************************************/
bool operator!=(const NewPlayerRow& p_lhs, const NewPlayerRow& p_rhs);

///@}

} // namespace ui

} // namespace cx

#endif // NEWPLAYERROW_H_D145FCB0_8682_48C4_B05E_7805685429E6
