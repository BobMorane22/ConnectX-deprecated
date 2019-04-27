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


#include <cxutil/include/ContractException.h>
#include <cxutil/include/LineSegment.h>

#include "../include/GeometricShape.h"


cxgui::GeometricShape::GeometricShape(const cxutil::Color& p_fillColor       ,
                                      const cxutil::Color& p_backgroundColor ,
                                      const cxutil::Color& p_borderColor     ,
                                      bool p_hasBorder                       ,
                                      double p_borderThickness               ,
                                      BorderStyle p_borderStyle              ,
                                      bool p_fillOnlyVisibleBackground
                                      )
 : m_fillColor{p_fillColor}
 , m_backgroundColor{p_backgroundColor}
 , m_borderColor{p_borderColor}
 , m_hasBorder{p_hasBorder}
 , m_borderThickness{p_borderThickness}
 , m_borderStyle{p_borderStyle}
 , m_fillOnlyVisibleBackground{p_fillOnlyVisibleBackground}
{
    PRECONDITION(p_borderThickness >= 0);
}


cxgui::GeometricShape::~GeometricShape() = default;


void cxgui::GeometricShape::reDraw()
{
    DrawingArea::queue_draw();
}


void cxgui::GeometricShape::changeFillColor(const cxutil::Color& p_newFillColor)
{
    m_fillColor = p_newFillColor;

    INVARIANTS();
}


void cxgui::GeometricShape::changeBackgroundColor(const cxutil::Color& p_newBackgroundColor)
{
    m_backgroundColor = p_newBackgroundColor;

    INVARIANTS();
}


void cxgui::GeometricShape::changeBorderColor(const cxutil::Color& p_newBorderColor)
{
    m_backgroundColor = p_newBorderColor;

    INVARIANTS();
}


void cxgui::GeometricShape::changeBorderStyle(BorderStyle p_newBorderStyle)
{
    m_borderStyle = p_newBorderStyle;

    INVARIANTS();
}


void cxgui::GeometricShape::showBorder()
{
    m_hasBorder = true;

    INVARIANTS();
}


void cxgui::GeometricShape::removeBorder()
{
    m_hasBorder = false;

    INVARIANTS();
}


bool cxgui::GeometricShape::on_draw(const Cairo::RefPtr<Cairo::Context>& p_context)
{
    draw(p_context);

    INVARIANTS();

    return true;
}


/*******************************************************************************************//**
 * @brief Draws the geometric shape.
 *
 * This is the actual method doing all the drawing.
 *
 * @param[in] p_context The Cairo::Context passed from the drawing handler.
 *
 **********************************************************************************************/
void cxgui::GeometricShape::draw(const Cairo::RefPtr<Cairo::Context>& p_context) const
{
    const Gtk::Allocation allocation{get_allocation()};

    const int width{allocation.get_width()};
    const int height{allocation.get_height()};
    const int smallestDimension{std::min(width, height)};

    drawBackgroundColor(p_context);
    drawFillColor(p_context);

    // If a border is required, change the border thickness according to
    // parent dimensions to allow smooth resizing of the border as the
    // parent is resized:
    if(m_hasBorder)
    {
        p_context->set_line_width(smallestDimension * 2 * m_borderThickness);
    }

    p_context->save();
    drawBorder(p_context);

    if(m_hasBorder)
    {
        double bdrRed, bdrGreen, bdrBlue, bdrAlpha;
        cxutil::normalize(borderColor(), bdrRed, bdrGreen, bdrBlue, bdrAlpha);

        p_context->set_source_rgba(bdrRed, bdrGreen, bdrBlue, bdrAlpha);


        if(isBorderSolid())
        {
            // Nothing to do!
        }
        else if(isBorderDotted())
        {
            double nbPointsOn{5.0};
            double nbPointsOff{nbPointsOn};

            const std::vector<double> pattern{nbPointsOn, nbPointsOff};
            p_context->set_dash(pattern, 0.0);
        }
        else if(isBorderDashed())
        {
            double nbPointsOn{10.0};
            double nbPointsOff{nbPointsOn};

            const std::vector<double> pattern{nbPointsOn, nbPointsOff};
            p_context->set_dash(pattern, 0.0);
        }
        else
        {
            CX_ASSERT_MSG(false, "Unsupported border style.");
        }

        p_context->stroke_preserve();
    }

    p_context->restore();
}


/*******************************************************************************************//**
 * @brief Draws the initial background color for the geometric shape.
 *
 * This is called as a sub part of the @c draw() method.
 *
 * @param[in] p_context The Cairo::Context passed from the drawing handler.
 *
 * @see draw
 *
 **********************************************************************************************/
void cxgui::GeometricShape::drawBackgroundColor(const Cairo::RefPtr<Cairo::Context>& p_context) const
{
    p_context->save();
    drawBorder(p_context);

    double bgRed, bgGreen, bgBlue, bgAlpha;
    cxutil::normalize(m_backgroundColor, bgRed, bgGreen, bgBlue, bgAlpha);
    p_context->set_source_rgba(bgRed, bgGreen, bgBlue, bgAlpha);

    const Gtk::Allocation allocation{get_allocation()};
    const int width{allocation.get_width()};
    const int height{allocation.get_height()};

    p_context->move_to(0    , 0     );
    p_context->line_to(width, 0     );
    p_context->line_to(width, height);
    p_context->line_to(0    , height);
    p_context->line_to(0    , 0     );

    if(m_fillOnlyVisibleBackground)
    {
        p_context->set_fill_rule(Cairo::FILL_RULE_EVEN_ODD);
    }

    p_context->fill();
    p_context->restore();
}


/*******************************************************************************************//**
 * @brief Draws the initial fill color for the geometric shape.
 *
 * This is called as a sub part of the @c draw() method.
 *
 * @param[in] p_context The Cairo::Context passed from the drawing handler.
 *
 * @see draw
 *
 **********************************************************************************************/
void cxgui::GeometricShape::drawFillColor(const Cairo::RefPtr<Cairo::Context>& p_context) const
{
    double fillRed, fillGreen, fillBlue, fillAlpha;
    cxutil::normalize(m_fillColor, fillRed, fillGreen, fillBlue, fillAlpha);

    p_context->set_source_rgba(fillRed, fillGreen, fillBlue, fillAlpha);

    drawBorder(p_context);
    p_context->fill();
}


/*******************************************************************************************//**
 * @brief Checks the class invariants.
 *
 * Checks that the border thickness is a positive real number.
 *
 **********************************************************************************************/
void cxgui::GeometricShape::checkInvariant() const
{
    INVARIANT(m_borderThickness >= 0);
}
