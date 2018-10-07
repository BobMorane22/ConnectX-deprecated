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
 * @file    About.h
 * @author  Eric Poirier
 * @date    August 2018
 * @version 1.0
 *
 * Interface for a simple 'about' dialog.
 *
 **************************************************************************************************/

#ifndef ABOUT_H_0AEBC545_3DCA_4109_8D54_CC1C623407DF
#define ABOUT_H_0AEBC545_3DCA_4109_8D54_CC1C623407DF

#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>

#include <cxutil/include/Date.h>

#include "Window.h"


namespace cxgui
{

/***********************************************************************************************//**
 * Regroups basic informations about the application copyright. These are:
 *
 * -# The full name of the copyright owner.
 * -# The date of the first day the copyright was valid.
 * -# The date of the last day the copyright was valid.
 *
 **************************************************************************************************/
struct CopyrightInformation
{
    std::string  m_copyrightOwner;
    cxutil::Date m_copyrightStart;
    cxutil::Date m_copyrightEnd  ;
};


/***********************************************************************************************//**
 * Regroups public information about the application. These are:
 *
 * -# A path to the application's artwork image file.
 * -# The application name.
 * -# The application version number. This number has to be formatted as a string. This is due
 *    to the fact that many numbering systems are used for different applications.
 * -# A short description of the application.
 *
 **************************************************************************************************/
struct ApplicationInformation
{
    std::string m_pathToArtwork;
    std::string m_name         ;
    std::string m_version      ;
    std::string m_description  ;
};


namespace dlg
{

/***********************************************************************************************//**
 * @class About
 *
 * @brief A simple 'about' dialog.
 *
 * Represents a simple 'about' dialog. These dialogs are helpful to provide information about the
 * software and the development team to the interested user. Mainly, it has three major sections:
 *
 *   - Basic information: this is presented in the main dialog window. It covers topics
 *                        such as the software name, version, copyright information and
 *                        so on.
 *
 *   - Credits: accessible through a button, the user can see the software credits in
 *              another window.
 *
 *   - License: accessible through a button, the user can read the software license in
 *              another window.
 *
 * @invariant All the application information is present (no empty strings).
 *
 **************************************************************************************************/
class About : public cxgui::dlg::Window
{

public:

    /*******************************************************************************************//**
     * Constructor.
     *
     * @param p_appInfo     The basic application information. All fields are required.
     * @param p_cpInfo      The basic copyright information. Don't bother finding the exact days
     *                      for the copyright start/end dates, only the years are displayed.
     *
     * @pre All the application information is present (no empty strings), except for the artwork
     *      file path, which can be empty.
     * @pre The copyright start year is at most the same as the copyright current/end year.
     * @pre The copyright has an owner (no empty strings).
     *
     * @note An empty artwork file path means that no artwork is supplied by the caller, and hence no
     *       artwork will be visible.
     *
     * @see cxgui::ApplicationInformation
     * @see cxgui::CopyrightInformation
     *
     **********************************************************************************************/
    About(const ApplicationInformation& p_appInfo,
          const CopyrightInformation& p_cpInfo
          );


    /*******************************************************************************************//**
     * Default destructor.
     *
     **********************************************************************************************/
    virtual ~About();


private:

    void checkInvariant() const;

///@{ @name Window setup

    virtual void setWindowIcon()    = 0;
    virtual void configureWindow()  override;
    virtual void registerLayouts()  = 0;
    virtual void registerWidgets()  override;
    virtual void configureLayouts() = 0;
    virtual void configureWidgets() override;

///@}

///@{ @name Data members

    Gtk::Image  m_artwork;              ///< The artwork for the application.

    Gtk::Label  m_softwareName;         ///< The application name.

    Gtk::Label  m_softwareDescription;  ///< A short application description (100 characters max).

    Gtk::Label  m_copyrightInformation; ///< The copyright information as 'Copyright (c) AAAA-BBBB Owner'
                                        ///< or 'Copyright (c) AAAA Owner' if the copyright start
                                        ///< year is the same as the end year.

    Gtk::Button m_credits;              ///< A button to launch the 'credits' dialog.

    Gtk::Button m_license;              ///< A button to launch the 'license' dialog.

    Gtk::Button m_close;                ///< A button to close the dialog.

///@}

};

} // namespace dlg

} // namespace cxgui

#endif // ABOUT_H_0AEBC545_3DCA_4109_8D54_CC1C623407DF

