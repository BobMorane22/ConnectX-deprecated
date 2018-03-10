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
 * @file    test_GeometricShape.cpp
 * @author  Eric Poirier
 * @date    March 2018
 * @version 1.0
 *
 * Unit tests for a the GeometricShape abstract class.
 *
 **************************************************************************************************/

#include<gtest/gtest.h>

#include "../../include/GeometricShape.h"


/**************************************************************************************************
 * @brief
 *
 *************************************************************************************************/
class GeometricShapeNotClosedTests : public cxgui::GeometricShape
{

public:

    /**********************************************************************************************
     * @brief
     *
     *
     *********************************************************************************************/
    GeometricShapeNotClosedTests( const cxutil::Color& p_fillColor       ,
                                  const cxutil::Color& p_backgroundColor ,
                                  const cxutil::Color& p_borderColor     ,
                                  bool p_hasBorder                       ,
                                  double p_borderThickness               ,
                                  cxgui::BorderStyle p_borderStyle
                                 ): GeometricShape(p_fillColor,
                                                   p_backgroundColor,
                                                   p_borderColor,
                                                   p_hasBorder,
                                                   p_borderThickness,
                                                   p_borderStyle)
    {
        // Nothing to do...
    }

private:

    /**********************************************************************************************
     * @brief
     *
     *
     *********************************************************************************************/
    virtual void drawBorder(const Cairo::RefPtr<Cairo::Context>& p_context) const override
    {
        const Gtk::Allocation allocation{get_allocation()};

        const int width{allocation.get_width()};
        const int height{allocation.get_height()};

        const int xCenter{width / 2};
        const int yCenter{height / 2};

        p_context->move_to(xCenter - width / 4, yCenter - height / 4);
        p_context->line_to(xCenter + width / 4, yCenter - height / 4);
        p_context->line_to(xCenter + width / 4, yCenter + height / 4);
    }

};


/**************************************************************************************************
 * @brief
 *
 *************************************************************************************************/
class GeometricShapeNotSimpleTests : public cxgui::GeometricShape
{

public:

    /**********************************************************************************************
     * @brief
     *
     *
     *********************************************************************************************/
    GeometricShapeNotSimpleTests( const cxutil::Color& p_fillColor       ,
                                  const cxutil::Color& p_backgroundColor ,
                                  const cxutil::Color& p_borderColor     ,
                                  bool p_hasBorder                       ,
                                  double p_borderThickness               ,
                                  cxgui::BorderStyle p_borderStyle
                                 ): GeometricShape(p_fillColor,
                                                   p_backgroundColor,
                                                   p_borderColor,
                                                   p_hasBorder,
                                                   p_borderThickness,
                                                   p_borderStyle)
    {
        // Nothing to do...
    }

private:

    /**********************************************************************************************
     * @brief
     *
     *
     *********************************************************************************************/
    virtual void drawBorder(const Cairo::RefPtr<Cairo::Context>& p_context) const override
    {
        const Gtk::Allocation allocation{get_allocation()};

        const int width{allocation.get_width()};
        const int height{allocation.get_height()};

        const int xCenter{width / 2};
        const int yCenter{height / 2};

        p_context->move_to(xCenter - width / 4, yCenter - height / 4);
        p_context->line_to(xCenter + width / 4, yCenter + height / 4);
        p_context->line_to(xCenter + width / 4, yCenter - height / 4);
        p_context->line_to(xCenter - width / 4, yCenter + height / 4);
        p_context->close_path();
    }

};


/**************************************************************************************************
 * @brief
 *
 *************************************************************************************************/
class GeometricShapeSimpleAndClosedSquareTests : public cxgui::GeometricShape
{

public:

    /**********************************************************************************************
     * @brief
     *
     *
     *********************************************************************************************/
    GeometricShapeSimpleAndClosedSquareTests( const cxutil::Color& p_fillColor       ,
                                              const cxutil::Color& p_backgroundColor ,
                                              const cxutil::Color& p_borderColor     ,
                                              bool p_hasBorder                       ,
                                              double p_borderThickness               ,
                                              cxgui::BorderStyle p_borderStyle       ,
                                              bool p_makeSureShapeIsClosed
                                             ): GeometricShape(p_fillColor,
                                                               p_backgroundColor,
                                                               p_borderColor,
                                                               p_hasBorder,
                                                               p_borderThickness,
                                                               p_borderStyle),
                                                               m_makeSureShapeIsClosed{p_makeSureShapeIsClosed}
    {
        // Nothing to do...
    }

private:

    /**********************************************************************************************
     * @brief
     *
     *
     *********************************************************************************************/
    virtual void drawBorder(const Cairo::RefPtr<Cairo::Context>& p_context) const override
    {
        const Gtk::Allocation allocation{get_allocation()};

        const int width{allocation.get_width()};
        const int height{allocation.get_height()};

        const int xCenter{width / 2};
        const int yCenter{height / 2};

        p_context->move_to(xCenter - width / 4, yCenter - height / 4);
        p_context->line_to(xCenter + width / 4, yCenter - height / 4);
        p_context->line_to(xCenter + width / 4, yCenter + height / 4);
        p_context->line_to(xCenter - width / 4, yCenter + height / 4);

        if(m_makeSureShapeIsClosed)
        {
            p_context->close_path();
        }
    }


    const bool m_makeSureShapeIsClosed; ///< Makes sure shape is closed by completing the path.

};

TEST(GeometricShapeTests, NothingYet)
{

}
