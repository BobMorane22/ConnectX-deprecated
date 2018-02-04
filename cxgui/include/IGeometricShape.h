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
 * @file    IGeometricShape.h
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Pure interface for a geometric shape widget utility.
 *
 **************************************************************************************************/


#ifndef IGEOMETRICSHAPE_H_312A51F3_19BC_48E4_BA7E_5DD0F0908D27
#define IGEOMETRICSHAPE_H_312A51F3_19BC_48E4_BA7E_5DD0F0908D27


class Cairo::RefPtr<Cairo::Context>;


namespace cxgui
{

/***********************************************************************************************//**
 * @brief Basis for geometric shape widget implementations.
 *
 * All geometric shapes, wether a pure shape (e.g. a circle) or a filled shape (e.g. a disc)
 * need to provide a way to draw itself to the screen. This pure interface enforces fullfilment
 * of this need in all derived classes.
 *
 **************************************************************************************************/
class IGeometricShape
{

public:

    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    virtual ~IGeometricShape();


protected:

    /*******************************************************************************************//**
     * @brief Draws the caller widget.
     *
     * Provides instructions on how to draw the the geometric shape widget defined by the caller.
     *
     **********************************************************************************************/
    virtual void draw(const Cairo::RefPtr<Cairo::Context>& p_context) = 0;
};

} // namespace cxgui

#endif // IGEOMETRICSHAPE_H_312A51F3_19BC_48E4_BA7E_5DD0F0908D27
