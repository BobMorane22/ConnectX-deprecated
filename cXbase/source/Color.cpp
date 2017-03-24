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
 * @date    September 2016
 * @version 0.1
 *
 * Implementation for a color utility.
 *
 **************************************************************************************************/

#include "../publicAPI/Color.h"

USING_NAMESPACE_STD
USING_NAMESPACE_CXBASE


bool Color::operator==(const Color& p_color) const
{
    bool sameColor{false};

    if(m_name == p_color.m_name)
    {
        sameColor = true;
    }

    return sameColor;
}

bool Color::operator!=(const Color& p_color) const
{
    return !(*this == p_color);
}
