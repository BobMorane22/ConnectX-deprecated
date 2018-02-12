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
 * @file    Disc.cpp
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Implementation for a disc widget utility.
 *
 **************************************************************************************************/

#include <algorithm>
#include <cmath>
#include <vector>

#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>

#include <cxutil/include/Assertion.h>

#include "../include/Disc.h"


cxgui::Disc::Disc(const cxutil::Color& p_backgroundColor,
                  const cxutil::Color& p_fillColor,
                  bool p_hasBorder,
                  const cxutil::Color& p_borderColor,
                  double p_borderThickness,
                  cxgui::BorderStyle p_borderStyle
                  ) : cxgui::GeometricShape(p_backgroundColor,
                                            p_fillColor,
                                            p_hasBorder,
                                            p_borderColor,
                                            p_borderThickness,
                                            p_borderStyle)
{
}


cxgui::Disc::~Disc() = default;


void cxgui::Disc::draw(const Cairo::RefPtr<Cairo::Context>& p_context)
{
    // Get space allocated by parent widget to the Disc:
    const Gtk::Allocation allocation{get_allocation()};

    const int width{allocation.get_width()};
    const int height{allocation.get_height()};
    const int smallestDimension{std::min(width, height)};

    // Get allocated space center position coordinates:
    const int xCenter{width / 2};
    const int yCenter{height / 2};

    // Get every color's individual components:
    double bgRed, bgGreen, bgBlue, bgAlpha;
    cxutil::normalize(m_backgroundColor, bgRed, bgGreen, bgBlue, bgAlpha);

    double fillRed, fillGreen, fillBlue, fillAlpha;
    cxutil::normalize(m_fillColor, fillRed, fillGreen, fillBlue, fillAlpha);

    // If a border is required, change the border thickness according to
    // parent dimensions to allow smooth resizing of the border as the
    // parent is resized:
    if(m_hasBorder)
    {
        p_context->set_line_width(smallestDimension * m_borderThinkness);
    }

    // Define and draw the background:
    p_context->save();

    p_context->set_source_rgba(bgRed, bgGreen, bgBlue, bgAlpha);

    p_context->move_to(0, 0);
    p_context->line_to(width, 0);
    p_context->line_to(width, height);
    p_context->line_to(0, height);
    p_context->line_to(0, 0);

    p_context->fill();

    p_context->restore();

    // Define and draw the disc:
    p_context->save();

    p_context->arc(xCenter,
                   yCenter,
                   smallestDimension / 2.5,
                   0.0,
                   2.0 * M_PI);

    // If a border is required, it needs to be drawn. It is drawn here:
    if(m_hasBorder)
    {
        double bdrRed, bdrGreen, bdrBlue, bdrAlpha;
        cxutil::normalize(m_borderColor, bdrRed, bdrGreen, bdrBlue, bdrAlpha);

        p_context->set_source_rgba(bdrRed, bdrGreen, bdrBlue, bdrAlpha);

        switch(m_borderStyle)
        {
            case BorderStyle::SOLID:
            {
                break;
            }
            case BorderStyle::DOTTED:
            {
                double nbPointsOn{5.0};
                double nbPointsOff{nbPointsOn};

                const std::vector<double> pattern {nbPointsOn, nbPointsOff};
                p_context->set_dash(pattern, 0.0);

                break;
            }
            case BorderStyle::DASHED:
            {
                double nbPointsOn{10.0};
                double nbPointsOff{nbPointsOn};

                const std::vector<double> pattern {nbPointsOn, nbPointsOff};
                p_context->set_dash(pattern, 0.0);

                break;
            }
            default:
                CX_ASSERT_MSG(false, "Unsupported border style.");
        }

        // Draw the line:
        p_context->stroke_preserve();
    }

    // We fill the disc here:
    p_context->set_source_rgba(fillRed, fillGreen, fillBlue, fillAlpha);
    p_context->fill_preserve();

    p_context->restore();
}
