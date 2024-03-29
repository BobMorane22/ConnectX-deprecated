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
 * @file    util.h
 * @author  Eric Poirier
 * @date    May 2018
 * @version 1.0
 *
 * Interface for some utility free functions.
 *
 **************************************************************************************************/

#ifndef UTIL_H_927C72F7_3F4B_4C3D_9ED8_FF3D17C388DD
#define UTIL_H_927C72F7_3F4B_4C3D_9ED8_FF3D17C388DD

#include <string>

#include <gdkmm/color.h>
#include <gdkmm/rgba.h>

#include <cxutil/include/Color.h>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Add tags (in to form of pango markup convenience tags) around a string.
 *
 * Wraps opening and closing tags around a string in to form of pango markup convenience tags.
 * For example, if you want to make some text, let's say the string 'Some text', smaller then
 * you can call this function in the following way:
 *
 *   @code
 *     addMarkupTags("Some text", "small");
 *   @endcode
 *
 * which will return the string
 *
 *   @verbatim
 *     <small>Some text</small>
 *   @endverbatim
 *
 * If the string already has tags around it (the same tag you are trying to add), no additional
 * tags will be added and the string will be left untouched. If the string has only one tag (either
 * the opening or the closing tag) only the missing tag will be added.
 *
 * @note it is not the responsibility of this function to apply the markup styling. It only
 *       formats  a string it so that when markup is activated, the string has the needed tags to
 *       appear as bold. See the pango markup documentation for more details.
 *
 * @param p_text The test to warp in between tags.
 * @param p_tag  The pango markup convenience tag.
 *
 * @pre The tag is a non-empty string composed of alpha characters only.
 *
 * @return The string passed as an argument wrapped in tags.
 *
 * @see Documentation for <a href="https://developer.gnome.org/pango/stable/PangoMarkupFormat.html">pango markup</a>.
 *
 *************************************************************************************************/
std::string addMarkupTags(const std::string& p_text, const std::string& p_tag);


/**********************************************************************************************//**
 * Add bold markup tags to a string. Note that it is not the responsibility of this method to
 * make the character string appear bold. It only formats it so that when markup is activated,
 * the string has the needed tags to appear as bold.
 *
 * @note For some string 'Some text...', the function will return the string '<b>Some text...</b>'.
 * @note If the string passed as an argument already has bold tags surrounding it, the function
 *       will not add extra tags and will simply return the original string. If the string has one
 *       of the left or right tag only, the missing tag will be added.
 *
 * @param p_textToMakeBold The string of characters to add bold markup tags to.
 *
 * @return The string with the markup bold tags added to it.
 *
 * @see addMarkupTags
 *
 * @todo Comment other similar functions!
 *
 *************************************************************************************************/
std::string addBoldMarkupTags(const std::string& p_textToMakeBold);


std::string addBigMarkupTags(const std::string& p_textToMakeBig);
std::string addItalicMarkupTags(const std::string& p_textToMakeItalic);
std::string addStrikethroughMarkupTags(const std::string& p_textToMakeStrikethrough);
std::string addSubscriptMarkupTags(const std::string& p_textToMakeSubscript);
std::string addSuperscriptMarkupTags(const std::string& p_textToMakeSuperscript);
std::string addSmallMarkupTags(const std::string& p_textToMakeSmall);
std::string addTrueTypeMarkupTags(const std::string& p_textToMakeTrueType);
std::string addUnderlineMarkupTags(const std::string& p_textToMakeunderline);


/*******************************************************************************************//**
 * Builds a string of the form <tt>rgba(r, g, b, a)</tt> where @c r , @c g @c b and @c a
 * represent the four RGBA components for the color. @c r, @c g and @c b are integers from
 * 0 to 255 and @c a is a ration from 0.0 (transparent) to 1.0 (opaque). This function is
 * useful to build @c Gdk::RGBA objects from a @c cxutil::Color type, which does not deal with
 * strings.
 *
 * @param p_localColor The @c cxutil::Color to be converted to a @c Gdk::RGBA compatible string.
 *
 * @return The @c Gdk compatible string representing the color passed as an argument.
 *
 * @see cxutil::Color
 *
 **********************************************************************************************/
 std::string buildGdkColorString(const cxutil::Color& p_localColor);


/*******************************************************************************************//**
 * Converts a @c Gdk::RGBA object to a @c cxutil::Color object.
 *
 * @param p_gdkColor The @c Gdk::RGBA object to convert.
 *
 * @return The @c cxutil::Color object represented the Gdk color passed as an argument.
 *
 * @note @c Gdk::RGBA internally store its RGBA components as 16 bits values, unlike
 *          @c cxutil::Color which store its equivalent data as 8 bits values. Therefore, it
 *          is inevitable that there is some precision loss when converting from @c Gdk to
 *          @c cxutil , since some colors exist only as Gdk colors. This function will convert
 *          to a color that is at most 1/257 away, when normalized.
 *
 * @see cxutil::Color
 *
 ***********************************************************************************************/
cxutil::Color convertToLocalColor(const Gdk::RGBA& p_gdkColor);


/*******************************************************************************************//**
 * Converts a @c cxutil::Color object to a @c Gdk::RGBA object.
 *
 * @param p_localColor The @c cxutil::Color object to convert.
 *
 * @return The @c Gdk::RGBA object represented the local color passed as an argument.
 *
 * @see cxutil::Color
 *
 **********************************************************************************************/
Gdk::RGBA convertToGdkRGBA(const cxutil::Color& p_localColor);


namespace deprecated
{

/*******************************************************************************************//**
 * Builds a string of the form <tt>#RRGGBB</tt> where @c RR , @c BB and @c BB represent the
 * three RGB components for the color, as hexadecimal values. This function is useful to
 * build @c Gdk::Color (deprecated) objects from a @c cxutil::Color type, which does not deal
 * with strings.
 *
 * @param p_localColor The @c cxutil::Color to be converted to a @c Gdk::Color compatible string.
 *
 * @return The Gdk compatible string representing the color passed as an argument.
 *
 * @see cxutil::Color
 *
 **********************************************************************************************/
std::string buildGdkColorString(const cxutil::Color& p_localColor);


/*******************************************************************************************//**
 * Converts a @c Gdk::Color object to a cxutil::Color object.
 *
 * @param p_gdkColor The @c Gdk::Color object to convert.
 *
 * @return The @c cxutil::Color object represented the Gdk color passed as an argument.
 *
 * @note @c Gdk::Color internally store its RGB components as 16 bits values, unlike
 *          @c cxutil::Color which store its equivalent data as 8 bits values. Therefore, it
 *          is inevitable that there is some precision loss when converting from @c Gdk to
 *          @c cxutil , since some colors exist only as Gdk colors. This function will convert
 *          to a color that is at most 1/257 away, when normalized.
 *
 * @deprecated According to the Gdk reference for Color : "When working with cairo,
 *             it is often more convenient to use a @c GdkRGBA instead, and @c GdkColor has
 *             been deprecated in favor of @c Gdk::RGBA." This function has been added here
 *             because some of the Gtkmm3 functionalities have not yet been ported to
 *             @c Gdk::RGBA (such as the @c Gtk::ColorButton for example) and still need
 *             support for @c Gdk::Color.
 *
 * @see cxutil::Color
 *
 ***********************************************************************************************/
cxutil::Color convertToLocalColor(const Gdk::Color& p_gdkColor);


/*******************************************************************************************//**
 * Converts a @c cxutil::Color object to a Gdk::Color object.
 *
 * @param p_localColor The @c cxutil::Color object to convert.
 *
 * @return The @c Gdk::Color object represented the local color passed as an argument.
 *
 * @deprecated According to the Gdk reference for Color : "When working with cairo,
 *             it is often more convenient to use a @c GdkRGBA instead, and @c GdkColor has
 *             been deprecated in favor of @c Gdk::RGBA." This function has been added here
 *             because some of the Gtkmm3 functionalities have not yet been ported to
 *             @c Gdk::RGBA (such as the @c Gtk::ColorButton for example) and still need
 *             support for @c Gdk::Color.
 *
 * @see cxutil::Color
 *
 **********************************************************************************************/
Gdk::Color convertToGdkColor(const cxutil::Color& p_localColor);

} // namespace deprecated

} // namespace cxgui

#endif // UTIL_H_927C72F7_3F4B_4C3D_9ED8_FF3D17C388DD

