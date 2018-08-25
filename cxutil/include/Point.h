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
 * @file    Point.h
 * @author  Eric Poirier
 * @date    April 2018
 * @version 1.0
 *
 * Interface for a point template utility.
 *
 **************************************************************************************************/

#ifndef POINT_H_91839565_7FF8_4221_BD53_1325EA075F3E
#define POINT_H_91839565_7FF8_4221_BD53_1325EA075F3E

#include <array>


namespace cxutil
{

namespace math
{

/***********************************************************************************************//**
 * @class Point
 *
 * @brief Generic euclidian space point utility.
 *
 * This genereic class represents a 1, 2 or 3D euclidian space point in the classic
 * <tt>(x, y, z)</tt> form.
 *
 * @tparam T The coordinate type (not necessarily a cxutil::Coordinate).
 * @tparam N The point dimension (either 1, 2 or 3). Higher dimensions are not supported.
 *
 **************************************************************************************************/
template<typename T, typename std::size_t N>
class Point final
{

public:

///{ @name Convenience values

    static const std::size_t X_COORDINATE{0};  ///< Access the @c x coordinate.
    static const std::size_t Y_COORDINATE{1};  ///< Access the @c y coordinate.
    static const std::size_t Z_COORDINATE{2};  ///< Access the @c z coordinate.

///@}


///@{ @name Object construction and destruction

    /*******************************************************************************************//**
     * @brief Default constructor.
     *
     * Constructs a point at the origin of the euclidian space (i.e. <tt>(0, 0, 0)</tt> for
     * @c int in 3D euclidian space).
     *
     * @note This constructor assumes that for the coordinate type @c T , the default constructor
     *       @c T() creates an origin coordinate. If you use your own type for @c T, you must
     *       make sure this is indeed the case or this constructor might not work as expected.
     *
     **********************************************************************************************/
    Point();


    /*******************************************************************************************//**
     * @brief 1D point constructor.
     *
     * Constructs a 1D point at the coordinate defined by @c p_x.
     *
     * @tparam T The coordinate type.
     *
     **********************************************************************************************/
    Point(const T& p_x);


    /*******************************************************************************************//**
     * @brief 2D point constructor.
     *
     * Constructs a 2D point defined as <tt>(p_x, p_y)</tt>.
     *
     * @tparam T The coordinate type.
     *
     **********************************************************************************************/
    Point(const T& p_x, const T& p_y);


    /*******************************************************************************************//**
     * @brief 3D point constructor.
     *
     * Constructs a 3D point defined as <tt>(p_x, p_y, p_z)</tt>.
     *
     * @tparam T The coordinate type.
     *
     **********************************************************************************************/
    Point(const T& p_x, const T& p_y, const T& p_z);


    /*******************************************************************************************//**
     * Default destructor.
     *
     **********************************************************************************************/
    ~Point();

///@}

///@{ @name Data access

    /*******************************************************************************************//**
     * @brief x-coordinate accessor.
     *
     * Gets the x-coordinate accessor. This method will compile for any valid @c N .
     *
     * @tparam T The coordinate type.
     * @tparam N The point dimension.
     *
     **********************************************************************************************/
    T x() const;


    /*******************************************************************************************//**
     * @brief y-coordinate accessor.
     *
     * Gets the y-coordinate accessor. This method will compile for any valid @c N greater than
     * one.
     *
     * @tparam T The coordinate type.
     * @tparam N The point dimension.
     *
     **********************************************************************************************/
    T y() const;


    /*******************************************************************************************//**
     * @brief z-coordinate accessor.
     *
     * Gets the z-coordinate accessor. This method will compile only when @c N is three.
     *
     * @tparam T The coordinate type.
     * @tparam N The point dimension.
     *
     **********************************************************************************************/
    T z() const;

///@}

///@{ @name Mutators

    /*******************************************************************************************//**
     * @brief Convenience x-coordinate mutator.
     *
     * Updates the x-coordinate. This method will compile for any valid @c N greater or equal to
     * one.
     *
     * @tparam T The coordinate type.
     * @tparam N The point dimension.
     *
     **********************************************************************************************/
    T& x();


    /*******************************************************************************************//**
     * @brief Convenience y-coordinate mutator.
     *
     * Updates the y-coordinate. This method will compile for any valid @c N greater than one.
     *
     * @tparam T The coordinate type.
     * @tparam N The point dimension.
     *
     **********************************************************************************************/
    T& y();


    /*******************************************************************************************//**
     * @brief Convenience z-coordinate mutator.
     *
     * Updates the z-coordinate. This method will compile only when @c N is three.
     *
     * @tparam T The coordinate type.
     * @tparam N The point dimension.
     *
     **********************************************************************************************/
    T& z();

///@}

///@{ @name Data access

    /*******************************************************************************************//**
     * @brief Random access operator (access only).
     *
     * Accesses either the @c x, @c y or @c z coordinate through an index. Here is the correspondence
     * table:
     *
     * <table>
     * <tr> <th> Index </th> <th> %Coordinate </th> </tr>
     * <tr> <td>   0   </td> <td>      x      </td> </tr>
     * <tr> <td>   1   </td> <td>      y      </td> </tr>
     * <tr> <td>   2   </td> <td>      z      </td> </tr>
     * </table>
     *
     * @tparam T The coordinate type.
     *
     * @pre @c p_index is a positive integer.
     * @pre @c p_index is at most the point dimension @c N .
     *
     **********************************************************************************************/
    const T& operator[](std::size_t p_index) const;

///@}

///@{ @name Mutators

    /*******************************************************************************************//**
     * @brief Random access operator (mutator only).
     *
     * Modifies either the @c x, @c y or @c z coordinate through an index. Here is the correspondence
     * table:
     *
     * <table>
     * <tr> <th> Index </th> <th> %Coordinate </th> </tr>
     * <tr> <td>   0   </td> <td>      x      </td> </tr>
     * <tr> <td>   1   </td> <td>      y      </td> </tr>
     * <tr> <td>   2   </td> <td>      z      </td> </tr>
     * </table>
     *
     * @tparam T The coordinate type.
     *
     * @pre @c p_index is a positive integer.
     * @pre @c p_index is at most the point dimension @c N .
     *
     **********************************************************************************************/
    T& operator[](std::size_t p_index);

///@}

    Point& operator+(const Point& p_point) = delete;
    Point& operator-(const Point& p_point) = delete;
    Point& operator*(const Point& p_point) = delete;
    Point& operator/(const Point& p_point) = delete;
    Point& operator%(const Point& p_point) = delete;

private:

    std::array<T, N> m_coordinates; ///< The different coordinates.

};

using Point1D = Point<double, 1>; ///< Common case of a 1D point with @c double as the coordinate type
using Point2D = Point<double, 2>; ///< Common case of a 2D point with @c double as the coordinate type
using Point3D = Point<double, 3>; ///< Common case of a 3D point with @c double as the coordinate type


///{ @name Comparison operators

/***********************************************************************************************//**
 * @brief Equality comparison operator for 1D points.
 *
 * @tparam T       The coordinate type.
 * @param  p_left  The first point to compare.
 * @param  p_right The second point to compare.
 *
 * @return @c true if all coordinates are respectively equal, @c false otherwise.
 *
 **************************************************************************************************/
template<typename T>
bool operator==(const Point<T, 1>& p_left, const Point<T, 1> p_right);


/***********************************************************************************************//**
 * @brief Equality comparison operator for 2D points.
 *
 * @tparam T       The coordinate type.
 * @param  p_left  The first point to compare.
 * @param  p_right The second point to compare.
 *
 * @return @c true if all coordinates are respectively equal, @c false otherwise.
 *
 **************************************************************************************************/
template<typename T>
bool operator==(const Point<T, 2>& p_left, const Point<T, 2> p_right);


/***********************************************************************************************//**
 * @brief Equality comparison operator for 3D points.
 *
 * @tparam T       The coordinate type.
 * @param  p_left  The first point to compare.
 * @param  p_right The second point to compare.
 *
 * @return @c true if all coordinates are respectively equal, @c false otherwise.
 *
 **************************************************************************************************/
template<typename T>
bool operator==(const Point<T, 3>& p_left, const Point<T, 3> p_right);


/***********************************************************************************************//**
 * @brief Non-equality comparison operator.
 *
 * @tparam T       The coordinate type.
 * @param  N       The point dimension.
 * @param  p_left  The first point to compare.
 * @param  p_right The second point to compare.
 *
 * @return @c true if at least one coordinate is not respectively equal in both points, @c false
 *         otherwise.
 *
 **************************************************************************************************/
template<typename T, typename std::size_t N>
bool operator!=(const Point<T, N>& p_left, const Point<T, N> p_right);


// All other comparison operator have no natural meaning:
template<typename T, typename std::size_t N>
bool operator<(const Point<T, N>& p_left, const Point<T, N> p_right) = delete;

template<typename T, typename std::size_t N>
bool operator<=(const Point<T, N>& p_left, const Point<T, N> p_right) = delete;

template<typename T, typename std::size_t N>
bool operator>(const Point<T, N>& p_left, const Point<T, N> p_right) = delete;

template<typename T, typename std::size_t N>
bool operator>=(const Point<T, N>& p_left, const Point<T, N> p_right) = delete;


///@}

} // namespace math

} // namespace cxutil


#include "../src/Point.ipp"

#endif // POINT_H_91839565_7FF8_4221_BD53_1325EA075F3E
