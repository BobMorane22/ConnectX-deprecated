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
#include <cxutil/include/narrow_cast.h>
#include <cxgui/include/util.h>

#include <gtest/gtest.h>


TEST(colors, buildGdkColorString_ColorRed_ReturnsStringForRed)
{
    const std::string stringRed{"rgba(255, 0, 0, 1)"};

    ASSERT_EQ(stringRed, cxgui::buildGdkColorString(cxutil::Color::red()));
}


TEST(colors, buildGdkColorString_ColorGreen_ReturnsStringForGreen)
{
    const std::string stringGreen{"rgba(0, 255, 0, 1)"};

    ASSERT_EQ(stringGreen, cxgui::buildGdkColorString(cxutil::Color::green()));
}


TEST(colors, buildGdkColorString_ColorBlue_ReturnsStringForBlue)
{
    const std::string stringBlue{"rgba(0, 0, 255, 1)"};

    ASSERT_EQ(stringBlue, cxgui::buildGdkColorString(cxutil::Color::blue()));
}


TEST(colors, buildGdkColorString_ColorAlpha_ReturnsStringForAlpha)
{
    const std::string stringTransparent{"rgba(255, 255, 255, 0)"};

    ASSERT_EQ(stringTransparent, cxgui::buildGdkColorString(cxutil::Color::transparent()));
}


TEST(colors, buildGdkColorString_ColorAlpha_ReturnsStringForAlphaNotZero)
{
    const std::string stringTransparent{"rgba(255, 255, 255, 0.2)"};

    ASSERT_EQ(stringTransparent, cxgui::buildGdkColorString(cxutil::Color{cxutil::RGBA{255, 255, 255, 51}}));
}


TEST(colors, buildDeprecatedGdkColorString_ColorRed_ReturnsStringForRed)
{
    const std::string stringRed{"#FF0000"};

    ASSERT_EQ(stringRed, cxgui::deprecated::buildGdkColorString(cxutil::Color::red()));
}


TEST(colors, buildDeprecatedGdkColorString_ColorGreen_ReturnsStringForGreen)
{
    const std::string stringGreen{"#00FF00"};

    ASSERT_EQ(stringGreen, cxgui::deprecated::buildGdkColorString(cxutil::Color::green()));
}


TEST(colors, buildDeprecatedGdkColorString_ColorBlue_ReturnsStringForBlue)
{
    const std::string stringBlue{"#0000FF"};

    ASSERT_EQ(stringBlue, cxgui::deprecated::buildGdkColorString(cxutil::Color::blue()));
}


TEST(colors, ConvertToLocalColor_SomeGdkRGBA_ReturnsEquivalentLocalColor)
{
    const cxutil::Color t_localColor{cxutil::RGBA{50, 100, 150, 200}};
    const Gdk::RGBA t_gdkColor{"rgba(50, 100, 150, 0.784313725)"};

    // Conversion:
    const cxutil::Color t_convertedColor{cxgui::convertToLocalColor(t_gdkColor)};

    ASSERT_EQ(t_localColor, t_convertedColor);
}


TEST(colors, ConvertToGdkRGBA_SomeLocalColor_ReturnsEquivalentGdkRGBA)
{
    const cxutil::Color t_localColor{cxutil::RGBA{50, 100, 150, 200}};

    // Conversion:
    const Gdk::RGBA t_convertedColor{cxgui::convertToGdkRGBA(t_localColor)};

    // Here there will be a small error when converting to Gdk::RGBA because it holds
    // 16 bits values for its RGBA values, unlike cxutil::Colors which hold 8 bits values.
    // Therefore, there is some lost during the conversion. See the conversion function
    // documentation for more details.

    // Absolute error ratio:
    const double max8bits {0xFF};
    const double max16bits{0xFFFF};

    const double absoluteErrorRatio{max8bits / max16bits};

    // Error ratios for the local color (on 8 bits):
    const double localRedRatio  {cxutil::narrow_cast<double>(t_localColor.r()) / max8bits};
    const double localGreenRatio{cxutil::narrow_cast<double>(t_localColor.g()) / max8bits};
    const double localBlueRatio {cxutil::narrow_cast<double>(t_localColor.b()) / max8bits};
    const double localAlphaRatio{cxutil::narrow_cast<double>(t_localColor.a()) / max8bits};

    // Error ratios for the Gdk color (on 16 bits):
    const double gdkConvertedRedRatio  {t_convertedColor.get_red()};
    const double gdkConvertedGreenRatio{t_convertedColor.get_green()};
    const double gdkConvertedBlueRatio {t_convertedColor.get_blue()};
    const double gdkConvertedAlphaRatio{t_convertedColor.get_alpha()};

    // Color components should, to a 8 bits factor, be within bounds:
    ASSERT_NEAR(localRedRatio  , gdkConvertedRedRatio  , absoluteErrorRatio);
    ASSERT_NEAR(localGreenRatio, gdkConvertedGreenRatio, absoluteErrorRatio);
    ASSERT_NEAR(localBlueRatio , gdkConvertedBlueRatio , absoluteErrorRatio);
    ASSERT_NEAR(localAlphaRatio, gdkConvertedAlphaRatio, absoluteErrorRatio);
}


TEST(colors, ConvertToLocalColor_SomeGdkDeprecatedColor_ReturnsEquivalentLocalColor)
{
    const cxutil::Color t_localColor{cxutil::RGBA{50, 100, 150, 255}};
    const Gdk::Color t_gdkColor{"#326496"};

    // Conversion:
    const cxutil::Color t_convertedColor{cxgui::deprecated::convertToLocalColor(t_gdkColor)};

    ASSERT_EQ(t_localColor, t_convertedColor);
}


TEST(colors, ConvertToGdkColor_SomeLocalColor_ReturnsEquivalentGdkDeprecatedColor)
{
    const cxutil::Color t_localColor{cxutil::RGBA{50, 100, 150, 255}};

    // Conversion:
    const Gdk::Color t_convertedColor{cxgui::deprecated::convertToGdkColor(t_localColor)};

    // Here there will be a small error when converting to Gdk::Color because it holds
    // 16 bits values for its RGB values, unlike cxutil::Colors which hold 8 bits values.
    // Therefore, there is some lost during the conversion. See the conversion function
    // documentation for more details.

    // Absolute error ratio:
    const double max8bits {0xFF};
    const double max16bits{0xFFFF};

    const double absoluteErrorRatio{max8bits / max16bits};

    // Error ratios for the local color (on 8 bits):
    const double localRedRatio  {cxutil::narrow_cast<double>(t_localColor.r()) / max8bits};
    const double localGreenRatio{cxutil::narrow_cast<double>(t_localColor.g()) / max8bits};
    const double localBlueRatio {cxutil::narrow_cast<double>(t_localColor.b()) / max8bits};

    // Error ratios for the Gdk color (on 16 bits):
    const double gdkConvertedRedRatio  {cxutil::narrow_cast<double>(t_convertedColor.get_red())  / max16bits};
    const double gdkConvertedGreenRatio{cxutil::narrow_cast<double>(t_convertedColor.get_green())/ max16bits};
    const double gdkConvertedBlueRatio {cxutil::narrow_cast<double>(t_convertedColor.get_blue()) / max16bits};

    // Color components should, to a 8 bits factor, be within bounds:
    ASSERT_NEAR(localRedRatio  , gdkConvertedRedRatio  , absoluteErrorRatio);
    ASSERT_NEAR(localGreenRatio, gdkConvertedGreenRatio, absoluteErrorRatio);
    ASSERT_NEAR(localBlueRatio , gdkConvertedBlueRatio , absoluteErrorRatio);
}
