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
 * @file    Vector.ipp
 * @author  Eric Poirier
 * @date    August 2018
 * @version 1.0
 *
 * Implementation for a the @c Vector class template. Implementations for the 2D and 3D
 * specific functionalities reside in @c Vector2D.ipp and @c Vector3D.ipp files respectively.
 *
 **************************************************************************************************/

#include "../include/narrow_cast.h"

template<typename T, std::size_t N>
cxutil::math::Vector<T, N>::Vector()
    : m_origin{cxutil::math::Point<T, N>()}
    , m_destination{cxutil::math::Point<T, N>()}
{
}


template<typename T, std::size_t N>
cxutil::math::Vector<T, N>::Vector(cxutil::math::Point<T, N> p_origin, cxutil::math::Point<T, N> p_destination)
    : m_origin{p_origin}
    , m_destination{p_destination}
{
}


template<typename T, std::size_t N>
cxutil::math::Vector<T, N>::~Vector() = default;


template<typename T, std::size_t N>
inline T cxutil::math::Vector<T, N>::x() const
{
    static_assert(N >= 1 && N < 4, "Invalid dimension.");

    // See The C++ Programming Language 4th Edition by B. Stroustroup
    // section 10.5.3 to see why this narrowing cast is necessary. This
    // goes for other similar methods/functions in this file.
    return cxutil::narrow_cast<T>(m_destination.x() - m_origin.x());
}


template<typename T, std::size_t N>
inline T cxutil::math::Vector<T, N>::y() const
{
    static_assert(N >= 2 && N < 4, "Invalid dimension.");

    return cxutil::narrow_cast<T>(m_destination.y() - m_origin.y());
}


template<typename T, std::size_t N>
inline T cxutil::math::Vector<T, N>::z() const
{
    static_assert(N == 3, "Invalid dimension.");

    return cxutil::narrow_cast<T>(m_destination.z() - m_origin.z());
}


template<typename T, std::size_t N>
inline const T cxutil::math::Vector<T, N>::operator[](std::size_t p_index) const
{
    PRECONDITION(p_index < N);

    return cxutil::narrow_cast<T>(m_destination[p_index] - m_origin[p_index]);
}


template<typename T, std::size_t N>
cxutil::math::Vector<T, N> cxutil::math::Vector<T, N>::operator-() const
{
    return cxutil::math::Vector<T, N>{m_destination, m_origin};
}


template<typename T, std::size_t N>
cxutil::math::Vector<T, N>& cxutil::math::Vector<T, N>::operator+=(const cxutil::math::Vector<T, N>& p_vector)
{
    for(std::size_t i{0}; i < N; ++i)
    {
        m_destination[i] = cxutil::narrow_cast<T>(m_destination[i] + p_vector[i]);
    }

    return *this;
}


template<typename T, std::size_t N>
cxutil::math::Vector<T, N>& cxutil::math::Vector<T, N>::operator-=(const Vector<T, N>& p_vector)
{
    for(std::size_t i{0}; i < N; ++i)
    {
        m_destination[i] = cxutil::narrow_cast<T>(m_destination[i] - p_vector[i]);
    }

    return *this;
}


template<typename T, std::size_t N>
cxutil::math::Vector<T, N>& cxutil::math::Vector<T, N>::operator*=(const T& p_scalar)
{
    for(std::size_t i{0}; i < N; ++i)
    {
        m_destination[i] = cxutil::narrow_cast<T>(m_origin[i] + p_scalar * (*this)[i]);
    }

    return *this;
}


template<typename T, std::size_t N>
T cxutil::math::dotProduct(const cxutil::math::Vector<T, N>& p_v1, const cxutil::math::Vector<T, N>& p_v2)
{
    T product = T(); // Here we assume T() means 'origin'.

    for(std::size_t i{0}; i < N; ++i)
    {
        product = cxutil::narrow_cast<T>(product + cxutil::narrow_cast<T>(p_v1[i] * p_v2[i]));
    }

    return product;
}


template<typename T, std::size_t N>
const cxutil::math::Vector<T, N>& cxutil::math::additionIdentity()
{
    static const cxutil::math::Vector<T, N> identity;

    return identity;
}


template<typename T, std::size_t N>
bool cxutil::math::operator==(const cxutil::math::Vector<T, N>& p_v1, const cxutil::math::Vector<T, N>& p_v2)
{
    bool areEqual{true};

    for(std::size_t i{0}; i < N; ++i)
    {
        areEqual &= (p_v1[i] == p_v2[i]);
    }

    return areEqual;
}


template<typename T, std::size_t N>
bool cxutil::math::operator!=(const cxutil::math::Vector<T, N>& p_v1, const cxutil::math::Vector<T, N>& p_v2)
{
    return !(p_v1 == p_v2);
}


template<typename T, std::size_t N>
cxutil::math::Vector<T, N> cxutil::math::operator+(const cxutil::math::Vector<T, N>& p_v1, const cxutil::math::Vector<T, N>& p_v2)
{
    return cxutil::math::Vector<T, N>{p_v1} += p_v2;
}


template<typename T, std::size_t N>
cxutil::math::Vector<T, N> cxutil::math::operator-(const cxutil::math::Vector<T, N>& p_v1, const cxutil::math::Vector<T, N>& p_v2)
{
    return cxutil::math::Vector<T, N>{p_v1} -= p_v2;
}


template<typename T, std::size_t N>
cxutil::math::Vector<T, N> cxutil::math::operator*(const T& p_scalar, const Vector<T, N>& p_vector)
{
    cxutil::math::Vector<T, N> temp{p_vector};
    return temp *= p_scalar;
}


template<typename T, std::size_t N>
cxutil::math::Vector<T, N> cxutil::math::operator*(const Vector<T, N>& p_vector, const T& p_scalar)
{
    cxutil::math::Vector<T, N> temp{p_vector};
    return temp *= p_scalar;
}
