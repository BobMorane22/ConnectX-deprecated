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
 * @date    September 2018
 * @version 1.0
 *
 * Implementation for a generic window.
 *
 **************************************************************************************************/

#include "../include/Window.h"

#include <iostream>

cxgui::dlg::Window::Window()
{
    signal_realize().connect([this]()
                             {
                                 init();
                             });

    add(m_mainLayout);
}


cxgui::dlg::Window::~Window() = default;


/***************************************************************************************************
 * @brief Window initialisation.
 *
 * This method is automatically called when the @c Window::signal_realize is sent by the window,
 * i.e. when every data structure used by the window is constructed and ready for use. It is hence
 * called after construction of the window and is therefore not subject to the constructor
 * restriction to avoid virtual methods. You can call anything you want from here because you
 * have the guarantee the window is fully constructed.
 *
 * @note Many windows and dialogs may depend on this method, so be careful when modifying it.
 *       Run all the tests!
 *
 **************************************************************************************************/
void cxgui::dlg::Window::init()
{
    setWindowIcon();
    configureWindow();
    registerLayouts();
    registerWidgets();
    configureLayouts();
    configureWidgets();
    configureSignalHandlers();
}

