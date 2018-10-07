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
 * @file    util.h
 * @author  Eric Poirier
 * @date    October 2018
 * @version 1.0
 *
 * Utilities for the cxexec library.
 *
 **************************************************************************************************/

#ifndef UTIL_H_AFF27968_0C9E_4E11_879E_35696052D2C8
#define UTIL_H_AFF27968_0C9E_4E11_879E_35696052D2C8

#include <cxutil/include/util.h>
#include <cxgui/include/Window.h>


namespace cx
{

namespace ui
{

/***********************************************************************************************//**
 * @enum IconSize
 *
 * @brief Connect X icon source image sizes.
 *
 **************************************************************************************************/
enum class IconSize
{
    PIXELS_16, ///< Use a 16 pixels source image.
    PIXELS_32, ///< Use a 32 pixels source image.
    PIXELS_64, ///< Use a 64 pixels source image.
    PIXELS_128,///< Use a 128 pixels source image.
    UNDEFINED  ///< Use whatever default size there is.
};


/***********************************************************************************************//**
 * @brief Set the Connect X window icon.
 *
 * Sets the Connect X window icon for a parent window.
 *
 * @param p_parent   The address of the parent window.
 * @param p_iconSize The wanted icon size. This does not affect the size of the onscreen
 *                   image. It only affects the quality of the source image file.
 *
 * @pre The parent window is valid.
 *
 **************************************************************************************************/
void setConnectXWindowIcon(cxgui::dlg::Window* p_parent, const IconSize p_iconSize);

} // namespace ui

} // namespace cx

#endif // UTIL_H_AFF27968_0C9E_4E11_879E_35696052D2C8

