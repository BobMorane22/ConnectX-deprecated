/***************************************************************************************************
 *
 * Copyright (C) 2018 Connect X team
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
 * @file    RAIICairoPath.cpp
 * @author  Eric Poirier
 * @date    March 2018
 * @version 1.0
 *
 * Implementation for an RAII handler of cairo paths.
 *
 **************************************************************************************************/

#include <cxutil/include/ContractException.h>

#include "../include/RAIICairoPath.h"


cxgui::RAIICairoPath::RAIICairoPath(Cairo::Path* p_pathHandle)
{
    PRECONDITION(p_pathHandle != nullptr);

    if(p_pathHandle != nullptr)
    {
        m_pathHandle = p_pathHandle;
    }
    else
    {
        m_pathHandle = nullptr;
    }
}


cxgui::RAIICairoPath::~RAIICairoPath()
{
    if(m_pathHandle != nullptr)
    {
        // Release handle accordingly:
        delete(m_pathHandle);
    }
}


cairo_path_t* cxgui::RAIICairoPath::operator->()
{
    // Gets the C handle:
    return m_pathHandle->cobj();
}


cxgui::RAIICairoPath::operator bool() const
{
    return m_pathHandle != nullptr;
}
