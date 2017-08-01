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
 * @file    Coordinate.h
 * @author  Eric Poirier
 * @date    October 2016
 * @version 0.1
 *
 * Interface for a single Coordinate.
 *
 **************************************************************************************************/

#ifndef COORDINATE_H_DCA364D9_C267_4BAC_9C3F_9FEE7C23F2D7
#define COORDINATE_H_DCA364D9_C267_4BAC_9C3F_9FEE7C23F2D7

#include "../src/cxutilInternal.h"


BEGIN_CXUTIL_NAMESPACE

/***********************************************************************************************//**
 * @class Coordinate
 *
 * Encapsulates a coordinate value.
 *
 * This is a simple encapsulation of a corrdinate value. This tool can be used directly, or serve
 * as a base class for more raffined coordinate types, or to avoid duplication.
 *
 * @tparam  T   A fully comparable type.
 * @note    The value stored is limited to types @c T where the comparison operators are @a all
 *          defined (more precisely, <tt> ==, !=, <, >, <= and >= </tt>).
 *
 **************************************************************************************************/
template <typename T>
class Coordinate
{

public:

///@{ @name Object construction and destruction
    Coordinate()            = delete;
    virtual ~Coordinate()   = default;


    /*******************************************************************************************//**
     * Constructor with parameter.
     *
     * Encapsulates a value.
     *
     * @param[in] p_value   The value to encapsulate in the Coordinate.
     *
     **********************************************************************************************/
    Coordinate(T p_value): m_value{p_value} {};
///@}


///@{ @name Data access
    /*******************************************************************************************//**
     * Gets the encapsulated value.
     *
     * @return The encapsulated value.
     *
     **********************************************************************************************/
    virtual T value() const { return m_value; }
///@}


///@{ @name Operators
    /*******************************************************************************************//**
     * Equal-to operator.
     *
     * The Coordinate objects are compared exactly like the are in the parameter @c T class.
     *
     * @param[in] p_coordinate The Coordinate to compare with.
     *
     **********************************************************************************************/
    virtual bool operator==(const Coordinate& p_coordinate) const    { return  m_value == p_coordinate.m_value; }


    /*******************************************************************************************//**
     * Equal-to operator.
     *
     * The Coordinate objects are compared exactly like the are in the parameter @c T class.
     *
     * @param[in] p_coordinate The Coordinate to compare with.
     *
     **********************************************************************************************/
    virtual bool operator!=(const Coordinate& p_coordinate) const    { return !(m_value == p_coordinate.m_value); }


    /*******************************************************************************************//**
     * Equal-to operator.
     *
     * The Coordinate objects are compared exactly like the are in the parameter @c T class.
     *
     * @param[in] p_coordinate The Coordinate to compare with.
     *
     **********************************************************************************************/
    virtual bool operator<(const Coordinate& p_coordinate) const     { return  m_value < p_coordinate.m_value; }


    /*******************************************************************************************//**
     * Equal-to operator.
     *
     * The Coordinate objects are compared exactly like the are in the parameter @c T class.
     *
     * @param[in] p_coordinate The Coordinate to compare with.
     *
     **********************************************************************************************/
    virtual bool operator<=(const Coordinate& p_coordinate) const    { return (m_value < p_coordinate.m_value)
                                                                           || (m_value == p_coordinate.m_value); }


    /*******************************************************************************************//**
     * Equal-to operator.
     *
     * The Coordinate objects are compared exactly like the are in the parameter @c T class.
     *
     * @param[in] p_coordinate The Coordinate to compare with.
     *
     **********************************************************************************************/
    virtual bool operator>(const Coordinate& p_coordinate) const     { return  m_value > p_coordinate.m_value; }


    /*******************************************************************************************//**
     * Equal-to operator.
     *
     * The Coordinate objects are compared exactly like the are in the parameter @c T class.
     *
     * @param[in] p_coordinate The Coordinate to compare with.
     *
     **********************************************************************************************/
    virtual bool operator>=(const Coordinate& p_coordinate) const    { return (m_value > p_coordinate.m_value)
                                                                           || (m_value == p_coordinate.m_value); }
///@}


protected:

    T m_value;   ///< The coordinate value.

};

END_CXUTIL_NAMESPACE

#endif // COORDINATE_H_DCA364D9_C267_4BAC_9C3F_9FEE7C23F2D7
