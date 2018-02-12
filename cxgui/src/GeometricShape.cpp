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
 * @file    GeometricShape.cpp
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Implementation for a geometric shape widget utility.
 *
 **************************************************************************************************/

#include "../include/GeometricShape.h"

cxgui::GeometricShape::GeometricShape(const cxutil::Color& p_backgroundColor ,
                                      const cxutil::Color& p_fillColor       ,
                                      bool p_hasBorder                       ,
                                      const cxutil::Color& p_borderColor     ,
                                      double p_borderThickness               ,
                                      BorderStyle p_borderStyle
                                      ): m_backgroundColor{p_backgroundColor},
                                         m_fillColor{p_fillColor},
                                         m_hasBorder{p_hasBorder},
                                         m_borderColor{p_borderColor},
                                         m_borderThinkness{p_borderThickness},
                                         m_borderStyle{p_borderStyle}
{
}


cxgui::GeometricShape::~GeometricShape() = default;


bool cxgui::GeometricShape::on_draw(const Cairo::RefPtr<Cairo::Context>& p_context)
{
    draw(p_context);

    return true;
}
