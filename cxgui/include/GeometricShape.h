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
 * @file    GeometricShape.h
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Interface for a geometric shape widget utility.
 *
 **************************************************************************************************/

#ifndef GEOMETRICSHAPE_H_312A51F3_19BC_48E4_BA7E_5DD0F0908D27
#define GEOMETRICSHAPE_H_312A51F3_19BC_48E4_BA7E_5DD0F0908D27

#include <gtkmm/drawingarea.h>

#include <cxutil/include/Color.h>

namespace cxgui
{

/***********************************************************************************************//**
 * @brief
 *
 *
 **************************************************************************************************/
enum class BorderStyle : int
{
    SOLID,
    DOTTED,
    DASHED,
};

/***********************************************************************************************//**
 * @brief
 *
 *
 **************************************************************************************************/
class GeometricShape : public Gtk::DrawingArea
{

public:

///@{ @name Object construction and destruction

    /*******************************************************************************************//**
     *
     **********************************************************************************************/
    GeometricShape(const cxutil::Color& p_fillColor       ,
                   const cxutil::Color& p_backgroundColor ,
                   const cxutil::Color& p_borderColor     ,
                   bool p_hasBorder                       ,
                   double p_borderThickness               ,
                   BorderStyle p_borderStyle
                   );

    /*******************************************************************************************//**
     *
     **********************************************************************************************/
    virtual ~GeometricShape();

///@}


protected:

///@{ @name Visual representation

    /*******************************************************************************************//**
     *
     **********************************************************************************************/
    virtual void draw(const Cairo::RefPtr<Cairo::Context>& p_context) = 0;


    /*******************************************************************************************//**
     *
     **********************************************************************************************/
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& p_context) override final;


///@}


///@{ @name Data members

    // Body:
    cxutil::Color m_fillColor;              ///<

    // Background:
    cxutil::Color m_backgroundColor;        ///<

    // Border:
    cxutil::Color m_borderColor;            ///<
    bool          m_hasBorder;              ///<
    double        m_borderThinkness;        ///<
    BorderStyle   m_borderStyle;            ///<

///@}

};

} // namespace cxgui

#endif // IGEOMETRICSHAPE_H_312A51F3_19BC_48E4_BA7E_5DD0F0908D27
