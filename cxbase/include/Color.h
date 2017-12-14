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
 * @version 1.0
 *
 * Interface for a RGBA color utility.
 *
 **************************************************************************************************/

#ifndef COLOR_H_52B8DD85_78C2_40D9_9354_8BA481E96E38
#define COLOR_H_52B8DD85_78C2_40D9_9354_8BA481E96E38

#include <cxutil/include/IEnforceContract.h>


namespace cxbase
{

/***********************************************************************************************//**
 * @class Color
 *
 * @brief An HTML compliant color class.
 *
 * A Color object is composed of 32 bits defining its position on the RGBA spectrum. Of the 32 
 * bits, 8 are for the red component, 8 are for the green component, 8 are for the blue component 
 * and 8 are for the alpha component, which defines opacity. The absence of color is reesented as 
 * the Color object for which all four RGBA components are set to 0. 
 * 
 * See https://www.w3schools.com/colors/colors_hex.asp for more information.
 *
 * @invariant All RBGA values are set between 0 and 255 inclusively.
 *
 * @see AsciiColorCode
 *
 **************************************************************************************************/
class Color final : public cxutil::IEnforceContract
{

public:

///@{ @name Object construction and destruction

    /*******************************************************************************************//**
     * Default constructor.
     *
     * Constructs a black color with complete opacity.
     *
     **********************************************************************************************/
    Color();


    /*******************************************************************************************//**
     * Constructor with parameters.
     *
     * @param[in] p_red             The red component.
     * @param[in] p_green           The green component.
     * @param[in] p_blue            The blue component.
     * @param[in] p_alpha           The alpha (opacity) component.
     *
     **********************************************************************************************/
    Color(int p_red, int p_green, int p_blue, int p_alpha);


    /*******************************************************************************************//**
     * Default destructor.
     *
     **********************************************************************************************/
    ~Color();


///@{ @name Data access

    /*******************************************************************************************//**
     * Red component accessor.
     *
     * @return The Color's red component value (8 bits).
     *
     **********************************************************************************************/
    int r() const {return m_red;}


    /*******************************************************************************************//**
     * Green component accessor.
     *
     * @return The Color's green component value (8 bits).
     *
     **********************************************************************************************/
    int g() const {return m_green;}


    /*******************************************************************************************//**
     * Blue component accessor.
     *
     * @return The Color's blue component value (8 bits).
     *
     **********************************************************************************************/
    int b() const {return m_blue;}


    /*******************************************************************************************//**
     * Alpha component accessor.
     *
     * @return The Color's alpha component value (8 bits).
     *
     **********************************************************************************************/
    int a() const {return m_alpha;}

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
    bool operator==(const Color& p_color) const;


    /*******************************************************************************************//**
     * Not-equal-to operator.
     *
     * Two Colors are considered @b NOT equal <em> if and only if </em> at least one of their RGBA
     * components is @b NOT equal. The way the Color is represented in text mode has no effect 
     * on the non-equality check.
     *
     * @param[in] p_color The Color to compare with.
     *
     **********************************************************************************************/
    bool operator!=(const Color& p_color) const;

///@}

///@{ @name Predefined Colors

    static const Color& transparent();
    static const Color& white();
    static const Color& black();

    static const Color& green();
    static const Color& red();
    static const Color& yellow();
    static const Color& blue();

///@}

protected:

    virtual void checkInvariant() const override;

private:

    int m_red    {0};     ///< The Color's red component.
    int m_green  {0};     ///< The Color's green component.
    int m_blue   {0};     ///< The Color's blue component.
    int m_alpha  {255};   ///< The Color's alpha (opacity) component.

};

} // namespace cxbase

#endif /* COLOR_H_52B8DD85_78C2_40D9-9354_8BA481E96E38 */
