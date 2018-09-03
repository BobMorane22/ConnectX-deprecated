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
 * @file    Credits.h
 * @author  Eric Poirier
 * @date    September 2018
 * @version 1.0
 *
 * Interface for a simple credits dialog.
 *
 **************************************************************************************************/

#ifndef CREDITS_H_55DEAE3E_5BBF_4645_AA91_BABF69B37B72
#define CREDITS_H_55DEAE3E_5BBF_4645_AA91_BABF69B37B72

#include <map>
#include <string>

#include <gtkmm/grid.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>
#include <gtkmm/window.h>


namespace cxgui
{

namespace dlg
{

enum class CreditedTeam : int
{
    DEVELOPPEMENT,
    DOCUMENTATION,
    ARTWORK,
};


/***********************************************************************************************//**
 *
 **************************************************************************************************/
class Credits : public Gtk::Window
{

public:

    using Name            = std::string;
    using EmailAddress    = std::string;
    using ContributorList = std::map<Name, EmailAddress>;

///@{ @name Object Construction and Destruction

    Credits();
    virtual ~Credits();

    void addCredit(const std::string& p_name, const std::string& p_email, CreditedTeam p_team);

///@}

private:

    void registerLayouts();
    void registerWidgets();
    void configureLayoutsAndWidgets();

///@{ @name Text Area Generation

    void populateListFromFile(const std::string& p_filePath, ContributorList& p_list);
    void formatTextArea();

///@}

///@{ @name Data members

    ContributorList     m_devList;    ///< A list of names and corresponiding email addresses
                                      ///< for the developpers.

    ContributorList     m_docList;    ///< A list of names and corresponiding email addresses
                                      ///< for the documentation writers.

    ContributorList     m_artList;    ///< A list of names and corresponiding email addresses
                                      ///< for the documentation artwork artists.

    Gtk::Grid           m_mainLayout; ///< The dialog's main layout.

    Gtk::ScrolledWindow m_scrollArea; ///< This is the scrolling area around the text.

    Gtk::TextView       m_textArea;   ///< This is the dialog text area, where users read
                                      ///< the credits.

    Glib::RefPtr<Gtk::TextBuffer> m_credits;    ///< The actual formatted credits text.

///@}

};

} // namespace dlg

} // namespace cxgui


#endif // CREDITS_H_55DEAE3E_5BBF_4645_AA91_BABF69B37B72
