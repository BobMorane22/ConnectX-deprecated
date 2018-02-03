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
 * @version 1.0
 *
 * Interface for a Disc utility.
 *
 **************************************************************************************************/

#ifndef DISC_H_97C4FDCA_4FD8_4DB4_B111_6F80F62266FA
#define DISC_H_97C4FDCA_4FD8_4DB4_B111_6F80F62266FA


#include <cxutil/include/Color.h>

namespace cxbase
{

/***********************************************************************************************//**
 * @class Disc
 *
 * @brief A colored Disc object.
 *
 * A Disc can be seen as a kind of colored token. It represents what Players use to make a move 
 * on the GameBoard.
 *
 * @see Color
 *
 **************************************************************************************************/
class Disc
{

public:

///@{ @name Object construction and destruction

    /*******************************************************************************************//**
     * Default destructor.
     *
     **********************************************************************************************/
    virtual ~Disc();


    /*******************************************************************************************//**
     * Default constructor.
     *
     * Constructs a Disc with a TRANSPARENT Color value. In a collection of Discs, this is to
     * be seen as the absence of a Disc.
     *
     **********************************************************************************************/
    Disc() : m_color{cxutil::Color::transparent()} {}


    /*******************************************************************************************//**
     * Parameter constructor.
     *
     * Constructs a Disc with the Color passed as an argument.
     *
     * @param[in] p_color The Color with which to create the Disc.
     *
     **********************************************************************************************/
    explicit Disc(const cxutil::Color& p_color) : m_color{p_color} {}

///@}


///@{ @name Data access
    /*******************************************************************************************//**
     * Color accessor.
     *
     * @return The Disc's Color.
     *
     **********************************************************************************************/
    cxutil::Color color() const {return m_color;}

///@}


///@{ @name Operators

    /*******************************************************************************************//**
     * Equal-to operator.
     *
     * Two discs are compared for equality by Color. Two discs are considered equal <em> if and
     * only if </em> their Colors are equal.
     *
     * @see Color::operator==().
     *
     **********************************************************************************************/
    virtual bool operator==(const Disc& p_disc) const;


    /*******************************************************************************************//**
     * Not-equal-to operator.
     *
     * Two discs are compared for non-equality by Color. Two discs are considered @b NOT equal
     * <em> if and only if </em> their Colors are @b NOT equal.
     *
     * @see Color::operator!=().
     *
     **********************************************************************************************/
    virtual bool operator!=(const Disc& p_disc) const;

///@}

///@{ @name Predefined Discs

    static const Disc& noDisc();
    static const Disc& whiteDisc();
    static const Disc& blackDisc();
    static const Disc& greenDisc();
    static const Disc& redDisc();
    static const Disc& yellowDisc();
    static const Disc& blueDisc();

///@}

private:

    cxutil::Color m_color;  ///< The disc Color.

};

} //namespace cxbase

#endif /* DISC_H_97C4FDCA_4FD8_4DB4_B111_6F80F62266FA */
