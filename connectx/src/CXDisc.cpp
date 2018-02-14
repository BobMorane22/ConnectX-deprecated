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
 * @file    CXDisc.cpp
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Implementation for a Connect X GUI disc utility.
 *
 **************************************************************************************************/


#include "../include/CXDisc.h"


cx::CXDisc::CXDisc(const cxutil::Color& p_fillColor,
                   const cxutil::Color& p_backgroundColor,
                   const cxutil::Color& p_borderColor) :
                       cxgui::Disc(p_fillColor,
                                   p_backgroundColor,
                                   p_borderColor)
{
}


cx::CXDisc::~CXDisc() = default;


void cx::CXDisc::updateFillColor(const cxutil::Color& p_newFillColor)
{
    // If necessary, change the fill color:
    if(m_fillColor != p_newFillColor)
    {
        m_fillColor = p_newFillColor;
    }
}


void cx::CXDisc::showBorder()
{
    m_borderColor = cxutil::Color::black();
}


void cx::CXDisc::removeBorder()
{
    m_borderColor = cxutil::Color::transparent();
}


void cx::CXDisc::reDraw()
{
    DrawingArea::queue_draw();
}
