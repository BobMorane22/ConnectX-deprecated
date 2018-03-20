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
 * @file    NDADisc.cpp
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Implementation for a Connect X GUI next disc area disc utility.
 *
 **************************************************************************************************/

#include "../include/NDADisc.h"


cx::ui::NDADisc::NDADisc() : cx::ui::CXDisc(cxutil::Color::transparent(),
                                    cxutil::Color::transparent(),
                                    cxutil::Color::transparent())
{
}


cx::ui::NDADisc::NDADisc(const cxbase::Disc& p_backEndDisc) : CXDisc(p_backEndDisc.color(),
                                                                 cxutil::Color::transparent(),
                                                                 cxutil::Color::black())
{
}


cx::ui::NDADisc::~NDADisc() = default;


void cx::ui::NDADisc::hide()
{
    changeFillColor(cxutil::Color::transparent());
    removeBorder();

    reDraw();
}


void cx::ui::NDADisc::update(const cxbase::Disc& p_newBackEndDisc)
{
    changeFillColor(p_newBackEndDisc.color());
    showBorder();

    reDraw();
}
