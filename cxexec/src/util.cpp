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
 * @file    util.cpp
 * @author  Eric Poirier
 * @date    October 2018
 * @version 1.0
 *
 * Utilities for the cxexec library.
 *
 **************************************************************************************************/

#include <cxutil/include/ContractException.h>

#include "../include/util.h"


void cx::ui::setConnectXWindowIcon(cxgui::dlg::Window* p_parent, const cx::ui::IconSize p_iconSize)
{
    PRECONDITION(p_parent != nullptr);

    using namespace cx::ui;

    std::string iconPath{cxutil::path::currentExecutablePath()};

    switch(p_iconSize)
    {
        case IconSize::PIXELS_16:   iconPath.append("/icons/cxicon16.png");   break;
        case IconSize::PIXELS_32:   iconPath.append("/icons/cxicon32.png");   break;
        case IconSize::PIXELS_64:   iconPath.append("/icons/cxicon64.png");   break;
        case IconSize::PIXELS_128:  iconPath.append("/icons/cxicon128.png");  break;

        default:
            iconPath.append("/icons/cxicon64.png");
            break;
    }

    p_parent->set_icon_from_file(iconPath);
}
