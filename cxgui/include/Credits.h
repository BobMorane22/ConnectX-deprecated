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

/***********************************************************************************************//**
 * @enum CreditedTeam
 *
 * @brief Lists all teams which appear in the dialog.
 *
 * If a team is not in this enumeration, it cannot be displayed in the dialog.
 *
 **************************************************************************************************/
enum class CreditedTeam : unsigned int
{
    DEVELOPPEMENT  = 1             ,  ///< Developpement team.
    DOCUMENTATION                  ,  ///< Documentation team.
    ARTWORK                        ,  ///< Artwork team.
    FIRST          = DEVELOPPEMENT ,  ///< Value for first group in the enum.
    LAST           = ARTWORK          ///< Value for last group in the enum.
};


/***********************************************************************************************//**
 * @class Credits
 *
 * @brief A simple 'credits' dialog.
 *
 * This dialog lists names/email pairs for credited contributors, sorted by teams. A contributor
 * can appear in more than one team, but not twice in a same team.
 *
 * There are two ways of feeding the credited members lists to the dialog: by giving it a file or
 * by giving it a harcoded collection of lists. Both these take place at construction and cannot
 * be modified dynamically.
 *
 * The syntax for <em>a line</em> in the file is as follow:
 *
 * @verbatim
 *
 *   team, full name, email
 *
 * @endverbatim
 *
 * where:
 *
 *   -# <tt>team</tt> is the credited team the contributor contributed to. Note that its
 *      spelling must match (even the case) the spellint in the CreditedTeam enum,
 *      otherwise parsing will fail. Options are: @c DEVELOPPEMENT, @c DOCUMENTATION and
 *      @c ARTWORK .
 *
 *   -# <tt>full name</tt> is the full name (first and last name, in that order).
 *
 *   -# <tt>email</tt> is the contributor's email address. Note that this address must contain
 *      the '@' character to be valid. It will appear as clickabel to the user who would like
 *      to reach a contributor, so make sure it is correct.
 *
 * Note that only one such line should appear on the same line in the file, otherwise parsing
 * will fail. Furthermore, blank lines and lines starting with '#' are ignored.
 *
 * @invariant Every list contains only non empty names.
 * @invariant Every list contains valid email addresses.
 * @invariant At least one contributor is listed (otherwise the dialog does not make sense).
 * @invariant If @c m_creditsFilePath is empty, the @c m_fromFile bolean is set to @c false,
 *            otherwise it is not empty.
 * @invariant @c m_creditsFilePath is a valid path on the system.
 *
 **************************************************************************************************/
class Credits : public Gtk::Window
{

public:

///@{ @name Convenience typedefs

    using Name            = std::string;                  ///< The contributor's name.
    using EmailAddress    = std::string;                  ///< The contributor's email address.
    using ContributorList = std::map<Name, EmailAddress>; ///< A list of contributors.

///@}

///@{ @name Object Construction and Destruction

    Credits() = delete;

    /*******************************************************************************************//**
     * @brief Constructor taking a collection of hardcoded lists.
     *
     * To use this constructor, all lists must have previously been harcoded into the program. This
     * is not the preferred way of instanciation this dialog because for every new contributor that
     * is added, a recompilation of the program is needed.
     *
     * @param p_contributorLists A list (a map, to be more precise) of all contributor lists.
     *
     * @pre @c p_contributorLists contains at least one element.
     * @pre @c p_contributorLists contains at most as many lists as there are credited teams.
     *
     **********************************************************************************************/
    Credits(const std::map<CreditedTeam, ContributorList>& p_contributorLists);


    /*******************************************************************************************//**
     * @brief Constructor taking a file path as an argument.
     *
     * The contributor lists are fed to the dialog via a file in which all the information is
     * listed, for every contributor. See the class' description for more information on the
     * syntax the file must follow in order to be adequatly parsed.
     *
     * @param p_creditsFilePath The path to the file containing the credits information, properly
     *                          formatted.
     *
     * @pre @c p_contributorLists is a valid path on the system.
     *
     **********************************************************************************************/
    Credits(const std::string& p_creditsFilePath);


    /*******************************************************************************************//**
     * Default destructor.
     *
     **********************************************************************************************/
    virtual ~Credits();

///@}

private:

    void registerLayouts();
    void registerWidgets();
    void configureLayoutsAndWidgets();

///@{ @name Text Area Generation

    void populateListFromFile();
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

    Glib::RefPtr<Gtk::TextBuffer> m_credits;         ///< The actual formatted credits text.

    const std::string             m_creditsFilePath; ///< A path to a file containing the credits
                                                     ///< information.

    const bool                    m_fromFile;        ///< Keeps track of the dialog's construction
                                                     ///< information. @c true if the dialog was
                                                     ///< constructed from a file, @c false
                                                     ///< otherwise.

///@}

};

} // namespace dlg

} // namespace cxgui


#endif // CREDITS_H_55DEAE3E_5BBF_4645_AA91_BABF69B37B72
