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
 * @file    LineSegment.ipp
 * @author  Eric Poirier
 * @date    August 2018
 * @version 1.0
 *
 * Implementation for a the @c LineSegment class template.
 *
 **************************************************************************************************/

#include "../include/Assertion.h"
#include "../include/Vector.h"


template <typename T, std::size_t N>
cxutil::math::LineSegment<T, N>::LineSegment(const cxutil::math::Point<T, N>& p_firstEndpoint,
                                             const cxutil::math::Point<T, N>& p_secondEndpoint)
 : m_firstEndpoint{p_firstEndpoint}
 , m_secondEndpoint{p_secondEndpoint}
{
    PRECONDITION(p_firstEndpoint != p_secondEndpoint);

    INVARIANTS();
}


template <typename T, std::size_t N>
cxutil::math::LineSegment<T, N>::~LineSegment() = default;


template <typename T, std::size_t N>
void cxutil::math::LineSegment<T, N>::checkInvariant() const
{
    INVARIANT(m_firstEndpoint != m_secondEndpoint);
}


template <typename T, std::size_t N>
bool areParallel(const cxutil::math::LineSegment<T, N>& p_first,
                 const cxutil::math::LineSegment<T, N>& p_second)
{
    using namespace cxutil::math;

    if(N == 1)
    {
        return true;
    }

    const Vector<T, N> v1{p_first.firstEndpoint(), p_first.secondEndpoint()};
    const Vector<T, N> v2{p_second.firstEndpoint(), p_second.secondEndpoint()};

    return crossProduct<T, N>(v1, v2) == Vector<T, N>();
}


template <typename T, std::size_t N>
bool areOrthogonal(const cxutil::math::LineSegment<T, N>& p_first,
                   const cxutil::math::LineSegment<T, N>& p_second)
{
    using namespace cxutil::math;

    if(N == 1)
    {
        return false;
    }

    const Vector<T, N> v1{p_first.firstEndpoint(), p_first.secondEndpoint()};
    const Vector<T, N> v2{p_second.firstEndpoint(), p_second.secondEndpoint()};

    return dotProduct<T, N>(v1, v2) == 0.0;
}


template <typename T, std::size_t N>
bool areColinear(const cxutil::math::LineSegment<T, N>& p_first,
                 const cxutil::math::LineSegment<T, N>& p_second)
{
    using namespace cxutil::math;

    if(N == 1)
    {
        return true;
    }

    const Vector<T, N> p{Point<T, N>(), p_first.firstEndpoint()};
    const Vector<T, N> r{Vector<T, N>{Point<T, N>(), p_first.secondEndpoint()} - p};

    const Vector<T, N> q{Point<T, N>(), p_second.firstEndpoint()};
    const Vector<T, N> s{Vector<T, N>{Point<T, N>(), p_second.secondEndpoint()} - q};

    return (crossProduct<T, N>(r, s) == 0.0) && (crossProduct<T, N>(q - p, r) == 0.0);
}


template <typename T, std::size_t N>
bool intersect(const cxutil::math::LineSegment<T, N>& p_first,
               const cxutil::math::LineSegment<T, N>& p_second,
               bool p_considerEndpoints = false)
{
    static_assert(N == 2, "This functionality is only supported in two dimensions for now.");

    using namespace cxutil::math;

    const Vector<T, N> p{Point<T, N>(), p_first.firstEndpoint()};
    const Vector<T, N> r{Vector<T, N>{Point<T, N>(), p_first.secondEndpoint()} - p};

    const Vector<T, N> q{Point<T, N>(), p_second.firstEndpoint()};
    const Vector<T, N> s{Vector<T, N>{Point<T, N>(), p_second.secondEndpoint()} - q};

    if(areColinear<T, N>(p_first, p_second))
    {
        // The two lines are collinear. Are they also overlapping?
        const T dotProdSR{dotProduct<T, N>(s, r)};
        const T dotProdRR{dotProduct<T, N>(s, r)};

        const T t0{r / dotProdRR};
        const T t1{t0 + dotProdSR / dotProdRR};

        const bool sAndRInSameDirection{dotProdSR > 0};

        if(sAndRInSameDirection)
        {
            // Interval is [t0, t1]:
            CX_ASSERT_MSG(t0 < t1, "We should have t0 < t1.");

            const bool isLeftOverlap {p_considerEndpoints ? t1 >= 0.0 && t1 <= 1.0 : t1 > 0.0 && t1 < 1.0};
            const bool isRightOverlap{p_considerEndpoints ? t0 >= 0.0 && t0 <= 1.0 : t0 > 0.0 && t0 < 1.0};
            const bool isTotalOverlap{p_considerEndpoints ? t0 <= 0.0 && t1 >= 1.0 : t0 < 0.0 && t1 > 1.0};

            return isLeftOverlap || isRightOverlap || isTotalOverlap;
        }
        else
        {
            // Interval is [t1, t0]:
            CX_ASSERT_MSG(t1 < t0, "We should have t0 < t1.");

            const bool isLeftOverlap {p_considerEndpoints ? t0 >= 0.0 && t0 <= 1.0 : t0 > 0.0 && t0 < 1.0};
            const bool isRightOverlap{p_considerEndpoints ? t1 >= 0.0 && t1 <= 1.0 : t1 > 0.0 && t1 < 1.0};
            const bool isTotalOverlap{p_considerEndpoints ? t1 <= 0.0 && t0 >= 1.0 : t1 < 0.0 && t0 > 1.0};

            return isLeftOverlap || isRightOverlap || isTotalOverlap;
        }
    }
    else if(areParallel<T, N>(p_first, p_second) && crossProduct<T, N>(q - p, r) != 0.0)
    {
        return false;
    }
    else if(crossProduct<T, N>(r, s) != 0.0)
    {
        const T t{crossProduct<T, N>(q - p, s) / crossProduct<T, N>(r, s)};
        const T u{crossProduct<T, N>(q - p, r) / crossProduct<T, N>(r, s)};

        return p_considerEndpoints ? (t >= 0.0 && t <= 1.0) && (u >= 0.0 && u <= 1.0) :
                                     (t > 0.0 && t < 1.0) && (u > 0.0 && u < 1.0);
    }

    CX_ASSERT_MSG(false, "All cases should have been covered.");

    return false;
}
