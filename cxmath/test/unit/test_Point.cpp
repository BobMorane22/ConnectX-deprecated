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
 * @file    test_Point.cpp
 * @author  Eric Poirier
 * @date    August 2018
 * @version 1.0
 *
 * Unit tests for a the @c Point class template.
 *
 **************************************************************************************************/

#include <gtest/gtest.h>

#include <cxmath/include/Point.h>
#include <cxutil/include/narrow_cast.h>


template <typename T>
class PointTest : public ::testing::Test
{

public:

    PointTest() = default;
    virtual ~PointTest() = default;

    cxmath::Point<T, 1> m_point1D;
    cxmath::Point<T, 2> m_point2D;
    cxmath::Point<T, 3> m_point3D;
};

typedef ::testing::Types<float, double, long double> PointRelatedTypes;
TYPED_TEST_CASE(PointTest, PointRelatedTypes);


TYPED_TEST(PointTest, DefaultConstructor_PointWithOneCoordinate_IsOrigin)
{
    ASSERT_EQ(this->m_point1D.x(), TypeParam());
}


TYPED_TEST(PointTest, DefaultConstructor_PointWithTwoCoordinates_IsOrigin)
{
    ASSERT_EQ(this->m_point2D.x(), TypeParam());
    ASSERT_EQ(this->m_point2D.y(), TypeParam());
}


TYPED_TEST(PointTest, DefaultConstructor_PointWithThreeCoordinates_IsOrigin)
{
    ASSERT_EQ(this->m_point3D.x(), TypeParam());
    ASSERT_EQ(this->m_point3D.y(), TypeParam());
    ASSERT_EQ(this->m_point3D.z(), TypeParam());
}


TYPED_TEST(PointTest, ConstructorWithParameters_PointWithOneCorrdinate_PointIsWellSet)
{
    using namespace cxmath;

    Point<TypeParam, 1> point{cxutil::narrow_cast<TypeParam>(1)};

    ASSERT_EQ(point.x(), cxutil::narrow_cast<TypeParam>(1));
}


TYPED_TEST(PointTest, ConstructorWithParameters_PointWithTwoCorrdinates_PointIsWellSet)
{
    using namespace cxmath;

    Point<TypeParam, 2> point{cxutil::narrow_cast<TypeParam>(1),
                              cxutil::narrow_cast<TypeParam>(2)};

    ASSERT_EQ(point.x(), cxutil::narrow_cast<TypeParam>(1));
    ASSERT_EQ(point.y(), cxutil::narrow_cast<TypeParam>(2));
}


TYPED_TEST(PointTest, ConstructorWithParameters_PointWithThreeCorrdinates_PointIsWellSet)
{
    using namespace cxmath;

    Point<TypeParam, 3> point{cxutil::narrow_cast<TypeParam>(1),
                                    cxutil::narrow_cast<TypeParam>(2),
                                    cxutil::narrow_cast<TypeParam>(3)};

    ASSERT_EQ(point.x(), cxutil::narrow_cast<TypeParam>(1));
    ASSERT_EQ(point.y(), cxutil::narrow_cast<TypeParam>(2));
    ASSERT_EQ(point.z(), cxutil::narrow_cast<TypeParam>(3));
}


TYPED_TEST(PointTest, MutatorX_PointWithOneCoordinate_UpdatesXCoordinateValue)
{
    using namespace cxmath;

    Point<TypeParam, 1> point;

    ASSERT_NE(point.x(), cxutil::narrow_cast<TypeParam>(10));

    point.x() = cxutil::narrow_cast<TypeParam>(10);

    ASSERT_EQ(point.x(), cxutil::narrow_cast<TypeParam>(10));
}

TYPED_TEST(PointTest, MutatorX_PointWithTwoCoordinates_UpdatesXCoordinateValue)
{
    using namespace cxmath;

    Point<TypeParam, 2> point;

    ASSERT_NE(point.x(), cxutil::narrow_cast<TypeParam>(10));

    point.x() = cxutil::narrow_cast<TypeParam>(10);

    ASSERT_EQ(point.x(), cxutil::narrow_cast<TypeParam>(10));
}

TYPED_TEST(PointTest, MutatorX_PointWithThreeCoordinates_UpdatesXCoordinateValue)
{
    using namespace cxmath;

    Point<TypeParam, 3> point;

    ASSERT_NE(point.x(), cxutil::narrow_cast<TypeParam>(10));

    point.x() = cxutil::narrow_cast<TypeParam>(10);

    ASSERT_EQ(point.x(), cxutil::narrow_cast<TypeParam>(10));
}


TYPED_TEST(PointTest, MutatorY_PointWithTwoCoordinates_UpdatesYCoordinateValue)
{
    using namespace cxmath;

    Point<TypeParam, 2> point;

    ASSERT_NE(point.y(), cxutil::narrow_cast<TypeParam>(10));

    point.y() = cxutil::narrow_cast<TypeParam>(10);

    ASSERT_EQ(point.y(), cxutil::narrow_cast<TypeParam>(10));
}


TYPED_TEST(PointTest, MutatorY_PointWithThreeCoordinates_UpdatesYCoordinateValue)
{
    using namespace cxmath;

    Point<TypeParam, 3> point;

    ASSERT_NE(point.y(), cxutil::narrow_cast<TypeParam>(10));

    point.y() = cxutil::narrow_cast<TypeParam>(10);

    ASSERT_EQ(point.y(), cxutil::narrow_cast<TypeParam>(10));
}


TYPED_TEST(PointTest, MutatorZ_PointWithThreeCoordinates_UpdatesZCoordinateValue)
{
    using namespace cxmath;

    Point<TypeParam, 3> point;

    ASSERT_NE(point.z(), cxutil::narrow_cast<TypeParam>(10));

    point.z() = cxutil::narrow_cast<TypeParam>(10);

    ASSERT_EQ(point.z(), cxutil::narrow_cast<TypeParam>(10));
}


TYPED_TEST(PointTest, SubscriptOperatorAccessor_IndexBelowZero_ExceptionThrown)
{
    ASSERT_THROW(this->m_point1D[-1], PreconditionException);
    ASSERT_THROW(this->m_point2D[-1], PreconditionException);
    ASSERT_THROW(this->m_point3D[-1], PreconditionException);
}


TYPED_TEST(PointTest, SubscriptOperatorAccessor_1DIndexIs1_ExceptionThrown)
{
    ASSERT_THROW(this->m_point1D[1], PreconditionException);
}


TYPED_TEST(PointTest, SubscriptOperatorAccessor_2DIndexIs2_ExceptionThrown)
{
    ASSERT_THROW(this->m_point2D[2], PreconditionException);
}


TYPED_TEST(PointTest, SubscriptOperatorAccessor_3DIndexIs3_ExceptionThrown)
{
    ASSERT_THROW(this->m_point1D[3], PreconditionException);
}


TYPED_TEST(PointTest, SubscriptOperatorAccessor_PointWithOneCoordinate_GetsX)
{
    using namespace cxmath;

    Point<TypeParam, 1> point;

    ASSERT_NE(point.x(), cxutil::narrow_cast<TypeParam>(10));

    point.x() = cxutil::narrow_cast<TypeParam>(10);

    ASSERT_EQ(point.x(), cxutil::narrow_cast<TypeParam>(10));

    // Check that both accessors are yield the same result:
    ASSERT_EQ(point[0], point.x());
}


TYPED_TEST(PointTest, SubscriptOperatorAccessor_PointWithTwoCoordinates_GetsX)
{
    using namespace cxmath;

    Point<TypeParam, 2> point;

    ASSERT_NE(point.x(), cxutil::narrow_cast<TypeParam>(10));

    point.x() = cxutil::narrow_cast<TypeParam>(10);

    ASSERT_EQ(point.x(), cxutil::narrow_cast<TypeParam>(10));

    // Check that both accessors are yield the same result:
    ASSERT_EQ(point[0], point.x());
}


TYPED_TEST(PointTest, SubscriptOperatorAccessor_PointWithThreeCoordinates_GetsX)
{
    using namespace cxmath;

    Point<TypeParam, 3> point;

    ASSERT_NE(point.x(), cxutil::narrow_cast<TypeParam>(10));

    point.x() = cxutil::narrow_cast<TypeParam>(10);

    ASSERT_EQ(point.x(), cxutil::narrow_cast<TypeParam>(10));

    // Check that both accessors are yield the same result:
    ASSERT_EQ(point[0], point.x());
}


TYPED_TEST(PointTest, SubscriptOperatorAccessor_PointWithTwoCoordinates_GetsY)
{
    using namespace cxmath;

    Point<TypeParam, 2> point;

    ASSERT_NE(point.y(), cxutil::narrow_cast<TypeParam>(10));

    point.y() = cxutil::narrow_cast<TypeParam>(10);

    ASSERT_EQ(point.y(), cxutil::narrow_cast<TypeParam>(10));

    // Check that both accessors are yield the same result:
    ASSERT_EQ(point[1], point.y());
}


TYPED_TEST(PointTest, SubscriptOperatorAccessor_PointWithThreeCoordinates_GetsY)
{
    using namespace cxmath;

    Point<TypeParam, 3> point;

    ASSERT_NE(point.y(), cxutil::narrow_cast<TypeParam>(10));

    point.y() = cxutil::narrow_cast<TypeParam>(10);

    ASSERT_EQ(point.y(), cxutil::narrow_cast<TypeParam>(10));

    // Check that both accessors are yield the same result:
    ASSERT_EQ(point[1], point.y());
}


TYPED_TEST(PointTest, SubscriptOperatorAccessor_PointWithThreeCoordinates_GetsZ)
{
    using namespace cxmath;

    Point<TypeParam, 3> point;

    ASSERT_NE(point.z(), cxutil::narrow_cast<TypeParam>(10));

    point.z() = cxutil::narrow_cast<TypeParam>(10);

    ASSERT_EQ(point.z(), cxutil::narrow_cast<TypeParam>(10));

    // Check that both accessors are yield the same result:
    ASSERT_EQ(point[2], point.z());
}


TYPED_TEST(PointTest, SubscriptOperatorMutator_IndexBelowZero_ExceptionThrown)
{
    ASSERT_THROW(this->m_point1D[-1] = cxutil::narrow_cast<TypeParam>(10), PreconditionException);
    ASSERT_THROW(this->m_point2D[-1] = cxutil::narrow_cast<TypeParam>(10), PreconditionException);
    ASSERT_THROW(this->m_point3D[-1] = cxutil::narrow_cast<TypeParam>(10), PreconditionException);
}


TYPED_TEST(PointTest, SubscriptOperatorMutator_1DIndexIs1_ExceptionThrown)
{
    ASSERT_THROW(this->m_point1D[1] = cxutil::narrow_cast<TypeParam>(10), PreconditionException);
}


TYPED_TEST(PointTest, SubscriptOperatorMutator_2DIndexIs2_ExceptionThrown)
{
    ASSERT_THROW(this->m_point2D[2] = cxutil::narrow_cast<TypeParam>(10), PreconditionException);
}


TYPED_TEST(PointTest, SubscriptOperatorMutator_3DIndexIs3_ExceptionThrown)
{
    ASSERT_THROW(this->m_point3D[3] = cxutil::narrow_cast<TypeParam>(10), PreconditionException);
}


TYPED_TEST(PointTest, SubscriptOperatorMutator_PointWithOneCoordinate_UpdatesX)
{
    using namespace cxmath;

    Point<TypeParam, 1> point;

    ASSERT_NE(point.x(), cxutil::narrow_cast<TypeParam>(10));

    point[0] = cxutil::narrow_cast<TypeParam>(10);

    ASSERT_EQ(point.x(), cxutil::narrow_cast<TypeParam>(10));
}


TYPED_TEST(PointTest, SubscriptOperatorMutator_PointWithTwoCoordinates_UpdatesX)
{
    using namespace cxmath;

    Point<TypeParam, 2> point;

    ASSERT_NE(point.x(), cxutil::narrow_cast<TypeParam>(10));

    point[0] = cxutil::narrow_cast<TypeParam>(10);

    ASSERT_EQ(point.x(), cxutil::narrow_cast<TypeParam>(10));
}


TYPED_TEST(PointTest, SubscriptOperatorMutator_PointWithThreeCoordinates_UpdatesX)
{
    using namespace cxmath;

    Point<TypeParam, 3> point;

    ASSERT_NE(point.x(), cxutil::narrow_cast<TypeParam>(10));

    point[0] = cxutil::narrow_cast<TypeParam>(10);

    ASSERT_EQ(point.x(), cxutil::narrow_cast<TypeParam>(10));
}


TYPED_TEST(PointTest, SubscriptOperatorMutator_PointWithTwoCoordinates_UpdatesY)
{
    using namespace cxmath;

    Point<TypeParam, 2> point;

    ASSERT_NE(point.y(), cxutil::narrow_cast<TypeParam>(10));

    point[1] = cxutil::narrow_cast<TypeParam>(10);

    ASSERT_EQ(point.y(), cxutil::narrow_cast<TypeParam>(10));
}


TYPED_TEST(PointTest, SubscriptOperatorMutator_PointWithThreeCoordinates_UpdatesY)
{
    using namespace cxmath;

    Point<TypeParam, 3> point;

    ASSERT_NE(point.y(), cxutil::narrow_cast<TypeParam>(10));

    point[1] = cxutil::narrow_cast<TypeParam>(10);

    ASSERT_EQ(point.y(), cxutil::narrow_cast<TypeParam>(10));
}


TYPED_TEST(PointTest, SubscriptOperatorMutator_PointWithThreeCoordinates_UpdatesZ)
{
    using namespace cxmath;

    Point<TypeParam, 3> point;

    ASSERT_NE(point.z(), cxutil::narrow_cast<TypeParam>(10));

    point[2] = cxutil::narrow_cast<TypeParam>(10);

    ASSERT_EQ(point.z(), cxutil::narrow_cast<TypeParam>(10));
}


TYPED_TEST(PointTest, EqualityOperator_TwoEqualPoints1D_ReturnsTrue)
{
    using namespace cxmath;

    const Point<TypeParam, 1> left{cxutil::narrow_cast<TypeParam>(1)};
    const Point<TypeParam, 1> right{cxutil::narrow_cast<TypeParam>(1)};

    ASSERT_TRUE(left == right);
}


TYPED_TEST(PointTest, EqualityOperator_TwoEqualPoints2D_ReturnsTrue)
{
    using namespace cxmath;

    const Point<TypeParam, 2> left{cxutil::narrow_cast<TypeParam>(1),
                                   cxutil::narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 2> right{cxutil::narrow_cast<TypeParam>(1),
                                    cxutil::narrow_cast<TypeParam>(2)};

    ASSERT_TRUE(left == right);
}


TYPED_TEST(PointTest, EqualityOperator_TwoEqualPoints3D_ReturnsTrue)
{
    using namespace cxmath;

    const Point<TypeParam, 3> left{cxutil::narrow_cast<TypeParam>(1),
                                   cxutil::narrow_cast<TypeParam>(2),
                                   cxutil::narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> right{cxutil::narrow_cast<TypeParam>(1),
                                    cxutil::narrow_cast<TypeParam>(2),
                                    cxutil::narrow_cast<TypeParam>(3)};

    ASSERT_TRUE(left == right);
}


TYPED_TEST(PointTest, EqualityOperator_TwoDifferentPoints1D_ReturnsFalse)
{
    using namespace cxmath;

    const Point<TypeParam, 1> left{cxutil::narrow_cast<TypeParam>(1)};
    const Point<TypeParam, 1> right{cxutil::narrow_cast<TypeParam>(-1)};

    ASSERT_FALSE(left == right);
}


TYPED_TEST(PointTest, EqualityOperator_TwoDifferentPoints2D_ReturnsFalse)
{
    using namespace cxmath;

    const Point<TypeParam, 2> left{cxutil::narrow_cast<TypeParam>(1),
                                   cxutil::narrow_cast<TypeParam>(-2)};

    const Point<TypeParam, 2> right{cxutil::narrow_cast<TypeParam>(1),
                                    cxutil::narrow_cast<TypeParam>(2)};

    ASSERT_FALSE(left == right);
}


TYPED_TEST(PointTest, EqualityOperator_TwoDifferentPoints3D_ReturnsFalse)
{
    using namespace cxmath;

    const Point<TypeParam, 3> left{cxutil::narrow_cast<TypeParam>(1),
                                   cxutil::narrow_cast<TypeParam>(2),
                                   cxutil::narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> right{cxutil::narrow_cast<TypeParam>(1),
                                    cxutil::narrow_cast<TypeParam>(2),
                                    cxutil::narrow_cast<TypeParam>(-3)};

    ASSERT_FALSE(left == right);
}


TYPED_TEST(PointTest, NonEqualityOperator_TwoDifferentPoints1D_ReturnsTrue)
{
    using namespace cxmath;

    const Point<TypeParam, 1> left{cxutil::narrow_cast<TypeParam>(1)};
    const Point<TypeParam, 1> right{cxutil::narrow_cast<TypeParam>(-1)};

    ASSERT_TRUE(left != right);
}


TYPED_TEST(PointTest, NonEqualityOperator_TwoDifferentPoints2D_ReturnsTrue)
{
    using namespace cxmath;

    const Point<TypeParam, 2> left{cxutil::narrow_cast<TypeParam>(1),
                                   cxutil::narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 2> right{cxutil::narrow_cast<TypeParam>(-1),
                                    cxutil::narrow_cast<TypeParam>(2)};

    ASSERT_TRUE(left != right);
}


TYPED_TEST(PointTest, NonEqualityOperator_TwoDifferentPoints3D_ReturnsTrue)
{
    using namespace cxmath;

    const Point<TypeParam, 3> left{cxutil::narrow_cast<TypeParam>(1),
                                   cxutil::narrow_cast<TypeParam>(-2),
                                   cxutil::narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> right{cxutil::narrow_cast<TypeParam>(1),
                                    cxutil::narrow_cast<TypeParam>(2),
                                    cxutil::narrow_cast<TypeParam>(3)};

    ASSERT_TRUE(left != right);
}


TYPED_TEST(PointTest, NonEqualityOperator_TwoEqualPoints1D_ReturnsFalse)
{
    using namespace cxmath;

    const Point<TypeParam, 1> left{cxutil::narrow_cast<TypeParam>(1)};
    const Point<TypeParam, 1> right{cxutil::narrow_cast<TypeParam>(1)};

    ASSERT_FALSE(left != right);
}


TYPED_TEST(PointTest, NonEqualityOperator_TwoEqualPoints2D_ReturnsFalse)
{
    using namespace cxmath;

    const Point<TypeParam, 2> left{cxutil::narrow_cast<TypeParam>(1),
                                   cxutil::narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 2> right{cxutil::narrow_cast<TypeParam>(1),
                                    cxutil::narrow_cast<TypeParam>(2)};

    ASSERT_FALSE(left != right);
}


TYPED_TEST(PointTest, NonEqualityOperator_TwoEqualPoints3D_ReturnsFalse)
{
    using namespace cxmath;

    const Point<TypeParam, 3> left{cxutil::narrow_cast<TypeParam>(1),
                                   cxutil::narrow_cast<TypeParam>(2),
                                   cxutil::narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> right{cxutil::narrow_cast<TypeParam>(1),
                                    cxutil::narrow_cast<TypeParam>(2),
                                    cxutil::narrow_cast<TypeParam>(3)};

    ASSERT_FALSE(left != right);
}
