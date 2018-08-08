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
 * @date    July 2018
 * @version 1.0
 *
 * Temporary utilities file (to be refactored once the UI is more stable).
 *
 **************************************************************************************************/

#ifndef UTIL_H_0F15E335_9720_45CB_94A6_40017E47D5A9
#define UTIL_H_0F15E335_9720_45CB_94A6_40017E47D5A9

#include <string>

#include <gdkmm/color.h>
#include <gdkmm/rgba.h>


/***********************************************************************************************//**
 * Produces a string containing the path for the current executable.
 *
 * @param p_pathOnly @true if only the path is needed, @false if the executable name is to be
 *                   included in the string.
 *
 * @return The path where the current executable is located, as a string.
 *
 * @note As of now, only barely supported on Linux (only tested on Ubuntu 16.04), nothing else.
 *       More OS/distros should come in the future, but this is not a priority.
 *
 **************************************************************************************************/
std::string currentExecutablePath(const bool p_pathOnly = true);

namespace cx
{

namespace ui
{

    /*******************************************************************************************//**
     * Builds a string of the form <tt> rgba(r, g, b, a) </tt> where @c r , @c g @c b and @c a
     * represent the four RGBA components for the color. This function is useful to build
     * @c Gdk::RGBA or @c Gdk::Color (deprecated) objects from a @x cxutil::Color type, which
     * does not deal with strings.
     *
     * @param p_localColor The @c cxutil::Color to be converted to a Gdk compatible string.
     *
     * @return The Gdk compatible string representing the color passed as an argument.
     *
     **********************************************************************************************/
     std::string buildGdkColorString(const cxutil::Color& p_localColor);


    /*******************************************************************************************//**
     * Converts a @c Gdk::RGBA object to a cxutil::Color object.
     *
     * @param p_gdkColor The @c Gdk::RGBA object to convert.
     *
     * @return The @c cxutil::Color object represented the Gdk color passed as an argument.
     *
     ***********************************************************************************************/
    cxutil::Color convertToLocalColor(const Gdk::RGBA& p_gdkColor);


    /*******************************************************************************************//**
     * Converts a @c cxutil::Color object to a Gdk::RGBA object.
     *
     * @param p_localColor The @c cxutil::Color object to convert.
     *
     * @return The @c Gdk::RGBA object represented the local color passed as an argument.
     *
     **********************************************************************************************/
    Gdk::RGBA convertToGdkRGBA(const cxutil::Color& p_localColor);


namespace deprecated
{
    /*******************************************************************************************//**
     * Converts a @c Gdk::Color object to a cxutil::Color object.
     *
     * @param p_gdkColor The @c Gdk::Color object to convert.
     *
     * @return The @c cxutil::Color object represented the Gdk color passed as an argument.
     *
     * @deprecated According to the Gdk reference for Color : "When working with cairo,
     *             it is often more convenient to use a @c GdkRGBA instead, and @c GdkColor has
     *             been deprecated in favor of @cGdkRGBA." This function has been added here
     *             because some of the Gtkmm3 functionalities have not yet been ported to
     *             @c Gdk::RGBA (such as the @cGtk::ColorButton for example) and still need
     *             support for @c Gdk::Color.
     *
     ***********************************************************************************************/
    cxutil::Color convertToLocalColor(const Gdk::Color& p_gdkColor);


    /*******************************************************************************************//**
     * Converts a @c cxutil::Color object to a Gdk::Color object.
     *
     * @param p_localColor The @c cxutil::Color object to convert.
     *
     * @return The @c Gdk::Color object represented the local color passed as an argument.
     *
     * @deprecated According to the Gdk reference for Color : "When working with cairo,
     *             it is often more convenient to use a @c GdkRGBA instead, and @c GdkColor has
     *             been deprecated in favor of @cGdkRGBA." This function has been added here
     *             because some of the Gtkmm3 functionalities have not yet been ported to
     *             @c Gdk::RGBA (such as the @cGtk::ColorButton for example) and still need
     *             support for @c Gdk::Color.
     *
     **********************************************************************************************/
    Gdk::Color convertToGdkColor(const cxutil::Color& p_localColor);

} // namespace deprecated

} // namespace ui

} // namespace cx

#endif // UTIL_H_0F15E335_9720_45CB_94A6_40017E47D5A9
