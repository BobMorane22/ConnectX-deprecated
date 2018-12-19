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

#include <cxutil/include/ReturnCode.h>

#include "NewPlayerRow.h"


namespace cx
{

namespace ui
{

/***********************************************************************************************//**
 * @class NewPlayersList
 *
 * @brief Widget to list players.
 *
 * Widget containing rows of players to be registered for a Connect X game, as well as the color
 * they have chosen for their discs.
 *
 * @see cx::ui::NewPlayerRow
 *
 **************************************************************************************************/
class NewPlayersList final : public Gtk::ListBox
{

public:

///@{ @name Object Construction and Destruction

    /*******************************************************************************************//**
     * @brief Default constructor.
     *
     * Constructs a list of two players with different colors. This is the basic Connect X
     * configuration, and is equivalent to the classic Connect 4 requirements.
     *
     **********************************************************************************************/
    NewPlayersList();


    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    virtual ~NewPlayersList();

///@}

///@{ @name Accessors


    /*******************************************************************************************//**
     * @brief Accesses the size of the list.
     *
     * The size of the list is the number of players (visually, the number of rows) contained
     * in the widget.
     *
     * @return The size of the list.
     *
     **********************************************************************************************/
    std::size_t size() const;


    /*******************************************************************************************//**
     * @brief Accesses a specific row's player disc color.
     *
     * For a given row index, gets the specific row's player disc color.
     *
     * @param p_index The row index.
     *
     * @pre The row index is at most the number of players in the list, minus one (zero-based).
     *
     * @return The row's player disc color.
     *
     **********************************************************************************************/
    cxutil::Color rowPlayerDiscColor(const std::size_t p_index) const;


    /*******************************************************************************************//**
     * @brief Accesses a specific row's player name.
     *
     * For a given row index, gets the specific row's player name.
     *
     * @param p_index The row index.
     *
     * @pre The row index is at most the number of players in the list, minus one (zero-based).
     *
     * @return The row's player name.
     *
     **********************************************************************************************/
    std::string rowPlayerName(const std::size_t p_index) const;


    /*******************************************************************************************//**
     * @brief Accesses all player disc colors in the list.
     *
     * @return An @c std::vector containing all the player disc colors in the list.
     *
     **********************************************************************************************/
    std::vector<cxutil::Color> rowColors() const;


    /*******************************************************************************************//**
     * @brief Accesses all player names in the list.
     *
     * @return An @c std::vector containing all the player names in the list.
     *
     **********************************************************************************************/
    std::vector<std::string> rowPlayerNames() const;


///@}

///@{ @name Mutators

    /*******************************************************************************************//**
     * @brief Adds a row to the list.
     *
     * Adds a row to the list. The row is appended at the end of the list.
     *
     * @param p_playerNewName      The player's name.
     * @param p_playerNewDiscColor The player's disc color.
     *
     * @pre The player name is not an empty string.
     *
     * @return A return code indicating if the operation succeeded. @c ReturnCode::OK is returned
     *         if the operation succeeded, @c ReturnCode::ERROR is returned if there was a problem
     *         appending the new row. If the return code is @c ReturnCode::ERROR , the row has
     *         not been added.
     *
     * @see cxutil::ReturnCode
     *
     **********************************************************************************************/
    cxutil::ReturnCode addRow(const std::string&   p_playerNewName,
                              const cxutil::Color& p_playerNewDiscColor);


    /*******************************************************************************************//**
     * @brief Removes a row from the list by its index.
     *
     * @param p_index The row index.
     *
     * @pre p_index The row index is at most the number of players in the list,
     *              minus one (zero-based).
     *
     * @return A @c cxutil::ReturnCode indicating if the operation succeeded or failed.
     *
     **********************************************************************************************/
    cxutil::ReturnCode removeRow(const std::size_t p_index);


    /*******************************************************************************************//**
     * @brief Removes a row from the list.
     *
     * Removes a row from the list. The row must match a given player name and disc color.. If
     * the player name and the disc color pair is not found, an error is returned and nothing
     * is removed.
     *
     * @param p_playerName      The player's name.
     * @param p_playerDiscColor The player's disc color.
     *
     * @pre The player name is not an empty string.
     *
     * @return A return code indicating if the operation succeeded. @c ReturnCode::OK is returned
     *         if the operation succeeded, @c ReturnCode::ERROR is returned if there was a problem
     *         removing the new row. If the return code is @c ReturnCode::ERROR , the row has
     *         not been added.
     *
     **********************************************************************************************/
    cxutil::ReturnCode removeRow(const std::string&   p_playerName,
                                 const cxutil::Color& p_playerDiscColor);


    /*******************************************************************************************//**
     * @brief Updates a row from its index.
     *
     * Updates row information from its index. You can update the player name and the player disc
     * color.
     *
     * @param p_index                 The row index.
     * @param p_newPlayerNewName      The player name.
     * @param p_newPlayerNewDiscColor The player disc color.
     *
     * @pre The row index is at most the number of players in the list, minus one (zero-based).
     * @pre The player name is not an empty string.
     *
     * @return A @c cxutil::ReturnCode indicating if the operation succeeded or failed.
     *
     **********************************************************************************************/
    cxutil::ReturnCode updateRow(const std::size_t    p_index,
                                 const std::string&   p_newPlayerNewName,
                                 const cxutil::Color& p_newPlayerNewDiscColor);


    /*******************************************************************************************//**
     * @brief Clears the list content.
     *
     * Removes every players in the list, leaving the container empty (visually, there are
     * no rows left).
     *
     * @post The list is empty (no more rows).
     *
     **********************************************************************************************/
    void clear();

///@}

private:

///@{ @name Internal container manipulations

    const cx::ui::NewPlayerRow* row(const std::size_t p_index) const;
    cx::ui::NewPlayerRow*       row(const std::size_t p_index);

    std::vector<const cx::ui::NewPlayerRow*> rows() const;
    std::vector<cx::ui::NewPlayerRow*>       rows();

    cxutil::ReturnCode removeManaged(cx::ui::NewPlayerRow* p_row);

///@}

};

} // namespace ui

} // namespace cx

#endif // NEWPLAYERSLIST_H_A39DED7C_43CD_419E_A4AA_4E6A61C46E63
