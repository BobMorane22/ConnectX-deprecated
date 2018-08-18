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
 * @file    Help.h
 * @author  Eric Poirier
 * @date    August 2018
 * @version 1.0
 *
 * Interface for a simple help dialog.
 *
 **************************************************************************************************/

#ifndef HELP_H_F4CF8CAB_6B79_4DFF_9AD1_5946B5DB5BE8
#define HELP_H_F4CF8CAB_6B79_4DFF_9AD1_5946B5DB5BE8

#include <string>

#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>


namespace cxgui
{

namespace dlg
{

/***********************************************************************************************//**
 * @class Help
 *
 * This class represents a simple help dialog presented to the user when he or she requests help.
 * It leaves two choices to the user:
 *
 * <ul>
 *   <li> open the online manual for help (no help is available locally); </li>
 *   <li> cancel the request and go back to the application. </li>
 * </ul>
 *
 * @invariant The help message is a non empty string.
 *
 **************************************************************************************************/
class Help : public Gtk::Window
{

public:

    /*******************************************************************************************//**
     * Constructor.
     *
     * @param p_visibleMsg The message to present to the user in the dialog. Note that markup
     *                     is activated for this message, so you can format it any way you want.
     *
     * @pre @c p_visibleMsg is a non empty string.
     *
     **********************************************************************************************/
    Help(const std::string& p_visibleMsg);


    /*******************************************************************************************//**
     * Default destructor.
     *
     **********************************************************************************************/
    virtual ~Help();


private:

    void checkInvariant() const;

    void registerLayouts();
    void registerWidgets();
    void configureLayoutsAndWidgets();


    Gtk::Label  m_visibleMsg;  ///< The message to be presented to the user.

    Gtk::Grid   m_layout;      ///< The window layout container.

    Gtk::Button m_readOnline;  ///< Button to consult the online documentation.
    Gtk::Button m_cancel;      ///< Button to cancel the help request and close the dialog.
};

} // namespace dlg

} // namespace cxgui

#endif // HELP_H_F4CF8CAB_6B79_4DFF_9AD1_5946B5DB5BE8

