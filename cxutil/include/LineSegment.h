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
 * @file    LineSegment.h
 * @author  Eric Poirier
 * @date    August 2018
 * @version 1.0
 *
 * Interface for a the @c LineSegment class template.
 *
 **************************************************************************************************/

#ifndef LINESEGMENT_H_211CAF0D_19F6_4B9B_A0FC_690207C49414
#define LINESEGMENT_H_211CAF0D_19F6_4B9B_A0FC_690207C49414

#include "ContractException.h"
#include "Point.h"

namespace cxutil
{

namespace math
{

/***********************************************************************************************//**
 * @class LineSegment
 *
 * @brief A class template representing line segments.
 *
 * Represents a line segment (not a full line), that is, a set of all point in the euclidian
 * space that lie on the straight line between an origin point and a destination point. It
 * is almost the same concept as the vector, but with no direction. Only the magnitude is
 * considered.
 *
 * @tparam T The coordinate type (must be a floating point type!).
 * @tparam N The euclidian space dimension.
 *
 * @invariant The two endpoints of the line segment are different points.
 *
 **************************************************************************************************/
template <typename T, std::size_t N>
class LineSegment final
{

public:

///@{ @name Object construction and destruction

    /*******************************************************************************************//**
     * @brief Constructor with parameters.
     *
     * Construct a line segment from a point of origin to a point of destination.
     *
     * @tparam T The coordinate type.
     * @tparam N The euclidian space dimension.
     *
     * @param m_firstEndpoint  The point of origin of the line segment.
     * @param m_secondEndpoint The point of destination of the line segment.
     *
     * @pre The two endpoints are different (otherwise you have a point, not a line segment).
     *
     **********************************************************************************************/
    LineSegment(const Point<T, N>& p_firstEndpoint, const Point<T, N>& p_secondEndpoint);


    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    ~LineSegment();

///@}

///@{ @name Data access.

    /*******************************************************************************************//**
     * @brief Returns a first endpoint.
     *
     * Even though the notation "first" is used, line segments endpoints have no order. This
     * gives access to one of the two endpoints. It will give access to the endpoint that is
     * not returned by the method @c secondEndpoint() .
     *
     * @return An endpoint.
     *
     * @see secondEndpoint
     *
     **********************************************************************************************/
    Point<T, N> firstEndpoint() const { return m_firstEndpoint; }


    /*******************************************************************************************//**
     * @brief Returns a second endpoint.
     *
     * Even though the notation "second" is used, line segments endpoints have no order. This
     * gives access to one of the two endpoints. It will give access to the endpoint that is
     * not returned by the method @c firstEndpoint() .
     *
     * @return An endpoint.
     *
     * @see firstEndpoint
     *
     **********************************************************************************************/
    Point<T, N> secondEndpoint() const { return m_secondEndpoint; }

///@}

private:

    void checkInvariant() const;

///@{ @name Data members

    Point<T, N> m_firstEndpoint;   ///< The point of origin.
    Point<T, N> m_secondEndpoint;  ///< The point of destination.

///@}

    static_assert(std::is_floating_point<T>(), "Floating point types are needed for the concept "
                                               "of line segments to make sense.");

};

using LineSegment2D = LineSegment<double, 2>;  ///< Convenience typedefs for the usual case of a line segment
                                               ///< using floating point types in a 2D euclidian space.

using LineSegment3D = LineSegment<double, 3>;  ///< Convenience typedefs for the usual case of a line segment
                                               ///< using floating point types in a 3D euclidian space.

///@{ @name Line segments comparison checks.

/***********************************************************************************************//**
 * @brief Checks if two line segments are parallel.
 *
 * @tparam T        The coordinate type.
 * @tparam N        The euclidian space dimension.
 *
 * @param  p_first  The fisrt line segment.
 * @param  p_second the second line segment.
 *
 * @note Supported only for N=2 now.
 *
 * @return @c true if the line segments are parallel, @c false otherwise.
 *
 **************************************************************************************************/
template <typename T>
bool areParallel(const LineSegment<T, 2>& p_first, const LineSegment<T, 2>& p_second);


/***********************************************************************************************//**
 * @brief Checks if two line segments are othogonal.
 *
 * @tparam T        The coordinate type.
 * @tparam N        The euclidian space dimension.
 *
 * @param  p_first  The fisrt line segment.
 * @param  p_second the second line segment.
 *
 * @note Supported only for N=2 now.
 *
 * @return @c true if the line segments are othogonal, @c false otherwise.
 *
 **************************************************************************************************/
template <typename T>
bool areOrthogonal(const LineSegment<T, 2>& p_first, const LineSegment<T, 2>& p_second);


/***********************************************************************************************//**
 * @brief Checks if two line segments are co-linear.
 *
 * @tparam T        The coordinate type.
 * @tparam N        The euclidian space dimension.
 *
 * @param  p_first  The fisrt line segment.
 * @param  p_second the second line segment.
 *
 * @note Supported only for N=2 now.
 *
 * @return @c true if the line segments are co-linear, @c false otherwise.
 *
 **************************************************************************************************/
template <typename T>
bool areColinear(const LineSegment<T, 2>& p_first, const LineSegment<T, 2>& p_second);


/***********************************************************************************************//**
 * @brief Checks if two line segments are parallel.
 *
 * @tparam T                   The coordinate type.
 * @tparam N                   The euclidian space dimension.
 *
 * @param  p_first             The fisrt line segment.
 * @param  p_second            the second line segment.
 * @param  p_considerEndpoints Consider the endpoints as part of the line segment.
 *
 * @note Supported only for N=2 now.
 *
 * @return @c true if the line segments are parallel, @c false otherwise.
 *
 **************************************************************************************************/
template <typename T>
bool intersect(const LineSegment<T, 2>& p_first, const LineSegment<T, 2>& p_second, bool p_considerEndpoints = false);

///@}

} // namespace math

} // namespace cxutil

#include "../src/LineSegment.ipp"

#endif // LINESEGMENT_H_211CAF0D_19F6_4B9B_A0FC_690207C49414
