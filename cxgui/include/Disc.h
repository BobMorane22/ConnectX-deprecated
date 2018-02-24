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
 * @brief Customizable disc shapes that can be drawn to the screen.
 *
 * A disc is a geometric shape which is defined by a circular border.
 *
 * @see GeometricShape
 *
 **************************************************************************************************/
class Disc : public GeometricShape
{

public:

    /*******************************************************************************************//**
     * @brief Constructor with parameters.
     *
     * Construct a cxgui::Disc object. By default, a black disc with a blue background is
     * constructed.
     *
     * @param[in] p_fillColor        The fill color.
     * @param[in] p_backgroundColor  The background color.
     * @param[in] p_borderColor      The border color (show if the border is visible).
     * @param[in] p_hasBorder        Visible state of the border.
     * @param[in] p_borderThickness  Thickness of the border.
     * @param[in] p_borderStyle      The border line style.
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
     * @brief Default destructor.
     *
     **********************************************************************************************/
    virtual ~Disc();


private:

    /*******************************************************************************************//**
     * @brief Draws the circular border for the Disc.
     *
     * @param[in] p_context The Cairo::Context passed from the drawing handler.
     *
     **********************************************************************************************/
    virtual void drawBorder(const Cairo::RefPtr<Cairo::Context>& p_context) override;


    /*******************************************************************************************//**
     * @brief Checks class invariants.
     *
     **********************************************************************************************/
    virtual void checkInvariant() const override;

};

} // namespace cxgui


#endif // DISC_H_533131F6_7FFA_4A0F_B794_8536167052AC
