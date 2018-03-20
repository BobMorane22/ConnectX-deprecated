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

#include <cxutil/include/narrow_cast.h>

#include "../include/CXDisc.h"


cx::ui::CXDisc::CXDisc(const cxutil::Color& p_fillColor,
                       const cxutil::Color& p_backgroundColor,
                       const cxutil::Color& p_borderColor) :
                       cxgui::Disc(p_fillColor,
                                   p_backgroundColor,
                                   p_borderColor)
{
}


cx::ui::CXDisc::~CXDisc() = default;


void cx::ui::CXDisc::highlight()
{
    const double darkerFill      {fillColor().lightness()};
    const double darkerBackground{backgroundColor().lightness()};

    const double highlightedFill      {darkerFill < 0.85 ? darkerFill + 0.15 : 1.00 };
    const double highlightedBackground{darkerBackground < 0.85 ? darkerBackground + 0.15 : 1.00 };

    changeFillColor(cxutil::Color{cxutil::HSLA{fillColor().hue(),
                                               fillColor().saturation(),
                                               highlightedFill,
                                               fillColor().alpha()}});

    changeBackgroundColor(cxutil::Color{cxutil::HSLA{backgroundColor().hue(),
                                                     backgroundColor().saturation(),
                                                     highlightedBackground,
                                                     backgroundColor().alpha()}});
}


void cx::ui::CXDisc::removeHighlighting()
{
    const double highlightedFill      {fillColor().lightness()};
    const double highlightedBackground{backgroundColor().lightness()};

    const double darkerFill      {highlightedFill < 0.15 ? 1.00 : highlightedFill - 0.15 };
    const double darkerBackground{highlightedBackground < 0.15 ? 1.00 : highlightedBackground - 0.15 };

    changeFillColor(cxutil::Color{cxutil::HSLA{fillColor().hue(),
                                               fillColor().saturation(),
                                               darkerFill,
                                               fillColor().alpha()}});

    changeBackgroundColor(cxutil::Color{cxutil::HSLA{backgroundColor().hue(),
                                                     backgroundColor().saturation(),
                                                     darkerBackground,
                                                     backgroundColor().alpha()}});
}
