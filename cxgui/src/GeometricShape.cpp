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

cxgui::GeometricShape::GeometricShape(const cxutil::Color& p_fillColor       ,
                                      const cxutil::Color& p_backgroundColor ,
                                      const cxutil::Color& p_borderColor     ,
                                      bool p_hasBorder                       ,
                                      double p_borderThickness               ,
                                      BorderStyle p_borderStyle
                                      ): m_fillColor{p_fillColor},
                                         m_backgroundColor{p_backgroundColor},
                                         m_borderColor{p_borderColor},
                                         m_hasBorder{p_hasBorder},
                                         m_borderThinkness{p_borderThickness},
                                         m_borderStyle{p_borderStyle}
{
    PRECONDITION(m_borderThinkness >= 0);

    INVARIANTS();
}


cxgui::GeometricShape::~GeometricShape() = default;


void cxgui::GeometricShape::reDraw()
{
    DrawingArea::queue_draw();
}


void cxgui::GeometricShape::showBorder()
{
    m_hasBorder = true;
}


void cxgui::GeometricShape::removeBorder()
{
    m_hasBorder = false;
}


bool cxgui::GeometricShape::on_draw(const Cairo::RefPtr<Cairo::Context>& p_context)
{
    draw(p_context);

    return true;
}


void cxgui::GeometricShape::draw(const Cairo::RefPtr<Cairo::Context>& p_context)
{
    const Gtk::Allocation allocation{get_allocation()};

    const int width{allocation.get_width()};
    const int height{allocation.get_height()};
    const int smallestDimension{std::min(width, height)};

    // If a border is required, change the border thickness according to
    // parent dimensions to allow smooth resizing of the border as the
    // parent is resized:
    if(m_hasBorder)
    {
        p_context->set_line_width(smallestDimension * m_borderThinkness);
    }

    p_context->save();
    drawBackgroundColor(p_context);
    p_context->restore();

    p_context->save();
    drawBorder(p_context);
    drawFillColor(p_context);
    p_context->restore();
}


void cxgui::GeometricShape::drawBackgroundColor(const Cairo::RefPtr<Cairo::Context>& p_context)
{
    double bgRed, bgGreen, bgBlue, bgAlpha;
    cxutil::normalize(m_backgroundColor, bgRed, bgGreen, bgBlue, bgAlpha);
    p_context->set_source_rgba(bgRed, bgGreen, bgBlue, bgAlpha);

    const Gtk::Allocation allocation{get_allocation()};
    const int width{allocation.get_width()};
    const int height{allocation.get_height()};

    p_context->move_to(0, 0);
    p_context->line_to(width, 0);
    p_context->line_to(width, height);
    p_context->line_to(0, height);
    p_context->line_to(0, 0);

    p_context->fill();
}


void cxgui::GeometricShape::drawFillColor(const Cairo::RefPtr<Cairo::Context>& p_context)
{
    double fillRed, fillGreen, fillBlue, fillAlpha;
    cxutil::normalize(m_fillColor, fillRed, fillGreen, fillBlue, fillAlpha);

    p_context->set_source_rgba(fillRed, fillGreen, fillBlue, fillAlpha);
    p_context->fill_preserve();
}


void cxgui::GeometricShape::checkInvariant() const
{
    INVARIANT(m_borderThinkness >= 0);
}
