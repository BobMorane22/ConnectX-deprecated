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

#include <algorithm>
#include <fstream>
#include <memory>
#include <sstream>
#include <tuple>

#include <cxutil/include/Assertion.h>
#include <cxutil/include/Coordinate.h>
#include <cxutil/include/narrow_cast.h>

#include <gdkmm/window.h>
#include <gtkmm/window.h>

#include "../include/GeometricShape.h"


namespace
{

using DataPoint = std::tuple<cxutil::Coordinate<double>, cxutil::Coordinate<double>>;


/***************************************************************************************************
 * @brief
 *
 **************************************************************************************************/
struct Vector
{
    double x; ///<
    double y; ///<
};


/***************************************************************************************************
 * @brief
 *
 *
 * @param p_v1
 * @param p_v2
 *
 * @return
 *
 * @todo Encapsulate this operation into a decent Vector class for linear algebra.
 *
 **************************************************************************************************/
static Vector diff(const Vector& p_v1, const Vector& p_v2)
{
    return Vector{p_v1.x - p_v2.x, p_v1.y - p_v2.y};
}


/***************************************************************************************************
 * @brief
 *
 *
 * @param p_v1
 * @param p_v2
 *
 * @return
 *
 * @todo Encapsulate this operation into a decent Vector class for linear algebra.
 *
 **************************************************************************************************/
static double crossProduct2D(const Vector& p_v1, const Vector& p_v2)
{
    return (p_v1.x * p_v2.y) - (p_v1.y * p_v2.x);
}


/***************************************************************************************************
 * @brief
 *
 *
 * @param p_v1
 * @param p_v2
 *
 * @return
 *
 * @todo Encapsulate this operation into a decent Vector class for linear algebra.
 *
 **************************************************************************************************/
static double dotProduct2D(const Vector& p_v1, const Vector& p_v2)
{
    return (p_v1.x * p_v2.x) + (p_v1.y * p_v2.y);
}

} // unamed namespace


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


bool cxgui::GeometricShape::on_draw(const Cairo::RefPtr<Cairo::Context>& p_context)
{
    CX_ASSERT_MSG(isTheBorderASimpleAndClosedCurve(), "The path you defined for your geometric "
                                                      "shape is not simple and closed.");

    draw(p_context);

    return true;
}


void cxgui::GeometricShape::draw(const Cairo::RefPtr<Cairo::Context>& p_context)
{
    const Gtk::Allocation allocation{get_allocation()};

    const int width{allocation.get_width()};
    const int height{allocation.get_height()};
    const int smallestDimension{std::min(width, height)};

    p_context->save();
    drawBackgroundColor(p_context);
    p_context->restore();

    // If a border is required, change the border thickness according to
    // parent dimensions to allow smooth resizing of the border as the
    // parent is resized:
    if(m_hasBorder)
    {
        p_context->set_line_width(smallestDimension * m_borderThinkness);
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

            const std::vector<double> pattern {nbPointsOn, nbPointsOff};
            p_context->set_dash(pattern, 0.0);
        }
        else if(isBorderDashed())
        {
            double nbPointsOn{10.0};
            double nbPointsOff{nbPointsOn};

            const std::vector<double> pattern {nbPointsOn, nbPointsOff};
            p_context->set_dash(pattern, 0.0);
        }
        else
        {
            CX_ASSERT_MSG(false, "Unsupported border style.");
        }

        p_context->stroke_preserve();
    }

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
    p_context->fill();
}


bool cxgui::GeometricShape::isTheBorderASimpleAndClosedCurve()
{
    // Get a mock context (no actual drawing needs to be done!):
    Glib::RefPtr<Gdk::Window> widgetWindow{get_window()};
    CX_ASSERT(widgetWindow);

    const Cairo::RefPtr<Cairo::Context> context{widgetWindow->create_cairo_context()};
    CX_ASSERT(context);

    // Get the underlying path as a collection of straight lines:
    drawBorder(context);
    Cairo::Path* path{context->copy_path_flat()};
    CX_ASSERT(path != nullptr);

    cairo_path_t* shapeFlatPath = path->cobj();
    CX_ASSERT(path != nullptr);

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
        const double xStart{shapeFlatPath->data[1].point.x};
        const double yStart{shapeFlatPath->data[1].point.y};

        // Get the ending point:
        const double xEnd{shapeFlatPath->data[lastIndex + 1].point.x};
        const double yEnd{shapeFlatPath->data[lastIndex + 1].point.y};

        isBorderClosed = (xStart == xEnd) &&
                         (yStart == yEnd);
    }

    // If the path is closed, we check if it is also simple:
    bool isPathSimple{true};

    if(isBorderClosed)
    {
        std::vector<DataPoint> dataPoints;

        for (int index{0}; index < shapeFlatPath->num_data; index += shapeFlatPath->data[index].header.length)
        {
            // Get points for flattened path:
            if(shapeFlatPath->data[index].header.type == CAIRO_PATH_LINE_TO ||
               shapeFlatPath->data[index].header.type == CAIRO_PATH_MOVE_TO)
            {
                const cxutil::Coordinate<double> x{shapeFlatPath->data[index + 1].point.x};
                std::cout << x.value() << "\t";

                const cxutil::Coordinate<double> y{shapeFlatPath->data[index + 1].point.y};
                dataPoints.push_back(std::make_tuple(x, y));
                std::cout << y.value() << std::endl;
            }
        }

        CX_ASSERT(!dataPoints.empty());

        // We check if the path is simple:
        //
        // Note: The algorithm used here is the one presented by Gareth Rees on this
        // Stack Overflow article:
        //
        //        https://stackoverflow.com/questions/563198/
        //                whats-the-most-efficent-way-to-calculate-where-two-line-segments-intersect
        //
        // It is simplified because we do not need to know at which point the segments intersect,
        // if they do, but only that they do.
        //
        for(int i{0}; i < cxutil::narrow_cast<int>(dataPoints.size()) - 2; ++i)
        {
            for(int j{i + 1}; j < cxutil::narrow_cast<int>(dataPoints.size()) -1; ++j)
            {
                Vector p, q, r, s;

                // First line segment:
                p.x = std::get<0>(dataPoints[i]).value();
                p.y = std::get<1>(dataPoints[i]).value();

                r.x = std::get<0>(dataPoints[i + 1]).value() - std::get<0>(dataPoints[i]).value();
                r.y = std::get<1>(dataPoints[i + 1]).value() - std::get<1>(dataPoints[i]).value();

                // Second line segment:
                q.x = std::get<0>(dataPoints[j]).value();
                q.y = std::get<1>(dataPoints[j]).value();

                s.x = std::get<0>(dataPoints[j + 1]).value() - std::get<0>(dataPoints[j]).value();
                s.y = std::get<1>(dataPoints[j + 1]).value() - std::get<1>(dataPoints[j]).value();

                bool areSegmentsIntersecting{false};

                if(crossProduct2D(r, s) == 0.0 && crossProduct2D(diff(q, p), r) == 0.0)
                {
                    std::cout << 1 << std::endl;
                    // The two lines are collinear. Are they also overlapping?
                    const double t0{dotProduct2D(diff(q, p), r) / dotProduct2D(r, r)};
                    const double t1{t0 + dotProduct2D(s, r) / dotProduct2D(r, r)};

                    const bool segmentsIntersect{(t0 > 0.0 && t0 < 1.0) && (t1 > 0.0 && t1 < 1.0)};

                    areSegmentsIntersecting |= segmentsIntersect;
                }
                else if(crossProduct2D(r, s) == 0.0 && crossProduct2D(diff(q, p), r) != 0.0)
                {
                    std::cout << 2 << std::endl;
                    // The two lines segments are parallel and non-intersecting
                }
                else if(crossProduct2D(r, s) != 0.0)
                {
                    std::cout << 3 << std::endl;
                    const double t{crossProduct2D(diff(q, p), s) / crossProduct2D(r, s)};
                    const double u{crossProduct2D(diff(q, p), r) / crossProduct2D(r, s)};
                    const bool tIn0To1{t > 0.0 && t < 1.0};
                    const bool uIn0To1{u > 0.0 && u < 1.0};

                    if(tIn0To1 && uIn0To1)
                    {
                        std::cout << 4 << std::endl;
                        areSegmentsIntersecting = true;
                        std::cout << "First segment:  " << "(" << p.x << ", " << p.y << ") and (" << r.x << ", " << r.y << ")" << std::endl;
                        std::cout << "Second segment: " << "(" << q.x << ", " << q.y << ") and (" << s.x << ", " << s.y << ")" << std::endl;
                        std::cout << "t = " << t << ", u = " << u << std::endl << std::endl;
                    }
                }
                else
                {
                    CX_ASSERT_MSG(false, "Impossible line segments configuration.");
                }

                isPathSimple &= !areSegmentsIntersecting;
            }
        }
    }

    cairo_path_destroy(shapeFlatPath);

    std::cout << "Closed: " << isBorderClosed << std::endl;
    std::cout << "Simple: " << isPathSimple   << std::endl;

    return isBorderClosed && isPathSimple;
}


void cxgui::GeometricShape::checkInvariant() const
{
    INVARIANT(m_borderThinkness >= 0);
}
