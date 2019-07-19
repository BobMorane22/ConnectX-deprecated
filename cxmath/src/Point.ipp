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
 * @file    Point.ipp
 * @author  Eric Poirier
 * @date    April 2018
 * @version 1.0
 *
 * Implementation for a Point template utility.
 *
 **************************************************************************************************/


#include <algorithm>

#include <cxutil/include/ContractException.h>


template<typename T, std::size_t N>
cxmath::Point<T, N>::Point()
{
    static_assert(N >= 1 && N < 4, "Invalid number of coordinates.");

    std::fill(m_coordinates.begin(), m_coordinates.end(), T());
}


template<typename T, std::size_t N>
cxmath::Point<T, N>::Point(const T& p_x)
{
    static_assert(N == 1, "A one dimensional point must have exactly one coordinate.");

    x() = p_x;
}


template<typename T, std::size_t N>
cxmath::Point<T, N>::Point(const T& p_x, const T& p_y)
{
    static_assert(N == 2, "A two dimensional point must have exactly two coordinates.");

    x() = p_x;
    y() = p_y;
}


template<typename T, std::size_t N>
cxmath::Point<T, N>::Point(const T& p_x, const T& p_y, const T& p_z)
{
    static_assert(N == 3, "A three dimensional point must have exactly three coordinates.");

    x() = p_x;
    y() = p_y;
    z() = p_z;
}


template<typename T, std::size_t N>
cxmath::Point<T, N>::~Point() = default;


template<typename T, std::size_t N>
inline T cxmath::Point<T, N>::x() const
{
    static_assert(N >= 1 && N < 4, "Invalid number of coordinates.");

    return m_coordinates[X_COORDINATE];
}


template<typename T, std::size_t N>
inline T cxmath::Point<T, N>::y() const
{
    static_assert(N >= 2 && N < 4, "Invalid number of coordinates.");

    return m_coordinates[Y_COORDINATE];
}


template<typename T, std::size_t N>
inline T cxmath::Point<T, N>::z() const
{
    static_assert(N == 3, "Invalid number of coordinates.");

    return m_coordinates[Z_COORDINATE];
}


template<typename T, std::size_t N>
inline T& cxmath::Point<T, N>::x()
{
    static_assert(N >= 1 && N < 4, "Invalid number of coordinates.");

    return m_coordinates[X_COORDINATE];
}


template<typename T, std::size_t N>
inline T& cxmath::Point<T, N>::y()
{
    static_assert(N >= 2 && N < 4, "Invalid number of coordinates.");

    return m_coordinates[Y_COORDINATE];
}


template<typename T, std::size_t N>
inline T& cxmath::Point<T, N>::z()
{
    static_assert(N == 3, "Invalid number of coordinates.");

    return m_coordinates[Z_COORDINATE];
}


template<typename T, std::size_t N>
inline const T& cxmath::Point<T, N>::operator[](std::size_t p_index) const
{
    PRECONDITION(p_index <= N - 1);

    return m_coordinates[p_index];
}


template<typename T, std::size_t N>
inline T& cxmath::Point<T, N>::operator[](std::size_t p_index)
{
    PRECONDITION(p_index <= N - 1);

    return const_cast<T&>(const_cast<const cxmath::Point<T, N>&>(*this)[p_index]);
}


template<typename T>
bool cxmath::operator==(const cxmath::Point<T, 1>& p_left, const cxmath::Point<T, 1> p_right)
{
    return p_left.x() == p_right.x();
}


template<typename T>
bool cxmath::operator==(const cxmath::Point<T, 2>& p_left, const cxmath::Point<T, 2> p_right)
{
    return (p_left.x() == p_right.x()) && (p_left.y() == p_right.y());
}


template<typename T>
bool cxmath::operator==(const cxmath::Point<T, 3>& p_left, const cxmath::Point<T, 3> p_right)
{
    return (p_left.x() == p_right.x()) && (p_left.y() == p_right.y()) && (p_left.z() == p_right.z());
}


template<typename T, typename std::size_t N>
bool cxmath::operator!=(const cxmath::Point<T, N>& p_left, const cxmath::Point<T, N> p_right)
{
    return !(p_left == p_right);
}
