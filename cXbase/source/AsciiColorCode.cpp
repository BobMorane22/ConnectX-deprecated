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


void AsciiColorCode::print(ostream& p_stream) const
{
	p_stream << m_asciiColorCode;
}
