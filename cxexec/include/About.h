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
 * @file    About.h
 * @author  Eric Poirier
 * @date    August 2018
 * @version 1.0
 *
 * Interface for the Connect X 'about' dialog.
 *
 **************************************************************************************************/

#ifndef ABOUT_H_6347564A_EF2C_4AA0_AB0B_8C3B9DD9F6F0
#define ABOUT_H_6347564A_EF2C_4AA0_AB0B_8C3B9DD9F6F0

#include <cxgui/include/About.h>


namespace cx
{

namespace ui
{

/***********************************************************************************************//**
 * @class About
 *
 *
 *
 **************************************************************************************************/
class About final : public cxgui::dlg::About
{

public:

    /*******************************************************************************************//**
     * Default constructor.
     *
     **********************************************************************************************/
    About();


    /*******************************************************************************************//**
     * Default destructor.
     *
     **********************************************************************************************/
    ~About();
};

} // namespace ui

} // namespace cx

#endif // ABOUT_H_6347564A_EF2C_4AA0_AB0B_8C3B9DD9F6F0
