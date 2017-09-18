/***************************************************************************************************
 * 
 * Copyright (C) 2017 Connect X team
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
 * @file    narrow_cast.h
 * @author  Eric Poirier
 * @date    August 2017
 * @version 1.0
 *
 * narrow_cast utility.
 *
 **************************************************************************************************/

#ifndef NARROW_CAST_H_4ACD64EC_E32D_421E_A0CC_9751ACAF8E31
#define NARROW_CAST_H_4ACD64EC_E32D_421E_A0CC_9751ACAF8E31

#include "Assertion.h"

namespace cxutil
{

/***********************************************************************************************//**
 * Cast while ensuring no narrowing has taken place.
 *
 * This cast makes sure a type @c Target can be casted to another type @c Source without any loss
 * of information. In the case where narrowing takes place during the cast, an assertion occurs.
 * Note that @c operator!= has to be defined for type @c Source, because of the assertion check.
 *
 * For more information and examples, see the book <em>The C++ Programming Language 
 * (Fourth Edition) </em> by Bjarne Stroustrup, p. 298 (see "narrow_cast").
 *
 * 
 * @tparam     Target   The type to cast to.
 * @tparam     Source   The type to cast from.
 * @param[in]  p_toCast The object to cast from type @c Source to type @c Target.
 *
 * @return     The @c p_toCast object casted to type @c Target.
 *
 **************************************************************************************************/
template<class Target, class Source>
Target narrow_cast(Source p_toCast)
{
    Target casted = static_cast<Target>(p_toCast);

    // Can we convert back without loosing information?
    CX_ASSERT(static_cast<Source>(casted) == p_toCast);

    return casted;
}

} // namespace cxutil

#endif // NARROW_CAST_H_4ACD64EC_E32D_421E_A0CC_9751ACAF8E31
