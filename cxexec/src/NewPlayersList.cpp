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

#include <algorithm>

#include <cxutil/include/Assertion.h>
#include <cxutil/include/ContractException.h>
#include <cxutil/include/narrow_cast.h>

#include "../include/NewPlayersList.h"


cx::ui::NewPlayersList::NewPlayersList()
{
    // We use Gtk::manage here to let Gtkmm deal with the children deletions:
    add(*Gtk::manage(new NewPlayerRow("-- Player 1 --", cxutil::Color::black())));
    add(*Gtk::manage(new NewPlayerRow("-- Player 2 --", cxutil::Color::red()  )));
}


cx::ui::NewPlayersList::~NewPlayersList() = default;


std::size_t cx::ui::NewPlayersList::size() const
{
    return get_children().size();
}


cxutil::Color cx::ui::NewPlayersList::rowPlayerDiscColor(const std::size_t p_index) const
{
    PRECONDITION(p_index < size());

    const cx::ui::NewPlayerRow* specificRow{row(p_index)};

    CX_ASSERT(specificRow);

    return specificRow->playerDiscColor();
}


std::string cx::ui::NewPlayersList::rowPlayerName(const std::size_t p_index) const
{
    PRECONDITION(p_index < size());

    const cx::ui::NewPlayerRow* specificRow{row(p_index)};

    CX_ASSERT(specificRow);

    return specificRow->playerName();
}


std::vector<cxutil::Color> cx::ui::NewPlayersList::rowColors() const
{
    std::vector<cxutil::Color> colors;

    for(const auto row : rows())
    {
        colors.push_back(row->playerDiscColor());
    }

    return colors;
}


std::vector<std::string> cx::ui::NewPlayersList::rowPlayerNames() const
{
    std::vector<std::string> names;

    for(const auto row : rows())
    {
        names.push_back(row->playerName());
    }

    return names;
}


cxutil::ReturnCode cx::ui::NewPlayersList::addRow(const std::string&    p_playerNewName,
                                                  const cxutil::Color&  p_playerNewDiscColor)
{
    using namespace cxutil;

    PRECONDITION(!p_playerNewName.empty());

    // We first make sure the color given as an argument does not already exist in the list:
    const std::vector<Color> colors{rowColors()};
    const bool colorAlreadyChosen{std::any_of(std::begin(colors),
                                              std::end(colors),
                                              [&p_playerNewDiscColor](const Color p_color)
                                              {
                                                  return p_color == p_playerNewDiscColor;
                                              })};

    if(colorAlreadyChosen)
    {
        return ReturnCode{ReturnCode::Code::ERROR, "The color already exists in the list."};
    }

    // The color is not already in use, we can continue:
    const std::size_t sizeBefore{size()};

    // We use Gtk::manage here to let Gtkmm deal with the children deletions:
    add(*Gtk::manage(new NewPlayerRow(p_playerNewName, p_playerNewDiscColor)));
    
    const std::size_t sizeAfter{size()};

    // We check if the new row has indeed been added:
    if(sizeAfter == sizeBefore + 1)
    {
        return ReturnCode{ReturnCode::Code::OK};
    }

    return ReturnCode{ReturnCode::Code::ERROR, "Unable to add player to the list."};
}


cxutil::ReturnCode cx::ui::NewPlayersList::removeRow(const std::size_t p_index)
{
    PRECONDITION(p_index < size());

    cx::ui::NewPlayerRow* specificRow{row(p_index)};

    CX_ASSERT(specificRow);

    return removeManaged(specificRow);
}


cxutil::ReturnCode cx::ui::NewPlayersList::removeRow(const std::string&    p_playerNewName,
                                                     const cxutil::Color&  p_playerNewDiscColor)
{
    PRECONDITION(!p_playerNewName.empty());

    using namespace cxutil;

    const cx::ui::NewPlayerRow rowToRemoveData{p_playerNewName, p_playerNewDiscColor};
    cx::ui::NewPlayerRow*      rowToRemoveAddress{nullptr};

    std::vector<cx::ui::NewPlayerRow*> allRows{rows()};

    for(auto row : allRows)
    {
        CX_ASSERT(row);

        if(*row == rowToRemoveData)
        {
            // This is the address of the row we want to remove:
            rowToRemoveAddress = row;
        }
    }

    if(rowToRemoveAddress)
    {
        return removeManaged(rowToRemoveAddress);
    }

    return ReturnCode{ReturnCode::Code::ERROR, "Row not found."};
}


cxutil::ReturnCode cx::ui::NewPlayersList::updateRow(const std::size_t    p_index,
                                                     const std::string&   p_playerNewName,
                                                     const cxutil::Color& p_playerNewDiscColor)
{
    PRECONDITION(p_index < size());
    PRECONDITION(!p_playerNewName.empty());

    using namespace cxutil;

    bool colorAlreadyChosen{std::any_of(std::begin(rowColors()),
                                        std::end(rowColors()),
                                        [&p_playerNewDiscColor](const cxutil::Color& p_color)
                                        {
                                            return p_playerNewDiscColor == p_color;
                                        })};

    if(colorAlreadyChosen)
    {
        return ReturnCode{ReturnCode::Code::ERROR, "The color already exists in the list."};
    }

    // All is fine, we can proceed with the update:
    cx::ui::NewPlayerRow* rowToUpdate{row(p_index)};
    CX_ASSERT(rowToUpdate);

    rowToUpdate->update(p_playerNewName, p_playerNewDiscColor);

    return ReturnCode{ReturnCode::Code::OK};
}


void cx::ui::NewPlayersList::clear()
{
    std::vector<NewPlayerRow*> allRows{rows()};

    for(auto row : allRows)
    {
        CX_ASSERT(row);
        CX_ASSERT(removeManaged(row).isOk());
    }

    // There should be no one left...
    POSTCONDITION(get_children().empty());
}


/***************************************************************************************************
 * @brief Access a row (@c const version).
 *
 * @param p_index The row index.
 *
 * @pre The row index is at most the number of players in the list,
 *      minus one (zero-based).
 *
 * @post The returned address is valid.
 *
 * @return The row address.
 *
 **************************************************************************************************/
const cx::ui::NewPlayerRow* cx::ui::NewPlayersList::row(const std::size_t p_index) const
{
    PRECONDITION(p_index < size());

    // We get the address of all the non-internal children (const version):
    const std::vector<const Gtk::Widget*> rows{get_children()};

    // We cast the needed widget to its most specific row type:
    const cx::ui::NewPlayerRow* row{cxutil::narrow_cast<const cx::ui::NewPlayerRow*>(rows[p_index])};

    POSTCONDITION(row);

    return row;
}


/***************************************************************************************************
 * @brief Access a row (non @c const version).
 *
 * @param p_index The row index.
 *
 * @pre The row index is at most the number of players in the list,
 *      minus one (zero-based).
 *
 * @post The returned address is valid.
 *
 * @return The row address.
 *
 * @note This ugly implementation only serves to avoid duplication of code with the @c const method
 *       version. See @c the const version for the logic. I thought better to leave the pre and post
 *       conditions even though they are also checked in the @c const version, just as a remainder
 *       that this method also needs them.
 *
 **************************************************************************************************/
cx::ui::NewPlayerRow* cx::ui::NewPlayersList::row(const std::size_t p_index)
{
    PRECONDITION(p_index < size());

    cx::ui::NewPlayerRow* row{const_cast<cx::ui::NewPlayerRow*>(static_cast<const cx::ui::NewPlayersList*>(this)->row(p_index))};

    POSTCONDITION(row);

    return row;
}


/*************************************************************************************************
 * @brief Gets the list of all rows by their addresses (@c const version).
 *
 * @post Every address in the returned vector is valid.
 *
 * @return A vector containig the row addresses.
 *
 **************************************************************************************************/
std::vector<const cx::ui::NewPlayerRow*> cx::ui::NewPlayersList::rows() const
{
    // We get the address of all the non-internal children:
    const std::vector<const Gtk::Widget*> baseRows{get_children()};

    // We setup a new vector, with specific types:
    std::vector<const cx::ui::NewPlayerRow*> specificRows;

    // We specialize every widget into its most specific type:
    for(auto row : baseRows)
    {
        specificRows.push_back(cxutil::narrow_cast<const cx::ui::NewPlayerRow*>(row));
    }

    POSTCONDITION(std::none_of(std::begin(specificRows),
                               std::end(specificRows),
                               [](const cx::ui::NewPlayerRow* p_row)
                               {
                                   return p_row == nullptr;
                               }));

    return specificRows;
}


/*************************************************************************************************
 * @brief Gets the list of all rows by their addresses (non @c const version).
 *
 * @post Every address in the returned vector is valid.
 *
 * @return A vector containig the row addresses.
 *
 * @note There seems to be no way to generate the non @c const version from the @ const version
 *       using casting here because of the @c std::vector. This is why, sadly, I was forced to
 *       introduce duplication in the code.
 *
 **************************************************************************************************/
std::vector<cx::ui::NewPlayerRow*> cx::ui::NewPlayersList::rows()
{
    // We get the address of all the non-internal children:
    const std::vector<Gtk::Widget*> baseRows{get_children()};

    // We setup a new vector, with specific types:
    std::vector<cx::ui::NewPlayerRow*> specificRows;

    // We specialize every widget into its most specific type:
    for(auto row : baseRows)
    {
        specificRows.push_back(cxutil::narrow_cast<cx::ui::NewPlayerRow*>(row));
    }

    POSTCONDITION(std::none_of(std::begin(specificRows),
                               std::end(specificRows),
                               [](const cx::ui::NewPlayerRow* p_row)
                               {
                                   return p_row == nullptr;
                               }));

    return specificRows;
}


/***************************************************************************************************
 * @brief Remove and delete a <tt>Gtk::manage</tt>d widget from the list.
 *
 * According to the Gtkmm documentation for the @c Gtk::Container::remove method:
 *
 *   "If widget is managed with @c Gtk::manage(), and you don't want to use widget again, then
 *    you should delete it, because there will no longer be any parent container to delete
 *    it automatically."
 *
 * Source: <a href=https://developer.gnome.org/gtkmm/stable/classGtk_1_1Container.html#a9f31c07118f7bdc7a4e0651acf35abbc>
           Gtk::Container</a>. This is exactly our case, so we @c delete it manually, in this
           method to avoid pollution.
 *
 * @param p_row The address of the row to @c remove (and @c delete ).
 *
 * @warning This internal service is dangerous: there is no way to check if the widget is either
 *          <tt>Gtk::manage</tt>d or on the stack. Be careful.
 *
 **************************************************************************************************/
cxutil::ReturnCode cx::ui::NewPlayersList::removeManaged(cx::ui::NewPlayerRow* p_row)
{
    using namespace cxutil;

    const std::vector<cx::ui::NewPlayerRow*> allRows{rows()};

    const bool rowDoesNotExist{std::none_of(std::begin(allRows),
                                            std::end(allRows),
                                            [p_row](const cx::ui::NewPlayerRow* p_aRow)
                                            {
                                                return p_aRow == p_row;
                                            })};

    if(rowDoesNotExist)
    {
        return ReturnCode{ReturnCode::Code::ERROR, "Row not found."};
    }

    const std::size_t nbRowsBefore{rows().size()};

    // Remove the row from the Gtk::Container:
    remove(*p_row);

    // Free it from the heap:
    delete(p_row);

    const std::size_t nbRowsAfter{rows().size()};

    if(nbRowsBefore != nbRowsAfter + 1)
    {
        return ReturnCode{ReturnCode::Code::ERROR, "A NewPlayersList row has not been deleted properly."};
    }

    return cxutil::ReturnCode{ReturnCode::Code::OK};
}

