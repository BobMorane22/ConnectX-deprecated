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
 * @file    CXDisc.h
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Interface for a Connect X GUI disc utility.
 *
 **************************************************************************************************/

#ifndef CXDISC_H_72172974_77FE_4634_97FA_FB68CB3954CB
#define CXDISC_H_72172974_77FE_4634_97FA_FB68CB3954CB

#include <cxgui/include/Disc.h>

namespace cx
{

/**********************************************************************************************//**
 *
 *
 *************************************************************************************************/
class CXDisc : public cxgui::Disc
{

public:

    /******************************************************************************************//**
     *
     *
     *********************************************************************************************/
    CXDisc(const cxutil::Color& p_fillColor,
           const cxutil::Color& p_backgroundColor,
           const cxutil::Color& p_borderColor = cxutil::Color::black());


    /******************************************************************************************//**
     *
     *********************************************************************************************/
    virtual ~CXDisc();


    /******************************************************************************************//**
     *
     *********************************************************************************************/
    void updateColor(const cxutil::Color& p_newColor);


    /******************************************************************************************//**
     *
     *********************************************************************************************/
    virtual void hide() = 0;

};

} // namespace cx

#endif // CXDISC_H_72172974_77FE_4634_97FA_FB68CB3954CB
