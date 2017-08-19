/***************************************************************************************************
 *
 * Copyright (C) 2016 Connect X team
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
 * @file    cxbaseInternal.h
 * @author  Eric Poirier
 * @date    November 2016
 * @version 0.1
 *
 * Deals with internal tools of the cXbase library.
 *
 * This file includes Connect X related global internal tools. For example, namespaces and includes
 * used throughout the entire Connect X codebase should be included here. @attention If a tools can
 * be accessed in a public way, or is cannot be acced in a public way but is not needed in all the
 * codebase, it should not be included here.
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
 * This is the standard library namespace.
 *
 **************************************************************************************************/
#define BEGIN_STD_NAMESPACE           namespace std {
#define END_STD_NAMESPACE             } // namespace std
#define USING_NAMESPACE_STD           using namespace std;
#define STD                           std

/***********************************************************************************************//**
 * @namespace cXbase
 *
 * This namespace englobes every Connect X related tools.
 *
 **************************************************************************************************/
#define BEGIN_CXBASE_NAMESPACE        namespace cXbase {
#define END_CXBASE_NAMESPACE          } // namespace cXbase
#define USING_NAMESPACE_CXBASE        using namespace cXbase;
#define CXBASE                        cXbase
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
