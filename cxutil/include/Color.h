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
 * Interface for a RGBA/HSLA color utility. Check the following link for more information:
 *
 *                    https://www.rapidtables.com/convert/color/hsl-to-rgb.html
 *
 **************************************************************************************************/

#ifndef COLOR_H_52B8DD85_78C2_40D9_9354_8BA481E96E38
#define COLOR_H_52B8DD85_78C2_40D9_9354_8BA481E96E38

#include <array>
#include <cstdint>


namespace cxutil
{

/**********************************************************************************************//**
 * @brief Red-Green-Blue-Alpha data structure.
 *
 * Each component is represented as a byte. This data structure is used to build cxutil::Color
 * objects.
 *
 * @note The validity of the fields is not checked as part of an RGBA object construction. It is
 *       the responsibility of the caller to make sure all fields are properly populated.
 *
 * @see cxutil::Color
 *
 *************************************************************************************************/
struct RGBA
{
    RGBA(uint8_t p_red, uint8_t p_green, uint8_t p_blue, uint8_t p_alpha);

    uint8_t m_red   = 0x00;
    uint8_t m_green = 0x00;
    uint8_t m_blue  = 0x00;
    uint8_t m_alpha = 0xFF;
};


/**********************************************************************************************//**
 * @brief Hue-Saturation-Lightness-Alpha data structure.
 *
 * Each component is represented as a floating point number from 0.0 to 1.0. The hue is the
 * normalized angle from 0 to 2π (0°-360°). The saturation lightness and alpha are percentages.
 *
 * @note The validity of the fields is not checked as part of an HSLA object construction. It is
 *       the responsibility of the caller to make sure all fields are properly populated.
 *
 * @see cxutil::Color
 *
 *
 *************************************************************************************************/
struct HSLA
{
    HSLA(double p_hue, double m_saturation, double m_lightness, double m_alpha);

    double m_hue        = 0.0;
    double m_saturation = 0.0;
    double m_lightness  = 0.0;
    double m_alpha      = 1.0;
};


/***********************************************************************************************//**
 * @class Color
 *
 * @brief An HTML compliant color class.
 *
 * A Color object is composed of 32 bits defining its position on the RGBA spectrum. Of the 32 
 * bits, 8 are for the red component, 8 are for the green component, 8 are for the blue component 
 * and 8 are for the alpha component, which defines opacity. The absence of color is represented as
 * the Color object for which all four RGBA components are set to 0. Note that the 32-bits
 * composing the color are contiguous in memory.
 *
 * See https://www.w3schools.com/colors/colors_hex.asp for more information.
 *
 **************************************************************************************************/
class Color final
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
     * Constructor with RGBA components.
     *
     * @param[in] p_rgba The RGBA components (packaged as a @c struct ) that compose the Color.
     *
     * @see RGBA
     *
     **********************************************************************************************/
    Color(const RGBA& p_rgba);


    /*******************************************************************************************//**
     * Constructor with HSLA components.
     *
     * @param[in] p_hsla The HSLA components (packaged as a @c struct ) that compose the Color.
     *
     * @pre All HSLA components stored in p_hsla are in the interval [0.0, 1.0].
     *
     * @see HSLA
     *
     **********************************************************************************************/
    Color(const HSLA& p_hsla);


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
    uint8_t r() const {return m_rgba[ColorIndex::RED];}


    /*******************************************************************************************//**
     * Green component accessor.
     *
     * @return The Color's green component value (8 bits).
     *
     **********************************************************************************************/
    uint8_t g() const {return m_rgba[ColorIndex::GREEN];}


    /*******************************************************************************************//**
     * Blue component accessor.
     *
     * @return The Color's blue component value (8 bits).
     *
     **********************************************************************************************/
    uint8_t b() const {return m_rgba[ColorIndex::BLUE];}


    /*******************************************************************************************//**
     * Alpha component accessor.
     *
     * @return The Color's alpha component value (8 bits).
     *
     **********************************************************************************************/
    uint8_t a() const {return m_rgba[ColorIndex::ALPHA];}


    /*******************************************************************************************//**
     * @brief Hue component accessor.
     *
     * @return The Color's hue component value (0.0 to 1.0).
     *
     **********************************************************************************************/
    double hue() const;


    /*******************************************************************************************//**
     * @brief Saturation component accessor.
     *
     * @return The Color's saturation component value (0.0 to 1.0).
     *
     **********************************************************************************************/
    double saturation() const;


    /*******************************************************************************************//**
     * @brief Lightness component accessor.
     *
     * @return The Color's lightness component value (0.0 to 1.0).
     *
     **********************************************************************************************/
    double lightness() const;


    /*******************************************************************************************//**
     * Alpha component accessor.
     *
     * This accessor is much like the @c a() accessor, but instead of returning the alpha value
     * as a byte, it returns it as a @c normalized double.
     *
     * @return The Color's alpha component value (0.0 to 1.0).
     *
     * @see a()
     *
     **********************************************************************************************/
    double alpha() const;

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


private:

    void checkInvariant() const;

    /***********************************************************************************************
     * @brief Color index enumeration.
     *
     * Use this index to help get the right Color component from the @c m_rgba member table.
     *
     **********************************************************************************************/
    enum ColorIndex
    {
        RED,
        GREEN,
        BLUE,
        ALPHA
    };

    std::array<uint8_t, 4> m_rgba{{0x00, 0x00, 0x00, 0xFF}}; ///< RGBA Color components (in order):
                                                             ///< red, green, blue, alpha.
                                                             ///<

    static_assert(sizeof(m_rgba) == 4, "The RGBA color is more than 32-bits.");

};


///{ @name Helper functions

/***********************************************************************************************//**
 * @brief Normalize color components.
 *
 * Normalizes color components in the [0, 1] interval.
 *
 * @param[in]  p_color The color to normalize.
 * @param[out] p_red   The normalized red component.
 * @param[out] p_green The normalized green component.
 * @param[out] p_blue  The normalized blue component.
 * @param[out] p_alpha The normalized alpha component.
 *
 * @post @c p_red is in the interval [0.0, 1.0].
 * @post @c p_green is in the interval [0.0, 1.0].
 * @post @c p_blue is in the interval [0.0, 1.0].
 * @post @c p_alpha is in the interval [0.0, 1.0].
 *
 * @see denormalize
 *
 **************************************************************************************************/
void normalize(const Color& p_color,
               double& p_red,
               double& p_green,
               double& p_blue,
               double& p_alpha);


/*******************************************************************************************//**
 * Constructor with normalized parameters.
 *
 * @param[in] p_red    The normalized red component.
 * @param[in] p_green  The normalized green component.
 * @param[in] p_blue   The normalized blue component.
 * @param[in] p_alpha  The normalized alpha (opacity) component.
 *
 * @return A color whose components are approximately represents the normalized values
 *         on 32 bits.
 *
 * @pre p_red is in the interval [0.0, 1.0]
 * @pre p_green is in the interval [0.0, 1.0]
 * @pre p_blue is in the interval [0.0, 1.0]
 * @pre p_alpha is in the interval [0.0, 1.0]
 *
 * @see normalize
 *
 **********************************************************************************************/
Color denormalize(const double p_red,
                  const double p_green,
                  const double p_blue,
                  const double p_alpha);

///@}

} // namespace cxutil

#endif /* COLOR_H_52B8DD85_78C2_40D9-9354_8BA481E96E38 */
