/***********************************************************************************************//**
 * @file    Coordinate.h
 * @author  Eric Poirier
 * @date    October 2016
 * @version 0.1
 *
 * Interface for a single Coordinate.
 *
 **************************************************************************************************/

#ifndef COORDINATE_H_
#define COORDINATE_H_

#include "cXbaseInternal.h"


BEGIN_CXBASE_NAMESPACE

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

END_CXBASE_NAMESPACE

#endif // COORDINATE_H_
