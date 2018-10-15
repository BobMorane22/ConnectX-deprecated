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
 * Implementation for the Connect X help dialog.
 *
 **************************************************************************************************/

#include <cstdio>
#include <iostream>
#include <sstream>

#include <cxgui/include/util.h>

#include "../include/Help.h"


namespace
{

std::string buildHelpMessage()
{
    std::ostringstream os;

    os << cxgui::addBoldMarkupTags("Do you want to read the manual online?")
       << std::endl
       << std::endl
       << "You will be redirected to the documentation web page where help pages are "
       << "maintained for every release."
       << std::endl;

    return os.str();
}

} // unamed namespace


cx::ui::Help::Help() : cxgui::dlg::Help(buildHelpMessage())
{
}


cx::ui::Help::~Help() = default;


void cx::ui::Help::setWindowIcon()
{
    cx::ui::setConnectXWindowIcon(this, IconSize::PIXELS_16);
}


void cx::ui::Help::registerLayouts()
{
    // Nothing to do, only main layout is needed.
}


void cx::ui::Help::configureSignalHandlers()
{
    // Important to call the base class signal to reuse their handlers:
    cxgui::dlg::Help::configureSignalHandlers();

    m_readOnline.signal_clicked().connect([this](){onConsultOnlineHelp();});
}


/***************************************************************************************************
 * @brief Handler for the 'Read online' button.
 *
 * Redirects to the Connect X documentation online page. It fires up the default web browser,
 * redirects to the documentation page and closes the window.
 *
 **************************************************************************************************/
void cx::ui::Help::onConsultOnlineHelp()
{
    // Open online page in web browser:
    const std::string browser             {"xdg-open http:"                 };
    const std::string documentationAddress{"github.com/BobMorane22/ConnectX"};
    const std::string sysCommand          {browser + documentationAddress   };
    system(sysCommand.c_str());

    // Close the help window:
    close();
}
