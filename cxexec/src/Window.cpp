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
 * @file    Window.cpp
 * @author  Eric Poirier
 * @date    October 2018
 * @version 1.0
 *
 * Implementation for an abstract generic Connect X related window.
 *
 **************************************************************************************************/

#include <cxutil/include/util.h>

#include "../include/Window.h"


cx::ui::Window::Window() = default;


cx::ui::Window::~Window() = default;


/***************************************************************************************************
 * @brief Sets the Connect X icon as the window icon.
 *
 **************************************************************************************************/
void cx::ui::Window::setWindowIcon()
{
    std::string iconPath{cxutil::path::currentExecutablePath()};
    iconPath.append("/icons/cxicon16.png");

    set_icon_from_file(iconPath);
}
