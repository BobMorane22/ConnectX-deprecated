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
 * Implementation for a Connect X GUI gameboard disc utility.
 *
 **************************************************************************************************/

#include "../include/GBDisc.h"


cx::GBDisc::GBDisc() : cx::CXDisc(cxutil::Color::black(), cxutil::Color::blue())
{
}


cx::GBDisc::GBDisc(const cxbase::Disc& p_backEndDisc) : CXDisc(p_backEndDisc.color(),
                                                               cxutil::Color::blue())
{
}


cx::GBDisc::~GBDisc() = default;


void cx::GBDisc::hide()
{
    updateFillColor(cxutil::Color::black());

    reDraw();
}


void cx::GBDisc::update(const cxbase::Disc& p_newBackEndDisc)
{
    updateFillColor(p_newBackEndDisc.color());

    reDraw();
}


