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
 * Interface for an RAII handler of cairomm paths.
 *
 **************************************************************************************************/

#ifndef RAIICAIROPATH_H_C422C72E_5D58_446F_ABE5_FF730DC2E5A6
#define RAIICAIROPATH_H_C422C72E_5D58_446F_ABE5_FF730DC2E5A6

#include <cairomm/path.h>

#include <cxutil/include/UnCopyable.h>

namespace cxgui
{

/***********************************************************************************************//**
 * @brief RAII handler class for cairomm paths.
 *
 * The official cairomm documentation (see cairomm/path.h) says that: "The application is
 * responsible for freeing the Path object when it is no longer needed.". This RAII handler
 * makes sure that happens. Note that by 'freeing', the documentation implies using @c delete
 * and not the @c cairo_path_destroy C routine. This C routine is invoked in the Cairo:Path
 * destructor, and we do not need to worry about it here.
 *
 * Why not use a smart pointer? Because the documentation also mentions that "there's currently no
 * way to access the path data without reverting to he C object (see @c cobj())." This RAII
 * gives access to the path data in a natural way, i.e. without explicitly reverting to the
 * C object. See @ operator-> for more information.
 *
 **************************************************************************************************/
class RAIICairoPath : private cxutil::UnCopyable
{

public:

    RAIICairoPath() = delete;


    /*******************************************************************************************//**
     * @brief Constructor.
     *
     * @param[in] p_pathHandle Cairomm path handle.
     *
     * @pre The handle is defined (i.e. not nullptr)
     *
     **********************************************************************************************/
    RAIICairoPath(Cairo::Path* p_pathHandle);


    /*******************************************************************************************//**
     * @brief Releases the handle.
     *
     **********************************************************************************************/
    ~RAIICairoPath();


    /*******************************************************************************************//**
     * @brief Class member access operator.
     *
     * Use this operator to work on a RAIICairoPath object like you would on a @c cairo_path_t*
     * pointer.For example:
     *
     * @code
     *
     *     RAIICairoPath pathRAII{context->copy_path()};
     *     CX_ASSERT_MSG(pathRAII, "Invalid path address.");
     *
     *     std::cout << pathRAII->num_data << std::endl;
     *
     * @endcode
     *
     * is equivalent to:
     *
     * @code
     *
     *     Cairo::Path* path{context->copy_path()};
     *     CX_ASSERT_MSG(path, "Invalid path address.");
     *
     *     std::cout << path->cobj()->num_data << std::endl; // cobj(): gets the C handle.
     *
     *     delete(path);
     *
     * @endcode
     *
     * @return The path C-handle address.
     *
     **********************************************************************************************/
    cairo_path_t* operator->();


    /*******************************************************************************************//**
     * @brief Boolean conversion operator.
     *
     * @return @c true if the handle is valid, @c false otherwise.
     *
     **********************************************************************************************/
    operator bool() const;


private:

    Cairo::Path* m_pathHandle; ///< The cairo path handle.

};

} // namespace cxgui

#endif // RAIICAIROPATH_H_C422C72E_5D58_446F_ABE5_FF730DC2E5A6

