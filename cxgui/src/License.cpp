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

    // Window setup:
        set_title("License");

        std::string iconPath{cxutil::path::currentExecutablePath()};
        iconPath.append("/icons/cxicon16.png");

        set_icon_from_file(iconPath);
        set_position(Gtk::WIN_POS_CENTER);

        // Layouts registration:
        registerLayouts();

        // Widgets registration in layouts:
        registerWidgets();

        // Layout and Widgets look:
        configureLayoutsAndWidgets();

        // Display all widgets:
        show_all();
}


cxgui::dlg::License::~License() = default;


void cxgui::dlg::License::registerLayouts()
{
    add(m_mainLayout);
}


void cxgui::dlg::License::registerWidgets()
{
    m_mainLayout.add(m_scrollArea);
    m_scrollArea.add(m_textArea);
}


void cxgui::dlg::License::configureLayoutsAndWidgets()
{
    populateLicenseFromFile();

    // Link the credits text buffer to its respective text view:
    m_textArea.set_buffer(m_license);

    // Expand to whole window:
    m_scrollArea.set_hexpand(true);
    m_scrollArea.set_vexpand(true);

    // Read only:
    m_textArea.set_editable(false);
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
    // Replace by RAII with every cases handled as soon as possible.

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
