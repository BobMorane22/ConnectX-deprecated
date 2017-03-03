/***********************************************************************************************//**
 * @file    AsciiColorCode.cpp
 * @author  Eric Poirier
 * @date    November 2016
 * @version 0.1
 *
 * Implementation for an ASCII color code utility.
 *
 **************************************************************************************************/

#include "../publicAPI/AsciiColorCode.h"

USING_NAMESPACE_STD
USING_NAMESPACE_CXBASE

AsciiColorCode::AsciiColorCode(char p_asciiColorCode): m_asciiColorCode{p_asciiColorCode}
{
    PRECONDITION((p_asciiColorCode >= 65 && p_asciiColorCode < 91) ||
                 (p_asciiColorCode >= 97 && p_asciiColorCode < 123) ||
                 (p_asciiColorCode == ' '));

    POSTCONDITION((m_asciiColorCode >= 65 && m_asciiColorCode < 91) ||
                  (m_asciiColorCode >= 97 && m_asciiColorCode < 123) ||
                  (m_asciiColorCode == ' '));

    INVARIANTS();
}


void AsciiColorCode::checkInvariant() const
{
    INVARIANT((m_asciiColorCode >= 65 && m_asciiColorCode < 91) ||
              (m_asciiColorCode >= 97 && m_asciiColorCode < 123) ||
              (m_asciiColorCode == ' '));
}


BEGIN_CXBASE_NAMESPACE

ostream& operator<<(ostream& p_flux, const AsciiColorCode& p_asciiColorCode)
{
    p_flux << p_asciiColorCode.m_asciiColorCode;

    return p_flux;
}

END_CXBASE_NAMESPACE
