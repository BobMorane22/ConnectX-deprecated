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
 * @date    July 2018
 * @version 1.0
 *
 * @brief Various general purpose utilities.
 *
 * These utilities are broken down into different categories, each with its own sub-namespace
 * to enable searching. Refer to the documentation to know more about each namespace. Most of
 * the time, these utilities are free functions, to better testability and enhance encapsulation.
 *
 **************************************************************************************************/

#ifndef UTIL_H_E3BBA82A_4FD4_454C_9525_F45B6370A29D
#define UTIL_H_E3BBA82A_4FD4_454C_9525_F45B6370A29D

#include <algorithm>
#include <cmath>
#include <limits>
#include <string>
#include <vector>


namespace cxutil
{

/***********************************************************************************************//**
 * @namespace path
 *
 * @brief Path utilities.
 *
 * These utilities are helpful when dealing with paths. Most of them are system specific, so
 * read the documentation before using!
 *
 **************************************************************************************************/
namespace path
{

/***********************************************************************************************//**
 * Produces a string containing the path for the current executable.
 *
 * @param p_pathOnly @c true if only the path is needed, @c false if the executable name is to be
 *                   included in the string.
 *
 * @return The path where the current executable is located, as a string.
 *
 * @note As of now, only barely supported on Linux (only tested on Ubuntu 16.04), nothing else.
 *       More OS/distros should come in the future, but this is not a priority.
 *
 **************************************************************************************************/
std::string currentExecutablePath(const bool p_pathOnly = true);

} // namespace path


namespace math
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

} // namespace math


namespace string
{

/***********************************************************************************************//**
 * @brief Vectorizes a string into tokens according to a delimiter.
 *
 * Splits a string into a vector according to a specific token. After this action, each element
 * of the returned vector contains the information between two delimiters. If the text to
 * vectorize is empty, an empty @c std::vector is returned. If the text is not empty but the
 * delimiter is nowhere to be found in it, a one element @c std::vector is returned, containing
 * the whole text. Finally, set @c p_keepDelimiter to @c true if you want to keep the ending
 * delimiter in each vector elements (except maybe the last, of course).
 *
 * @param p_text      The string to vectorize.
 * @param p_delimiter The delimiter from which to vectorize.
 * @param p_keepToken @c true if you want the end delimiter to be included in the vector elements
 *                    (when applicable), @c false otherwise.
 *
 * @pre @c p_delimiter is not an empty string.
 *
 * @return A vector of strings corresponding to the text passed as an argument.
 *
 ***************************************************************************************************/
std::vector<std::string> vectorize(const std::string& p_text,
                                   const std::string& p_delimiter,
                                   const bool p_keepDelimiter = false);

} // namespace string

} // namespace cxutil

#endif // UTIL_H_E3BBA82A_4FD4_454C_9525_F45B6370A29D
