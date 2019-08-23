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
 * @file    ChainLogger.cpp
 * @author  Eric Poirier
 * @date    July 2019
 * @version 1.0
 *
 * Logger using a chain of responsability to forward its logging information to another
 * logger.
 *
 **************************************************************************************************/

#include "../include/ChainLogger.h"


void cxlog::ChainLogger::setSucessor(std::unique_ptr<ILogger>&& p_sucessor)
{
    m_successor = std::move(p_sucessor);
}


bool cxlog::ChainLogger::hasSucessor() const
{
    if(m_successor != nullptr)
    {
        return true;
    }

    return false;
}
