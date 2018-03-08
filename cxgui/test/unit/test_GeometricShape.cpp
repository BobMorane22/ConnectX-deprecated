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
class GeometricShapeTests : public cxgui::GeometricShape
{
public:

    /**********************************************************************************************
     * @brief
     *
     *
     *********************************************************************************************/
    GeometricShapeTests( const cxutil::Color& p_fillColor       ,
                         const cxutil::Color& p_backgroundColor ,
                         const cxutil::Color& p_borderColor     ,
                         bool p_hasBorder                       ,
                         double p_borderThickness               ,
                         cxgui::BorderStyle p_borderStyle       ,
                         cxgui::BorderDrawer p_drawBorder
                        ): GeometricShape(p_fillColor,
                                          p_backgroundColor,
                                          p_borderColor,
                                          p_hasBorder,
                                          p_borderThickness,
                                          p_borderStyle,
                                          p_drawBorder)
    {
        // Nothing to do...
    }


    /**********************************************************************************************
     * @brief
     *
     *
     *********************************************************************************************/
    virtual ~GeometricShapeTests() = default;
};


TEST(GeometricShapeTests, NothingYet)
{

}
