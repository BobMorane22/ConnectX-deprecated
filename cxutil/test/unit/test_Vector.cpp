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
 * @file    test_Vector.cpp
 * @author  Eric Poirier
 * @date    August 2018
 * @version 1.0
 *
 * Unit tests for a the @c Vector class template.
 *
 **************************************************************************************************/

#include <gtest/gtest.h>

#include <cxutil/include/narrow_cast.h>
#include <cxutil/include/Vector.h>

template <typename T>
class VectorTest : public ::testing::Test
{

public:

    VectorTest() = default;
    virtual ~VectorTest() = default;

    const cxutil::math::Vector<T, 1> addIden1D{cxutil::math::additionIdentity<T, 1>()};
    const cxutil::math::Vector<T, 2> addIden2D{cxutil::math::additionIdentity<T, 2>()};
    const cxutil::math::Vector<T, 3> addIden3D{cxutil::math::additionIdentity<T, 3>()};

    cxutil::math::Vector<T, 1> m_vector1D;
    cxutil::math::Vector<T, 2> m_vector2D;
    cxutil::math::Vector<T, 3> m_vector3D;
};

typedef ::testing::Types<char, short, int, double, long long, long double> VectorRelatedTypes;
TYPED_TEST_CASE(VectorTest, VectorRelatedTypes);


TYPED_TEST(VectorTest, DefaultConstructor_1D_FromOriginLengthIs0)
{
    ASSERT_EQ(this->m_vector1D.x(), cxutil::narrow_cast<TypeParam>(0));
}


TYPED_TEST(VectorTest, DefaultConstructor_2D_FromOriginLengthIs0)
{
    ASSERT_EQ(this->m_vector2D.x(), cxutil::narrow_cast<TypeParam>(0));
    ASSERT_EQ(this->m_vector2D.y(), cxutil::narrow_cast<TypeParam>(0));
}


TYPED_TEST(VectorTest, DefaultConstructor_3D_FromOriginLengthIs0)
{
    ASSERT_EQ(this->m_vector3D.x(), cxutil::narrow_cast<TypeParam>(0));
    ASSERT_EQ(this->m_vector3D.y(), cxutil::narrow_cast<TypeParam>(0));
    ASSERT_EQ(this->m_vector3D.z(), cxutil::narrow_cast<TypeParam>(0));
}


TYPED_TEST(VectorTest, ConstructorWithParameters_1D_VectorWellDefined)
{
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin     {cxutil::narrow_cast<TypeParam>(1)};
    const Point<TypeParam, 1> destination{cxutil::narrow_cast<TypeParam>(3)};

    const Vector<TypeParam, 1> vector{origin, destination};

    ASSERT_EQ(vector.x(), cxutil::narrow_cast<TypeParam>(2));

    ASSERT_EQ(vector.origin(), origin);
    ASSERT_EQ(vector.destination(), destination);
}


TYPED_TEST(VectorTest, ConstructorWithParameters_2D_VectorWellDefined)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin{cxutil::narrow_cast<TypeParam>(1),
                                     cxutil::narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 2> destination{cxutil::narrow_cast<TypeParam>(3),
                                          cxutil::narrow_cast<TypeParam>(4)};

    const Vector<TypeParam, 2> vector{origin, destination};

    ASSERT_EQ(vector.x(), cxutil::narrow_cast<TypeParam>(2));
    ASSERT_EQ(vector.y(), cxutil::narrow_cast<TypeParam>(2));

    ASSERT_EQ(vector.origin(), origin);
    ASSERT_EQ(vector.destination(), destination);
}


TYPED_TEST(VectorTest, ConstructorWithParameters_3D_VectorWellDefined)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin{cxutil::narrow_cast<TypeParam>(1),
                                     cxutil::narrow_cast<TypeParam>(2),
                                     cxutil::narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> destination{cxutil::narrow_cast<TypeParam>(3),
                                          cxutil::narrow_cast<TypeParam>(4),
                                          cxutil::narrow_cast<TypeParam>(5)};

    const Vector<TypeParam, 3> vector{origin, destination};

    ASSERT_EQ(vector.x(), cxutil::narrow_cast<TypeParam>(2));
    ASSERT_EQ(vector.y(), cxutil::narrow_cast<TypeParam>(2));
    ASSERT_EQ(vector.z(), cxutil::narrow_cast<TypeParam>(2));

    ASSERT_EQ(vector.origin(), origin);
    ASSERT_EQ(vector.destination(), destination);
}


TYPED_TEST(VectorTest, Origin_ZeroVector1D_ReturnsOrigin)
{
    const cxutil::math::Point<TypeParam, 1> origin;

    ASSERT_EQ(this->m_vector1D.origin(), origin);
}


TYPED_TEST(VectorTest, Origin_ZeroVector2D_ReturnsOrigin)
{
    const cxutil::math::Point<TypeParam, 2> origin;

    ASSERT_EQ(this->m_vector2D.origin(), origin);
}


TYPED_TEST(VectorTest, Origin_ZeroVector3D_ReturnsOrigin)
{
    const cxutil::math::Point<TypeParam, 3> origin;

    ASSERT_EQ(this->m_vector3D.origin(), origin);
}


TYPED_TEST(VectorTest, Origin_SomeVector1D_ReturnsOrigin)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin{narrow_cast<TypeParam>(1)};
    const Vector<TypeParam, 1> vector{origin, Point<TypeParam, 1>()};

    ASSERT_EQ(vector.origin(), origin);
}


TYPED_TEST(VectorTest, Origin_SomeVector2D_ReturnsOrigin)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin{narrow_cast<TypeParam>(1),
                                     narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 2> vector{origin, Point<TypeParam, 2>()};

    ASSERT_EQ(vector.origin(), origin);
}


TYPED_TEST(VectorTest, Origin_SomeVector3D_ReturnsOrigin)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin{narrow_cast<TypeParam>(1),
                                     narrow_cast<TypeParam>(2),
                                     narrow_cast<TypeParam>(3)};

    const Vector<TypeParam, 3> vector{origin, Point<TypeParam, 3>()};

    ASSERT_EQ(vector.origin(), origin);
}


TYPED_TEST(VectorTest, Origin_Two1DVectorsAdded_OriginOfTheFirstIsUnchanged)
{
    using namespace cxutil;
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 1> origin1{narrow_cast<TypeParam>(1)};
    const Point<TypeParam, 1> destination1{narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 1> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 1> origin2{narrow_cast<TypeParam>(-1)};
    const Point<TypeParam, 1> destination2{narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 1> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 1> sum{vector1 + vector2};

    ASSERT_EQ(sum.origin(), vector1.origin());
}


TYPED_TEST(VectorTest, Origin_Two1DVectorsSubstracted_OriginOfTheFirstIsUnchanged)
{
    using namespace cxutil;
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 1> origin1{narrow_cast<TypeParam>(1)};
    const Point<TypeParam, 1> destination1{narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 1> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 1> origin2{narrow_cast<TypeParam>(-1)};
    const Point<TypeParam, 1> destination2{narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 1> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 1> diff = vector1 - vector2;

    ASSERT_EQ(diff.origin(), vector1.origin());
}


TYPED_TEST(VectorTest, Origin_ScalarTimesA1DVector_OriginIsUnchanged)
{
    using namespace cxutil;
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 1> origin{narrow_cast<TypeParam>(1)};
    const Point<TypeParam, 1> destination{narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 1> vector{origin, destination};

    // Scalar:
    const TypeParam k{narrow_cast<TypeParam>(5)};

    // Operation:
    const Vector<TypeParam, 1> prod = k*vector;

    ASSERT_EQ(prod.origin(), vector.origin());
}


TYPED_TEST(VectorTest, Origin_1DVectorTimesAScalar_OriginIsUnchanged)
{
    using namespace cxutil;
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 1> origin{narrow_cast<TypeParam>(1)};
    const Point<TypeParam, 1> destination{narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 1> vector{origin, destination};

    // Scalar:
    const TypeParam k{narrow_cast<TypeParam>(5)};

    // Operation:
    const Vector<TypeParam, 1> prod = vector*k;

    ASSERT_EQ(prod.origin(), vector.origin());
}


TYPED_TEST(VectorTest, Origin_Two2DVectorsAdded_OriginOfTheFirstIsUnchanged)
{
    using namespace cxutil;
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 2> origin1{narrow_cast<TypeParam>(1),
                                      narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 2> destination1{narrow_cast<TypeParam>(2),
                                           narrow_cast<TypeParam>(4)};

    const Vector<TypeParam, 2> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 2> origin2{narrow_cast<TypeParam>(-1),
                                      narrow_cast<TypeParam>(-2)};

    const Point<TypeParam, 2> destination2{narrow_cast<TypeParam>(2),
                                           narrow_cast<TypeParam>(3)};

    const Vector<TypeParam, 2> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 2> sum{vector1 + vector2};

    ASSERT_EQ(sum.origin(), vector1.origin());
}


TYPED_TEST(VectorTest, Origin_Two2DVectorsSubstracted_OriginOfTheFirstIsUnchanged)
{
    using namespace cxutil;
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 2> origin1{narrow_cast<TypeParam>(1),
                                      narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 2> destination1{narrow_cast<TypeParam>(2),
                                           narrow_cast<TypeParam>(4)};

    const Vector<TypeParam, 2> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 2> origin2{narrow_cast<TypeParam>(-1),
                                      narrow_cast<TypeParam>(-2)};

    const Point<TypeParam, 2> destination2{narrow_cast<TypeParam>(2),
                                           narrow_cast<TypeParam>(3)};

    const Vector<TypeParam, 2> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 2> diff = vector1 - vector2;

    ASSERT_EQ(diff.origin(), vector1.origin());
}


TYPED_TEST(VectorTest, Origin_ScalarTimesA2DVector_OriginIsUnchanged)
{
    using namespace cxutil;
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 2> origin{narrow_cast<TypeParam>(1),
                                     narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 2> destination{narrow_cast<TypeParam>(2),
                                          narrow_cast<TypeParam>(4)};

    const Vector<TypeParam, 2> vector{origin, destination};

    // Scalar:
    const TypeParam k{narrow_cast<TypeParam>(5)};

    // Operation:
    const Vector<TypeParam, 2> prod = k*vector;

    ASSERT_EQ(prod.origin(), vector.origin());
}


TYPED_TEST(VectorTest, Origin_2DVectorTimesAScalar_OriginIsUnchanged)
{
    using namespace cxutil;
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 2> origin{narrow_cast<TypeParam>(1),
                                     narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 2> destination{narrow_cast<TypeParam>(2),
                                          narrow_cast<TypeParam>(4)};

    const Vector<TypeParam, 2> vector{origin, destination};

    // Scalar:
    const TypeParam k{narrow_cast<TypeParam>(5)};

    // Operation:
    const Vector<TypeParam, 2> prod = vector*k;

    ASSERT_EQ(prod.origin(), vector.origin());
}


TYPED_TEST(VectorTest, Origin_Two3DVectorsAdded_OriginOfTheFirstIsUnchanged)
{
    using namespace cxutil;
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 3> origin1{narrow_cast<TypeParam>(1),
                                      narrow_cast<TypeParam>(2),
                                      narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> destination1{narrow_cast<TypeParam>(2),
                                           narrow_cast<TypeParam>(4),
                                           narrow_cast<TypeParam>(6)};

    const Vector<TypeParam, 3> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 3> origin2{narrow_cast<TypeParam>(-1),
                                      narrow_cast<TypeParam>(-2),
                                      narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> destination2{narrow_cast<TypeParam>(2),
                                           narrow_cast<TypeParam>(3),
                                           narrow_cast<TypeParam>(4)};

    const Vector<TypeParam, 3> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 3> sum{vector1 + vector2};

    ASSERT_EQ(sum.origin(), vector1.origin());
}


TYPED_TEST(VectorTest, Origin_Two3DVectorsSubstracted_OriginOfTheFirstIsUnchanged)
{
    using namespace cxutil;
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 3> origin1{narrow_cast<TypeParam>(1),
                                      narrow_cast<TypeParam>(2),
                                      narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> destination1{narrow_cast<TypeParam>(2),
                                           narrow_cast<TypeParam>(4),
                                           narrow_cast<TypeParam>(6)};

    const Vector<TypeParam, 3> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 3> origin2{narrow_cast<TypeParam>(-1),
                                      narrow_cast<TypeParam>(-2),
                                      narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> destination2{narrow_cast<TypeParam>(2),
                                           narrow_cast<TypeParam>(3),
                                           narrow_cast<TypeParam>(4)};

    const Vector<TypeParam, 3> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 3> diff = vector1 - vector2;

    ASSERT_EQ(diff.origin(), vector1.origin());
}


TYPED_TEST(VectorTest, Origin_ScalarTimesA3DVector_OriginIsUnchanged)
{
    using namespace cxutil;
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 3> origin{narrow_cast<TypeParam>(1),
                                     narrow_cast<TypeParam>(2),
                                     narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> destination{narrow_cast<TypeParam>(2),
                                          narrow_cast<TypeParam>(4),
                                          narrow_cast<TypeParam>(6)};

    const Vector<TypeParam, 3> vector{origin, destination};

    // Scalar:
    const TypeParam k{narrow_cast<TypeParam>(5)};

    // Operation:
    const Vector<TypeParam, 3> prod = k*vector;

    ASSERT_EQ(prod.origin(), vector.origin());
}


TYPED_TEST(VectorTest, Origin_3DVectorTimesAScalar_OriginIsUnchanged)
{
    using namespace cxutil;
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 3> origin{narrow_cast<TypeParam>(1),
                                     narrow_cast<TypeParam>(2),
                                     narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> destination{narrow_cast<TypeParam>(2),
                                          narrow_cast<TypeParam>(4),
                                          narrow_cast<TypeParam>(6)};

    const Vector<TypeParam, 3> vector{origin, destination};

    // Scalar:
    const TypeParam k{narrow_cast<TypeParam>(5)};

    // Operation:
    const Vector<TypeParam, 3> prod = vector*k;

    ASSERT_EQ(prod.origin(), vector.origin());
}



TYPED_TEST(VectorTest, Destination_ZeroVector1D_ReturnsOrigin)
{
    const cxutil::math::Point<TypeParam, 1> origin;

    ASSERT_EQ(this->m_vector1D.destination(), origin);
}


TYPED_TEST(VectorTest, Destination_ZeroVector2D_ReturnsOrigin)
{
    const cxutil::math::Point<TypeParam, 2> origin;

    ASSERT_EQ(this->m_vector2D.destination(), origin);
}


TYPED_TEST(VectorTest, Destination_ZeroVector3D_ReturnsOrigin)
{
    const cxutil::math::Point<TypeParam, 3> origin;

    ASSERT_EQ(this->m_vector3D.destination(), origin);
}


TYPED_TEST(VectorTest, Destination_SomeVector1D_ReturnsDestination)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin;
    const Point<TypeParam, 1> destination{narrow_cast<TypeParam>(1)};

    const Vector<TypeParam, 1> vector{origin, destination};

    ASSERT_EQ(vector.destination(), destination);
}


TYPED_TEST(VectorTest, Destination_SomeVector2D_ReturnsDestination)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin;
    const Point<TypeParam, 2> destination{narrow_cast<TypeParam>(1),
                                          narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 2> vector{origin, destination};

    ASSERT_EQ(vector.destination(), destination);
}


TYPED_TEST(VectorTest, Destination_SomeVector3D_ReturnsDestination)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin;
    const Point<TypeParam, 3> destination{narrow_cast<TypeParam>(1),
                                          narrow_cast<TypeParam>(2),
                                          narrow_cast<TypeParam>(3)};

    const Vector<TypeParam, 3> vector{origin, destination};

    ASSERT_EQ(vector.destination(), destination);
}


TYPED_TEST(VectorTest, Destination_Two1DVectorsAdded_ReturnsUpdatedDestination)
{
    using namespace cxutil;
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 1> origin1{narrow_cast<TypeParam>(1)};
    const Point<TypeParam, 1> destination1{narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 1> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 1> origin2{narrow_cast<TypeParam>(-1)};
    const Point<TypeParam, 1> destination2{narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 1> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 1> sum = vector1 + vector2;

    // Expected result:
    const Point<TypeParam, 1> expectedResult{narrow_cast<TypeParam>(5)};

    ASSERT_EQ(sum.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_Two1DVectorsSubstracted_ReturnsUpdatedDestination)
{
    using namespace cxutil;
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 1> origin1{narrow_cast<TypeParam>(1)};
    const Point<TypeParam, 1> destination1{narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 1> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 1> origin2{narrow_cast<TypeParam>(-1)};
    const Point<TypeParam, 1> destination2{narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 1> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 1> diff = vector1 - vector2;

    // Expected result:
    const Point<TypeParam, 1> expectedResult{narrow_cast<TypeParam>(-1)};

    ASSERT_EQ(diff.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_ScalarTimesA1DVector_ReturnsUpdatedDestination)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin{narrow_cast<TypeParam>(1)};

    const Point<TypeParam, 1> destination{narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 1> vector{origin, destination};

    const TypeParam k{narrow_cast<TypeParam>(5)};

    const Vector<TypeParam, 1> prod = k*vector;

    const Point<TypeParam, 1> expectedResult{narrow_cast<TypeParam>(6)};

    ASSERT_EQ(prod.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_1DVectorTimesAScalar_ReturnsUpdatedDestination)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin{narrow_cast<TypeParam>(1)};

    const Point<TypeParam, 1> destination{narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 1> vector{origin, destination};

    const TypeParam k{narrow_cast<TypeParam>(5)};

    const Vector<TypeParam, 1> prod = vector*k;

    const Point<TypeParam, 1> expectedResult{narrow_cast<TypeParam>(6)};

    ASSERT_EQ(prod.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_Two2DVectorsAdded_ReturnsUpdatedDestination)
{
    using namespace cxutil;
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 2> origin1{narrow_cast<TypeParam>(1),
                                      narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 2> destination1{narrow_cast<TypeParam>(2),
                                           narrow_cast<TypeParam>(4)};

    const Vector<TypeParam, 2> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 2> origin2{narrow_cast<TypeParam>(-1),
                                      narrow_cast<TypeParam>(-2)};

    const Point<TypeParam, 2> destination2{narrow_cast<TypeParam>(2),
                                           narrow_cast<TypeParam>(3)};

    const Vector<TypeParam, 2> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 2> sum = vector1 + vector2;

    // Expected result:
    const Point<TypeParam, 2> expectedResult{narrow_cast<TypeParam>(5),
                                             narrow_cast<TypeParam>(9)};

    ASSERT_EQ(sum.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_Two2DVectorsSubstracted_ReturnsUpdatedDestination)
{
    using namespace cxutil;
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 2> origin1{narrow_cast<TypeParam>(1),
                                      narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 2> destination1{narrow_cast<TypeParam>(2),
                                           narrow_cast<TypeParam>(4)};

    const Vector<TypeParam, 2> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 2> origin2{narrow_cast<TypeParam>(-1),
                                      narrow_cast<TypeParam>(-2)};

    const Point<TypeParam, 2> destination2{narrow_cast<TypeParam>(2),
                                           narrow_cast<TypeParam>(3)};

    const Vector<TypeParam, 2> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 2> diff = vector1 - vector2;

    // Expected result:
    const Point<TypeParam, 2> expectedResult{narrow_cast<TypeParam>(-1),
                                             narrow_cast<TypeParam>(-1)};

    ASSERT_EQ(diff.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_ScalarTimesA2DVector_ReturnsUpdatedDestination)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin{narrow_cast<TypeParam>(1),
                                     narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 2> destination{narrow_cast<TypeParam>(2),
                                          narrow_cast<TypeParam>(4)};

    const Vector<TypeParam, 2> vector{origin, destination};

    const TypeParam k{narrow_cast<TypeParam>(5)};

    const Vector<TypeParam, 2> prod = k*vector;

    const Point<TypeParam, 2> expectedResult{narrow_cast<TypeParam>(6),
                                             narrow_cast<TypeParam>(12)};

    ASSERT_EQ(prod.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_2DVectorTimesAScalar_ReturnsUpdatedDestination)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin{narrow_cast<TypeParam>(1),
                                     narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 2> destination{narrow_cast<TypeParam>(2),
                                          narrow_cast<TypeParam>(4)};

    const Vector<TypeParam, 2> vector{origin, destination};

    const TypeParam k{narrow_cast<TypeParam>(5)};

    const Vector<TypeParam, 2> prod = vector*k;

    const Point<TypeParam, 2> expectedResult{narrow_cast<TypeParam>(6),
                                             narrow_cast<TypeParam>(12)};

    ASSERT_EQ(prod.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_Two3DVectorsAdded_ReturnsUpdatedDestination)
{
    using namespace cxutil;
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 3> origin1{narrow_cast<TypeParam>(1),
                                      narrow_cast<TypeParam>(2),
                                      narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> destination1{narrow_cast<TypeParam>(2),
                                           narrow_cast<TypeParam>(4),
                                           narrow_cast<TypeParam>(6)};

    const Vector<TypeParam, 3> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 3> origin2{narrow_cast<TypeParam>(-1),
                                      narrow_cast<TypeParam>(-2),
                                      narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> destination2{narrow_cast<TypeParam>(2),
                                           narrow_cast<TypeParam>(3),
                                           narrow_cast<TypeParam>(4)};

    const Vector<TypeParam, 3> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 3> sum = vector1 + vector2;

    // Expected result:
    const Point<TypeParam, 3> expectedResult{narrow_cast<TypeParam>(5),
                                             narrow_cast<TypeParam>(9),
                                             narrow_cast<TypeParam>(7)};

    ASSERT_EQ(sum.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_Two3DVectorsSubstracted_ReturnsUpdatedDestination)
{
    using namespace cxutil;
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 3> origin1{narrow_cast<TypeParam>(1),
                                      narrow_cast<TypeParam>(2),
                                      narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> destination1{narrow_cast<TypeParam>(2),
                                           narrow_cast<TypeParam>(4),
                                           narrow_cast<TypeParam>(6)};

    const Vector<TypeParam, 3> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 3> origin2{narrow_cast<TypeParam>(-1),
                                      narrow_cast<TypeParam>(-2),
                                      narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> destination2{narrow_cast<TypeParam>(2),
                                           narrow_cast<TypeParam>(3),
                                           narrow_cast<TypeParam>(4)};

    const Vector<TypeParam, 3> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 3> diff = vector1 - vector2;

    // Expected result:
    const Point<TypeParam, 3> expectedResult{narrow_cast<TypeParam>(-1),
                                             narrow_cast<TypeParam>(-1),
                                             narrow_cast<TypeParam>(5)};

    ASSERT_EQ(diff.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_ScalarTimesA3DVector_ReturnsUpdatedDestination)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin{narrow_cast<TypeParam>(1),
                                     narrow_cast<TypeParam>(2),
                                     narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> destination{narrow_cast<TypeParam>(2),
                                          narrow_cast<TypeParam>(4),
                                          narrow_cast<TypeParam>(6)};

    const Vector<TypeParam, 3> vector{origin, destination};

    const TypeParam k{narrow_cast<TypeParam>(5)};

    const Vector<TypeParam, 3> prod = k*vector;

    const Point<TypeParam, 3> expectedResult{narrow_cast<TypeParam>(6),
                                             narrow_cast<TypeParam>(12),
                                             narrow_cast<TypeParam>(18)};

    ASSERT_EQ(prod.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_3DVectorTimesAScalar_ReturnsUpdatedDestination)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin{narrow_cast<TypeParam>(1),
                                     narrow_cast<TypeParam>(2),
                                     narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> destination{narrow_cast<TypeParam>(2),
                                          narrow_cast<TypeParam>(4),
                                          narrow_cast<TypeParam>(6)};

    const Vector<TypeParam, 3> vector{origin, destination};

    const TypeParam k{narrow_cast<TypeParam>(5)};

    const Vector<TypeParam, 3> prod = vector*k;

    const Point<TypeParam, 3> expectedResult{narrow_cast<TypeParam>(6),
                                             narrow_cast<TypeParam>(12),
                                             narrow_cast<TypeParam>(18)};

    ASSERT_EQ(prod.destination(), expectedResult);
}


TYPED_TEST(VectorTest, X_Origin1DVector_Returns0)
{
    ASSERT_EQ(this->m_vector1D.x(), cxutil::narrow_cast<TypeParam>(0));
}


TYPED_TEST(VectorTest, X_Origin2DVector_Returns0)
{
    ASSERT_EQ(this->m_vector2D.x(), cxutil::narrow_cast<TypeParam>(0));
}


TYPED_TEST(VectorTest, X_Origin3DVector_Returns0)
{
    ASSERT_EQ(this->m_vector3D.x(), cxutil::narrow_cast<TypeParam>(0));
}


TYPED_TEST(VectorTest, Y_Origin2DVector_Returns0)
{
    ASSERT_EQ(this->m_vector2D.y(), cxutil::narrow_cast<TypeParam>(0));
}


TYPED_TEST(VectorTest, Y_Origin3DVector_Returns0)
{
    ASSERT_EQ(this->m_vector3D.y(), cxutil::narrow_cast<TypeParam>(0));
}


TYPED_TEST(VectorTest, Z_Origin3DVector_Returns0)
{
    ASSERT_EQ(this->m_vector3D.z(), cxutil::narrow_cast<TypeParam>(0));
}


TYPED_TEST(VectorTest, X_Some1DVector_ReturnsXComponent)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin{narrow_cast<TypeParam>(1)};
    const Point<TypeParam, 1> destination{narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 1> vector{origin, destination};

    ASSERT_EQ(vector.x(), narrow_cast<TypeParam>(1));
}


TYPED_TEST(VectorTest, X_Some2DVector_ReturnsXComponent)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin{narrow_cast<TypeParam>(1),
                                     narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 2> destination{narrow_cast<TypeParam>(2),
                                          narrow_cast<TypeParam>(4)};

    const Vector<TypeParam, 2> vector{origin, destination};

    ASSERT_EQ(vector.x(), narrow_cast<TypeParam>(1));
}


TYPED_TEST(VectorTest, X_Some3DVector_ReturnsXComponent)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin{narrow_cast<TypeParam>(1),
                                     narrow_cast<TypeParam>(2),
                                     narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> destination{narrow_cast<TypeParam>(2),
                                          narrow_cast<TypeParam>(4),
                                          narrow_cast<TypeParam>(6)};

    const Vector<TypeParam, 3> vector{origin, destination};

    ASSERT_EQ(vector.x(), narrow_cast<TypeParam>(1));
}


TYPED_TEST(VectorTest, Y_Some2DVector_ReturnsYComponent)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin{narrow_cast<TypeParam>(1),
                                     narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 2> destination{narrow_cast<TypeParam>(2),
                                          narrow_cast<TypeParam>(4)};

    const Vector<TypeParam, 2> vector{origin, destination};

    ASSERT_EQ(vector.y(), narrow_cast<TypeParam>(2));
}


TYPED_TEST(VectorTest, Y_Some3DVector_ReturnsYComponent)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin{narrow_cast<TypeParam>(1),
                                     narrow_cast<TypeParam>(2),
                                     narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> destination{narrow_cast<TypeParam>(2),
                                          narrow_cast<TypeParam>(4),
                                          narrow_cast<TypeParam>(6)};

    const Vector<TypeParam, 3> vector{origin, destination};

    ASSERT_EQ(vector.y(), narrow_cast<TypeParam>(2));
}


TYPED_TEST(VectorTest, Z_Some3DVector_ReturnsZComponent)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin{narrow_cast<TypeParam>(1),
                                     narrow_cast<TypeParam>(2),
                                     narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> destination{narrow_cast<TypeParam>(2),
                                          narrow_cast<TypeParam>(4),
                                          narrow_cast<TypeParam>(6)};

    const Vector<TypeParam, 3> vector{origin, destination};

    ASSERT_EQ(vector.z(), narrow_cast<TypeParam>(3));
}


TYPED_TEST(VectorTest, SubscriptOperator_Some1DVectorSusbriptN_ExceptionThrown)
{
    ASSERT_THROW(this->m_vector1D[1], PreconditionException);
}


TYPED_TEST(VectorTest, SubscriptOperator_Some2DVectorSusbriptN_ExceptionThrown)
{
    ASSERT_THROW(this->m_vector2D[2], PreconditionException);
}


TYPED_TEST(VectorTest, SubscriptOperator_Some3DVectorSusbriptN_ExceptionThrown)
{
    ASSERT_THROW(this->m_vector3D[3], PreconditionException);
}


TYPED_TEST(VectorTest, SubscriptOperator_Some1DVector_ReturnsComponent)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin{narrow_cast<TypeParam>(1)};
    const Point<TypeParam, 1> destination{narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 1> vector{origin, destination};

    // Extra parentheses in the subscript is neccessary because ASSERT_EQ is a macro!
    ASSERT_EQ(vector[(Vector<TypeParam, 1>::X_COMPONENT)], vector.x());
}


TYPED_TEST(VectorTest, SubscriptOperator_Some2DVector_ReturnsComponent)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin{narrow_cast<TypeParam>(1),
                                     narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 2> destination{narrow_cast<TypeParam>(2),
                                          narrow_cast<TypeParam>(4)};

    const Vector<TypeParam, 2> vector{origin, destination};

    // Extra parentheses in the subscript is neccessary because ASSERT_EQ is a macro!
    ASSERT_EQ(vector[(Vector<TypeParam, 2>::X_COMPONENT)], vector.x());
    ASSERT_EQ(vector[(Vector<TypeParam, 2>::Y_COMPONENT)], vector.y());
}


TYPED_TEST(VectorTest, SubscriptOperator_Some3DVector_ReturnsComponent)
{
    using namespace cxutil;
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin{narrow_cast<TypeParam>(1),
                                     narrow_cast<TypeParam>(2),
                                     narrow_cast<TypeParam>(3)};

    const Point<TypeParam, 3> destination{narrow_cast<TypeParam>(2),
                                          narrow_cast<TypeParam>(4),
                                          narrow_cast<TypeParam>(6)};

    const Vector<TypeParam, 3> vector{origin, destination};

    // Extra parentheses in the subscript is neccessary because ASSERT_EQ is a macro!
    ASSERT_EQ(vector[(Vector<TypeParam, 3>::X_COMPONENT)], vector.x());
    ASSERT_EQ(vector[(Vector<TypeParam, 3>::Y_COMPONENT)], vector.y());
    ASSERT_EQ(vector[(Vector<TypeParam, 3>::Z_COMPONENT)], vector.z());
}


/***************************************************************************************************
 * A note to the developpers...
 *
 * The following tests verify that the cxutil::math::Vector class satisfies the  8 conditions of a
 * vector space over T. Let u, v and w be arbritary cxutil::math::Vector objects and a and b
 * scalars in T. We want to verify (only through unit testing, not formally) that:
 *
 *   1. u + (v + w) = (u + v) + w
 *   2. u + v = v + u
 *   3. v + 0 = v
 *   4. v + (−v) = 0
 *   5. a(bv) = (ab)v
 *   6. 1v = v
 *   7. a(u + v) = au + av
 *   8. (a + b)v = av + bv
 *
 * where 0 is the identity over addition and 1 is the identity over multiplication.
 *
 * These tests do not aim to prove that cxutil::math::Vector is a vector space over T, but
 * rather that is most likely is, based on various examples. In other works, these tests aim to
 * prove that the implementation of cxutil::math::Vector most likely agree with its theoretical
 * vector space properties. A formal proof that cxutil::math::Vector forms a vector space can be
 * obtained mathematically from its definition. See the cxutil::math::Vector for more details.
 *
 * Note: here, the definition of vector space is of course limited by the capacity of registers
 *       and hence is not as broad as the mathematical one. For extremely small or large values,
 *       the vector space conditions will not hold anymore since the capacity of registers to hold
 *       precision is limited.
 *
 **************************************************************************************************/

