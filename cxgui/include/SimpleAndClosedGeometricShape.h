/***************************************************************************************************
 *
 * Copyright (C) 2019 Connect X team
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
 * @file    SimpleAndClosedGeometricShape.h
 * @author  Eric Poirier
 * @date    January 2019
 * @version 1.0
 *
 * Interface for a simple and closed geometric shape widget utility.
 *
 **************************************************************************************************/

#ifndef SIMPLEANDCLOSEDGEOMETRICSHAPE_H_1A10D65E_8666_416C_8DE0_8EBFEB4FB24B
#define SIMPLEANDCLOSEDGEOMETRICSHAPE_H_1A10D65E_8666_416C_8DE0_8EBFEB4FB24B

#include "GeometricShape.h"

namespace cxgui
{


/***********************************************************************************************//**
 * @brief Customizable simple and closed geometric shapes that can be drawn to the screen.
 *
 * A geometric shape is simple and closed if no two points (except the start and endpoint) lie on
 * top of each other and if both start and end points are the same.
 *
 * Use this base abstract class to derive from if you need to create a simple and closedgeometric
 * shape (square, circle, triangle, etc) that can be drawn to the screen as an independent widget.
 * Override the @c drawBorder() method to define your own shape. Note that if the shape defined
 * in your @c drawBorder() method is not simple and closed, an assertion will occur on construction.
 *
 * @see cxgui::GeometricShape#drawBorder
 *
 **************************************************************************************************/
class SimpleAndClosedGeometricShape : public cxgui::GeometricShape
{

public:

///@{ @name Object Construction and Destruction

    /*******************************************************************************************//**
     * @brief Constructor with parameters.
     *
     * Constructs a geometric shape with a given border, fill and background color.
     *
     * @param[in] p_fillColor                  The fill color.
     * @param[in] p_backgroundColor            The background color.
     * @param[in] p_borderColor                The border color (show if the border is visible).
     * @param[in] p_hasBorder                  Visible state of the border.
     * @param[in] p_borderThickness            Thickness of the border.
     * @param[in] p_borderStyle                The border line style.
     * @param[in] p_fillOnlyVisibleBackground  Fill option: fill whole background, or only the
     *                                         visible background (around the shape).
     *
     * @pre The border thickness is a positive real number(verified when @c on_draw() is called).
     *
     * @see cx::BorderStyle
     *
     **********************************************************************************************/
    SimpleAndClosedGeometricShape(const cxutil::Color& p_fillColor       ,
                                  const cxutil::Color& p_backgroundColor ,
                                  const cxutil::Color& p_borderColor     ,
                                  bool p_hasBorder                       ,
                                  double p_borderThickness               ,
                                  BorderStyle p_borderStyle              ,
                                  bool p_fillOnlyVisibleBackground = false
                                  );


    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     * Destructs the geometric shape.
     *
     **********************************************************************************************/
    virtual ~SimpleAndClosedGeometricShape() override;

///@}


private:

///@{ @name Automatic Drawing Process

    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& p_context) override final;

    bool isTheBorderASimpleAndClosedCurve() const;

///@}


///@{ @name Data Members

    mutable bool  m_simpleAndClosedCheckDone;  // Flag that makes sure the method
                                               // 'isTheBorderASimpleAndClosedCurve()'
                                               // is called at least once. It is mutable
                                               // because its value is modified at the
                                               // end of that method, which is const. This
                                               // check needs not be repeated because it
                                               // is very expensive, and useless to perform
                                               // more than once.

///@}

};

} // namespace cxgui

#endif // SIMPLEANDCLOSEDGEOMETRICSHAPE_H_1A10D65E_8666_416C_8DE0_8EBFEB4FB24B
