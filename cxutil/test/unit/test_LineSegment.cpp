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
 * @file    test_LineSegment.cpp
 * @author  Eric Poirier
 * @date    August 2018
 * @version 1.0
 *
 * Unit tests for a the @c LineSegment class template.
 *
 **************************************************************************************************/

#include <gtest/gtest.h>

#include <cxutil/include/narrow_cast.h>
#include <cxutil/include/LineSegment.h>


template <typename T>
class LineSegmentTest : public ::testing::Test
{

public:

    LineSegmentTest() = default;
    virtual ~LineSegmentTest() = default;

};

typedef ::testing::Types<double, long double> LineSegmentRelatedTypes;
TYPED_TEST_CASE(LineSegmentTest, LineSegmentRelatedTypes);


namespace
{

/***************************************************************************************************
 * @brief Generates a 1D point.
 *
 * @tparam T   The coordinate type.
 * @param  p_x The x coordinate.
 *
 * @return The 1D corresponding point.
 *
 **************************************************************************************************/
template <typename T>
cxutil::math::Point<T, 1> make1DTestPoint(const T& p_x)
{
    using namespace cxutil;

    return math::Point<T, 1>{narrow_cast<T>(p_x)};
}


/***************************************************************************************************
 * @brief Generates a 2D point.
 *
 * @tparam T   The coordinate type.
 * @param  p_x The x coordinate.
 * @param  p_y The y coordinate.
 *
 * @return The 1D corresponding point.
 *
 **************************************************************************************************/
template <typename T>
cxutil::math::Point<T, 2> make2DTestPoint(const T& p_x, const T& p_y)
{
    using namespace cxutil;

    return math::Point<T, 2>{narrow_cast<T>(p_x), narrow_cast<T>(p_y)};
}


/***************************************************************************************************
 * @brief Generates a 3D point.
 *
 * @tparam T   The coordinate type.
 * @param  p_x The x coordinate.
 * @param  p_y The y coordinate.
 * @param  p_z The z coordinate.
 *
 * @return The 3D corresponding point.
 *
 **************************************************************************************************/
template <typename T>
cxutil::math::Point<T, 3> make3DTestPoint(const T& p_x, const T& p_y, const T& p_z)
{
    using namespace cxutil;

    return math::Point<T, 3>{narrow_cast<T>(p_x), narrow_cast<T>(p_y), narrow_cast<T>(p_z)};
}

} // unamed namespace


TYPED_TEST(LineSegmentTest, ConstructorWithParameters_TwoEqual1DEndpoints_ExceptionThrown)
{
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin;
    const Point<TypeParam, 1> destination;

    ASSERT_THROW((LineSegment<TypeParam, 1>{origin, destination}), PreconditionException);
}


TYPED_TEST(LineSegmentTest, ConstructorWithParameters_TwoEqual2DEndpoints_ExceptionThrown)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin;
    const Point<TypeParam, 2> destination;

    ASSERT_THROW((LineSegment<TypeParam, 2>{origin, destination}), PreconditionException);
}


TYPED_TEST(LineSegmentTest, ConstructorWithParameters_TwoEqual3DEndpoints_ExceptionThrown)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin;
    const Point<TypeParam, 3> destination;

    ASSERT_THROW((LineSegment<TypeParam, 3>{origin, destination}), PreconditionException);
}


TYPED_TEST(LineSegmentTest, ConstructorWithParameters_TwoDifferent1DEndpoints_NoExceptionThrown)
{
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin;
    const Point<TypeParam, 1> destination{make1DTestPoint<TypeParam>(1)};

    ASSERT_NO_THROW((LineSegment<TypeParam, 1>{origin, destination}));
}


TYPED_TEST(LineSegmentTest, ConstructorWithParameters_TwoDifferent2DEndpoints_NoExceptionThrown)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin;
    const Point<TypeParam, 2> destination{make2DTestPoint<TypeParam>(1, 1)};

    ASSERT_NO_THROW((LineSegment<TypeParam, 2>{origin, destination}));
}


TYPED_TEST(LineSegmentTest, ConstructorWithParameters_TwoDifferent3DEndpoints_NoExceptionThrown)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin;
    const Point<TypeParam, 3> destination{make3DTestPoint<TypeParam>(1, 1, 1)};

    ASSERT_NO_THROW((LineSegment<TypeParam, 3>{origin, destination}));
}


TYPED_TEST(LineSegmentTest, FirstEndpoint_Two1DEndpoints_ReturnsFirstEndpoint)
{
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin;
    const Point<TypeParam, 1> destination{make1DTestPoint<TypeParam>(1)};

    LineSegment<TypeParam, 1> lineSegment{origin, destination};

    ASSERT_EQ(lineSegment.firstEndpoint(), origin);
}


TYPED_TEST(LineSegmentTest, FirstEndpoint_Two2DEndpoints_ReturnsFirstEndpoint)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin;
    const Point<TypeParam, 2> destination{make2DTestPoint<TypeParam>(1, 1)};

    LineSegment<TypeParam, 2> lineSegment{origin, destination};

    ASSERT_EQ(lineSegment.firstEndpoint(), origin);
}


TYPED_TEST(LineSegmentTest, FirstEndpoint_Two3DEndpoints_ReturnsFirstEndpoint)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin;
    const Point<TypeParam, 3> destination{make3DTestPoint<TypeParam>(1, 1, 1)};

    LineSegment<TypeParam, 3> lineSegment{origin, destination};

    ASSERT_EQ(lineSegment.firstEndpoint(), origin);
}


TYPED_TEST(LineSegmentTest, SecondEndpoint_Two1DEndpoints_ReturnsSecondEndpoint)
{
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin;
    const Point<TypeParam, 1> destination{make1DTestPoint<TypeParam>(1)};

    LineSegment<TypeParam, 1> lineSegment{origin, destination};

    ASSERT_EQ(lineSegment.secondEndpoint(), destination);
}


TYPED_TEST(LineSegmentTest, SecondEndpoint_Two2DEndpoints_ReturnsSecondEndpoint)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin;
    const Point<TypeParam, 2> destination{make2DTestPoint<TypeParam>(1, 1)};

    LineSegment<TypeParam, 2> lineSegment{origin, destination};

    ASSERT_EQ(lineSegment.secondEndpoint(), destination);
}


TYPED_TEST(LineSegmentTest, SecondEndpoint_Two3DEndpoints_ReturnsSecondEndpoint)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin;
    const Point<TypeParam, 3> destination{make3DTestPoint<TypeParam>(1, 1, 1)};

    LineSegment<TypeParam, 3> lineSegment{origin, destination};

    ASSERT_EQ(lineSegment.secondEndpoint(), destination);
}


TYPED_TEST(LineSegmentTest, GetEndpoint_Two1DEndpoints_EndpointsAreDifferent)
{
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin;
    const Point<TypeParam, 1> destination{make1DTestPoint<TypeParam>(1)};

    LineSegment<TypeParam, 1> lineSegment{origin, destination};

    ASSERT_NE(lineSegment.firstEndpoint(), lineSegment.secondEndpoint());
}


TYPED_TEST(LineSegmentTest, GetEndpoint_Two2DEndpoints_EndpointsAreDifferent)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin;
    const Point<TypeParam, 2> destination{make2DTestPoint<TypeParam>(1, 1)};

    LineSegment<TypeParam, 2> lineSegment{origin, destination};

    ASSERT_NE(lineSegment.firstEndpoint(), lineSegment.secondEndpoint());
}


TYPED_TEST(LineSegmentTest, GetEndpoint_Two3DEndpoints_EndpointsAreDifferent)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin;
    const Point<TypeParam, 3> destination{make3DTestPoint<TypeParam>(1, 1, 1)};

    LineSegment<TypeParam, 3> lineSegment{origin, destination};

    ASSERT_NE(lineSegment.firstEndpoint(), lineSegment.secondEndpoint());
}
