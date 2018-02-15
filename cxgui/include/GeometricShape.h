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
 * @brief Border styles for shapes.
 *
 * Available border line style used to draw a GeometricShape's border. Available styles are:
 *
 * @li @c SOLID  : ____________________
 * @li @c DOTTED : _ _ _ _ _ _ _ _ _ _
 * @li @c DASHED : __ __ __ __ __ __ __
 *
 **************************************************************************************************/
enum class BorderStyle : int
{
    SOLID,
    DOTTED,
    DASHED,
};


/***********************************************************************************************//**
 * @brief Customizable geometric shapes that can be drawn to the screen.
 *
 * A geometric shape is an external boundary (a border) defining two regions: the internal and
 * external regions. These regions are referred to respectively as the fill and the background
 * regions. The border is a line usually forming closed path. Although this condition does not
 * define a class invariant, not respecting it will result in undefined behavior as far as the
 * visual layout of the shape is concerned. In this case, you might not get a shape at all. The
 * border, although it always exists, might not be visible.
 *
 * Use this base abstract class to derive from if you need to create a geometric shape (square,
 * circle, triangle, etc) that can be drawn to the screen as an independent widget.
 *
 * @invariant The border thickness is a positive real number.
 * @invariant The border is a simple and closed curve.
 *
 **************************************************************************************************/
class GeometricShape : public Gtk::DrawingArea, public cxutil::IEnforceContract
{

public:

///@{ @name Object Construction and Destruction

    /*******************************************************************************************//**
     * @brief Constructor with parameters.
     *
     * Constructs a geometric shape with a given border, fill and background color.
     *
     * @param p_fillColor        The fill color.
     * @param p_backgroundColor  The background color.
     * @param p_borderColor      The border color (show if the border is visible).
     * @param p_hasBorder        Visible state of the border.
     * @param p_borderThickness  Thickness of the border.
     * @param p_borderStyle      The border line style.
     *
     * @pre p_borderThickness is a positive real number.
     *
     * @see cx::BorderStyle
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
     * @brief Default destructor.
     *
     * Destructs the geometric shape.
     *
     **********************************************************************************************/
    virtual ~GeometricShape();

///@}


protected:

///@{ @name Shape Actions

    /******************************************************************************************//**
     * @brief Redraw the geometric shape.
     *
     * Schedules a geometric shape redraw on the screen. This needs to be called if you made
     * changes to the shape (for example if you hid the border) and you want these changes
     * to take effect on the screen.
     *
     *********************************************************************************************/
    void reDraw();


    /******************************************************************************************//**
     * @brief Show the border.
     *
     *********************************************************************************************/
    void showBorder();


    /******************************************************************************************//**
     * @brief Hides the border.
     *
     *********************************************************************************************/
    void removeBorder();

///@}

///@{ @name Data Members

    // Body:
    cxutil::Color m_fillColor;              ///< The fill color.

    // Background:
    cxutil::Color m_backgroundColor;        ///< The background color.

    // Border:
    cxutil::Color m_borderColor;            ///< The border color.
    bool          m_hasBorder;              ///< The border's visible state.
    double        m_borderThinkness;        ///< The border thickness.
    BorderStyle   m_borderStyle;            ///< The border line style (see cx::BorderStyle).

///@}


private:

///@{ @name Automatic Drawing Process

    /*******************************************************************************************//**
     * @brief Signal handler called when the widget is to be drawn to the screen.
     *
     * This signal handler is called after the widget has been realized and needs to be drawn
     * to the screen. calling @c reDraw() will trigger this signal handler.
     *
     * @see reDraw
     *
     **********************************************************************************************/
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& p_context) override final;


    /*******************************************************************************************//**
     * @brief Draws the geometric shape.
     *
     * This is the actual method doing all the drawing. Its behavior is completely defined by the
     * the three methods: @c drawBackgroundColor(), @c drawBorder() and @c drawFillColor()
     * respectively.Overriding the @c drawBorder() method will completely define the shape.
     *
     * @see drawBackgroundColor
     * @see drawBorder
     * @see drawFillColor
     *
     **********************************************************************************************/
    void draw(const Cairo::RefPtr<Cairo::Context>& p_context);


    /*******************************************************************************************//**
     * @brief Draws the initial background color for the geometric shape.
     *
     * This is called as a sub part of the @c draw() method.
     *
     * @see draw
     *
     **********************************************************************************************/
    void drawBackgroundColor(const Cairo::RefPtr<Cairo::Context>& p_context);


    /*******************************************************************************************//**
     * @brief Draws the shape's border.
     *
     * This method needs to be overridden by any child class to define how the border, for the
     * particular geometric shape represented by that child class, will be drawn. This method
     * is automatically called by @c draw().
     *
     * @see draw
     *
     **********************************************************************************************/
    virtual void drawBorder(const Cairo::RefPtr<Cairo::Context>& p_context) = 0;


    /*******************************************************************************************//**
     * @brief Draws the initial background color for the geometric shape.
     *
     * This is called as a sub part of the @c draw() method.
     *
     * @see draw
     *
     **********************************************************************************************/
    void drawFillColor(const Cairo::RefPtr<Cairo::Context>& p_context);

///@}

///@{ @name Contract

    /*******************************************************************************************//**
     * @brief Checks the class invariants.
     *
     * Checks that:
     *
     *   @li The boarder thickness is a positive real number.
     *
     **********************************************************************************************/
    virtual void checkInvariant() const override;

///@}

};

} // namespace cxgui

#endif // IGEOMETRICSHAPE_H_312A51F3_19BC_48E4_BA7E_5DD0F0908D27
