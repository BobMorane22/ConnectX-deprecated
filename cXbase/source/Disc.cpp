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
