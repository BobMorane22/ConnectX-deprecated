/***************************************************************************************************
 *
 * Copyright (C) 2019 Connect X team
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
 * @file    ITimestampFormatter.h
 * @author  Eric Poirier
 * @date    July 2019
 * @version 1.0
 *
 * Interface to implement timestamp formatters from. The responsability of a timestamp formatter is
 * to take the system time and to output it in a needed format.
 *
 **************************************************************************************************/

#ifndef ITIMESTAMPFORMATTER_H_22F72E26_2882_465A_B401_872CE78017A2
#define ITIMESTAMPFORMATTER_H_22F72E26_2882_465A_B401_872CE78017A2

#include <string>


namespace cxlog
{

/***********************************************************************************************//**
 * @brief Timestamp formatter interface.
 *
 * Specifies a common interface that every timestamp formatter must share.
 *
 **************************************************************************************************/
class ITimestampFormatter
{

public:

    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    virtual ~ITimestampFormatter() = default;


    /*******************************************************************************************//**
     * @brief Format a timestamp to a string.
     *
     * @return A string containing the formatted timestamp.
     *
     **********************************************************************************************/
    virtual std::string formatTimestamp() const = 0;

};

} // namespace cxlog

#endif // ITIMESTAMPFORMATTER_H_22F72E26_2882_465A_B401_872CE78017A2
