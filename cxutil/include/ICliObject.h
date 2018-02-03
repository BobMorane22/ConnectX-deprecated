/***************************************************************************************************
 *
 * Copyright (C) 2017 Connect X team
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
 * @file    ICliObject.h
 * @author  Eric Poirier
 * @date    June 2017
 * @version 0.1
 *
 * Interface for reusable CLI interfacing.
 *
 **************************************************************************************************/

#ifndef CLIOBJECT_H_3FD2758A_36D4_4A51_BAE9_9346D1806B3B
#define CLIOBJECT_H_3FD2758A_36D4_4A51_BAE9_9346D1806B3B

#include <iostream>
#include <string>

namespace cxutil
{

/***********************************************************************************************//**
 * @interface ICliObject
 *
 * Interface for enforcing polymorphic CLI interfacing.
 *
 * Once inherited from, this interface forces the user to implement the @c print() virtual method
 * which is used inside the stream insertion operator to emulate polymorphic behaviour. There
 * is no need to re-implement the stream insertion operator, only the @c print() method.
 *
 **************************************************************************************************/

class ICliObject
{
public:

    virtual ~ICliObject() = default;

    /*******************************************************************************************//**
     * Stream insertion operator.
     *
     * Simply calls the @c print() method. In other words, what is returned by the @c print()
     * method is inserted "as is" in the stream.
     *
     **********************************************************************************************/
    friend std::ostream& operator<<(std::ostream& p_stream, const ICliObject& p_cliUiObject)
    {
        p_cliUiObject.print(p_stream);

        return p_stream;
    }


protected:

    /*******************************************************************************************//**
     * Represent object as an ASCII text string and insert it into a stream.
     *
     * This method is internally called by the stream insertion operator ( @c operator<< ) to
     * emulate polymorphic behavior in the text representation of the implementing class. This
     * method alone should be redefined in all derived classes.
     *
     * @param[in] p_stream The stream into which to insert the text string representing the
     *            CliUiObject.
     *
     **********************************************************************************************/
    virtual void print(std::ostream& p_stream) const = 0;

};


} // namespace cxutil

#endif /* ICLIOBJECT_H_3FD2758A_36D4_4A51_BAE9_9346D1806B3B */
