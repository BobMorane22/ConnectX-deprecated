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
 * @date    September 2018
 * @version 1.0
 *
 * Interface for a generic window.
 *
 **************************************************************************************************/

#ifndef WINDOW_H_0A630348_EB2E_40A6_A426_68F2DF750663
#define WINDOW_H_0A630348_EB2E_40A6_A426_68F2DF750663

#include <gtkmm/grid.h>
#include <gtkmm/window.h>

namespace cxgui
{

namespace dlg
{

/***********************************************************************************************//**
 * @class Window
 *
 * @brief Abstract window base class.
 *
 * Derive from this class to make a window. It offers a variety of goodies, one being that
 * you can easily configure your window after it has been realized. This helps clean up the
 * construction/destruction process and enforces uniformity. If you decide to use this base
 * class, you will (minimally) need to do the following:
 *
 *   -# Inherit from it.
 *
 *   -# Define all the layouts and widgets you need.
 *
 *   -# Override every virtual methods to your needs.
 *
 * The rest should be done automatically by the framework.
 *
 **************************************************************************************************/
class Window : public Gtk::Window
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


protected:

    Gtk::Grid m_mainLayout; ///< The window's main layout. This is where every other widget/
                            ///< layout is embedded to make up the window.


private:

    /*******************************************************************************************//**
     * @brief Sets an icon for the window.
     *
     * Override this method to specify a path for the window icon.
     *
     **********************************************************************************************/
    virtual void setWindowIcon() = 0;


    /*******************************************************************************************//**
     * @brief Configures the window.
     *
     * Override this method to configure window properties.
     *
     **********************************************************************************************/
    virtual void configureWindow() = 0;


    /*******************************************************************************************//**
     * @brief Structures the layouts.
     *
     * Override this method to structure your layouts. For example, if you have a sublayout, add
     * it (register it) to the main layout here so that it is know to the window.
     *
     **********************************************************************************************/
    virtual void registerLayouts() = 0;


    /*******************************************************************************************//**
     * @brief Structure the widgets.
     *
     * Override this method to structure your widgets. Add them to the layouts they belong to so
     * that they appear as you intended (layout-wise) on the screen.
     *
     **********************************************************************************************/
    virtual void registerWidgets() = 0;


    /*******************************************************************************************//**
     * @brief Configure the layouts' attributes.
     *
     * Override this method to have control on layouts' attributes. If you need to set anything
     * else than a 'Layout A contains layout B' dependence, this is where it happens.
     *
     **********************************************************************************************/
    virtual void configureLayouts() = 0;


    /*******************************************************************************************//**
     * @brief Configure widgets' attributes.
     *
     * Override this method to have control on the widgets' attributes. If you need to set anything
     * else than a 'Widget A belongs to layout B' dependence, this is where it happens.
     *
     **********************************************************************************************/
    virtual void configureWidgets() = 0;


    void init();

};

} // namespace dlg

} // namespace cxgui

#endif // WINDOW_H_0A630348_EB2E_40A6_A426_68F2DF750663
