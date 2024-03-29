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
 * @file    util.h
 * @author  Eric Poirier
 * @date    July 2019
 * @version 1.0
 *
 * @brief Various math utilities.
 *
 **************************************************************************************************/

#ifndef UTIL_H_E3BBA82A_4FD4_454C_9525_F45B6370A29D
#define UTIL_H_E3BBA82A_4FD4_454C_9525_F45B6370A29D

#include <algorithm>
#include <cmath>
#include <limits>


namespace cxmath
{

/***********************************************************************************************//**
 * @brief Checks if two numbers are equal considering rounding errors.
 *
 * When comparing floating points, rounding errors often make the naive equality check fail,
 * even though the results are logically equivalent (i.e on a piece of paper, they would be).
 * This test lets the caller specify a tolerance on the result such that the test passes even
 * though the floating point values are a little different due to rounding errors. See
 * <a href=https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html>this article</a>
 * to know more about floating point arithmetic and roundig off errors.
 *
 * @note This function will compile only for floating point types. If you don't have a floating
 *       point type, use the standard equality check instead, it is much cheaper.
 *
 * @tparam T                  The type of the numbers (floating point only).
 *
 * @param  p_lhs              The number to compare with to the left.
 * @param  p_rhs              The number to compare with to the right.
 * @param  p_errorFactor      The error factor (as a scaling factor on the minimal machine error).
 * @param  p_errorMarginNear0 Special fixed margin to test against when numbers are near 0.
 *
 * @return @c true if the two numbers are equal or almost equal (according to the error factor)
 *         @c false otherwise.
 *
 **************************************************************************************************/
template<typename T>
bool areLogicallyEqual(const T& p_lhs,
                       const T& p_rhs,
                       const T& p_errorFactor = 1.0f,
                       const T& p_errorMarginNear0 = 1e-15f)
{
    static_assert(std::is_floating_point<T>(), "Only floating point types need this special treatement. "
                                               "Use the standard equality comparison instead.");

    // Maybe we are lucky?
    if(p_lhs == p_rhs)
    {
        return true;
    }

    // Nope, let's move on:
    const T delta{std::abs(p_lhs - p_rhs)};

    // Case when near 0:
    if(delta <= p_errorMarginNear0)
    {
        return true;
    }

    // Normal case:
    const T lhs    {std::abs(p_lhs)};
    const T rhs    {std::abs(p_rhs)};
    const T largest{std::max(lhs, rhs)};

    if(delta <= largest * std::numeric_limits<T>::epsilon() * p_errorFactor)
    {
        return true;
    }

    return false;
}

} // namespace cxmath


#endif // UTIL_H_E3BBA82A_4FD4_454C_9525_F45B6370A29D
