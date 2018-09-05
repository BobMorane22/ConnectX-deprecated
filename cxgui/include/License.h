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
 * @file    License.h
 * @author  Eric Poirier
 * @date    September 2018
 * @version 1.0
 *
 * Interface for a simple 'license' dialog.
 *
 **************************************************************************************************/

#ifndef LICENSE_H_433175C8_7E27_4F67_8C70_4CF93A6BD1E3
#define LICENSE_H_433175C8_7E27_4F67_8C70_4CF93A6BD1E3

#include <gtkmm/grid.h>
#include <gtkmm/textview.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/window.h>


namespace cxgui
{

namespace dlg
{

/***********************************************************************************************//**
 * @class License
 *
 * @brief A simple 'license' dialog.
 *
 * Shows a liscense in plain text format in a dialog. No text formatting is possible. The license
 * text is read into the dialog from a file containing the license text at construction.
 *
 * @invariant The license file path is a valid file path on the system.
 *
 **************************************************************************************************/
class License : public Gtk::Window
{

public:

///@{ @name Object construction and destruction

    /*******************************************************************************************//**
     * @brief Constructor.
     *
     * The file text is fed to the dialog which will then display is without attempting any
     * formatting to the text. It will look just like the text file in a text editor.
     *
     * @param p_licenseFilePath A path to the license file.
     *
     * @pre @c p_licenseFilePath is a valid file path on the system.
     *
     ***********************************************************************************************/
    License(const std::string& p_licenseFilePath);


    /*********************************************************************************************//**
     * @brief Default destructor.
     *
     ************************************************************************************************/
    virtual ~License();

///@}

private:

    void registerLayouts();
    void registerWidgets();
    void configureLayoutsAndWidgets();

///@{ @name Text area generation

    void populateLicenseFromFile();

///@}

///@{ @name Data members

    Gtk::Grid                     m_mainLayout;       ///< The dialog's main layout.
    Gtk::TextView                 m_textArea;         ///< The text area displaying the license.
    Gtk::ScrolledWindow           m_scrollArea;       ///< The scrolling area.
    Glib::RefPtr<Gtk::TextBuffer> m_license;          ///< The buffer containing the license text.
    const std::string             m_licenseFilePath;  ///< The license file path.

///@}

};

} // namespace dlg

} // namespace cxgui



#endif // LICENSE_H_433175C8_7E27_4F67_8C70_4CF93A6BD1E3
