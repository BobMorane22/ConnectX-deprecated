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

#include <cxmath/include/Vector.h>
#include <cxmath/include/util.h>
#include <cxutil/include/Assertion.h>


template <typename T, std::size_t N>
cxmath::LineSegment<T, N>::LineSegment(const cxmath::Point<T, N>& p_firstEndpoint,
                                       const cxmath::Point<T, N>& p_secondEndpoint)
 : m_firstEndpoint{p_firstEndpoint}
 , m_secondEndpoint{p_secondEndpoint}
{
    PRECONDITION(p_firstEndpoint != p_secondEndpoint);

    INVARIANTS();
}


template <typename T, std::size_t N>
cxmath::LineSegment<T, N>::~LineSegment() = default;


template <typename T, std::size_t N>
void cxmath::LineSegment<T, N>::checkInvariant() const
{
    INVARIANT(m_firstEndpoint != m_secondEndpoint);
}


template <typename T>
bool cxmath::areParallel(const cxmath::LineSegment<T, 2>& p_first,
                         const cxmath::LineSegment<T, 2>& p_second)
{
    using namespace cxmath;

    const Vector<T, 2> v1{p_first.firstEndpoint(), p_first.secondEndpoint()};
    const Vector<T, 2> v2{p_second.firstEndpoint(), p_second.secondEndpoint()};

    T result;
    crossProduct(v1, v2, result);

    return areLogicallyEqual<T>(result, 0.0);
}


template <typename T>
bool cxmath::areOrthogonal(const cxmath::LineSegment<T, 2>& p_first,
                           const cxmath::LineSegment<T, 2>& p_second)
{
    using namespace cxmath;

    const Vector<T, 2> v1{p_first.firstEndpoint(), p_first.secondEndpoint()};
    const Vector<T, 2> v2{p_second.firstEndpoint(), p_second.secondEndpoint()};

    return areLogicallyEqual<T>(dotProduct<T, 2>(v1, v2), 0.0);
}


template <typename T>
bool cxmath::areColinear(const cxmath::LineSegment<T, 2>& p_first,
                         const cxmath::LineSegment<T, 2>& p_second)
{
    using namespace cxmath;

    const Vector<T, 2> p{Point<T, 2>(), p_first.firstEndpoint()};
    const Vector<T, 2> r{Point<T, 2>(), p_first.secondEndpoint()};

    const Vector<T, 2> q{Point<T, 2>(), p_second.firstEndpoint()};
    const Vector<T, 2> s{Point<T, 2>(), p_second.secondEndpoint()};

    T crossProdRS;
    T crossProdQPR;

    crossProduct(r, s, crossProdRS);
    crossProduct(q - p, r, crossProdQPR);

    return areLogicallyEqual<T>(crossProdRS, 0.0) && areLogicallyEqual<T>(crossProdQPR, 0.0);
}


template <typename T>
bool cxmath::intersect(const cxmath::LineSegment<T, 2>& p_first,
                       const cxmath::LineSegment<T, 2>& p_second,
                       bool p_considerEndpoints)
{
    using namespace cxmath;

    const Vector<T, 2> p{Point<T, 2>(), p_first.firstEndpoint()};
    const Vector<T, 2> r{Vector<T, 2>{Point<T, 2>(), p_first.secondEndpoint()} - p};

    const Vector<T, 2> q{Point<T, 2>(), p_second.firstEndpoint()};
    const Vector<T, 2> s{Vector<T, 2>{Point<T, 2>(), p_second.secondEndpoint()} - q};

    T crossProdQPR;
    T crossProdQPS;
    T crossProdRS;

    crossProduct(q - p, r, crossProdQPR);
    crossProduct(q - p, s, crossProdQPS);
    crossProduct(r, s,     crossProdRS);

    if(areColinear<T>(p_first, p_second))
    {
        // The two lines are collinear. Are they also overlapping?
        const T dotProdSR{dotProduct<T, 2>(s, r)};
        const T dotProdRR{dotProduct<T, 2>(r, r)};

        const T t0{dotProduct<T, 2>(q - p, r) / dotProdRR};
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
    else if(areParallel<T>(p_first, p_second) && !areLogicallyEqual<T>(crossProdQPR, 0.0))
    {
        return false;
    }
    else if(!areLogicallyEqual<T>(crossProdRS, 0.0))
    {
        const T t{crossProdQPS / crossProdRS};
        const T u{crossProdQPR / crossProdRS};

        if(p_considerEndpoints)
        {
            return (t >= 0.0 && t <= 1.0) && (u >= 0.0 && u <= 1.0);
        }
        else
        {
            return (t > 0.0 && t < 1.0) && (u > 0.0 && u < 1.0);
        }
    }

    return false;
}
