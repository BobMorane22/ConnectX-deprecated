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
 * @file    Name.cpp
 * @author  Eric Poirier
 * @date    November 2016
 * @version 0.1
 *
 * Implementation for a name utility.
 *
 **************************************************************************************************/

#include "../include/Name.h"

USING_NAMESPACE_STD
USING_NAMESPACE_CXUTIL

Name::Name(const std::string& p_name): m_name{p_name}
{
    PRECONDITION(!p_name.empty());

    INVARIANTS();
}

void Name::checkInvariant() const
{
    INVARIANT(!m_name.empty());
}
