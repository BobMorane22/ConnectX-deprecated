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
 * @file    SimpleAndClosedGeometricShape.cpp
 * @author  Eric Poirier
 * @date    January 2019
 * @version 1.0
 *
 * Implementation for a simple and closed geometric shape widget utility.
 *
 **************************************************************************************************/


#include <cxutil/include/LineSegment.h>

#include "../include/SimpleAndClosedGeometricShape.h"
#include "../include/RAIICairoPath.h"


cxgui::SimpleAndClosedGeometricShape::SimpleAndClosedGeometricShape(const cxutil::Color& p_fillColor       ,
                                                                    const cxutil::Color& p_backgroundColor ,
                                                                    const cxutil::Color& p_borderColor     ,
                                                                    bool p_hasBorder                       ,
                                                                    double p_borderThickness               ,
                                                                    BorderStyle p_borderStyle              ,
                                                                    bool p_fillOnlyVisibleBackground
                                                                    )
 : GeometricShape(p_fillColor       ,
                  p_backgroundColor ,
                  p_borderColor     ,
                  p_hasBorder       ,
                  p_borderThickness ,
                  p_borderStyle     ,
                  p_fillOnlyVisibleBackground
   )
 , m_simpleAndClosedCheckDone{false}
{
    // Nothing to do...
}


cxgui::SimpleAndClosedGeometricShape::~SimpleAndClosedGeometricShape() = default;


/*******************************************************************************************//**
 * @brief Signal handler called when the widget is to be drawn to the screen.
 *
 * This signal handler is called after the widget has been realized and needs to be drawn
 * to the screen. Calling @c reDraw() will trigger this signal handler.
 *
 * @param[in] p_context The Cairo::Context passed from the drawing handler.
 *
 * @see GeometricShape#reDraw
 *
 **********************************************************************************************/
bool cxgui::SimpleAndClosedGeometricShape::on_draw(const Cairo::RefPtr<Cairo::Context>& p_context)
{
    // Call the parent handler:
    cxgui::GeometricShape::on_draw(p_context);

    if(!m_simpleAndClosedCheckDone)
    {
        CX_ASSERT_MSG(isTheBorderASimpleAndClosedCurve(), "The geometric shape you are attempting "
                                                          "to draw is either not closed or not "
                                                          "simple.");
    }

    return true;
}


/*******************************************************************************************//**
 * @brief Checks if the border is a simple and closed curve.
 *
 * In other words, it checks that the drawn shape defines a simple and closed curve,
 * i.e. a curve for which the starting point is the ending point and such that no other
 * two points on the curve are the same.
 *
 * @return @c true if the border defined in @c drawBorder() is a simple and closed curve,
 *         @c false otherwise.
 *
 **********************************************************************************************/
bool cxgui::SimpleAndClosedGeometricShape::isTheBorderASimpleAndClosedCurve() const
{
    // Get a mock context (no actual drawing needs to be done!):
    Cairo::RefPtr<Cairo::Surface> mockSurface{Cairo::ImageSurface::create(Cairo::Format::FORMAT_A8, 200, 200)};
    CX_ASSERT(mockSurface);

    Cairo::RefPtr<Cairo::Context> context{Cairo::Context::create(mockSurface)};
    CX_ASSERT(context);

    // Get the underlying path as a collection of straight lines:
    drawBorder(context);

    cxgui::RAIICairoPath shapeFlatPath{context->copy_path_flat()};
    CX_ASSERT(shapeFlatPath);

    // We check if the shape is closed. To do this, we first check if there is
    // a CAIRO_PATH_CLOSE_PATH in the path data, since it does not cost much. If this
    // test is not conclusive, it might not mean the shape is not closed: maybe it
    // was closed by hand, with a call to @c line_to() instead of @c close_path(). So
    // we check if the starting point matches the ending point, to cover this case too:
    bool isBorderClosed{false};
    int lastIndex{0};

    for (int index{0}; index < shapeFlatPath->num_data; index += shapeFlatPath->data[index].header.length)
    {
        if(shapeFlatPath->data[index].header.type == CAIRO_PATH_CLOSE_PATH)
        {
            isBorderClosed = true;
        }
        if(shapeFlatPath->data[index].header.type == CAIRO_PATH_LINE_TO ||
           shapeFlatPath->data[index].header.type == CAIRO_PATH_MOVE_TO)
        {
            lastIndex = index;
        }
    }

    if(!isBorderClosed)
    {
        // Get starting point:
        const cxutil::math::Point2D startPoint{shapeFlatPath->data[1].point.x,
                                               shapeFlatPath->data[1].point.y};

        // Get the ending point:
        const cxutil::math::Point2D endPoint{shapeFlatPath->data[lastIndex + 1].point.x,
                                             shapeFlatPath->data[lastIndex + 1].point.y};

        /*! @todo This naked equality test is dangerous on <tt>double</tt>s and should be
        replaced by some kind of logical equality with some tolerance. */
        isBorderClosed = (startPoint == endPoint);
    }

    // If the path is closed, we check if it is also simple:
    bool isPathSimple{true};

    if(isBorderClosed)
    {
        std::vector<cxutil::math::Point2D> dataPoints;

        for (int index{0}; index < shapeFlatPath->num_data; index += shapeFlatPath->data[index].header.length)
        {
            // Get points for flattened path:
            if(shapeFlatPath->data[index].header.type == CAIRO_PATH_LINE_TO ||
               shapeFlatPath->data[index].header.type == CAIRO_PATH_MOVE_TO)
            {
                cxutil::math::Point2D dataPoint{shapeFlatPath->data[index + 1].point.x,
                                                shapeFlatPath->data[index + 1].point.y};

                dataPoints.push_back(std::move(dataPoint));
            }
        }

        CX_ASSERT(!dataPoints.empty());

        // We check if the path is simple:
        for(std::size_t i = 0; i < dataPoints.size() - 2; ++i)
        {
            for(std::size_t j = i + 1; j < dataPoints.size() - 1; ++j)
            {
                using namespace cxutil::math;
                
                const LineSegment2D fistSegment  {dataPoints[i], dataPoints[i + 1]};
                const LineSegment2D secondSegment{dataPoints[j], dataPoints[j + 1]};

                isPathSimple &= !cxutil::math::intersect<double>(fistSegment, secondSegment);
            }
        }
    }

    m_simpleAndClosedCheckDone = true;

    return isBorderClosed && isPathSimple;
}

