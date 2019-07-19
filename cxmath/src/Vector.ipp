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

#include <cxutil/include/narrow_cast.h>

#include "../include/util.h"


template<typename T, std::size_t N>
cxmath::Vector<T, N>::Vector()
    : m_origin{cxmath::Point<T, N>()}
    , m_destination{cxmath::Point<T, N>()}
{
}


template<typename T, std::size_t N>
cxmath::Vector<T, N>::Vector(cxmath::Point<T, N> p_origin, cxmath::Point<T, N> p_destination)
    : m_origin{p_origin}
    , m_destination{p_destination}
{
}


template<typename T, std::size_t N>
cxmath::Vector<T, N>::~Vector() = default;


template<typename T, std::size_t N>
inline T cxmath::Vector<T, N>::x() const
{
    static_assert(N >= 1 && N < 4, "Invalid dimension.");

    return m_destination.x() - m_origin.x();
}


template<typename T, std::size_t N>
inline T cxmath::Vector<T, N>::y() const
{
    static_assert(N >= 2 && N < 4, "Invalid dimension.");

    return m_destination.y() - m_origin.y();
}


template<typename T, std::size_t N>
inline T cxmath::Vector<T, N>::z() const
{
    static_assert(N == 3, "Invalid dimension.");

    return m_destination.z() - m_origin.z();
}


template<typename T, std::size_t N>
inline const T cxmath::Vector<T, N>::operator[](std::size_t p_index) const
{
    PRECONDITION(p_index < N);

    return m_destination[p_index] - m_origin[p_index];
}


template<typename T, std::size_t N>
cxmath::Vector<T, N> cxmath::Vector<T, N>::operator-() const
{
    return cxmath::Vector<T, N>{m_destination, m_origin};
}


template<typename T, std::size_t N>
cxmath::Vector<T, N>& cxmath::Vector<T, N>::operator+=(const cxmath::Vector<T, N>& p_vector)
{
    for(std::size_t i{0}; i < N; ++i)
    {
        m_destination[i] = m_destination[i] + p_vector[i];
    }

    return *this;
}


template<typename T, std::size_t N>
cxmath::Vector<T, N>& cxmath::Vector<T, N>::operator-=(const cxmath::Vector<T, N>& p_vector)
{
    for(std::size_t i{0}; i < N; ++i)
    {
        m_destination[i] = m_destination[i] - p_vector[i];
    }

    return *this;
}


template<typename T, std::size_t N>
cxmath::Vector<T, N>& cxmath::Vector<T, N>::operator*=(const T& p_scalar)
{
    for(std::size_t i{0}; i < N; ++i)
    {
        m_destination[i] = m_origin[i] + p_scalar * (*this)[i];
    }

    return *this;
}


template<typename T, std::size_t N>
T cxmath::dotProduct(const cxmath::Vector<T, N>& p_v1, const cxmath::Vector<T, N>& p_v2)
{
    T product = T(); // Here we assume T() means 'origin'.

    for(std::size_t i{0}; i < N; ++i)
    {
        product += p_v1[i] * p_v2[i];
    }

    return product;
}


template<typename T, std::size_t N>
const cxmath::Vector<T, N>& cxmath::additionIdentity()
{
    static const cxmath::Vector<T, N> identity;

    return identity;
}


template<typename T, std::size_t N>
bool cxmath::operator==(const cxmath::Vector<T, N>& p_v1, const cxmath::Vector<T, N>& p_v2)
{
    bool areEqual{true};

    for(std::size_t i{0}; i < N; ++i)
    {
        areEqual &= (cxmath::areLogicallyEqual<T>(p_v1[i], p_v2[i]));
    }

    return areEqual;
}


template<typename T, std::size_t N>
bool cxmath::operator!=(const cxmath::Vector<T, N>& p_v1, const cxmath::Vector<T, N>& p_v2)
{
    return !(p_v1 == p_v2);
}


template<typename T, std::size_t N>
cxmath::Vector<T, N> cxmath::operator+(const cxmath::Vector<T, N>& p_v1, const cxmath::Vector<T, N>& p_v2)
{
    return cxmath::Vector<T, N>{p_v1} += p_v2;
}


template<typename T, std::size_t N>
cxmath::Vector<T, N> cxmath::operator-(const cxmath::Vector<T, N>& p_v1, const cxmath::Vector<T, N>& p_v2)
{
    return cxmath::Vector<T, N>{p_v1} -= p_v2;
}


template<typename T, std::size_t N>
cxmath::Vector<T, N> cxmath::operator*(const T& p_scalar, const Vector<T, N>& p_vector)
{
    cxmath::Vector<T, N> temp{p_vector};

    return temp *= p_scalar;
}


template<typename T, std::size_t N>
cxmath::Vector<T, N> cxmath::operator*(const Vector<T, N>& p_vector, const T& p_scalar)
{
    cxmath::Vector<T, N> temp{p_vector};

    return temp *= p_scalar;
}
