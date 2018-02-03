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

#include "../include/Color.h"
#include "../include/narrow_cast.h"


cxutil::Color::Color() = default;


cxutil::Color::Color(int p_red,  int p_green, int p_blue, int p_alpha) : m_red{p_red}, m_green{p_green}, m_blue{p_blue}, m_alpha{p_alpha}
{
    PRECONDITION(p_red   >= 0);
    PRECONDITION(p_green >= 0);
    PRECONDITION(p_blue  >= 0);
    PRECONDITION(p_alpha >= 0);

    PRECONDITION(p_red   < 256);
    PRECONDITION(p_green < 256);
    PRECONDITION(p_blue  < 256);
    PRECONDITION(p_alpha < 256);

    POSTCONDITION(m_red   == p_red);
    POSTCONDITION(m_green == p_green);
    POSTCONDITION(m_blue  == p_blue);
    POSTCONDITION(m_alpha == p_alpha);

    INVARIANTS();
}


cxutil::Color::~Color() = default;


bool cxutil::Color::operator==(const cxutil::Color& p_color) const
{
    bool sameColor{false};

    if(m_red == p_color.m_red && m_green == p_color.m_green &&
       m_blue == p_color.m_blue && m_alpha == p_color.m_alpha)
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
    static const cxutil::Color TRANSPARENT{255, 255, 255, 0};

    return TRANSPARENT;
}


const cxutil::Color& cxutil::Color::white()
{
    static const cxutil::Color WHITE{255, 255, 255, 255};

    return WHITE;
}


const cxutil::Color& cxutil::Color::black()
{
    static const cxutil::Color BLACK{0  , 0  , 0  , 255};

    return BLACK;
}


const cxutil::Color& cxutil::Color::green()
{
    static const cxutil::Color GREEN{0  , 128, 0  , 255};

    return GREEN;
}


const cxutil::Color& cxutil::Color::red()
{
    static const cxutil::Color RED{255, 0  , 0  , 255};

    return RED;
}


const cxutil::Color& cxutil::Color::yellow()
{
    static const cxutil::Color YELLOW{255, 255, 0  , 255};

    return YELLOW;
}


const cxutil::Color& cxutil::Color::blue()
{
    static const cxutil::Color BLUE{0  , 0  , 255, 255};

    return BLUE;
}


void cxutil::Color::checkInvariant() const
{
    INVARIANT(m_red   >= 0);
    INVARIANT(m_green >= 0);
    INVARIANT(m_blue  >= 0);
    INVARIANT(m_alpha >= 0);

    INVARIANT(m_red   < 256);
    INVARIANT(m_green < 256);
    INVARIANT(m_blue  < 256);
    INVARIANT(m_alpha < 256);
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
    POSTCONDITION(p_red   <= 1.0);
    POSTCONDITION(p_green >= 0.0);
    POSTCONDITION(p_green <= 1.0);
    POSTCONDITION(p_blue  >= 0.0);
    POSTCONDITION(p_blue  <= 1.0);
    POSTCONDITION(p_alpha >= 0.0);
    POSTCONDITION(p_alpha <= 1.0);
}
