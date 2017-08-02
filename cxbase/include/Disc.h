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
 * @file    Disc.h
 * @author  Eric Poirier
 * @date    October 2016
 * @version 0.1
 *
 * Interface for a Disc utility.
 *
 **************************************************************************************************/

#ifndef DISC_H_97C4FDCA_4FD8_4DB4_B111_6F80F62266FA
#define DISC_H_97C4FDCA_4FD8_4DB4_B111_6F80F62266FA


#include <cxutil/include/ICliObject.h>

#include "Color.h"

BEGIN_CXBASE_NAMESPACE


/***********************************************************************************************//**
 * @class Disc
 *
 * A colored Disc object.
 *
 * A Disc can be seen as a kind of colored token. It's only data member is a Color.
 *
 * @see Color
 *
 **************************************************************************************************/
class Disc : public CXUTIL::ICliObject
{

public:

///@{ @name Object construction and destruction
    virtual ~Disc() = default;

    /*******************************************************************************************//**
     * Default constructor.
     *
     * Constructs a Disc with a TRANSPARENT Color value. In a collection of Discs, this is to
     * be seen as the absence of a Disc.
     *
     **********************************************************************************************/
    Disc() : m_color{Color::TRANSPARENT} {}


    /*******************************************************************************************//**
     * Parameter constructor.
     *
     * Constructs a Disc with the Color passed as an argument.
     *
     * @param[in] p_color The color with which to create the Disc.
     *
     **********************************************************************************************/
    Disc(const Color& p_color) : m_color{p_color} {}
///@}


///@{ @name Data access
    /*******************************************************************************************//**
     * Color accessor.
     *
     * @return The Disc's Color.
     *
     **********************************************************************************************/
    Color color() const {return m_color;}


    /*******************************************************************************************//**
     * ASCII Color code accessor.
     *
     * @return The Disc's Color's AsciiColorCode.
     *
     **********************************************************************************************/
    AsciiColorCode asciiColorCode() const {return m_color.asciiColorCode();}
///@}


///@{ @name Operators
    /*******************************************************************************************//**
     * Equal-to operator.
     *
     * Two discs are compared for equality by Color. Two discs are considered equal <em> if and
     * only if </em> both their Colors are equal and their ASCII Color code is equal.
     *
     * @see Color::operator==().
     *
     **********************************************************************************************/
    virtual bool operator==(const Disc &p_disc) const;


    /*******************************************************************************************//**
     * Not-equal-to operator.
     *
     * Two discs are compared for non-equality by Color. Two discs are considered @b NOT equal
     * <em> if and only if </em> either their Colors are @b NOT equal, or their ASCII Color code
     * (or both).
     *
     * @see Color::operator!=().
     *
     **********************************************************************************************/
    virtual bool operator!=(const Disc &p_disc) const;


///@}

///@{ @name Predefined Discs
    static const Disc NO_DISC;
    static const Disc WHITE_DISC;
    static const Disc BLACK_DISC;

    static const Disc GREEN_DISC;
    static const Disc RED_DISC;
    static const Disc YELLOW_DISC;
    static const Disc BLUE_DISC;
///@}

protected:

    /*******************************************************************************************//**
     * Text to stream.
     *
     * Inserts the Disc formatted in text mode into a stream. To do so, it uses the Disc Color's
     * AsciiColorCode. It adds one space character to the left and one space character to the right
     * of the AsciiColorCode @c char value. For example, if you define a Disc as such:
     *
     *  @verbatim
     *    Disc aDisc{Color{Name{"Red"}, AsciiColorCode{'R'}}};
     *  @endverbatim
     *
     * You will get the following string inserted into the stream:
     *
     *  @verbatim
     *    " R "       // Without the quotes
     *  @endverbatim
     *
     * So if you write this:
     *
     *  @verbatim
     *    std::cout << "|" << aDisc << "|";
     *  @endverbatim
     *
     * You will see this to the console:
     *
     *  @verbatim
     *    "| R |"    // Without the quotes
     *  @endverbatim
     *
     * @param[in] p_stream  The stream in which to insert.
     *
     **********************************************************************************************/
    virtual void print(std::ostream& p_stream) const override;


private:

    Color m_color;  ///< The disc Color.

};

END_CXBASE_NAMESPACE

#endif /* DISC_H_97C4FDCA_4FD8_4DB4_B111_6F80F62266FA */
