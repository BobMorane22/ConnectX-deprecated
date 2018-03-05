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
 * @file    RAIICairoPath.h
 * @author  Eric Poirier
 * @date    March 2018
 * @version 1.0
 *
 * Interface for an RAII handler of cairo paths.
 *
 **************************************************************************************************/

#ifndef RAIICAIROPATH_H_C422C72E_5D58_446F_ABE5_FF730DC2E5A6
#define RAIICAIROPATH_H_C422C72E_5D58_446F_ABE5_FF730DC2E5A6

#include <cairomm/path.h>

namespace cxgui
{

/***********************************************************************************************//**
 * @brief RAII handler class for cairo paths.
 *
 * The official cairomm documentation (see cairomm/path.h) says that: " The application is
 * responsible for freeing the Path object when it is no longer needed. ". This RAII handler
 * makes sure that happens.
 *
 **************************************************************************************************/
class RAIICairoPath
{

public:

    RAIICairoPath() = delete;


    /*******************************************************************************************//**
     * @brief C++-handle constructor (Cairomm).
     *
     * @param[in] p_pathHandle C++ Cairo path handle.
     *
     * @pre The handle is defined (i.e. not nullptr)
     *
     **********************************************************************************************/
    RAIICairoPath(Cairo::Path* p_pathHandle);


    /*******************************************************************************************//**
     * @brief C-handle constructor (Cairo).
     *
     * @param[in] p_pathHandle C Cairo path handle.
     *
     * @pre The handle is defined (i.e. not NULL or nullptr)
     *
     **********************************************************************************************/
    RAIICairoPath(cairo_path_t* p_pathHandle);


    /*******************************************************************************************//**
     * @brief Releases the handle.
     *
     * See https://www.cairographics.org/manual/cairo-Paths.html for more information.
     *
     **********************************************************************************************/
    ~RAIICairoPath();


    /*******************************************************************************************//**
     * @brief Class member access operator.
     *
     * @return The path handle address.
     *
     **********************************************************************************************/
    cairo_path_t* operator->();


    /*******************************************************************************************//**
     * @brief Boolean conversion operator
     *
     * @return @c true if the handle is valid, @c false otherwise.
     *
     **********************************************************************************************/
    operator bool() const;


private:

    cairo_path_t* m_pathHandle; ///< The cairo path handle.

};

} // namespace cxgui

#endif // RAIICAIROPATH_H_C422C72E_5D58_446F_ABE5_FF730DC2E5A6

