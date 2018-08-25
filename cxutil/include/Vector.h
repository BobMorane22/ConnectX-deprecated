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
 * @file    Vector.h
 * @author  Eric Poirier
 * @date    August 2018
 * @version 1.0
 *
 * Interface for a the @c Vector class template.
 *
 **************************************************************************************************/

#ifndef VECTOR_H_03807259_4016_454E_9619_21A3330E4CAE
#define VECTOR_H_03807259_4016_454E_9619_21A3330E4CAE


#include "Point.h"

namespace cxutil
{

namespace math
{

/***********************************************************************************************//**
 * @brief Generic euclidian space vector class.
 *
 * This class is an approximation of a mathematical vector (and not the concept of a container
 * such as an @c std::vector ) in euclidian space where all points have coordinates of type @c T .
 * A vector is defined by a magnitude and a direction. Equivalently, a vector has a point of origin
 * and a point of destination. In this case, the direction is the unit vector from the origin
 * towards the destination and the magnitude is the euclidian distance between the two points.
 *
 * To be a candidate for this class, the type @c T must have the following properties:
 *
 *   - @c T has an additive identity and this identity is given by T().
 *   - @c T is comparable (i.e comparison operators are defined).
 *   - +, - and * arithmetic operators are defined for @c T.
 *
 * @tparam T The coordinate type (not necessarily a cxutil::Coordinate). One can also think of
 *           it mathematically as the field over which the vector space is defined.
 * @tparam N The dimension (either 1, 2 or 3). Higher dimensions are not supported.
 *
 **************************************************************************************************/
template<typename T, std::size_t N>
class Vector final
{

public:

///{ @name Convenience values

    static const std::size_t X_COMPONENT{0}; ///< Access @c x component.
    static const std::size_t Y_COMPONENT{1}; ///< Access @c y component.
    static const std::size_t Z_COMPONENT{2}; ///< Access @c z component.

///@}

///{ @name Object construction and destruction

    /*******************************************************************************************//**
     * @brief Default constructor.
     *
     * Build a vector going from the origin (i.e <tt>(0, 0, 0)</tt> for the real numbers) to
     * the origin and having length 0.
     *
     **********************************************************************************************/
    Vector();


    /*******************************************************************************************//**
     * @brief Constructor with parameters.
     *
     * Construct a vector going from an origin point to a destination point.
     *
     * @param p_origin       The origin of the vector.
     * @param p_destination  The destination of the vector.
     *
     **********************************************************************************************/
    Vector(Point<T, N> p_origin, Point<T, N> p_destination);


    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    ~Vector();

///@}

///{ @name Data access

    /*******************************************************************************************//**
     * @brief Gets the point of origin of the vector.
     *
     * The point of origin is decided at construction. Even if two vectors are considered equal,
     * they might not share the same point of origin.
     *
     * @return The point of origin of the vector.
     *
     **********************************************************************************************/
    Point<T, N> origin() const { return m_origin; }


    /*******************************************************************************************//**
     * @brief Gets the point of destination of the vector.
     *
     * The point of destination is decided at construction. Unlike the point of origin though, it
     * can vary when operations are performed on the vector. Again, even if two vectors are
     * equal, they might not share the same point of destination.
     *
     * @return The point of destination of the vector.
     *
     **********************************************************************************************/
    Point<T, N> destination() const { return m_destination; }


    /*******************************************************************************************//**
     * @brief Accesses the vector's @c x component.
     *
     * @tparam T The coordinate type.
     *
     * @return The vector's @c x component.
     *
     **********************************************************************************************/
    T x() const;


    /*******************************************************************************************//**
     * @brief Accesses the vector's @c y component.
     *
     * @tparam T The coordinate type.
     *
     * @return The vector's @c y component.
     *
     **********************************************************************************************/
    T y() const;


    /*******************************************************************************************//**
     * @brief Accesses the vector's @c z component.
     *
     * @tparam T The coordinate type
     *
     * @return The vector's @c z component.
     *
     **********************************************************************************************/
    T z() const;


    /*******************************************************************************************//**
     * @brief Accesses a vector component.
     *
     * With this operator, you can access any of the vector's component(s). Here is the
     * correspondence table:
     *
     * <table>
     * <tr> <th> Index </th> <th> Component </th> </tr>
     * <tr> <td>   0   </td> <td>      x    </td> </tr>
     * <tr> <td>   1   </td> <td>      y    </td> </tr>
     * <tr> <td>   2   </td> <td>      z    </td> </tr>
     * </table>
     *
     * @tparam T      The coordinate type
     * @param p_index The index of the component you want to access.
     *
     * @pre @c p_index is greater or equal to zero.
     * @pre @c p_index is smaller than @c N .
     *
     * @return The requested component value.
     *
     **********************************************************************************************/
    const T operator[](std::size_t p_index) const;

///@}

///{ @name Arithmetic operators

    Vector<T, N> operator-() const;

    Vector<T, N>& operator+=(const Vector<T, N>& p_vector);
    Vector<T, N>& operator-=(const Vector<T, N>& p_vector);
    Vector<T, N>& operator*=(const T& p_scalar);

///@}

private:

    Point<T, N> m_origin;      ///< Vector point of origin.
    Point<T, N> m_destination; ///< Vector destination.

};

using Vector1D = Vector<double, 1>; ///< Common case of a 1D vector with @c double as the coordinate type.
using Vector2D = Vector<double, 2>; ///< Common case of a 2D vector with @c double as the coordinate type.
using Vector3D = Vector<double, 3>; ///< Common case of a 3D vector with @c double as the coordinate type.


/*************************************** 2D-Specific Operations ***************************************/
template<typename T>
void crossProduct(const Vector<T, 2>& p_v1, const Vector<T, 2>& p_v2, T& p_result);

/*************************************** 3D-Specific Operations ***************************************/
template<typename T>
void crossProduct(const Vector<T, 3>& p_v1, const Vector<T, 3>& p_v2, Vector<T, 3>& p_result);

/*************************************** nD-Specific Operations ***************************************/

template<typename T, std::size_t N>
const Vector<T, N>& additionIdentity();

template<typename T, std::size_t N>
bool operator==(const Vector<T, N>& p_v1, const Vector<T, N>& p_v2);

template<typename T, std::size_t N>
bool operator!=(const Vector<T, N>& p_v1, const Vector<T, N>& p_v2);

template<typename T, std::size_t N>
Vector<T, N> operator+(const Vector<T, N>& p_v1, const Vector<T, N>& p_v2);

template<typename T, std::size_t N>
Vector<T, N> operator-(const Vector<T, N>& p_v1, const Vector<T, N>& p_v2);

template<typename T, std::size_t N>
Vector<T, N> operator*(const T& p_scalar, const Vector<T, N>& p_vector);

template<typename T, std::size_t N>
Vector<T, N> operator*(const Vector<T, N>& p_vector, const T& p_scalar);

template<typename T, std::size_t N>
T dotProduct(const Vector<T, N>& p_v1, const Vector<T, N>& p_v2);

}// namespace math

} // namespace cxutil

#include "../src/Vector.ipp"
#include "../src/Vector2D.ipp"
#include "../src/Vector3D.ipp"

#endif // VECTOR_H_03807259_4016_454E_9619_21A3330E4CAE
