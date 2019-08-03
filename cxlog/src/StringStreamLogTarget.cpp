/***************************************************************************************************
 *
 * Copyright (C) 2019 Connect X team
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
 * @file    StringStreamLogTarget.cpp
 * @author  Eric Poirier
 * @date    July 2019
 * @version 1.0
 *
 * String stream log target. With this target, you can log to a string.
 *
 **************************************************************************************************/

#include <cxinv/include/assertion.h>

#include "../include/StringStreamLogTarget.h"


cxlog::StringStreamLogTarget::StringStreamLogTarget(std::ostringstream& p_stringStream)
 : m_stringStream{p_stringStream}
{
}


void cxlog::StringStreamLogTarget::log(const std::string& p_message)
{
    if(stringStream())
    {
        stringStream() << p_message;

        return;
    }

    ASSERT_ERROR_MSG("String stream not valid.");
}
