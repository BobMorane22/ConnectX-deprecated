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
 * @file    test_util.cpp
 * @author  Eric Poirier
 * @date    July 2018
 * @version 1.0
 *
 * Unit tests for temporary utilities (to be refactored once the UI is more stable).
 *
 **************************************************************************************************/

#include <string>

#include <cxutil/include/Color.h>

#include <gtest/gtest.h>

#include "../../include/util.h"


TEST(util, buildGdkColorString_ColorRed_ReturnsStringForRed)
{
    const std::string stringRed{"rgba(255, 0, 0, 255)"};

    ASSERT_TRUE(stringRed == cx::ui::buildGdkColorString(cxutil::Color::red()));
}


TEST(util, buildGdkColorString_ColorGreen_ReturnsStringForGreen)
{
    const std::string stringGreen{"rgba(0, 255, 0, 255)"};

    ASSERT_TRUE(stringGreen == cx::ui::buildGdkColorString(cxutil::Color::green()));
}


TEST(util, buildGdkColorString_ColorBlue_ReturnsStringForBlue)
{
    const std::string stringBlue{"rgba(0, 0, 255, 255)"};

    ASSERT_TRUE(stringBlue == cx::ui::buildGdkColorString(cxutil::Color::blue()));
}


TEST(util, buildGdkColorString_ColorAlpha_ReturnsStringForAlpha)
{
    const std::string stringTransparent{"rgba(0, 0, 255, 255)"};

    ASSERT_TRUE(stringTransparent == cx::ui::buildGdkColorString(cxutil::Color::transparent()));
}
