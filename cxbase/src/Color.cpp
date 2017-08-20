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
 * @version 0.2
 *
 * Implementation for a color utility.
 *
 **************************************************************************************************/

#include "../include/Color.h"

using namespace cxbase;

const Color Color::TRANSPARENT    {255, 255, 255, 0  , AsciiColorCode{' '}};
const Color Color::WHITE          {255, 255, 255, 255, AsciiColorCode{'W'}};
const Color Color::BLACK          {0  , 0  , 0  , 255, AsciiColorCode{'K'}};

const Color Color::GREEN          {0  , 128, 0  , 255, AsciiColorCode{'G'}};
const Color Color::RED            {255, 0  , 0  , 255, AsciiColorCode{'R'}};
const Color Color::YELLOW         {255, 255, 0  , 255, AsciiColorCode{'Y'}};
const Color Color::BLUE           {0  , 0  , 255, 255, AsciiColorCode{'B'}};

Color::Color(int p_red, int p_green,
             int p_blue, int p_alpha,
             AsciiColorCode p_asciiColorCode) :
                                               m_red{p_red},
                                               m_green{p_green},
                                               m_blue{p_blue},
                                               m_alpha{p_alpha},
                                               m_asciiColorCode{p_asciiColorCode}
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

bool Color::operator==(const Color& p_color) const
{
    bool sameColor{false};

    if(m_red == p_color.m_red && m_green == p_color.m_green &&
       m_blue == p_color.m_blue && m_alpha == p_color.m_alpha)
    {
        sameColor = true;
    }

    return sameColor;
}

bool Color::operator!=(const Color& p_color) const
{
    return !(*this == p_color);
}

void Color::checkInvariant() const
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
