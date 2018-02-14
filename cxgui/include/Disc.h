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
 * @file    Disc.h
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Interface for a disc widget utility.
 *
 **************************************************************************************************/

#ifndef DISC_H_533131F6_7FFA_4A0F_B794_8536167052AC
#define DISC_H_533131F6_7FFA_4A0F_B794_8536167052AC

#include "GeometricShape.h"

namespace cxgui
{

/***********************************************************************************************//**
 * @brief
 *
 *
 **************************************************************************************************/
class Disc : public GeometricShape
{

public:

    /*******************************************************************************************//**
     *
     **********************************************************************************************/
    Disc(const cxutil::Color& p_fillColor       = cxutil::Color::black(),
         const cxutil::Color& p_backgroundColor = cxutil::Color::blue() ,
         const cxutil::Color& p_borderColor     = cxutil::Color::black(),
         bool p_hasBorder                       = true                  ,
         double p_borderThickness               = 0.02                  ,
         BorderStyle p_borderStyle              = BorderStyle::SOLID
         );


    /*******************************************************************************************//**
     *
     **********************************************************************************************/
    virtual ~Disc();


protected:

    /*******************************************************************************************//**
     *
     **********************************************************************************************/
    void draw(const Cairo::RefPtr<Cairo::Context>& p_context) override;

};

} // namespace cxgui


#endif // DISC_H_533131F6_7FFA_4A0F_B794_8536167052AC
