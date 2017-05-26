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

#include "../publicAPI/Disc.h"

USING_NAMESPACE_STD
USING_NAMESPACE_CXBASE


bool Disc::operator==(const Disc &p_disc) const
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

bool Disc::operator!=(const Disc &p_disc) const
{
    return !(*this == p_disc);
}

BEGIN_CXBASE_NAMESPACE

ostream& operator<<(ostream& p_flux, const Disc& p_disc)
{

    p_flux << " " << p_disc.asciiColorCode() << " ";

    return p_flux;
}

END_CXBASE_NAMESPACE
