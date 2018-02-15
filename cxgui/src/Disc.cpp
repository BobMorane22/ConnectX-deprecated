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


cxgui::Disc::Disc(const cxutil::Color& p_fillColor,
                  const cxutil::Color& p_backgroundColor,
                  const cxutil::Color& p_borderColor,
                  bool p_hasBorder,
                  double p_borderThickness,
                  cxgui::BorderStyle p_borderStyle
                  ) : cxgui::GeometricShape(p_fillColor,
                                            p_backgroundColor,
                                            p_borderColor,
                                            p_hasBorder,
                                            p_borderThickness,
                                            p_borderStyle)
{
}


cxgui::Disc::~Disc() = default;


void cxgui::Disc::drawBorder(const Cairo::RefPtr<Cairo::Context>& p_context)
{
    const Gtk::Allocation allocation{get_allocation()};

    const int width{allocation.get_width()};
    const int height{allocation.get_height()};
    const int smallestDimension{std::min(width, height)};

    const int xCenter{width / 2};
    const int yCenter{height / 2};

    p_context->arc(xCenter,
                   yCenter,
                   smallestDimension / 2.5,
                   0.0,
                   2.0 * M_PI);

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

        p_context->stroke_preserve();
    }
}


void cxgui::Disc::checkInvariant() const
{

}
