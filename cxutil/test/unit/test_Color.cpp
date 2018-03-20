/***************************************************************************************************
 *
 * Copyright (C) 2016 Connect X team
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
 * @file    test_Color.cpp
 * @author  Eric Poirier
 * @date    May 2017
 * @version 1.0
 * @sa https://www.w3schools.com/cssref/css_colors.asp
 *
 * Unit tests for a the Color class.
 *
 **************************************************************************************************/

#include <tuple>
#include <vector>

#include <gtest/gtest.h>

#include <cxutil/include/Color.h>
#include <cxutil/include/ContractException.h>


static const double MAX_PRECISION_RGB_8BITS{1.0/255.0};


class ColorTests: public::testing::Test
{
public:

    const cxutil::Color t_defaultColor;

    const cxutil::Color t_colorRed        {cxutil::RGBA{255, 0, 0, 255}};
    const cxutil::Color t_transparentColor{cxutil::Color::transparent()};
    const cxutil::Color t_colorPastel     {cxutil::RGBA{182, 174, 224, 200}};
};


TEST_F(ColorTests, Constructor_Default_Black)
{
    const cxutil::Color defaultColor{cxutil::RGBA{0, 0, 0, 255}};
    ASSERT_EQ(t_defaultColor, defaultColor);
}


TEST_F(ColorTests, ConstructorParamRGBA_Red_RedColor)
{
    const cxutil::Color red{cxutil::RGBA{255, 0, 0, 255}};
    ASSERT_EQ(t_colorRed, red);
}


TEST_F(ColorTests, ConstructorParamHSLA_HueBelowZero_ThrowsException)
{
    const cxutil::HSLA t_invalid{-1.0, 0.5, 0.5, 0.5};
    ASSERT_THROW((cxutil::Color{t_invalid}), PreconditionException);
}


TEST_F(ColorTests, ConstructorParamHSLA_SaturationBelowZero_ThrowsException)
{
    const cxutil::HSLA t_invalid{0.5, -1.0, 0.5, 0.5};
    ASSERT_THROW((cxutil::Color{t_invalid}), PreconditionException);
}


TEST_F(ColorTests, ConstructorParamHSLA_LightnessBelowZero_ThrowsException)
{
    const cxutil::HSLA t_invalid{0.5, 0.5, -1.0, 0.5};
    ASSERT_THROW((cxutil::Color{t_invalid}), PreconditionException);
}


TEST_F(ColorTests, ConstructorParamHSLA_AlphaBelowZero_ThrowsException)
{
    const cxutil::HSLA t_invalid{0.5, 0.5, 0.5, -1.0};
    ASSERT_THROW((cxutil::Color{t_invalid}), PreconditionException);
}


TEST_F(ColorTests, ConstructorParamHSLA_HueOverOne_ThrowsException)
{
    const cxutil::HSLA t_invalid{2.0, 0.5, 0.5, 0.5};
    ASSERT_THROW((cxutil::Color{t_invalid}), PreconditionException);
}


TEST_F(ColorTests, ConstructorParamHSLA_SaturationOverOne_ThrowsException)
{
    const cxutil::HSLA t_invalid{0.5, 2.0, 0.5, 0.5};
    ASSERT_THROW((cxutil::Color{t_invalid}), PreconditionException);
}


TEST_F(ColorTests, ConstructorParamHSLA_LightnessOverOne_ThrowsException)
{
    const cxutil::HSLA t_invalid{0.5, 0.5, 2.0, 0.5};
    ASSERT_THROW((cxutil::Color{t_invalid}), PreconditionException);
}


TEST_F(ColorTests, ConstructorParamHSLA_AlphaOverOne_ThrowsException)
{
    const cxutil::HSLA t_invalid{0.5, 0.5, 0.5, 2.0};
    ASSERT_THROW((cxutil::Color{t_invalid}), PreconditionException);
}


TEST_F(ColorTests, ConstructorParamHSLA_Red_RedColor)
{
    const cxutil::Color red{cxutil::HSLA{0.0, 1.0, 0.5, 1.0}};
    ASSERT_EQ(t_colorRed, red);
}


TEST_F(ColorTests, ConstructorParamHSLA_Pastel_PastelColor)
{
    const cxutil::Color t_pastel{cxutil::HSLA{250.0/360.0, 0.45, 0.78, 0.784}};
    ASSERT_EQ(t_pastel, t_colorPastel);
}


TEST_F(ColorTests, RedAccessor_Default_ReturnsRedComponent)
{
    ASSERT_EQ(255, t_colorRed.r());
}


TEST_F(ColorTests, GreenAccessor_Default_ReturnsGreenComponent)
{
    ASSERT_EQ(0, t_colorRed.g());
}


TEST_F(ColorTests, BlueAccessor_Default_ReturnsBlueComponent)
{
    ASSERT_EQ(0, t_colorRed.b());
}


TEST_F(ColorTests, AlphaAccessor_Default_ReturnsAlphaComponent)
{
    ASSERT_EQ(255, t_colorRed.a());
}


TEST_F(ColorTests, HueAccessor_Pastel_ReturnsHueComponent)
{
    ASSERT_NEAR(250.0/360.0, t_colorPastel.hue(), MAX_PRECISION_RGB_8BITS);
}


TEST_F(ColorTests, SaturationAccessor_Pastel_ReturnsSaturationComponent)
{
    ASSERT_NEAR(0.45, t_colorPastel.saturation(), MAX_PRECISION_RGB_8BITS);
}


TEST_F(ColorTests, LightnessAccessor_Pastel_ReturnsLightnessComponent)
{
    ASSERT_NEAR(0.78, t_colorPastel.lightness(), MAX_PRECISION_RGB_8BITS);
}


TEST_F(ColorTests, AlphaAccessor_Pastel_ReturnsNormalizedAlphaComponent)
{
    ASSERT_NEAR(0.784, t_colorPastel.alpha(), MAX_PRECISION_RGB_8BITS);
}


TEST_F(ColorTests, EqualOperator_SameColors_ReturnsTrue)
{
    const cxutil::Color t_colorOther{cxutil::RGBA{255, 0, 0, 255}};
    ASSERT_TRUE(t_colorRed == t_colorOther);
}


TEST_F(ColorTests, EqualOperator_DifferentRedElementOnly_ReturnsFalse)
{
    const cxutil::Color t_colorOther{cxutil::RGBA{254, 0, 0, 255}};
    ASSERT_FALSE(t_colorRed == t_colorOther);
}


TEST_F(ColorTests, EqualOperator_DifferentGreenElementOnly_ReturnsFalse)
{
    const cxutil::Color t_colorOther{cxutil::RGBA{255, 1, 0, 255}};
    ASSERT_FALSE(t_colorRed == t_colorOther);
}


TEST_F(ColorTests, EqualOperator_DifferentBlueElementOnly_ReturnsFalse)
{
    const cxutil::Color t_colorOther{cxutil::RGBA{255, 0, 1, 255}};
    ASSERT_FALSE(t_colorRed == t_colorOther);
}


TEST_F(ColorTests, EqualOperator_DifferentAlphaElementOnly_ReturnsFalse)
{
    const cxutil::Color t_colorOther{cxutil::RGBA{255, 0, 0, 254}};
    ASSERT_FALSE(t_colorRed == t_colorOther);
}


TEST_F(ColorTests, EqualOperator_DifferentAsciiColorCodeOnly_ReturnsTrue)
{
    const cxutil::Color t_colorOther{cxutil::RGBA{255, 0, 0, 255}};
    ASSERT_TRUE(t_colorRed == t_colorOther);
}


TEST_F(ColorTests, NotEqualOperator_SameColors_ReturnsFalse)
{
    const cxutil::Color t_colorOther{cxutil::RGBA{255, 0, 0, 255}};
    ASSERT_FALSE(t_colorRed != t_colorOther);
}


TEST_F(ColorTests, NotEqualOperator_DifferentRedElementOnly_ReturnsTrue)
{
    const cxutil::Color t_colorOther{cxutil::RGBA{254, 0, 0, 255}};
    ASSERT_TRUE(t_colorRed != t_colorOther);
}


TEST_F(ColorTests, NotEqualOperator_DifferentGreenElementOnly_ReturnsTrue)
{
    const cxutil::Color t_colorOther{cxutil::RGBA{255, 1, 0, 255}};
    ASSERT_TRUE(t_colorRed != t_colorOther);
}


TEST_F(ColorTests, NotEqualOperator_DifferentBlueElementOnly_ReturnsTrue)
{
    const cxutil::Color t_colorOther{cxutil::RGBA{255, 0, 1, 255}};
    ASSERT_TRUE(t_colorRed != t_colorOther);
}


TEST_F(ColorTests, NotEqualOperator_DifferentAlphaElementOnly_ReturnsTrue)
{
    const cxutil::Color t_colorOther{cxutil::RGBA{255, 0, 0, 254}};
    ASSERT_TRUE(t_colorRed != t_colorOther);
}


TEST(Color, Normalize_SemiTransparentGrey_RGBAOneHalf)
{
    const double t_rWanted{127.0 / 255.0};
    const double t_gWanted{127.0 / 255.0};
    const double t_bWanted{127.0 / 255.0};
    const double t_aWanted{127.0 / 255.0};

    const cxutil::Color semiTransparentGrey{cxutil::RGBA{127, 127, 127, 127}};

    double t_rResult, t_gResult, t_bResult, t_aResult;

    cxutil::normalize(semiTransparentGrey, t_rResult, t_gResult, t_bResult, t_aResult);

    ASSERT_EQ(t_rWanted, t_rResult);
    ASSERT_EQ(t_gWanted, t_gResult);
    ASSERT_EQ(t_bWanted, t_bResult);
    ASSERT_EQ(t_aWanted, t_aResult);
}


TEST(Color, Normalize_OpaqueBlack_RGBOnesAndAZero)
{
    const double t_rWanted{1.0};
    const double t_gWanted{1.0};
    const double t_bWanted{1.0};
    const double t_aWanted{0.0};

    const cxutil::Color opaqueBlack{cxutil::RGBA{255, 255, 255, 0}};

    double t_rResult, t_gResult, t_bResult, t_aResult;

    cxutil::normalize(opaqueBlack, t_rResult, t_gResult, t_bResult, t_aResult);

    ASSERT_EQ(t_rWanted, t_rResult);
    ASSERT_EQ(t_gWanted, t_gResult);
    ASSERT_EQ(t_bWanted, t_bResult);
    ASSERT_EQ(t_aWanted, t_aResult);
}


TEST(Color, Denormalize_OnesAndAZero_OpaqueBlack)
{
    const double t_red  {1.0};
    const double t_green{1.0};
    const double t_blue {1.0};
    const double t_alpha{0.0};

    const cxutil::Color t_opaqueBlack{cxutil::RGBA{255, 255, 255, 0}};

    ASSERT_TRUE(t_opaqueBlack == cxutil::denormalize(t_red, t_green, t_blue, t_alpha));
}


TEST(Color, Denormalize_StandardComponents_RepresentativeColor)
{
    const double t_red  {0.2345};
    const double t_green{0.5679};
    const double t_blue {0.1107};
    const double t_alpha{0.8976};

    const cxutil::Color t_representative{cxutil::RGBA{60, 145, 28, 229}};

    ASSERT_TRUE(t_representative == cxutil::denormalize(t_red, t_green, t_blue, t_alpha));
}

/***************************************************************************************************
 * This special test makes sure map between the RGBA color space and the HSLA color
 * space always work for sample colors across the whole spectrum. Some limit cases
 * are also included. If this test passes, you can be relatively sure the RGBA/HSLA
 * mapping mechanism has not been broken. Go ahead and add some cases if you wish,
 * as long as it has not already been tested! this link:
 *
 *         https://www.rapidtables.com/convert/color/rgb-to-hsl.html
 *
 * can help quickly adding test cases...
 *
 **************************************************************************************************/
TEST(Color, RGBAtoHSLAMappingMechanish_ColorsAcrossSpectrum_ConversionsWork)
{
    using ColorList = std::vector<std::tuple<cxutil::Color, cxutil::Color>>;

    using namespace cxutil;

    const ColorList t_equalColors{
        std::make_tuple(Color{RGBA{0  , 0  , 0  , 255}}, Color{HSLA{0.00       , 0.00, 0.00, 1.00}}),
        std::make_tuple(Color{RGBA{0  , 102, 102, 255}}, Color{HSLA{0.50       , 1.00, 0.20, 1.00}}),
        std::make_tuple(Color{RGBA{51 , 102, 102, 255}}, Color{HSLA{0.50       , 0.33, 0.30, 1.00}}),
        std::make_tuple(Color{RGBA{102, 102, 102, 255}}, Color{HSLA{0.00       , 0.00, 0.40, 1.00}}),
        std::make_tuple(Color{RGBA{153, 102, 102, 255}}, Color{HSLA{0.00       , 0.20, 0.50, 1.00}}),
        std::make_tuple(Color{RGBA{204, 102, 102, 255}}, Color{HSLA{0.00       , 0.50, 0.60, 1.00}}),
        std::make_tuple(Color{RGBA{255, 102, 102, 255}}, Color{HSLA{0.00       , 1.00, 0.70, 1.00}}),
        std::make_tuple(Color{RGBA{102, 0  , 102, 255}}, Color{HSLA{300.0/360.0, 1.00, 0.20, 1.00}}),
        std::make_tuple(Color{RGBA{102, 51 , 102, 255}}, Color{HSLA{300.0/360.0, 0.33, 0.30, 1.00}}),
        std::make_tuple(Color{RGBA{102, 153, 102, 255}}, Color{HSLA{120.0/360.0, 0.20, 0.50, 1.00}}),
        std::make_tuple(Color{RGBA{102, 204, 102, 255}}, Color{HSLA{120.0/360.0, 0.50, 0.60, 1.00}}),
        std::make_tuple(Color{RGBA{102, 255, 102, 255}}, Color{HSLA{120.0/360.0, 1.00, 0.70, 1.00}}),
        std::make_tuple(Color{RGBA{102, 102, 0  , 255}}, Color{HSLA{60.00/360.0, 1.00, 0.20, 1.00}}),
        std::make_tuple(Color{RGBA{102, 102, 51 , 255}}, Color{HSLA{60.00/360.0, 0.33, 0.30, 1.00}}),
        std::make_tuple(Color{RGBA{102, 102, 153, 255}}, Color{HSLA{240.0/360.0, 0.20, 0.50, 1.00}}),
        std::make_tuple(Color{RGBA{102, 102, 204, 255}}, Color{HSLA{240.0/360.0, 0.50, 0.60, 1.00}}),
        std::make_tuple(Color{RGBA{102, 102, 255, 255}}, Color{HSLA{240.0/360.0, 1.00, 0.70, 1.00}}),
        std::make_tuple(Color{RGBA{255, 255, 255, 255}}, Color{HSLA{1.00       , 1.00, 1.00, 1.00}})
    };

    for(auto& equalColorSet : t_equalColors)
    {
        using namespace std;

        ASSERT_NEAR(get<0>(equalColorSet).r()         , get<1>(equalColorSet).r()         , MAX_PRECISION_RGB_8BITS);
        ASSERT_NEAR(get<0>(equalColorSet).g()         , get<1>(equalColorSet).g()         , MAX_PRECISION_RGB_8BITS);
        ASSERT_NEAR(get<0>(equalColorSet).b()         , get<1>(equalColorSet).b()         , MAX_PRECISION_RGB_8BITS);
        ASSERT_NEAR(get<0>(equalColorSet).a()         , get<1>(equalColorSet).a()         , MAX_PRECISION_RGB_8BITS);
        ASSERT_NEAR(get<0>(equalColorSet).hue()       , get<1>(equalColorSet).hue()       , MAX_PRECISION_RGB_8BITS);
        ASSERT_NEAR(get<0>(equalColorSet).saturation(), get<1>(equalColorSet).saturation(), MAX_PRECISION_RGB_8BITS);
        ASSERT_NEAR(get<0>(equalColorSet).lightness() , get<1>(equalColorSet).lightness() , MAX_PRECISION_RGB_8BITS);
    }
}


/***************************************************************************************************
 * Special test case to show that a large number of conversion does not allow for non convergence
 * of the color values.
 *
 **************************************************************************************************/
TEST(Color, RGBAtoHSLAMappingMechanish_MultipleConversion_NoDivergence)
{
    const cxutil::Color rgbaInitial{cxutil::RGBA{123, 221, 15, 63}};
    const cxutil::Color hslaInitial{cxutil::HSLA{0.247, 0.873, 0.463, 0.247}};

    cxutil::Color rgba{rgbaInitial};
    cxutil::Color hsla{hslaInitial};

    // 50 conversions:
    for(int i{0}; i < 50; ++i)
    {
        using namespace cxutil;

        Color buffer = rgba;
        rgba = Color{RGBA{hsla.r(), hsla.g(), hsla.b(), hsla.a()}};
        hsla = Color{HSLA{buffer.hue(), buffer.saturation(), buffer.lightness(), buffer.alpha()}};
    }

    // Initial values should still apply:
    ASSERT_NEAR(rgba.r()         , rgbaInitial.r()         , MAX_PRECISION_RGB_8BITS);
    ASSERT_NEAR(rgba.g()         , rgbaInitial.g()         , MAX_PRECISION_RGB_8BITS);
    ASSERT_NEAR(rgba.b()         , rgbaInitial.b()         , MAX_PRECISION_RGB_8BITS);
    ASSERT_NEAR(rgba.a()         , rgbaInitial.a()         , MAX_PRECISION_RGB_8BITS);
    ASSERT_NEAR(rgba.hue()       , rgbaInitial.hue()       , MAX_PRECISION_RGB_8BITS);
    ASSERT_NEAR(rgba.saturation(), rgbaInitial.saturation(), MAX_PRECISION_RGB_8BITS);
    ASSERT_NEAR(rgba.lightness() , rgbaInitial.lightness() , MAX_PRECISION_RGB_8BITS);

    ASSERT_NEAR(hsla.r()         , hslaInitial.r()         , MAX_PRECISION_RGB_8BITS);
    ASSERT_NEAR(hsla.g()         , hslaInitial.g()         , MAX_PRECISION_RGB_8BITS);
    ASSERT_NEAR(hsla.b()         , hslaInitial.b()         , MAX_PRECISION_RGB_8BITS);
    ASSERT_NEAR(hsla.a()         , hslaInitial.a()         , MAX_PRECISION_RGB_8BITS);
    ASSERT_NEAR(hsla.hue()       , hslaInitial.hue()       , MAX_PRECISION_RGB_8BITS);
    ASSERT_NEAR(hsla.saturation(), hslaInitial.saturation(), MAX_PRECISION_RGB_8BITS);
    ASSERT_NEAR(hsla.lightness() , hslaInitial.lightness() , MAX_PRECISION_RGB_8BITS);
}
