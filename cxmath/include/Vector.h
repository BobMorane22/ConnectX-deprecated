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


namespace cxmath
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
 * @tparam T The coordinate type. One can also think of it mathematically as the field over
 * which the vector space is defined.
 *
 * @tparam N The dimension (either 1, 2 or 3). Higher dimensions are not supported.
 *
 **************************************************************************************************/
template<typename T, std::size_t N>
class Vector final
{

public:

///@{ @name Convenience values

    static const std::size_t X_COMPONENT{0}; ///< Access @c x component.
    static const std::size_t Y_COMPONENT{1}; ///< Access @c y component.
    static const std::size_t Z_COMPONENT{2}; ///< Access @c z component.

///@}

///@{ @name Object construction and destruction

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

///@{ @name Data access

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

///@{ @name Arithmetic operators

    /*******************************************************************************************//**
     * @brief Unary minus operator.
     *
     * Reverts the point of origin and the destination point of the vector. This means that for
     * a vector @c v, @c -v is the vector of same magnitude going in the opposite direction of
     * @c v from @c v 's destination point. Of course, this operation reverses the sign of
     * all vector components.
     *
     * @return A vector with reverted point of origin and destination.
     *
     **********************************************************************************************/
    Vector<T, N> operator-() const;


    /*******************************************************************************************//**
     * @brief Addition assignment operator.
     *
     * Performs vector addition on the current (calling) vector.
     *
     * @param p_vector The vector to add to the current vector.
     *
     * @return The sum vector.
     *
     ***********************************************************************************************/
    Vector<T, N>& operator+=(const Vector<T, N>& p_vector);


    /*******************************************************************************************//**
     * @brief Subtraction assignment operator.
     *
     * Performs vector subtraction on the current (calling) vector.
     *
     * @param p_vector The vector to subtract to the current vector.
     *
     * @return The difference vector.
     *
     ***********************************************************************************************/
    Vector<T, N>& operator-=(const Vector<T, N>& p_vector);


    /*******************************************************************************************//**
     * @brief Multiplication assignment operator (scalar).
     *
     * Performs <em>scalar</em> multiplication on the current (calling) vector.
     *
     * @tparam T       The coordinate type.
     * @param p_scalar The scalar by which to multiply the current vector.
     *
     * @return The product vector.
     *
     **********************************************************************************************/
    Vector<T, N>& operator*=(const T& p_scalar);

///@}

private:

    Point<T, N> m_origin;      ///< Vector point of origin.
    Point<T, N> m_destination; ///< Vector destination.

    static_assert(std::is_floating_point<T>(), "Floating point types only are accepted.");

};

using Vector1D = Vector<double, 1>; ///< Common case of a 1D vector with @c double as the coordinate type.
using Vector2D = Vector<double, 2>; ///< Common case of a 2D vector with @c double as the coordinate type.
using Vector3D = Vector<double, 3>; ///< Common case of a 3D vector with @c double as the coordinate type.


///@{ @name Comparison operators

/***********************************************************************************************//**
 * @brief Equality comparison operator.
 *
 * Two vectors are considered equal <em>if and only if</em> all of their respective components
 * are equal. Note that two equal vectors can have different origin and destination points but
 * still be considered equal, because only magnitude and direction is considered. One of the
 * drawback of this definition is that for floating point types, this operator might not work
 * as expected because of rounding off errors.
 *
 * @tparam T   The components type.
 * @tparam N   The vectors dimension.
 *
 * @param p_v1 The first vector to compare with.
 * @param p_v2 The second vector to compare with.
 *
 * @return @c true if the two vectore are equal, @c false otherwise.
 *
 **************************************************************************************************/
template<typename T, std::size_t N>
bool operator==(const Vector<T, N>& p_v1, const Vector<T, N>& p_v2);


/***********************************************************************************************//**
 * @brief Non equality comparison operator.
 *
 * Two vectors are considered NOT equal <em>if and only if</em> at least one of their component
 * is different. Note that two equal can have different origin and destination points but still be
 * considered equal, because only magnitude and direction is considered. One of the drawback of
 * this definition is that for floating point types, this operator might not work as expected
 * because of rounding off errors.
 *
 * @tparam T    The components type.
 * @tparam N    The vectors dimension.
 *
 * @param  p_v1 The first vector to compare with.
 * @param  p_v2 The second vector to compare with.
 *
 * @return @c true if the two vectore are NOT equal, @c false otherwise.
 *
 **************************************************************************************************/
template<typename T, std::size_t N>
bool operator!=(const Vector<T, N>& p_v1, const Vector<T, N>& p_v2);

///@}

///@{ @name Arithmetic operators

/***********************************************************************************************//**
 * @brief Vector addition operator.
 *
 * Performs vector addition on two vectors.
 *
 * @tparam T    The components type.
 * @tparam N    The vectors dimension.
 *
 * @param  p_v1 The first vector operand.
 * @param  p_v2 The second vector operand.
 *
 * @return The sum vector.
 *
 **************************************************************************************************/
template<typename T, std::size_t N>
Vector<T, N> operator+(const Vector<T, N>& p_v1, const Vector<T, N>& p_v2);


/***********************************************************************************************//**
 * @brief Vector subtraction operator.
 *
 * Performs vector difference on two vectors.
 *
 * @tparam T    The components type.
 * @tparam N    The vectors dimension.
 *
 * @param  p_v1 The first vector operand.
 * @param  p_v2 The second vector operand.
 *
 * @return The difference vector.
 *
 **************************************************************************************************/
template<typename T, std::size_t N>
Vector<T, N> operator-(const Vector<T, N>& p_v1, const Vector<T, N>& p_v2);


/***********************************************************************************************//**
 * @brief Scalar multiplication operator.
 *
 * Scales a vector by a scalar value.
 *
 * @tparam T        The components type.
 * @tparam N        The vectors dimension.
 *
 * @param  p_scalar The scalar by which to scale the vector.
 * @param  p_vector The vector to scale.
 *
 * @return The scaled vector.
 *
 **************************************************************************************************/
template<typename T, std::size_t N>
Vector<T, N> operator*(const T& p_scalar, const Vector<T, N>& p_vector);


/***********************************************************************************************//**
 *
 * @copydoc cxmath::operator*(T, cxmath::Vector<T, N>)
 *
 **************************************************************************************************/
template<typename T, std::size_t N>
Vector<T, N> operator*(const Vector<T, N>& p_vector, const T& p_scalar);

///@}

///@{ @name Two dimensional operations

/***********************************************************************************************//**
 * @brief Classic 2D cross product.
 *
 * @tparam     T        The components type.
 *
 * @param[in]  p_v1     The first vector.
 * @param[in]  p_v2     The second vector.
 * @param[out] p_result The result of the 2D cross product of @c p_v1 and @c p_v2 .
 *
 * @note This operation is only available (under this form) in two dimensions.
 *
 **************************************************************************************************/
template<typename T>
void crossProduct(const Vector<T, 2>& p_v1, const Vector<T, 2>& p_v2, T& p_result);

///@}

///@{ @name Three dimensional operations

/***********************************************************************************************//**
 * @brief Classic 3D cross product.
 *
 * @tparam     T        The components type.
 *
 * @param[in]  p_v1     The first vector.
 * @param[in]  p_v2     The second vector.
 * @param[out] p_result The result of the 3D cross product of @c p_v1 and @c p_v2 .
 *
 * @note This operation is only available (under this form) in three dimensions.
 *
 **************************************************************************************************/
template<typename T>
void crossProduct(const Vector<T, 3>& p_v1, const Vector<T, 3>& p_v2, Vector<T, 3>& p_result);

///@}

///@{ @name N dimensional operations

/***********************************************************************************************//**
 * @brief Gets the addition identity vector for specific types and dimensions.
 *
 * @tparam T  The components type.
 * @tparam N  The vectors dimension.
 *
 * @return The addition identity vector.
 *
 **************************************************************************************************/
template<typename T, std::size_t N>
const Vector<T, N>& additionIdentity();


/***********************************************************************************************//**
 * @brief Classic dot product.
 *
 * @tparam T    The components type.
 * @tparam N    The vectors dimension.
 *
 * @param  p_v1 The first vector.
 * @param  p_v2 The second vector.
 *
 * @return The result of the dot product of @c p_v1 with @c p_v2 .
 *
 **************************************************************************************************/
template<typename T, std::size_t N>
T dotProduct(const Vector<T, N>& p_v1, const Vector<T, N>& p_v2);

///@}

}// namespace cxmath


#include "../src/Vector.ipp"
#include "../src/Vector2D.ipp"
#include "../src/Vector3D.ipp"

#endif // VECTOR_H_03807259_4016_454E_9619_21A3330E4CAE
