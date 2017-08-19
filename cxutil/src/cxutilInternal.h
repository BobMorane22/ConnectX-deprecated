/***************************************************************************************************
 *
 * Copyright (C) 2017 Connect X team
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
 * @file    cxutilInternal.h
 * @author  Eric Poirier
 * @date    July, 2017
 * @version 0.1
 *
 * Deals with internal tools of the cxutil library.
 *
 * This file includes cxutil related global internal tools. For example, namespaces and includes
 * used throughout the entire cxutil codebase should be included here. @attention If a tools can
 * be accessed in a public way, or is cannot be accessed in a public way but is not needed in all 
 * the codebase, it should not be included here.
 *
 **************************************************************************************************/

#include <iostream>

/***********************************************************************************************//**
 * @name Namespaces
 *
 * Frequently used namespaces.
 *
 **************************************************************************************************/
///@{

/***********************************************************************************************//**
 * @namespace std
 *
 * This is the standard library namespace. You can find documentation on this namespace either 
 * in Bjarne Stroustrup's <em>The C++ Programming Language (Fourth Edition)</em> in Part IV or on 
 * the Internet, for example here: http://www.cplusplus.com/reference/.
 *
 **************************************************************************************************/
#define BEGIN_STD_NAMESPACE           namespace std {
#define END_STD_NAMESPACE             } // namespace std
#define USING_NAMESPACE_STD           using namespace std;
#define STD                           std

/***********************************************************************************************//**
 * @namespace cxutil
 *
 * This namespace englobes every cxutil related tools.
 *
 **************************************************************************************************/
#define BEGIN_CXUTIL_NAMESPACE        namespace cxutil {
#define END_CXUTIL_NAMESPACE          } // namespace cxutil
#define USING_NAMESPACE_CXUTIL        using namespace cxutil;
#define CXUTIL                        cxutil
///@}

/***********************************************************************************************//**
 * @def UNUSED_VARIABLE(x)
 *
 * Ensures that the variable @c x is not seen as an unused variable by the compiler.
 *
 * The macro performs a @c void cast on the variable @c _variable_. It is most useful when the
 * compiler has been set to treat warnings as errors. For example, in g++, the <tt > error: 'x'
 * defined but not used [-Werror=unused-variable] </tt> can be silenced using this macro.
 *
 **************************************************************************************************/
#define UNUSED_VARIABLE(_variable_) \
    (void)(_variable_)
