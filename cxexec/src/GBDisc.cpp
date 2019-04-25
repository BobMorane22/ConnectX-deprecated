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
 * @file    GBDisc.cpp
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Implementation for a Connect X GUI game board disc utility.
 *
 **************************************************************************************************/

#include "../include/GBDisc.h"


cx::ui::GBDisc::GBDisc() : cx::ui::Chip(cxutil::Color::black(),
                                        cxutil::Color::blue(),
                                        cxutil::Color::black())
{
}


cx::ui::GBDisc::GBDisc(const cxbase::Disc& p_backEndDisc) : Chip(p_backEndDisc.color(),
                                                                 cxutil::Color::blue())
{
}


cx::ui::GBDisc::~GBDisc() = default;


void cx::ui::GBDisc::hide()
{
    changeFillColor(cxutil::Color::black());

    reDraw();
}


void cx::ui::GBDisc::update(const cxbase::Disc& p_newBackEndDisc)
{
    changeFillColor(p_newBackEndDisc.color());

    reDraw();
}


void cx::ui::GBDisc::drawBorder(const Cairo::RefPtr<Cairo::Context>& p_context) const
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
}
