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
 * @file    Credits.cpp
 * @author  Eric Poirier
 * @date    September 2018
 * @version 1.0
 *
 * Implementation for the Connect X 'credits' dialog.
 *
 **************************************************************************************************/

#include <cxutil/include/util.h>

#include "../include/Credits.h"
#include "../include/util.h"


cx::ui::Credits::Credits() : cxgui::dlg::Credits(cxutil::path::currentExecutablePath() + "/ressources/contributors")
{
}


cx::ui::Credits::~Credits() = default;


void cx::ui::Credits::setWindowIcon()
{
    cx::ui::setConnectXWindowIcon(this, cx::ui::IconSize::PIXELS_16);
}


void cx::ui::Credits::registerLayouts()
{
    // Nothing to do here. Only the main layout is needed.
}


void cx::ui::Credits::configureLayouts()
{
    m_mainLayout.set_border_width(15);
}
