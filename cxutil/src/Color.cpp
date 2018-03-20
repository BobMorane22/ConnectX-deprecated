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
 * @file    Color.cpp
 * @author  Eric Poirier
 * @date    April 2017
 * @version 1.0
 *
 * Implementation for a color utility.
 *
 **************************************************************************************************/

#include <cmath>

#include <algorithm>

#include "../include/Color.h"
#include "../include/narrow_cast.h"
#include "../include/ContractException.h"


namespace
{

/**********************************************************************************************//**
 * @brief Converts the representation of a color the HSLA spectrum to the RGBA spectrum.
 *
 * @param[in] p_hsla A structure containing the HSLA color components.
 *
 * @pre Every component in the p_hsla structure is in the interval [0.0, 1.0].
 *
 * @post The RGBA structure that is constructed from the input HSLA structure represents the
 *       same Color as the input HSLA structure.
 *
 * Source: https://stackoverflow.com/questions/2353211/hsl-to-rgb-color-conversion
 *
 *************************************************************************************************/
cxutil::RGBA hslaToRgba(const cxutil::HSLA& p_hsla)
{
    PRECONDITION(p_hsla.m_hue        >= 0.0);
    PRECONDITION(p_hsla.m_saturation >= 0.0);
    PRECONDITION(p_hsla.m_lightness  >= 0.0);
    PRECONDITION(p_hsla.m_alpha      >= 0.0);

    PRECONDITION(p_hsla.m_hue        <= 1.0);
    PRECONDITION(p_hsla.m_saturation <= 1.0);
    PRECONDITION(p_hsla.m_lightness  <= 1.0);
    PRECONDITION(p_hsla.m_alpha      <= 1.0);

    double red, green, blue;

    if(p_hsla.m_saturation == 0.0)
    {
        red   = p_hsla.m_lightness;
        green = p_hsla.m_lightness;
        blue  = p_hsla.m_lightness;
    }
    else
    {
        const auto hue2rgb {[](double p, double q, double t)
             {
                 if(t < 0.0)
                 {
                     t += 1.0;
                 }

                 if(t > 1.0)
                 {
                     t -= 1;
                 }

                 if(t < 1.0/6.0)
                 {
                     return p + (q - p) * 6.0 * t;
                 }

                 if(t < 1.0/2.0)
                 {
                     return q;
                 }

                 if(t < 2.0/3.0)
                 {
                     return p + (q - p) * (2.0/3.0 - t) * 6.0;
                 }

                 return p;
             }};

        double q;

        if(p_hsla.m_lightness < 0.5)
        {
            q = p_hsla.m_lightness * (1.0 + p_hsla.m_saturation);
        }
        else
        {
            q = p_hsla.m_lightness + p_hsla.m_saturation - p_hsla.m_lightness * p_hsla.m_saturation;
        }

        const double p{2.0 * p_hsla.m_lightness - q};

        red   = hue2rgb(p, q, p_hsla.m_hue + 1.0/3.0);
        green = hue2rgb(p, q, p_hsla.m_hue          );
        blue  = hue2rgb(p, q, p_hsla.m_hue - 1.0/3.0);
    }

    const uint8_t r{cxutil::narrow_cast<uint8_t>(std::round(red            * 255.0))};
    const uint8_t g{cxutil::narrow_cast<uint8_t>(std::round(green          * 255.0))};
    const uint8_t b{cxutil::narrow_cast<uint8_t>(std::round(blue           * 255.0))};
    const uint8_t a{cxutil::narrow_cast<uint8_t>(std::round(p_hsla.m_alpha * 255.0))};

    return cxutil::RGBA{r, g, b, a};
}


/**********************************************************************************************//**
 * @brief Converts the representation of a color the RGBA spectrum to the HSLA spectrum.
 *
 * @param[in] p_rgba A structure containing the RGBA color components.
 *
 * @post The HSLA structure that is constructed from the input RGBA structure represents the
 *       same Color as the input RGBA structure.
 *
 * Source: https://stackoverflow.com/questions/2353211/hsl-to-rgb-color-conversion
 *
 *************************************************************************************************/
cxutil::HSLA rgbaToHsla(const cxutil::RGBA& p_rgba)
{
    const double r{p_rgba.m_red   / 255.0};
    const double g{p_rgba.m_green / 255.0};
    const double b{p_rgba.m_blue  / 255.0};

    const double maximum = std::max(std::max(r, g), b);
    const double minimum = std::min(std::min(r, g), b);

    double h, s;
    const double l{(maximum + minimum) / 2.0};

    if(maximum == minimum)
    {
        h = s = 0.0;
    }
    else
    {
        double  d{maximum - minimum};

        if(l > 0.5)
        {
            s = d / (2.0 - maximum - minimum);
        }
        else
        {
            s = d / (maximum + minimum);
        }

        if(maximum == r)
        {
            h = (g - b) / d + (g < b ? 6.0 : 0.0);
        }
        else if(maximum == g)
        {
            h = (b - r) / d + 2.0;
        }
        else if (maximum == b)
        {
            h = (r - g) / d + 4.0;
        }

        h /= 6.0;
    }

    const double a{static_cast<double>(p_rgba.m_alpha) / 255.0};

    return cxutil::HSLA{h, s, l, a};
}

} // anonymous namespace


cxutil::RGBA::RGBA(uint8_t p_red, uint8_t p_green, uint8_t p_blue, uint8_t p_alpha) :
                   m_red{p_red},
                   m_green{p_green},
                   m_blue{p_blue},
                   m_alpha{p_alpha}
{
}


cxutil::HSLA::HSLA(double p_hue, double p_saturation, double p_lightness, double p_alpha) :
                   m_hue{p_hue},
                   m_saturation{p_saturation},
                   m_lightness{p_lightness},
                   m_alpha{p_alpha}
{
}


cxutil::Color::Color() = default;


cxutil::Color::Color(const RGBA& p_rgba) : m_rgba{{p_rgba.m_red, p_rgba.m_green, p_rgba.m_blue, p_rgba.m_alpha}}
{
    INVARIANTS();
}


cxutil::Color::Color(const HSLA& p_hsla)
{
    PRECONDITION(p_hsla.m_hue        >= 0.0);
    PRECONDITION(p_hsla.m_saturation >= 0.0);
    PRECONDITION(p_hsla.m_lightness  >= 0.0);
    PRECONDITION(p_hsla.m_alpha      >= 0.0);

    PRECONDITION(p_hsla.m_hue        <= 1.0);
    PRECONDITION(p_hsla.m_saturation <= 1.0);
    PRECONDITION(p_hsla.m_lightness  <= 1.0);
    PRECONDITION(p_hsla.m_alpha      <= 1.0);

    const RGBA rgba{hslaToRgba(p_hsla)};

    m_rgba[ColorIndex::RED]   = rgba.m_red;
    m_rgba[ColorIndex::GREEN] = rgba.m_green;
    m_rgba[ColorIndex::BLUE]  = rgba.m_blue;
    m_rgba[ColorIndex::ALPHA] = rgba.m_alpha;
}


cxutil::Color::~Color() = default;


double cxutil::Color::hue() const
{
    const RGBA rgba{m_rgba[ColorIndex::RED],
                    m_rgba[ColorIndex::GREEN],
                    m_rgba[ColorIndex::BLUE],
                    m_rgba[ColorIndex::ALPHA]};

    HSLA hlsa{rgbaToHsla(rgba)};

    return hlsa.m_hue;
}


double cxutil::Color::saturation() const
{
    const RGBA rgba{m_rgba[ColorIndex::RED],
                    m_rgba[ColorIndex::GREEN],
                    m_rgba[ColorIndex::BLUE],
                    m_rgba[ColorIndex::ALPHA]};

    HSLA hlsa{rgbaToHsla(rgba)};

    return hlsa.m_saturation;
}


double cxutil::Color::lightness() const
{
    const RGBA rgba{m_rgba[ColorIndex::RED],
                    m_rgba[ColorIndex::GREEN],
                    m_rgba[ColorIndex::BLUE],
                    m_rgba[ColorIndex::ALPHA]};

    HSLA hlsa{rgbaToHsla(rgba)};

    return hlsa.m_lightness;
}


double cxutil::Color::alpha() const
{
    return narrow_cast<double>(m_rgba[ColorIndex::ALPHA]) / 255.0;
}


bool cxutil::Color::operator==(const cxutil::Color& p_color) const
{
    bool sameColor{false};

    if(m_rgba[ColorIndex::RED]   == p_color.r() &&
       m_rgba[ColorIndex::GREEN] == p_color.g() &&
       m_rgba[ColorIndex::BLUE]  == p_color.b() &&
       m_rgba[ColorIndex::ALPHA] == p_color.a()    )
    {
        sameColor = true;
    }

    return sameColor;
}


bool cxutil::Color::operator!=(const cxutil::Color& p_color) const
{
    return !(*this == p_color);
}


const cxutil::Color& cxutil::Color::transparent()
{
    static const cxutil::Color TRANSPARENT{RGBA{0xFF, 0xFF, 0xFF, 0x00}};

    return TRANSPARENT;
}


const cxutil::Color& cxutil::Color::white()
{
    static const cxutil::Color WHITE{RGBA{0xFF, 0xFF, 0xFF, 0xFF}};

    return WHITE;
}


const cxutil::Color& cxutil::Color::black()
{
    static const cxutil::Color BLACK{RGBA{0x00 , 0x00 , 0x00 , 0xFF}};

    return BLACK;
}


const cxutil::Color& cxutil::Color::green()
{
    static const cxutil::Color GREEN{RGBA{0x00 , 0xFF, 0x00 , 0xFF}};

    return GREEN;
}


const cxutil::Color& cxutil::Color::red()
{
    static const cxutil::Color RED{RGBA{0xFF, 0x00 , 0x00 , 0xFF}};

    return RED;
}


const cxutil::Color& cxutil::Color::yellow()
{
    static const cxutil::Color YELLOW{RGBA{0xFF, 0xFF, 0x00 , 0xFF}};

    return YELLOW;
}


const cxutil::Color& cxutil::Color::blue()
{
    static const cxutil::Color BLUE{RGBA{0x00 , 0x00 , 0xFF, 0xFF}};

    return BLUE;
}


void cxutil::Color::checkInvariant() const
{
}


void cxutil::normalize(const cxutil::Color& p_color,
                       double& p_red,
                       double& p_green,
                       double& p_blue,
                       double& p_alpha)
{
    p_red   = cxutil::narrow_cast<double>(p_color.r()) / 255.0;
    p_green = cxutil::narrow_cast<double>(p_color.g()) / 255.0;
    p_blue  = cxutil::narrow_cast<double>(p_color.b()) / 255.0;
    p_alpha = cxutil::narrow_cast<double>(p_color.a()) / 255.0;

    POSTCONDITION(p_red   >= 0.0);
    POSTCONDITION(p_green >= 0.0);
    POSTCONDITION(p_blue  >= 0.0);
    POSTCONDITION(p_alpha >= 0.0);

    POSTCONDITION(p_red   <= 1.0);
    POSTCONDITION(p_green <= 1.0);
    POSTCONDITION(p_blue  <= 1.0);
    POSTCONDITION(p_alpha <= 1.0);
}


cxutil::Color cxutil::denormalize(const double p_red,
                                  const double p_green,
                                  const double p_blue,
                                  const double p_alpha)
{
    PRECONDITION(p_red   >= 0.0);
    PRECONDITION(p_green >= 0.0);
    PRECONDITION(p_blue  >= 0.0);
    PRECONDITION(p_alpha >= 0.0);

    PRECONDITION(p_red   <= 1.0);
    PRECONDITION(p_green <= 1.0);
    PRECONDITION(p_blue  <= 1.0);
    PRECONDITION(p_alpha <= 1.0);

    uint8_t red   {cxutil::narrow_cast<uint8_t>(std::round(p_red * 255.0))  };
    uint8_t green {cxutil::narrow_cast<uint8_t>(std::round(p_green * 255.0))};
    uint8_t blue  {cxutil::narrow_cast<uint8_t>(std::round(p_blue * 255.0)) };
    uint8_t alpha {cxutil::narrow_cast<uint8_t>(std::round(p_alpha * 255.0))};

    return Color{RGBA{red, green, blue, alpha}};
}
