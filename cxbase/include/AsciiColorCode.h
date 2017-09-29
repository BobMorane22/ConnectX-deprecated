/***************************************************************************************************
 *
 * Copyright (C) 2016 Connect X team
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
 * @file    AsciiColorCode.h
 * @author  Eric Poirier
 * @date    November 2016
 * @version 0.1
 *
 * Interface for an ASCII color code utility.
 *
 **************************************************************************************************/

#ifndef ASCIICOLORCODE_H_89A38543_0B75_49ED_807D_B95EB8A3B7F6
#define ASCIICOLORCODE_H_89A38543_0B75_49ED_807D_B95EB8A3B7F6

#include <cxutil/include/ICliObject.h>
#include <cxutil/include/IEnforceContract.h>


namespace cxbase
{

/***********************************************************************************************//**
 * @class AsciiColorCode
 *
 * An ASCII code representing a color.
 *
 * An ASCII color code is an ASCII character that is used to represent a color (for example in a
 * terminal, or a text file). Not all ASCII characters can be used to represent a color. In fact,
 * only letters (lower or upper case) and the space character can be used.
 *
 * For example, these are some of the ways the color @a Black can be represented:
 *      @li the character @c 'B';
 *      @li the character @c 'b';
 *      @li the character @c 'x';
 *      @li the character @c ' '.
 *
 * However, the last two examples are not recommended for readibility purposes.
 *
 * @invariant An ASCII color code is always a letter (lower or upper case) or a space character.
 *
 * @see Color
 *
 **************************************************************************************************/
class AsciiColorCode : public cxutil::IEnforceContract, public cxutil::ICliObject
{

public:

///@{ @name Object construction and destruction

    /*******************************************************************************************//**
     * Default destructor.
     *
     **********************************************************************************************/
    virtual ~AsciiColorCode();


    /*******************************************************************************************//**
     * Constructor with parameters.
     *
     * Constructs an AsciiColorCode object from a character (@c char).
     *
     * @param[in]   p_asciiColorCode The char containing the ASCII code.
     * @pre         @c p_asciiColorCode is a letter (lower or upper case) or a space.
     * @post        @c m_asciiColorCode is a letter (lower or upper case) or a space.
     *
     **********************************************************************************************/
    explicit AsciiColorCode(char p_asciiColorCode);

///@}

///@{ @name Data access

    /*******************************************************************************************//**
     * Accessor for the ascii color code attribute.
     *
     * @return A @c char representing the ASCII color code.
     *
     **********************************************************************************************/
    char toChar() const { return m_asciiColorCode; }

///@}


///@{ @name Operators

    /*******************************************************************************************//**
     * Equal-to operator.
     *
     * The operator compares for equality the @c char code value of the two AsciiColorCode objects
     * for equality.
     *
     * @param[in] p_asciiColorCode The AsciiColorCode to compare with.
     *
     **********************************************************************************************/
    bool operator==(const AsciiColorCode& p_asciiColorCode) const { return p_asciiColorCode.m_asciiColorCode == m_asciiColorCode; }


    /*******************************************************************************************//**
     * Not-equal-to operator.
     *
     * The operator compares for equality the @c char code value of the two AsciiColorCode objects
     * for non-equality.
     *
     * @param[in] p_asciiColorCode The AsciiColorCode to compare with.
     *
     **********************************************************************************************/
    bool operator!=(const AsciiColorCode& p_asciiColorCode) const { return p_asciiColorCode.m_asciiColorCode != m_asciiColorCode; }

///@}


protected:

    /*******************************************************************************************//**
     * Print text to stream.
     *
     * The AsciiColorCode is represented as the @c char from which it is constructed.
     *
     * @param[in] p_stream The stream in which to insert the text representation.
     *
     **********************************************************************************************/
    virtual void print(std::ostream& p_stream) const override;


    virtual void checkInvariant() const override;


private:


    char m_asciiColorCode; ///< The ASCII @c char.

};

} // namespace cxbase

#endif // ASCIICOLORCODE_H_89A38543_0B75_49ED_807D_B95EB8A3B7F6
