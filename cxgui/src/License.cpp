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
 * @file    License.cpp
 * @author  Eric Poirier
 * @date    September 2018
 * @version 1.0
 *
 * Implementation for a simple 'license' dialog.
 *
 **************************************************************************************************/

#include <fstream>

#include <cxutil/include/Assertion.h>
#include <cxutil/include/ContractException.h>
#include <cxutil/include/util.h>

#include "../include/License.h"


cxgui::dlg::License::License(const std::string& p_licenseFilePath)
 : m_licenseFilePath{p_licenseFilePath}
{
    PRECONDITION(!p_licenseFilePath.empty());
}


cxgui::dlg::License::~License() = default;


void cxgui::dlg::License::configureWindow()
{
    set_title("License");
    set_position(Gtk::WIN_POS_CENTER);

    // We get the screen information to calculate good dimensions
    // for the dialog. Sadly, by default, almost no information is
    // displayed because of the scrolling area:
    Glib::RefPtr<Gdk::Screen> screen{Gdk::Screen::get_default()};
    CX_ASSERT(screen);

    const int nbOfMonitors{screen->get_n_monitors()          };
    const int width       {screen->get_width() / nbOfMonitors};
    const int height      {screen->get_height()              };

    set_size_request(width/4, height/2);
}


void cxgui::dlg::License::registerWidgets()
{
    m_mainLayout.add(m_scrollArea);
    m_scrollArea.add(m_textArea);
}


void cxgui::dlg::License::configureWidgets()
{
    populateLicenseFromFile();

    // Link the credits text buffer to its respective text view:
    m_textArea.set_buffer(m_license);

    // Expand to whole window:
    m_scrollArea.set_hexpand(true);
    m_scrollArea.set_vexpand(true);

    // Read only:
    m_textArea.set_editable(false);

    show_all();

    INVARIANTS();
}


/***********************************************************************************************//**
 * @brief Reads the content of the license file into the dialog.
 *
 * Tranfers the text content of the license file to the text buffer. No attempt at formatting
 * the text is done. It is read into the buffer as is.
 *
 **************************************************************************************************/
void cxgui::dlg::License::populateLicenseFromFile()
{
    // Create a Textbuffer with the TagTable:
    m_license = Gtk::TextBuffer::create();
    m_textArea.set_buffer(m_license);

    std::ifstream in{m_licenseFilePath, std::ifstream::in};

    CX_ASSERT(in.is_open());

    std::stringstream sstr;
    sstr << in.rdbuf();

    m_license->set_text(sstr.str());

    in.close();
}


void cxgui::dlg::License::checkInvariant() const
{
    INVARIANT(!m_licenseFilePath.empty());
}
