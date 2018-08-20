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
 * @brief Various general purpose utilities.
 *
 * These utilities are broken down into different categories, each with its own sub-namespace
 * to enable searching. Refer to the documentation to know more about each namespace. Most of
 * the time, these utilities are free functions, to better testability and enhance encapsulation.
 *
 **************************************************************************************************/

#ifndef UTIL_H_E3BBA82A_4FD4_454C_9525_F45B6370A29D
#define UTIL_H_E3BBA82A_4FD4_454C_9525_F45B6370A29D

// path
#include <string>


namespace cxutil
{

/***********************************************************************************************//**
 * @namespace path
 *
 * @brief Path utilities.
 *
 * These utilities are helpful when dealing with paths. Most of them are system specific, so
 * read the documentation before using!
 *
 **************************************************************************************************/
namespace path
{

/***********************************************************************************************//**
 * Produces a string containing the path for the current executable.
 *
 * @param p_pathOnly @c true if only the path is needed, @c false if the executable name is to be
 *                   included in the string.
 *
 * @return The path where the current executable is located, as a string.
 *
 * @note As of now, only barely supported on Linux (only tested on Ubuntu 16.04), nothing else.
 *       More OS/distros should come in the future, but this is not a priority.
 *
 **************************************************************************************************/
std::string currentExecutablePath(const bool p_pathOnly = true);

} // namespace path

} // namespace cxutil

#endif // UTIL_H_E3BBA82A_4FD4_454C_9525_F45B6370A29D
