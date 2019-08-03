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
 * @file    StdLogTarget.cpp
 * @author  Eric Poirier
 * @date    July 2019
 * @version 1.0
 *
 * Standard output log target.
 *
 **************************************************************************************************/

#include <cxinv/include/assertion.h>

#include "../include/StdLogTarget.h"


void cxlog::StdLogTarget::log(const std::string& p_message)
{
    ASSERT_MSG(stdStream().good(), "Standard stream is in a bad state.");

    if(&stdStream())
    {
        stdStream() << p_message;
    }
}
