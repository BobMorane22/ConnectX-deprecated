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
 * @file    Help.cpp
 * @author  Eric Poirier
 * @date    August 2018
 * @version 1.0
 *
 * Implementation for a simple help dialog.
 *
 **************************************************************************************************/

#include <cxutil/include/ContractException.h>
#include <cxutil/include/util.h>

#include "../include/Help.h"


cxgui::dlg::Help::Help(const std::string& p_visibleMsg)
{
    PRECONDITION(!p_visibleMsg.empty());

    // Setup the help message:
    m_visibleMsg.set_text(p_visibleMsg);
}


cxgui::dlg::Help::~Help() = default;


void cxgui::dlg::Help::configureWindow()
{
    set_title("Help");

    set_position(Gtk::WIN_POS_CENTER);
    set_border_width(15);
}


void cxgui::dlg::Help::registerWidgets()
{
    m_mainLayout.attach(m_visibleMsg, 0, 0, 2, 1);
    m_mainLayout.attach(m_cancel,     0, 1, 1, 1);
    m_mainLayout.attach(m_readOnline, 1, 1, 1, 1);
}


void cxgui::dlg::Help::configureLayouts()
{
    // This makes sure both buttons are of equal width:
    m_mainLayout.set_column_homogeneous(true);
}


void cxgui::dlg::Help::configureWidgets()
{
    m_visibleMsg.set_use_markup(true);
    m_cancel.set_label("Cancel");
    m_readOnline.set_label("Read online");

    // For some reason, the window is too tall. We shrink it vertically
    // to match the container:
    const int width {get_width()              };
    const int height{m_mainLayout.get_height()};

    // First make a size request:
    set_size_request(width, height);

    // Then resize accordinly:
    resize(width, height);

    show_all_children();
}


void cxgui::dlg::Help::configureSignalHandlers()
{
    m_cancel.signal_clicked().connect([this](){onCancel();});

    INVARIANTS();
}


/***************************************************************************************************
 * @brief Handler for the 'Cancel' button.
 *
 * Cancels the help request and closes the help window.
 *
 **************************************************************************************************/
void cxgui::dlg::Help::onCancel()
{
    close();
}


void cxgui::dlg::Help::checkInvariant() const
{
    INVARIANT(!m_visibleMsg.get_text().empty());
}
