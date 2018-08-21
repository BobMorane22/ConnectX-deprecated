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
 * @file    util.cpp
 * @author  Eric Poirier
 * @date    May 2018
 * @version 1.0
 *
 * Implementation for some utility free functions.
 *
 **************************************************************************************************/

#include <algorithm>
#include <iomanip>
#include <sstream>

#include <cxutil/include/Assertion.h>
#include <cxutil/include/ContractException.h>
#include <cxutil/include/narrow_cast.h>
#include <cxutil/include/Color.h>

#include "../include/util.h"


std::string cxgui::addMarkupTags(const std::string& p_text, const std::string& p_tag)
{
    PRECONDITION(!p_tag.empty());
    PRECONDITION(std::all_of(p_tag.begin(), p_tag.end(),
                 [](const char p_letter)
                 {
                     return bool(isalpha(p_letter));
                 }));

    // We build the opening in closing tag:
    const std::string leftTag {"<"  + p_tag + ">" };
    const std::string rightTag{"</" + p_tag + ">" };

    const size_t lenLeft {leftTag.length()};
    const size_t lenRight{lenLeft + 1     };
    const size_t lenExpr {p_text.length() };

    if(lenExpr < lenLeft)
    {
        return leftTag + p_text + rightTag;
    }

    if(lenExpr == lenLeft && p_text == rightTag)
    {
        return p_text + rightTag;
    }

    const bool leftTagIsPresent  {p_text.substr(0, lenLeft) == leftTag                  };
    const bool rightTagIsPresent {p_text.substr(lenExpr - lenRight, lenExpr) == rightTag};
    const bool bothTagsArePresent{leftTagIsPresent && rightTagIsPresent                 };

    if(bothTagsArePresent)
    {
        return p_text;
    }

    if(leftTagIsPresent)
    {
        return p_text + rightTag;
    }

    if(rightTagIsPresent)
    {
        return leftTag + p_text;
    }

    return leftTag + p_text + rightTag;
}


std::string cxgui::addBoldMarkupTags(const std::string& p_textToMakeBold)
{
    return cxgui::addMarkupTags(p_textToMakeBold, "b");
}


std::string cxgui::addBigMarkupTags(const std::string& p_textToMakeBig)
{
    return cxgui::addMarkupTags(p_textToMakeBig, "big");
}


std::string cxgui::addItalicMarkupTags(const std::string& p_textToMakeItalic)
{
    return cxgui::addMarkupTags(p_textToMakeItalic, "i");
}


std::string cxgui::addStrikethroughMarkupTags(const std::string& p_textToMakeStrikethrough)
{
    return cxgui::addMarkupTags(p_textToMakeStrikethrough, "s");
}


std::string cxgui::addSubscriptMarkupTags(const std::string& p_textToMakeSubscript)
{
    return cxgui::addMarkupTags(p_textToMakeSubscript, "sub");
}


std::string cxgui::addSuperscriptMarkupTags(const std::string& p_textToMakeSuperscript)
{
    return cxgui::addMarkupTags(p_textToMakeSuperscript, "sup");
}


std::string cxgui::addSmallMarkupTags(const std::string& p_textToMakeSmall)
{
    return cxgui::addMarkupTags(p_textToMakeSmall, "small");
}


std::string cxgui::addTrueTypeMarkupTags(const std::string& p_textToMakeTrueType)
{
    return cxgui::addMarkupTags(p_textToMakeTrueType, "tt");
}


std::string cxgui::addUnderlineMarkupTags(const std::string& p_textToMakeunderline)
{
    return cxgui::addMarkupTags(p_textToMakeunderline, "u");
}


std::string cxgui::buildGdkColorString(const cxutil::Color& p_localColor)
{
    std::ostringstream os;

    os << "rgba(" << unsigned(p_localColor.r())
       << ", "    << unsigned(p_localColor.g())
       << ", "    << unsigned(p_localColor.b())
       << ", "    << p_localColor.alpha()
       << ")";

    return os.str();
}


std::string cxgui::deprecated::buildGdkColorString(const cxutil::Color& p_localColor)
{
    using namespace std;

    ostringstream os;

    os << "#"
       << uppercase << setfill('0') << setw(2) << hex << unsigned(p_localColor.r())
       << uppercase << setfill('0') << setw(2) << hex << unsigned(p_localColor.g())
       << uppercase << setfill('0') << setw(2) << hex << unsigned(p_localColor.b());

    return os.str();
}


cxutil::Color cxgui::convertToLocalColor(const Gdk::RGBA& p_gdkColor)
{
    const uint8_t red   {cxutil::narrow_cast<uint8_t>((p_gdkColor.get_red_u()   >> 8) & 0xFF)};
    const uint8_t green {cxutil::narrow_cast<uint8_t>((p_gdkColor.get_green_u() >> 8) & 0xFF)};
    const uint8_t blue  {cxutil::narrow_cast<uint8_t>((p_gdkColor.get_blue_u()  >> 8) & 0xFF)};
    const uint8_t alpha {cxutil::narrow_cast<uint8_t>((p_gdkColor.get_alpha_u() >> 8) & 0xFF)};

    return cxutil::Color{cxutil::RGBA{red, green, blue, alpha}};
}


cxutil::Color cxgui::deprecated::convertToLocalColor(const Gdk::Color& p_gdkColor)
{
    const uint8_t red   {cxutil::narrow_cast<uint8_t>((p_gdkColor.get_red()   >> 8) & 0xFF)};
    const uint8_t green {cxutil::narrow_cast<uint8_t>((p_gdkColor.get_green() >> 8) & 0xFF)};
    const uint8_t blue  {cxutil::narrow_cast<uint8_t>((p_gdkColor.get_blue()  >> 8) & 0xFF)};

    return cxutil::Color{cxutil::RGBA{red, green, blue, 255}};
}


Gdk::RGBA cxgui::convertToGdkRGBA(const cxutil::Color& p_localColor)
{
    return Gdk::RGBA{cxgui::buildGdkColorString(p_localColor)};
}


Gdk::Color cxgui::deprecated::convertToGdkColor(const cxutil::Color& p_localColor)
{
    return Gdk::Color{cxgui::deprecated::buildGdkColorString(p_localColor)};
}
