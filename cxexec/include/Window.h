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
 * @file    Window.h
 * @author  Eric Poirier
 * @date    October 2018
 * @version 1.0
 *
 * Interface for an abstract generic Connect X related window.
 *
 **************************************************************************************************/

#ifndef WINDOW_H_BB491835_4AC9_4603_BD41_31A415BEF665
#define WINDOW_H_BB491835_4AC9_4603_BD41_31A415BEF665

#include <cxgui/include/Window.h>

namespace cx
{

namespace ui
{

/***********************************************************************************************//**
 * @class Window
 *
 * @brief Abstract Connect X window.
 *
 * This abstract window is meant to be the base class of every other Connect X related windows and
 * dialogs. It encapsulate the data and behaviours that should be shared among all of them.
 *
 **************************************************************************************************/
class Window : public cxgui::dlg::Window
{

public:

    /*******************************************************************************************//**
     * @brief Default constructor.
     *
     **********************************************************************************************/
    Window();


    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    virtual ~Window();


private:


    virtual void setWindowIcon() final override;

};

} // namespace ui

} // namespace cx

#endif // WINDOW_H_BB491835_4AC9_4603_BD41_31A415BEF665
