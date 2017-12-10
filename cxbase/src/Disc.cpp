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
 * @file    Disc.cpp
 * @author  Eric Poirier
 * @date    October 2016
 * @version 0.1
 *
 * Implementation for a Disc utility.
 *
 **************************************************************************************************/

#include <sstream>

#include "../include/Disc.h"


using namespace cxbase;


Disc::~Disc() = default;

bool Disc::operator==(const Disc& p_disc) const
{
    bool isEqual = false;

    if(m_color == p_disc.m_color)
    {
        if(asciiColorCode() == p_disc.asciiColorCode())
        {
            isEqual = true;
        }
    }

    return isEqual;
}


bool Disc::operator!=(const Disc& p_disc) const
{
    return !(*this == p_disc);
}


const Disc& Disc::noDisc()
{
    static const Disc NO_DISC{Color::transparent()};

    return NO_DISC;
}


const Disc& Disc::whiteDisc()
{
    static const Disc WHITE_DISC{Color::white()};

    return WHITE_DISC;
}


const Disc& Disc::blackDisc()
{
    static const Disc BLACK_DISC{Color::black()};

    return BLACK_DISC;
}


const Disc& Disc::greenDisc()
{
    static const Disc GREEN_DISC{Color::green()};

    return GREEN_DISC;
}


const Disc& Disc::redDisc()
{
    static const Disc RED_DISC{Color::red()};

    return RED_DISC;
}


const Disc& Disc::yellowDisc()
{
    static const Disc YELLOW_DISC{Color::yellow()};

    return YELLOW_DISC;
}


const Disc& Disc::blueDisc()
{
    static const Disc BLUE_DISC{Color::blue()};

    return BLUE_DISC;
}


void Disc::print(std::ostream& p_stream) const
{
    p_stream << " " << asciiColorCode() << " ";
}
