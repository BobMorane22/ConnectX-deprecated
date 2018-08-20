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
 * @file    About.cpp
 * @author  Eric Poirier
 * @date    August 2018
 * @version 1.0
 *
 * Implementation for the Connect X 'about' dialog.
 *
 **************************************************************************************************/

#include <cxutil/include/Date.h>
#include <cxexec/include/util.h>

#include "../include/About.h"


namespace
{

const cxgui::ApplicationInformation APPLICATION_INFORMATION
{
    currentExecutablePath() + "/icons/cxicon64.png",
    "Connect X",
    "1.0",
    "A scalable connect 4 game."
};

const cxgui::CopyrightInformation COPYRIGHT_INFORMATION
{
    "Eric Poirier",
    cxutil::Date{2016, 1, 1},
    cxutil::Date()
};

} // unamed namespace


cx::ui::About::About() : cxgui::dlg::About(APPLICATION_INFORMATION, COPYRIGHT_INFORMATION)
{
}


cx::ui::About::~About() = default;
