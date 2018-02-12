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
     * @param p_backgroundColor
     * @param p_fillColor
     * @param p_hasBorder
     * @param p_borderColor
     * @param p_borderThickness
     * @param p_borderStyle
     *
     **********************************************************************************************/
    GeometricShape(const cxutil::Color& p_backgroundColor ,
                   const cxutil::Color& p_fillColor       ,
                   bool p_hasBorder                       ,
                   const cxutil::Color& p_borderColor     ,
                   double p_borderThickness               ,
                   BorderStyle p_borderStyle
                   );

    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    virtual ~GeometricShape();

///@}


protected:

///@{ @name Visual representation

    /*******************************************************************************************//**
     * @brief
     *
     **********************************************************************************************/
    virtual void draw(const Cairo::RefPtr<Cairo::Context>& p_context) = 0;


    /*******************************************************************************************//**
     * @brief
     *
     **********************************************************************************************/
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& p_context) override final;


///@}


///@{ @name Data members

    // Background:
    cxutil::Color m_backgroundColor;        ///<

    // Body:
    cxutil::Color m_fillColor;              ///<

    // Border:
    bool          m_hasBorder;              ///<
    cxutil::Color m_borderColor;            ///<
    double        m_borderThinkness;        ///<
    BorderStyle   m_borderStyle;            ///<

///@}

};

} // namespace cxgui

#endif // IGEOMETRICSHAPE_H_312A51F3_19BC_48E4_BA7E_5DD0F0908D27
