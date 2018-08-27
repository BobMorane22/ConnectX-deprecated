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
 * @file    Vector3D.ipp
 * @author  Eric Poirier
 * @date    August 2018
 * @version 1.0
 *
 * Implementation for a the @c Vector class template 3D specific functionalities.
 *
 **************************************************************************************************/


template<typename T>
void cxutil::math::crossProduct(const math::Vector<T, 3>& p_v1,
                                const math::Vector<T, 3>& p_v2,
                                math::Vector<T, 3>& p_result)
{
    using namespace cxutil;
    using namespace cxutil::math;

    p_result = Vector<T, 3>{Point<T, 3>{},
                            Point<T, 3> {
                                          p_v1.y() * p_v2.z() - p_v1.z() * p_v2.y(),
                                          p_v1.z() * p_v2.x() - p_v1.x() * p_v2.z(),
                                          p_v1.x() * p_v2.y() - p_v1.y() * p_v2.x() }
    };
}
