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
 * @file    Color.h
 * @author  Eric Poirier
 * @date    April 2017
 * @version 0.2
 *
 * Interface for a RGBA color utility.
 *
 **************************************************************************************************/

#ifndef COLOR_H_
#define COLOR_H_

#include "AsciiColorCode.h"
#include "Name.h"

BEGIN_CXBASE_NAMESPACE


/***********************************************************************************************//**
 * @class Color
 *
 * A Color object is composed of 32 bits defining its position on the RGBA spectrum and an
 * AsciiColorCode (optional) to display in text mode. Of the 32 bits, 8 are for the red component,
 * 8 are for the green component, 8 are for the blue component and 8 are for the alpha component,
 * which defines opacity. The absence is seen as the color for which all four RGBA components are
 * set to 0. See https://www.w3schools.com/colors/colors_hex.asp for more information.
 *
 * @invariant All RBGA values are set between 0 and 255 inclusively.
 *
 * @see AsciiColorCode
 *
 **************************************************************************************************/
class Color : public IEnforceContract
{

public:

///@{ @name Object construction and destruction
    virtual ~Color() = default;


    /*******************************************************************************************//**
     * Default constructor.
     *
     * Constructs a black color with complete opacity. The AsciiColorCode is a space (' ').
     *
     **********************************************************************************************/
    Color() = default;


    /*******************************************************************************************//**
     * Constructor with parameters.
     *
     * @param[in] p_red             The red component.
     * @param[in] p_green           The green component.
     * @param[in] p_blue            The blue component.
     * @param[in] p_alpha           The alpha (opacity) component.
     * @param[in] p_asciiColorCode  The Color's AsciiColorCode.
     *
     **********************************************************************************************/
    Color(int p_red, int p_green, int p_blue, int p_alpha, AsciiColorCode p_asciiColorCode);


///@{ @name Data access
    /*******************************************************************************************//**
     * Red component accessor.
     *
     * @return The Color's red component value (8 bits).
     *
     **********************************************************************************************/
    int red() const {return m_red;}

    /*******************************************************************************************//**
     * Green component accessor.
     *
     * @return The Color's green component value (8 bits).
     *
     **********************************************************************************************/
    int green() const {return m_green;}

    /*******************************************************************************************//**
     * Blue component accessor.
     *
     * @return The Color's blue component value (8 bits).
     *
     **********************************************************************************************/
    int blue() const {return m_blue;}

    /*******************************************************************************************//**
     * Aplpha component accessor.
     *
     * @return The Color's alpha component value (8 bits).
     *
     **********************************************************************************************/
    int alpha() const {return m_alpha;}

    /*******************************************************************************************//**
     * AsciiColorCode accessor.
     *
     * @return The Color's asciiColorCode.
     *
     **********************************************************************************************/
    AsciiColorCode asciiColorCode() const {return m_asciiColorCode;}
///@}


///@{ @name Operators
    /*******************************************************************************************//**
     * Equal-to operator.
     *
     * Two Colors are considered equal <em> if and only if </em> all of their four RGBA components
     * are equal. The way the Color is represented in text mode has no effect on the equality
     * check.
     *
     * @param[in] p_color The Color to compare with.
     *
     **********************************************************************************************/
    virtual bool operator==(const Color& p_color) const;


    /*******************************************************************************************//**
     * Not-equal-to operator.
     *
     * Two Colors are considered @b NOT equal <em> if and only if </em> at least one of their RGBA
     * components are NOT equal. The way the color is represented in text mode has no effect on
     * the non-equality check.
     *
     * @param[in] p_color The Color to compare with.
     *
     **********************************************************************************************/
    virtual bool operator!=(const Color& p_color) const;
///@}

///@{ @name Predefined Colors
    static const Color TRANSPARENT;
    static const Color WHITE;
    static const Color BLACK;

    static const Color GREEN;
    static const Color RED;
    static const Color YELLOW;
    static const Color BLUE;
///@}

protected:
    virtual void checkInvariant() const;

private:

    // RGB definition:
    int             m_red               {0};     ///< The Color's red component.
    int             m_green             {0};     ///< The Color's green component.
    int             m_blue              {0};     ///< The Color's blue component.
    int             m_alpha             {255};   ///< The Color's alpha (opacity) component.

    // Terminal representation:
    AsciiColorCode      m_asciiColorCode    {' '};

};

END_CXBASE_NAMESPACE

#endif /* COLOR_H_ */
