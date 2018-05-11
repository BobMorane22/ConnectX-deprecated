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
 * @file    utils.h
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

namespace cxgui
{

/**********************************************************************************************//**
 * Add bold markup tags to a string. Note that it is not the responsability of this method to
 * make the character string appear bold. It only formats it so that when markup is activated,
 * the string has the needed tags to appear as bold.
 *
 * @note For some string 'Some text...', the function will return the string '<b>Some text...</b>'.
 * @note If the string passed as an argument already has bold tags surrounding it, the function
 *       will not add extra tags and will simply return the original string.
 *
 * @todo Implement second note and test!!
 *
 * @param p_textToMakeBold [in] The string of characters to add bold markup tags to.
 *
 * @return The string with the markup bold tags added to it.
 *
 *************************************************************************************************/
std::string addBoldMarkupTags(const std::string& p_textToMakeBold);

} // namespace cxgui

#endif // UTIL_H_927C72F7_3F4B_4C3D_9ED8_FF3D17C388DD

