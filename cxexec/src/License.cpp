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
 * Implementation for the Connect X 'license' dialog.
 *
 **************************************************************************************************/

#include <cxutil/include/util.h>

#include "../include/License.h"
#include "../include/util.h"


cx::ui::License::License() : cxgui::dlg::License{cxutil::path::currentExecutablePath()
                                                 + "/ressources/COPYING"}
{
    // Nothing to do...
}


cx::ui::License::~License() = default;


void cx::ui::License::setWindowIcon()
{
    cx::ui::setConnectXWindowIcon(this, cx::ui::IconSize::PIXELS_16);
}


void cx::ui::License::registerLayouts()
{
    // Nothing to do, only the main layout is used.
}


void cx::ui::License::configureLayouts()
{
    // Nothing to do, only the main layout is used.
}
