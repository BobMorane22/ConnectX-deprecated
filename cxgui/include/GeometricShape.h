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
 * Interface for a simple and closed geometric shape widget utility.
 *
 **************************************************************************************************/

#ifndef GEOMETRICSHAPE_H_312A51F3_19BC_48E4_BA7E_5DD0F0908D27
#define GEOMETRICSHAPE_H_312A51F3_19BC_48E4_BA7E_5DD0F0908D27

#include <gtkmm/drawingarea.h>

#include <cxutil/include/Color.h>

namespace cxgui
{

/*******************************************************************************************//**
 * @brief Defines the shape's border.
 *
 * This functor needs to be defined by any child class to define how the border, for the
 * particular geometric shape represented by that child class, will be drawn. This method
 * is automatically called by @c draw(). Here is an example to get a centered circle
 * shape:
 *
 *   @code
 *
 *       // Get information abount the containing widget:
 *       const Gtk::Allocation allocation{get_allocation()};
 *
 *       // Calculate needed dimensions:
 *       const int width{allocation.get_width()};
 *       const int height{allocation.get_height()};
 *       const int smallestDimension{std::min(width, height)};
 *
 *       const int xCenter{width / 2};
 *       const int yCenter{height / 2};
 *
 *       // Setup the shape:
 *       p_context->arc(xCenter,
 *                      yCenter,
 *                      smallestDimension / 2.5,
 *                      0.0,
 *                      2.0 * M_PI);
 *
 *       p_context->close_path();
 *
 *   @endcode
 *
 * @param[in] p_context The Cairo::Context passed from the drawing handler.
 *
 * @see draw
 *
 **********************************************************************************************/
using BorderDrawer = std::function<void(const Cairo::RefPtr<Cairo::Context>& p_context)>;


/***********************************************************************************************//**
 * @brief Border styles for shapes.
 *
 * Available border line styles used to draw a GeometricShape's border. Available styles are:
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
 * regions. The border must be a simple and closed curve. The border, although it always exists,
 * might not be visible.
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
     * @param[in] p_fillColor        The fill color.
     * @param[in] p_backgroundColor  The background color.
     * @param[in] p_borderColor      The border color (show if the border is visible).
     * @param[in] p_hasBorder        Visible state of the border.
     * @param[in] p_borderThickness  Thickness of the border.
     * @param[in] p_borderStyle      The border line style.
     * @param[in] p_drawBorder       The border drawing functor.
     *
     * @pre The border thickness is a positive real number(verified when @c on_draw() is called).
     * @pre The border is a simple and closed curve.
     *
     * @see cx::BorderStyle
     *
     **********************************************************************************************/
    GeometricShape(const cxutil::Color& p_fillColor       ,
                   const cxutil::Color& p_backgroundColor ,
                   const cxutil::Color& p_borderColor     ,
                   bool p_hasBorder                       ,
                   double p_borderThickness               ,
                   BorderStyle p_borderStyle              ,
                   BorderDrawer p_drawBorder
                   );


    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     * Destructs the geometric shape. Note that the destructor is pure virtual.
     *
     **********************************************************************************************/
    virtual ~GeometricShape() = 0;

///@}


protected:

///@{ @name Shape Actions and Properties.

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
     * @brief Sets a new fill region Color.
     *
     * @param[in] p_newFillColor The new fill region Color.
     *
     *********************************************************************************************/
    void changeFillColor(const cxutil::Color& p_newFillColor);


    /******************************************************************************************//**
     * @brief Accesses the active fill region Color.
     *
     * @return The active the fill region Color.
     *
     *********************************************************************************************/
    cxutil::Color fillColor() const { return m_fillColor; };


    /******************************************************************************************//**
     * @brief Sets a new background region Color.
     *
     * @param[in] p_newBackgroundColor The new background region Color.
     *
     *********************************************************************************************/
    void changeBackgroundColor(const cxutil::Color& p_newBackgroundColor);


    /******************************************************************************************//**
     * Accesses the active background region color.
     *
     * @return The active background region Color.
     *
     *********************************************************************************************/
    cxutil::Color backgroundColor() const { return m_backgroundColor; };


    /******************************************************************************************//**
     * @brief Sets a new border Color.
     *
     * @param[in] p_newBorderColor The new border Color.
     *
     *********************************************************************************************/
    void changeBorderColor(const cxutil::Color& p_newBorderColor);


    /******************************************************************************************//**
     * @brief Accesses the active border Color.
     *
     * @return The active border Color.
     *
     *********************************************************************************************/
    cxutil::Color borderColor() const { return m_borderColor; };


    /******************************************************************************************//**
     * Sets a new border style.
     *
     * @param[in] p_newBorderStyle The new boarder style.
     *
     *********************************************************************************************/
    void changeBorderStyle(BorderStyle p_newBorderStyle);


    /******************************************************************************************//**
     * Checks if the geometric shape has an active border.
     *
     * @return @c true if the border is active, @c false otherwise.
     *
     *********************************************************************************************/
    bool hasBorder() const { return m_hasBorder; }


    /******************************************************************************************//**
     * Checks if the border style is SOLID.
     *
     * @return @c true if the border style is SOLID, @c false otherwise.
     *
     *********************************************************************************************/
    bool isBorderSolid() const { return m_borderStyle == BorderStyle::SOLID; };


    /******************************************************************************************//**
     * Checks if the border style is DOTTED.
     *
     * @return @c true if the border style is DOTTED, @c false otherwise.
     *
     * @see BoarderStyle
     *
     *********************************************************************************************/
    bool isBorderDotted() const { return m_borderStyle == BorderStyle::DOTTED; };


    /******************************************************************************************//**
     * Checks if the border style is DASHED.
     *
     * @return @c true if the border style is DASHED, @c false otherwise.
     *
     * @see BoarderStyle
     *
     *********************************************************************************************/
    bool isBorderDashed() const { return m_borderStyle == BorderStyle::DASHED; };


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


private:

///@{ @name Automatic Drawing Process

    bool on_draw            (const Cairo::RefPtr<Cairo::Context>& p_context) override final;
    void draw               (const Cairo::RefPtr<Cairo::Context>& p_context);
    void drawBackgroundColor(const Cairo::RefPtr<Cairo::Context>& p_context);
    void drawFillColor      (const Cairo::RefPtr<Cairo::Context>& p_context);

///@}

///@{ @name Contract

    bool isTheBorderASimpleAndClosedCurve() const;
    virtual void checkInvariant() const override;

///@}

///@{ @name Data Members

        // Body:
        cxutil::Color m_fillColor;              ///< The fill color.

        // Background:
        cxutil::Color m_backgroundColor;        ///< The background color.

        // Border:
        cxutil::Color m_borderColor;            ///< The border color.
        bool          m_hasBorder;              ///< The border's visible state.
        double        m_borderThickness;        ///< The border thickness.
        BorderStyle   m_borderStyle;            ///< The border line style (see BorderStyle).
        BorderDrawer  m_drawBorder;             ///< The border drawing functor.

///@}

};

} // namespace cxgui

#endif // IGEOMETRICSHAPE_H_312A51F3_19BC_48E4_BA7E_5DD0F0908D27
