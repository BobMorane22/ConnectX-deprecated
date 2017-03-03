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
