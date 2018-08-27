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

#include <iostream>
#include <random>
#include <type_traits>

#include <gtest/gtest.h>

#include <cxutil/include/narrow_cast.h>
#include <cxutil/include/Vector.h>

template <typename T>
class VectorTest : public ::testing::Test
{

public:

    VectorTest() = default;
    virtual ~VectorTest() = default;

    cxutil::math::Vector<T, 1> m_vector1D;
    cxutil::math::Vector<T, 2> m_vector2D;
    cxutil::math::Vector<T, 3> m_vector3D;
};


typedef ::testing::Types<int, double, long long, long double> VectorRelatedTypes;
TYPED_TEST_CASE(VectorTest, VectorRelatedTypes);


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

    const Point<TypeParam, 1> origin     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination{make1DTestPoint<TypeParam>(3)};

    const Vector<TypeParam, 1> vector{origin, destination};

    ASSERT_EQ(vector.x(), cxutil::narrow_cast<TypeParam>(2));

    ASSERT_EQ(vector.origin(), origin);
    ASSERT_EQ(vector.destination(), destination);
}


TYPED_TEST(VectorTest, ConstructorWithParameters_2D_VectorWellDefined)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination{make2DTestPoint<TypeParam>(3, 4)};

    const Vector<TypeParam, 2> vector{origin, destination};

    ASSERT_EQ(vector.x(), cxutil::narrow_cast<TypeParam>(2));
    ASSERT_EQ(vector.y(), cxutil::narrow_cast<TypeParam>(2));

    ASSERT_EQ(vector.origin(), origin);
    ASSERT_EQ(vector.destination(), destination);
}


TYPED_TEST(VectorTest, ConstructorWithParameters_3D_VectorWellDefined)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination{make3DTestPoint<TypeParam>(3, 4, 5)};

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
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin{make1DTestPoint<TypeParam>(1)};
    const Vector<TypeParam, 1> vector{origin, Point<TypeParam, 1>()};

    ASSERT_EQ(vector.origin(), origin);
}


TYPED_TEST(VectorTest, Origin_SomeVector2D_ReturnsOrigin)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin{make2DTestPoint<TypeParam>(1, 2)};

    const Vector<TypeParam, 2> vector{origin, Point<TypeParam, 2>()};

    ASSERT_EQ(vector.origin(), origin);
}


TYPED_TEST(VectorTest, Origin_SomeVector3D_ReturnsOrigin)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin{make3DTestPoint<TypeParam>(1, 2, 3)};

    const Vector<TypeParam, 3> vector{origin, Point<TypeParam, 3>()};

    ASSERT_EQ(vector.origin(), origin);
}


TYPED_TEST(VectorTest, Origin_Two1DVectorsAdded_OriginOfTheFirstIsUnchanged)
{
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 1> origin1     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination1{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 1> origin2     {make1DTestPoint<TypeParam>(-1)};
    const Point<TypeParam, 1> destination2{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 1> sum{vector1 + vector2};

    ASSERT_EQ(sum.origin(), vector1.origin());
}


TYPED_TEST(VectorTest, Origin_Two1DVectorsSubstracted_OriginOfTheFirstIsUnchanged)
{
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 1> origin1     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination1{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 1> origin2     {make1DTestPoint<TypeParam>(-1)};
    const Point<TypeParam, 1> destination2{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 1> diff = vector1 - vector2;

    ASSERT_EQ(diff.origin(), vector1.origin());
}


TYPED_TEST(VectorTest, Origin_ScalarTimesA1DVector_OriginIsUnchanged)
{
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 1> origin     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> vector{origin, destination};

    // Scalar:
    const TypeParam k{cxutil::narrow_cast<TypeParam>(5)};

    // Operation:
    const Vector<TypeParam, 1> prod = k*vector;

    ASSERT_EQ(prod.origin(), vector.origin());
}


TYPED_TEST(VectorTest, Origin_1DVectorTimesAScalar_OriginIsUnchanged)
{
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 1> origin     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> vector{origin, destination};

    // Scalar:
    const TypeParam k{cxutil::narrow_cast<TypeParam>(5)};

    // Operation:
    const Vector<TypeParam, 1> prod = vector*k;

    ASSERT_EQ(prod.origin(), vector.origin());
}


TYPED_TEST(VectorTest, Origin_Two2DVectorsAdded_OriginOfTheFirstIsUnchanged)
{
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 2> origin1     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination1{make2DTestPoint<TypeParam>(2, 4)};

    const Vector<TypeParam, 2> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 2> origin2     {make2DTestPoint<TypeParam>(-1, -2)};
    const Point<TypeParam, 2> destination2{make2DTestPoint<TypeParam>(2, 3)};

    const Vector<TypeParam, 2> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 2> sum{vector1 + vector2};

    ASSERT_EQ(sum.origin(), vector1.origin());
}


TYPED_TEST(VectorTest, Origin_Two2DVectorsSubstracted_OriginOfTheFirstIsUnchanged)
{
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 2> origin1     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination1{make2DTestPoint<TypeParam>(2, 4)};

    const Vector<TypeParam, 2> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 2> origin2     {make2DTestPoint<TypeParam>(-1, -2)};
    const Point<TypeParam, 2> destination2{make2DTestPoint<TypeParam>(2, 3)};

    const Vector<TypeParam, 2> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 2> diff = vector1 - vector2;

    ASSERT_EQ(diff.origin(), vector1.origin());
}


TYPED_TEST(VectorTest, Origin_ScalarTimesA2DVector_OriginIsUnchanged)
{
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 2> origin     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination{make2DTestPoint<TypeParam>(2, 4)};

    const Vector<TypeParam, 2> vector{origin, destination};

    // Scalar:
    const TypeParam k{cxutil::narrow_cast<TypeParam>(5)};

    // Operation:
    const Vector<TypeParam, 2> prod = k*vector;

    ASSERT_EQ(prod.origin(), vector.origin());
}


TYPED_TEST(VectorTest, Origin_2DVectorTimesAScalar_OriginIsUnchanged)
{
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 2> origin     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination{make2DTestPoint<TypeParam>(2, 4)};

    const Vector<TypeParam, 2> vector{origin, destination};

    // Scalar:
    const TypeParam k{cxutil::narrow_cast<TypeParam>(5)};

    // Operation:
    const Vector<TypeParam, 2> prod = vector*k;

    ASSERT_EQ(prod.origin(), vector.origin());
}


TYPED_TEST(VectorTest, Origin_Two3DVectorsAdded_OriginOfTheFirstIsUnchanged)
{
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 3> origin1     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination1{make3DTestPoint<TypeParam>(2, 4, 6)};

    const Vector<TypeParam, 3> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 3> origin2     {make3DTestPoint<TypeParam>(-1, -2, 3)};
    const Point<TypeParam, 3> destination2{make3DTestPoint<TypeParam>(2, 3, 4)};

    const Vector<TypeParam, 3> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 3> sum{vector1 + vector2};

    ASSERT_EQ(sum.origin(), vector1.origin());
}


TYPED_TEST(VectorTest, Origin_Two3DVectorsSubstracted_OriginOfTheFirstIsUnchanged)
{
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 3> origin1     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination1{make3DTestPoint<TypeParam>(2, 4, 6)};

    const Vector<TypeParam, 3> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 3> origin2     {make3DTestPoint<TypeParam>(-1, -2, 3)};
    const Point<TypeParam, 3> destination2{make3DTestPoint<TypeParam>(2, 3, 4)};

    const Vector<TypeParam, 3> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 3> diff = vector1 - vector2;

    ASSERT_EQ(diff.origin(), vector1.origin());
}


TYPED_TEST(VectorTest, Origin_ScalarTimesA3DVector_OriginIsUnchanged)
{
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 3> origin     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination{make3DTestPoint<TypeParam>(2, 4, 6)};

    const Vector<TypeParam, 3> vector{origin, destination};

    // Scalar:
    const TypeParam k{cxutil::narrow_cast<TypeParam>(5)};

    // Operation:
    const Vector<TypeParam, 3> prod = k*vector;

    ASSERT_EQ(prod.origin(), vector.origin());
}


TYPED_TEST(VectorTest, Origin_3DVectorTimesAScalar_OriginIsUnchanged)
{
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 3> origin     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination{make3DTestPoint<TypeParam>(2, 4, 6)};

    const Vector<TypeParam, 3> vector{origin, destination};

    // Scalar:
    const TypeParam k{cxutil::narrow_cast<TypeParam>(5)};

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
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin;
    const Point<TypeParam, 1> destination{make1DTestPoint<TypeParam>(1)};

    const Vector<TypeParam, 1> vector{origin, destination};

    ASSERT_EQ(vector.destination(), destination);
}


TYPED_TEST(VectorTest, Destination_SomeVector2D_ReturnsDestination)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin;
    const Point<TypeParam, 2> destination{make2DTestPoint<TypeParam>(1, 2)};

    const Vector<TypeParam, 2> vector{origin, destination};

    ASSERT_EQ(vector.destination(), destination);
}


TYPED_TEST(VectorTest, Destination_SomeVector3D_ReturnsDestination)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin;
    const Point<TypeParam, 3> destination{make3DTestPoint<TypeParam>(1, 2, 3)};

    const Vector<TypeParam, 3> vector{origin, destination};

    ASSERT_EQ(vector.destination(), destination);
}


TYPED_TEST(VectorTest, Destination_Two1DVectorsAdded_ReturnsUpdatedDestination)
{
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 1> origin1     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination1{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 1> origin2     {make1DTestPoint<TypeParam>(-1)};
    const Point<TypeParam, 1> destination2{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 1> sum = vector1 + vector2;

    // Expected result:
    const Point<TypeParam, 1> expectedResult{make1DTestPoint<TypeParam>(5)};

    ASSERT_EQ(sum.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_Two1DVectorsSubstracted_ReturnsUpdatedDestination)
{
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 1> origin1     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination1{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 1> origin2     {make1DTestPoint<TypeParam>(-1)};
    const Point<TypeParam, 1> destination2{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 1> diff = vector1 - vector2;

    // Expected result:
    const Point<TypeParam, 1> expectedResult{make1DTestPoint<TypeParam>(-1)};

    ASSERT_EQ(diff.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_ScalarTimesA1DVector_ReturnsUpdatedDestination)
{
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> vector{origin, destination};

    const TypeParam k{cxutil::narrow_cast<TypeParam>(5)};

    const Vector<TypeParam, 1> prod = k*vector;

    const Point<TypeParam, 1> expectedResult{make1DTestPoint<TypeParam>(6)};

    ASSERT_EQ(prod.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_1DVectorTimesAScalar_ReturnsUpdatedDestination)
{
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> vector{origin, destination};

    const TypeParam k{cxutil::narrow_cast<TypeParam>(5)};

    const Vector<TypeParam, 1> prod = vector*k;

    const Point<TypeParam, 1> expectedResult{make1DTestPoint<TypeParam>(6)};

    ASSERT_EQ(prod.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_Two2DVectorsAdded_ReturnsUpdatedDestination)
{
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 2> origin1     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination1{make2DTestPoint<TypeParam>(2, 4)};

    const Vector<TypeParam, 2> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 2> origin2     {make2DTestPoint<TypeParam>(-1, -2)};
    const Point<TypeParam, 2> destination2{make2DTestPoint<TypeParam>(2, 3)};

    const Vector<TypeParam, 2> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 2> sum = vector1 + vector2;

    // Expected result:
    const Point<TypeParam, 2> expectedResult{make2DTestPoint<TypeParam>(5, 9)};

    ASSERT_EQ(sum.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_Two2DVectorsSubstracted_ReturnsUpdatedDestination)
{
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 2> origin1     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination1{make2DTestPoint<TypeParam>(2, 4)};

    const Vector<TypeParam, 2> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 2> origin2     {make2DTestPoint<TypeParam>(-1, -2)};
    const Point<TypeParam, 2> destination2{make2DTestPoint<TypeParam>(2, 3)};

    const Vector<TypeParam, 2> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 2> diff = vector1 - vector2;

    // Expected result:
    const Point<TypeParam, 2> expectedResult{make2DTestPoint<TypeParam>(-1, -1)};

    ASSERT_EQ(diff.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_ScalarTimesA2DVector_ReturnsUpdatedDestination)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination{make2DTestPoint<TypeParam>(2, 4)};

    const Vector<TypeParam, 2> vector{origin, destination};

    const TypeParam k{cxutil::narrow_cast<TypeParam>(5)};

    const Vector<TypeParam, 2> prod = k*vector;

    const Point<TypeParam, 2> expectedResult{make2DTestPoint<TypeParam>(6, 12)};

    ASSERT_EQ(prod.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_2DVectorTimesAScalar_ReturnsUpdatedDestination)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination{make2DTestPoint<TypeParam>(2, 4)};

    const Vector<TypeParam, 2> vector{origin, destination};

    const TypeParam k{cxutil::narrow_cast<TypeParam>(5)};

    const Vector<TypeParam, 2> prod = vector*k;

    const Point<TypeParam, 2> expectedResult{make2DTestPoint<TypeParam>(6, 12)};

    ASSERT_EQ(prod.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_Two3DVectorsAdded_ReturnsUpdatedDestination)
{
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 3> origin1     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination1{make3DTestPoint<TypeParam>(2, 4, 6)};

    const Vector<TypeParam, 3> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 3> origin2     {make3DTestPoint<TypeParam>(-1, -2, 3)};
    const Point<TypeParam, 3> destination2{make3DTestPoint<TypeParam>(2, 3, 4)};

    const Vector<TypeParam, 3> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 3> sum = vector1 + vector2;

    // Expected result:
    const Point<TypeParam, 3> expectedResult{make3DTestPoint<TypeParam>(5, 9, 7)};

    ASSERT_EQ(sum.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_Two3DVectorsSubstracted_ReturnsUpdatedDestination)
{
    using namespace cxutil::math;

    // First vector:
    const Point<TypeParam, 3> origin1     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination1{make3DTestPoint<TypeParam>(2, 4, 6)};

    const Vector<TypeParam, 3> vector1{origin1, destination1};

    // Second vector:
    const Point<TypeParam, 3> origin2     {make3DTestPoint<TypeParam>(-1, -2, 3)};
    const Point<TypeParam, 3> destination2{make3DTestPoint<TypeParam>(2, 3, 4)};

    const Vector<TypeParam, 3> vector2{origin2, destination2};

    // Operation:
    const Vector<TypeParam, 3> diff = vector1 - vector2;

    // Expected result:
    const Point<TypeParam, 3> expectedResult{make3DTestPoint<TypeParam>(-1, -1, 5)};

    ASSERT_EQ(diff.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_ScalarTimesA3DVector_ReturnsUpdatedDestination)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination{make3DTestPoint<TypeParam>(2, 4, 6)};

    const Vector<TypeParam, 3> vector{origin, destination};

    const TypeParam k{cxutil::narrow_cast<TypeParam>(5)};

    const Vector<TypeParam, 3> prod = k*vector;

    const Point<TypeParam, 3> expectedResult{make3DTestPoint<TypeParam>(6, 12, 18)};

    ASSERT_EQ(prod.destination(), expectedResult);
}


TYPED_TEST(VectorTest, Destination_3DVectorTimesAScalar_ReturnsUpdatedDestination)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination{make3DTestPoint<TypeParam>(2, 4, 6)};

    const Vector<TypeParam, 3> vector{origin, destination};

    const TypeParam k{cxutil::narrow_cast<TypeParam>(5)};

    const Vector<TypeParam, 3> prod = vector*k;

    const Point<TypeParam, 3> expectedResult{make3DTestPoint<TypeParam>(6, 12, 18)};

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
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> vector{origin, destination};

    ASSERT_EQ(vector.x(), cxutil::narrow_cast<TypeParam>(1));
}


TYPED_TEST(VectorTest, X_Some2DVector_ReturnsXComponent)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination{make2DTestPoint<TypeParam>(2, 4)};

    const Vector<TypeParam, 2> vector{origin, destination};

    ASSERT_EQ(vector.x(), cxutil::narrow_cast<TypeParam>(1));
}


TYPED_TEST(VectorTest, X_Some3DVector_ReturnsXComponent)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination{make3DTestPoint<TypeParam>(2, 4, 6)};

    const Vector<TypeParam, 3> vector{origin, destination};

    ASSERT_EQ(vector.x(), cxutil::narrow_cast<TypeParam>(1));
}


TYPED_TEST(VectorTest, Y_Some2DVector_ReturnsYComponent)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination{make2DTestPoint<TypeParam>(2, 4)};

    const Vector<TypeParam, 2> vector{origin, destination};

    ASSERT_EQ(vector.y(), cxutil::narrow_cast<TypeParam>(2));
}


TYPED_TEST(VectorTest, Y_Some3DVector_ReturnsYComponent)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination{make3DTestPoint<TypeParam>(2, 4, 6)};

    const Vector<TypeParam, 3> vector{origin, destination};

    ASSERT_EQ(vector.y(), cxutil::narrow_cast<TypeParam>(2));
}


TYPED_TEST(VectorTest, Z_Some3DVector_ReturnsZComponent)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination{make3DTestPoint<TypeParam>(2, 4, 6)};

    const Vector<TypeParam, 3> vector{origin, destination};

    ASSERT_EQ(vector.z(), cxutil::narrow_cast<TypeParam>(3));
}


TYPED_TEST(VectorTest, SubscriptOperator_Some1DVectorSusbriptN_ExceptionThrown)
{
    using namespace cxutil::math;

    ASSERT_THROW(this->m_vector1D[(Vector<TypeParam, 1>::X_COMPONENT + 1)], PreconditionException);
}


TYPED_TEST(VectorTest, SubscriptOperator_Some2DVectorSusbriptN_ExceptionThrown)
{
    using namespace cxutil::math;

    ASSERT_THROW(this->m_vector2D[(Vector<TypeParam, 2>::Y_COMPONENT + 1)], PreconditionException);
}


TYPED_TEST(VectorTest, SubscriptOperator_Some3DVectorSusbriptN_ExceptionThrown)
{
    using namespace cxutil::math;

    ASSERT_THROW(this->m_vector3D[(Vector<TypeParam, 3>::Z_COMPONENT + 1)], PreconditionException);
}


TYPED_TEST(VectorTest, SubscriptOperator_Some1DVector_ReturnsComponent)
{
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> vector{origin, destination};

    // Extra parentheses in the subscript is neccessary because ASSERT_EQ is a macro!
    ASSERT_EQ(vector[(Vector<TypeParam, 1>::X_COMPONENT)], vector.x());
}


TYPED_TEST(VectorTest, SubscriptOperator_Some2DVector_ReturnsComponent)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination{make2DTestPoint<TypeParam>(2, 4)};

    const Vector<TypeParam, 2> vector{origin, destination};

    // Extra parentheses in the subscript is neccessary because ASSERT_EQ is a macro!
    ASSERT_EQ(vector[(Vector<TypeParam, 2>::X_COMPONENT)], vector.x());
    ASSERT_EQ(vector[(Vector<TypeParam, 2>::Y_COMPONENT)], vector.y());
}


TYPED_TEST(VectorTest, SubscriptOperator_Some3DVector_ReturnsComponent)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination{make3DTestPoint<TypeParam>(2, 4, 6)};

    const Vector<TypeParam, 3> vector{origin, destination};

    // Extra parentheses in the subscript is neccessary because ASSERT_EQ is a macro!
    ASSERT_EQ(vector[(Vector<TypeParam, 3>::X_COMPONENT)], vector.x());
    ASSERT_EQ(vector[(Vector<TypeParam, 3>::Y_COMPONENT)], vector.y());
    ASSERT_EQ(vector[(Vector<TypeParam, 3>::Z_COMPONENT)], vector.z());
}


TYPED_TEST(VectorTest, UnaryMinus_ZeroVector1D_ReturnsZeroVector)
{
    ASSERT_EQ(-(this->m_vector1D), this->m_vector1D);
}


TYPED_TEST(VectorTest, UnaryMinus_ZeroVector2D_ReturnsZeroVector)
{
    ASSERT_EQ(-(this->m_vector2D), this->m_vector2D);
}


TYPED_TEST(VectorTest, UnaryMinus_ZeroVector3D_ReturnsZeroVector)
{
    ASSERT_EQ(-(this->m_vector3D), this->m_vector3D);
}


TYPED_TEST(VectorTest, UnaryMinus_SomeVector1D_ReturnsOppositeVector)
{
    using namespace cxutil::math;

    Point<TypeParam, 1> origin     {make1DTestPoint<TypeParam>(1)};
    Point<TypeParam, 1> destination{make1DTestPoint<TypeParam>(2)};

    Vector<TypeParam, 1> vector        {origin, destination};
    Vector<TypeParam, 1> expectedResult{destination, origin};

    ASSERT_EQ(-vector, expectedResult);
}


TYPED_TEST(VectorTest, UnaryMinus_SomeVector2D_ReturnsOppositeVector)
{
    using namespace cxutil::math;

    Point<TypeParam, 2> origin     {make2DTestPoint<TypeParam>(1, 2)};
    Point<TypeParam, 2> destination{make2DTestPoint<TypeParam>(2, 4)};

    Vector<TypeParam, 2> vector        {origin, destination};
    Vector<TypeParam, 2> expectedResult{destination, origin};

    ASSERT_EQ(-vector, expectedResult);
}


TYPED_TEST(VectorTest, UnaryMinus_SomeVector3D_ReturnsOppositeVector)
{
    using namespace cxutil::math;

    Point<TypeParam, 3> origin     {make3DTestPoint<TypeParam>(1, 2, 3)};
    Point<TypeParam, 3> destination{make3DTestPoint<TypeParam>(2, 4, 6)};

    Vector<TypeParam, 3> vector        {origin, destination};
    Vector<TypeParam, 3> expectedResult{destination, origin};

    ASSERT_EQ(-vector, expectedResult);
}


TYPED_TEST(VectorTest, AdditionAssignement_SomeVector1D_ReturnsSum)
{
    using namespace cxutil::math;

    // First vector:
    Point<TypeParam, 1> origin1     {make1DTestPoint<TypeParam>(1)};
    Point<TypeParam, 1> destination1{make1DTestPoint<TypeParam>(2)};

    Vector<TypeParam, 1> vector1{origin1, destination1};

    // Second vector:
    Point<TypeParam, 1> origin2     {make1DTestPoint<TypeParam>(2)};
    Point<TypeParam, 1> destination2{make1DTestPoint<TypeParam>(1)};

    Vector<TypeParam, 1> vector2{origin2, destination2};

    ASSERT_EQ(vector1 += vector2, this->m_vector1D);
}


TYPED_TEST(VectorTest, AdditionAssignement_SomeVector2D_ReturnsSum)
{
    using namespace cxutil::math;

    // First vector:
    Point<TypeParam, 2> origin1     {make2DTestPoint<TypeParam>(1, 2)};
    Point<TypeParam, 2> destination1{make2DTestPoint<TypeParam>(2, 4)};

    Vector<TypeParam, 2> vector1{origin1, destination1};

    // Second vector:
    Point<TypeParam, 2> origin2     {make2DTestPoint<TypeParam>(2, 4)};
    Point<TypeParam, 2> destination2{make2DTestPoint<TypeParam>(1, 2)};

    Vector<TypeParam, 2> vector2{origin2, destination2};

    ASSERT_EQ(vector1 += vector2, this->m_vector2D);
}


TYPED_TEST(VectorTest, AdditionAssignement_SomeVector3D_ReturnsSum)
{
    using namespace cxutil::math;

    // First vector:
    Point<TypeParam, 3> origin1     {make3DTestPoint<TypeParam>(1, 2, 3)};
    Point<TypeParam, 3> destination1{make3DTestPoint<TypeParam>(2, 4, 6)};

    Vector<TypeParam, 3> vector1{origin1, destination1};

    // Second vector:
    Point<TypeParam, 3> origin2     {make3DTestPoint<TypeParam>(2, 4, 6)};
    Point<TypeParam, 3> destination2{make3DTestPoint<TypeParam>(1, 2, 3)};

    Vector<TypeParam, 3> vector2{origin2, destination2};

    ASSERT_EQ(vector1 += vector2, this->m_vector3D);
}


TYPED_TEST(VectorTest, SubtractionAssignement_SomeVector1D_ReturnsDifference)
{
    using namespace cxutil::math;

    // First vector:
    Point<TypeParam, 1> origin     {make1DTestPoint<TypeParam>(1)};
    Point<TypeParam, 1> destination{make1DTestPoint<TypeParam>(2)};

    Vector<TypeParam, 1> vector1{origin, destination};

    // Second vector:
    Vector<TypeParam, 1> vector2{origin, destination};

    ASSERT_EQ(vector1 -= vector2, this->m_vector1D);
}


TYPED_TEST(VectorTest, SubtractionAssignement_SomeVector2D_ReturnsDifference)
{
    using namespace cxutil::math;

    // First vector:
    Point<TypeParam, 2> origin     {make2DTestPoint<TypeParam>(1, 2)};
    Point<TypeParam, 2> destination{make2DTestPoint<TypeParam>(2, 4)};

    Vector<TypeParam, 2> vector1{origin, destination};

    // Second vector:
    Vector<TypeParam, 2> vector2{origin, destination};

    ASSERT_EQ(vector1 -= vector2, this->m_vector2D);
}


TYPED_TEST(VectorTest, SubtractionAssignement_SomeVector3D_ReturnsDifference)
{
    using namespace cxutil::math;

    // First vector:
    Point<TypeParam, 3> origin     {make3DTestPoint<TypeParam>(1, 2, 3)};
    Point<TypeParam, 3> destination{make3DTestPoint<TypeParam>(2, 4, 6)};

    Vector<TypeParam, 3> vector1{origin, destination};

    // Second vector:
    Vector<TypeParam, 3> vector2{origin, destination};

    ASSERT_EQ(vector1 -= vector2, this->m_vector3D);
}


TYPED_TEST(VectorTest, ProductAssignement_SomeVector1D_ReturnsProduct)
{
    using namespace cxutil::math;

    // First vector:
    Point<TypeParam, 1> origin1     {make1DTestPoint<TypeParam>(1)};
    Point<TypeParam, 1> destination1{make1DTestPoint<TypeParam>(2)};

    Vector<TypeParam, 1> vector{origin1, destination1};

    // Second vector:
    Point<TypeParam, 1> origin2     {make1DTestPoint<TypeParam>(1)};
    Point<TypeParam, 1> destination2{make1DTestPoint<TypeParam>(3)};

    Vector<TypeParam, 1> expectedResult{origin2, destination2};

    // Scalar:
    const TypeParam k{cxutil::narrow_cast<TypeParam>(2)};

    ASSERT_EQ(vector *= k, expectedResult);
}


TYPED_TEST(VectorTest, ProductAssignement_SomeVector2D_ReturnsProduct)
{
    using namespace cxutil::math;

    // First vector:
    Point<TypeParam, 2> origin1     {make2DTestPoint<TypeParam>(1, 2)};
    Point<TypeParam, 2> destination1{make2DTestPoint<TypeParam>(2, 4)};

    Vector<TypeParam, 2> vector{origin1, destination1};

    // Second vector:
    Point<TypeParam, 2> origin2     {make2DTestPoint<TypeParam>(1, 2)};
    Point<TypeParam, 2> destination2{make2DTestPoint<TypeParam>(3, 6)};

    Vector<TypeParam, 2> expectedResult{origin2, destination2};

    // Scalar:
    const TypeParam k{cxutil::narrow_cast<TypeParam>(2)};

    ASSERT_EQ(vector *= k, expectedResult);
}


TYPED_TEST(VectorTest, ProductAssignement_SomeVector3D_ReturnsProduct)
{
    using namespace cxutil::math;

    // First vector:
    Point<TypeParam, 3> origin1     {make3DTestPoint<TypeParam>(1, 2, 3)};
    Point<TypeParam, 3> destination1{make3DTestPoint<TypeParam>(2, 4, 6)};

    Vector<TypeParam, 3> vector{origin1, destination1};

    // Second vector:
    Point<TypeParam, 3> origin2     {make3DTestPoint<TypeParam>(1, 2, 3)};
    Point<TypeParam, 3> destination2{make3DTestPoint<TypeParam>(3, 6, 9)};

    Vector<TypeParam, 3> expectedResult{origin2, destination2};

    // Scalar:
    const TypeParam k{cxutil::narrow_cast<TypeParam>(2)};

    ASSERT_EQ(vector *= k, expectedResult);
}


TYPED_TEST(VectorTest, EqualityOperator_TwoEqual1DVectors_ReturnsTrue)
{
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin1     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination1{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> left{origin1, destination1};

    const Point<TypeParam, 1> origin2     {make1DTestPoint<TypeParam>(2)};
    const Point<TypeParam, 1> destination2{make1DTestPoint<TypeParam>(3)};

    const Vector<TypeParam, 1> right{origin2, destination2};

    ASSERT_TRUE(left == right);
}


TYPED_TEST(VectorTest, EqualityOperator_TwoEqual2DVectors_ReturnsTrue)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin1     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination1{make2DTestPoint<TypeParam>(2, 3)};

    const Vector<TypeParam, 2> left{origin1, destination1};

    const Point<TypeParam, 2> origin2     {make2DTestPoint<TypeParam>(2, 3)};
    const Point<TypeParam, 2> destination2{make2DTestPoint<TypeParam>(3, 4)};

    const Vector<TypeParam, 2> right{origin2, destination2};

    ASSERT_TRUE(left == right);
}


TYPED_TEST(VectorTest, EqualityOperator_TwoEqual3DVectors_ReturnsTrue)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin1     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination1{make3DTestPoint<TypeParam>(2, 3, 4)};

    const Vector<TypeParam, 3> left{origin1, destination1};

    const Point<TypeParam, 3> origin2     {make3DTestPoint<TypeParam>(2, 3, 4)};
    const Point<TypeParam, 3> destination2{make3DTestPoint<TypeParam>(3, 4, 5)};

    const Vector<TypeParam, 3> right{origin2, destination2};

    ASSERT_TRUE(left == right);
}


TYPED_TEST(VectorTest, EqualityOperator_TwoDifferent1DVectors_ReturnsFalse)
{
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin1     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination1{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> left{origin1, destination1};

    const Point<TypeParam, 1> origin2     {make1DTestPoint<TypeParam>(-2)};
    const Point<TypeParam, 1> destination2{make1DTestPoint<TypeParam>(3)};

    const Vector<TypeParam, 1> right{origin2, destination2};

    ASSERT_FALSE(left == right);
}


TYPED_TEST(VectorTest, EqualityOperator_TwoDifferent2DVectors_ReturnsFalse)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin1     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination1{make2DTestPoint<TypeParam>(2, 3)};

    const Vector<TypeParam, 2> left{origin1, destination1};

    const Point<TypeParam, 2> origin2     {make2DTestPoint<TypeParam>(-2, -3)};
    const Point<TypeParam, 2> destination2{make2DTestPoint<TypeParam>(3, 4)};

    const Vector<TypeParam, 2> right{origin2, destination2};

    ASSERT_FALSE(left == right);
}


TYPED_TEST(VectorTest, EqualityOperator_TwoDifferent3DVectors_ReturnsFalse)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin1     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination1{make3DTestPoint<TypeParam>(2, 3, 4)};

    const Vector<TypeParam, 3> left{origin1, destination1};

    const Point<TypeParam, 3> origin2     {make3DTestPoint<TypeParam>(-2, -3, -4)};
    const Point<TypeParam, 3> destination2{make3DTestPoint<TypeParam>(3, 4, 5)};

    const Vector<TypeParam, 3> right{origin2, destination2};

    ASSERT_FALSE(left == right);
}


TYPED_TEST(VectorTest, NonEqualityOperator_TwoDifferent1DVectors_ReturnsTrue)
{
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin1     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination1{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> left{origin1, destination1};

    const Point<TypeParam, 1> origin2     {make1DTestPoint<TypeParam>(-2)};
    const Point<TypeParam, 1> destination2{make1DTestPoint<TypeParam>(3)};

    const Vector<TypeParam, 1> right{origin2, destination2};

    ASSERT_TRUE(left != right);
}


TYPED_TEST(VectorTest, NonEqualityOperator_TwoDifferent2DVectors_ReturnsTrue)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin1     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination1{make2DTestPoint<TypeParam>(2, 3)};

    const Vector<TypeParam, 2> left{origin1, destination1};

    const Point<TypeParam, 2> origin2     {make2DTestPoint<TypeParam>(-2, -3)};
    const Point<TypeParam, 2> destination2{make2DTestPoint<TypeParam>(3, 4)};

    const Vector<TypeParam, 2> right{origin2, destination2};

    ASSERT_TRUE(left != right);
}


TYPED_TEST(VectorTest, NonEqualityOperator_TwoDifferent3DVectors_ReturnsTrue)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin1     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination1{make3DTestPoint<TypeParam>(2, 3, 4)};

    const Vector<TypeParam, 3> left{origin1, destination1};

    const Point<TypeParam, 3> origin2     {make3DTestPoint<TypeParam>(-2, -3, -4)};
    const Point<TypeParam, 3> destination2{make3DTestPoint<TypeParam>(3, 4, 5)};

    const Vector<TypeParam, 3> right{origin2, destination2};

    ASSERT_TRUE(left != right);
}


TYPED_TEST(VectorTest, NonEqualityOperator_TwoEqual1DVectors_ReturnsFalse)
{
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin1     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination1{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> left{origin1, destination1};

    const Point<TypeParam, 1> origin2     {make1DTestPoint<TypeParam>(2)};
    const Point<TypeParam, 1> destination2{make1DTestPoint<TypeParam>(3)};

    const Vector<TypeParam, 1> right{origin2, destination2};

    ASSERT_FALSE(left != right);
}


TYPED_TEST(VectorTest, NonEqualityOperator_TwoEqual2DVectors_ReturnsFalse)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin1     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination1{make2DTestPoint<TypeParam>(2, 3)};

    const Vector<TypeParam, 2> left{origin1, destination1};

    const Point<TypeParam, 2> origin2     {make2DTestPoint<TypeParam>(2, 3)};
    const Point<TypeParam, 2> destination2{make2DTestPoint<TypeParam>(3, 4)};

    const Vector<TypeParam, 2> right{origin2, destination2};

    ASSERT_FALSE(left != right);
}


TYPED_TEST(VectorTest, NonEqualityOperator_TwoEqual3DVectors_ReturnsFalse)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin1     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination1{make3DTestPoint<TypeParam>(2, 3, 4)};

    const Vector<TypeParam, 3> left{origin1, destination1};

    const Point<TypeParam, 3> origin2     {make3DTestPoint<TypeParam>(2, 3, 4)};
    const Point<TypeParam, 3> destination2{make3DTestPoint<TypeParam>(3, 4, 5)};

    const Vector<TypeParam, 3> right{origin2, destination2};

    ASSERT_FALSE(left != right);
}

TYPED_TEST(VectorTest, VectorAddition_Two1DVectorsAdded_ReturnsSumVector)
{
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin1     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination1{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> vect1{origin1, destination1};

    const Point<TypeParam, 1> origin2     {make1DTestPoint<TypeParam>(2)};
    const Point<TypeParam, 1> destination2{make1DTestPoint<TypeParam>(3)};

    const Vector<TypeParam, 1> vect2{origin2, destination2};

    const Point<TypeParam, 1> origin3     {make1DTestPoint<TypeParam>(2)};
    const Point<TypeParam, 1> destination3{make1DTestPoint<TypeParam>(4)};

    const Vector<TypeParam, 1> sum{origin3, destination3};

    ASSERT_EQ(vect1 + vect2, sum);
}


TYPED_TEST(VectorTest, VectorAddition_Two2DVectorsAdded_ReturnsSumVector)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin1     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination1{make2DTestPoint<TypeParam>(2, 3)};

    const Vector<TypeParam, 2> vect1{origin1, destination1};

    const Point<TypeParam, 2> origin2     {make2DTestPoint<TypeParam>(2, 3)};
    const Point<TypeParam, 2> destination2{make2DTestPoint<TypeParam>(3, 4)};

    const Vector<TypeParam, 2> vect2{origin2, destination2};

    const Point<TypeParam, 2> origin3     {make2DTestPoint<TypeParam>(2, 3)};
    const Point<TypeParam, 2> destination3{make2DTestPoint<TypeParam>(4, 5)};

    const Vector<TypeParam, 2> sum{origin3, destination3};

    ASSERT_EQ(vect1 + vect2, sum);
}


TYPED_TEST(VectorTest, VectorAddition_Two3DVectorsAdded_ReturnsSumVector)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin1     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination1{make3DTestPoint<TypeParam>(2, 3, 4)};

    const Vector<TypeParam, 3> vect1{origin1, destination1};

    const Point<TypeParam, 3> origin2     {make3DTestPoint<TypeParam>(2, 3, 4)};
    const Point<TypeParam, 3> destination2{make3DTestPoint<TypeParam>(3, 4, 5)};

    const Vector<TypeParam, 3> vect2{origin2, destination2};

    const Point<TypeParam, 3> origin3     {make3DTestPoint<TypeParam>(2, 3, 4)};
    const Point<TypeParam, 3> destination3{make3DTestPoint<TypeParam>(4, 5, 6)};

    const Vector<TypeParam, 3> sum{origin3, destination3};

    ASSERT_EQ(vect1 + vect2, sum);
}


TYPED_TEST(VectorTest, VectorSubtraction_Two1DVectorsSubtracted_ReturnsDifferenceVector)
{
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin1     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination1{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> vect1{origin1, destination1};

    const Point<TypeParam, 1> origin2     {make1DTestPoint<TypeParam>(2)};
    const Point<TypeParam, 1> destination2{make1DTestPoint<TypeParam>(3)};

    const Vector<TypeParam, 1> vect2{origin2, destination2};

    ASSERT_EQ(vect1 - vect2, this->m_vector1D);
}


TYPED_TEST(VectorTest, VectorSubtraction_Two2DVectorsSubtracted_ReturnsDifferenceVector)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin1     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination1{make2DTestPoint<TypeParam>(2, 3)};

    const Vector<TypeParam, 2> vect1{origin1, destination1};

    const Point<TypeParam, 2> origin2     {make2DTestPoint<TypeParam>(2, 3)};
    const Point<TypeParam, 2> destination2{make2DTestPoint<TypeParam>(3, 4)};

    const Vector<TypeParam, 2> vect2{origin2, destination2};

    ASSERT_EQ(vect1 - vect2, this->m_vector2D);
}


TYPED_TEST(VectorTest, VectorSubtraction_Two3DVectorsSubtracted_ReturnsDifferenceVector)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin1     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination1{make3DTestPoint<TypeParam>(2, 3, 4)};

    const Vector<TypeParam, 3> vect1{origin1, destination1};

    const Point<TypeParam, 3> origin2     {make3DTestPoint<TypeParam>(2, 3, 4)};
    const Point<TypeParam, 3> destination2{make3DTestPoint<TypeParam>(3, 4, 5)};

    const Vector<TypeParam, 3> vect2{origin2, destination2};

    ASSERT_EQ(vect1 - vect2, this->m_vector3D);
}


TYPED_TEST(VectorTest, LeftScalarMultiplication_ScalarTimes1DVector_ReturnsScaledVector)
{
    using namespace cxutil::math;

    const TypeParam k{cxutil::narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 1> origin1     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination1{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> vect{origin1, destination1};

    const Point<TypeParam, 1> origin2     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination2{make1DTestPoint<TypeParam>(3)};

    const Vector<TypeParam, 1> prod{origin2, destination2};

    ASSERT_EQ(k*vect, prod);
}


TYPED_TEST(VectorTest, LeftScalarMultiplication_ScalarTimes2DVector_ReturnsScaledVector)
{
    using namespace cxutil::math;

    const TypeParam k{cxutil::narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 2> origin1     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination1{make2DTestPoint<TypeParam>(2, 3)};

    const Vector<TypeParam, 2> vect{origin1, destination1};

    const Point<TypeParam, 2> origin2     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination2{make2DTestPoint<TypeParam>(3, 4)};

    const Vector<TypeParam, 2> prod{origin2, destination2};

    ASSERT_EQ(k*vect, prod);
}


TYPED_TEST(VectorTest, LeftScalarMultiplication_ScalarTimes3DVector_ReturnsScaledVector)
{
    using namespace cxutil::math;

    const TypeParam k{cxutil::narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 3> origin1     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination1{make3DTestPoint<TypeParam>(2, 3, 4)};

    const Vector<TypeParam, 3> vect{origin1, destination1};

    const Point<TypeParam, 3> origin2     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination2{make3DTestPoint<TypeParam>(3, 4, 5)};

    const Vector<TypeParam, 3> prod{origin2, destination2};

    ASSERT_EQ(k*vect, prod);
}


TYPED_TEST(VectorTest, RightScalarMultiplication_ScalarTimes1DVector_ReturnsScaledVector)
{
    using namespace cxutil::math;

    const TypeParam k{cxutil::narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 1> origin1     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination1{make1DTestPoint<TypeParam>(2)};

    const Vector<TypeParam, 1> vect{origin1, destination1};

    const Point<TypeParam, 1> origin2     {make1DTestPoint<TypeParam>(1)};
    const Point<TypeParam, 1> destination2{make1DTestPoint<TypeParam>(3)};

    const Vector<TypeParam, 1> prod{origin2, destination2};

    ASSERT_EQ(vect*k, prod);
}


TYPED_TEST(VectorTest, RightScalarMultiplication_ScalarTimes2DVector_ReturnsScaledVector)
{
    using namespace cxutil::math;

    const TypeParam k{cxutil::narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 2> origin1     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination1{make2DTestPoint<TypeParam>(2, 3)};

    const Vector<TypeParam, 2> vect{origin1, destination1};

    const Point<TypeParam, 2> origin2     {make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination2{make2DTestPoint<TypeParam>(3, 4)};

    const Vector<TypeParam, 2> prod{origin2, destination2};

    ASSERT_EQ(vect*k, prod);
}


TYPED_TEST(VectorTest, RightScalarMultiplication_ScalarTimes3DVector_ReturnsScaledVector)
{
    using namespace cxutil::math;

    const TypeParam k{cxutil::narrow_cast<TypeParam>(2)};

    const Point<TypeParam, 3> origin1     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination1{make3DTestPoint<TypeParam>(2, 3, 4)};

    const Vector<TypeParam, 3> vect{origin1, destination1};

    const Point<TypeParam, 3> origin2     {make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination2{make3DTestPoint<TypeParam>(3, 4, 5)};

    const Vector<TypeParam, 3> prod{origin2, destination2};

    ASSERT_EQ(vect*k, prod);
}


TYPED_TEST(VectorTest, CrossProduct2D_Two2DVectorsA_ReturnsCrossProductValue)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin;
    const Point<TypeParam, 2> destination1{make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination2{make2DTestPoint<TypeParam>(3, 4)};


    const Vector<TypeParam, 2> u{origin, destination1};
    const Vector<TypeParam, 2> v{origin, destination2};

    const TypeParam expectedResult{cxutil::narrow_cast<TypeParam>(-2)};

    TypeParam result;

    crossProduct(u, v, result);

    ASSERT_EQ(result, expectedResult);
}


TYPED_TEST(VectorTest, CrossProduct2D_Two2DVectorsB_ReturnsCrossProductValue)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin;
    const Point<TypeParam, 2> destination1{make2DTestPoint<TypeParam>(1, 2)};
    const Point<TypeParam, 2> destination2{make2DTestPoint<TypeParam>(-7, 16)};


    const Vector<TypeParam, 2> u{origin, destination1};
    const Vector<TypeParam, 2> v{origin, destination2};

    const TypeParam expectedResult{cxutil::narrow_cast<TypeParam>(30)};

    TypeParam result;

    crossProduct(u, v, result);

    ASSERT_EQ(result, expectedResult);
}


TYPED_TEST(VectorTest, CrossProduct3D_Two2DIdenticalVectors_Returns0)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin;
    const Point<TypeParam, 2> destination1{make2DTestPoint<TypeParam>(1, 2)};

    const Vector<TypeParam, 2> u{origin, destination1};

    const TypeParam expectedResult{cxutil::narrow_cast<TypeParam>(0)};

    TypeParam result;

    crossProduct(u, u, result);

    ASSERT_EQ(result, expectedResult);
}


TYPED_TEST(VectorTest, CrossProduct3D_Two3DVectorsA_ReturnsCrossProduct3DVector)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin;
    const Point<TypeParam, 3> destination1{make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination2{make3DTestPoint<TypeParam>(4, 5, 6)};

    const Vector<TypeParam, 3> u{origin, destination1};
    const Vector<TypeParam, 3> v{origin, destination2};

    const Point<TypeParam, 3> destination3{make3DTestPoint<TypeParam>(-3, 6, -3)};
    const Vector<TypeParam, 3> expectedResult{origin, destination3};

    Vector<TypeParam, 3> result;

    crossProduct(u, v, result);

    ASSERT_EQ(result, expectedResult);
}


TYPED_TEST(VectorTest, CrossProduct3D_Two3DVectorsB_ReturnsCrossProduct3DVector)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin;
    const Point<TypeParam, 3> destination1{make3DTestPoint<TypeParam>(1, 2, 3)};
    const Point<TypeParam, 3> destination2{make3DTestPoint<TypeParam>(-6, 3, 15)};

    const Vector<TypeParam, 3> u{origin, destination1};
    const Vector<TypeParam, 3> v{origin, destination2};

    const Point<TypeParam, 3> destination3{make3DTestPoint<TypeParam>(21, -33, 15)};
    const Vector<TypeParam, 3> expectedResult{origin, destination3};

    Vector<TypeParam, 3> result;

    crossProduct(u, v, result);

    ASSERT_EQ(result, expectedResult);
}


TYPED_TEST(VectorTest, AdditionIdentity_InstantiateNew1DVector_VectorIsAdditionIdentity)
{
    ASSERT_EQ((cxutil::math::additionIdentity<TypeParam, 1>()), this->m_vector1D);
}


TYPED_TEST(VectorTest, AdditionIdentity_InstantiateNew2DVector_VectorIsAdditionIdentity)
{
    ASSERT_EQ((cxutil::math::additionIdentity<TypeParam, 2>()), this->m_vector2D);
}


TYPED_TEST(VectorTest, AdditionIdentity_InstantiateNew3DVector_VectorIsAdditionIdentity)
{
    ASSERT_EQ((cxutil::math::additionIdentity<TypeParam, 3>()), this->m_vector3D);
}


TYPED_TEST(VectorTest, DotProduct_Two1DVectors_ReturnsDotProductValue)
{
    using namespace cxutil::math;

    const Point<TypeParam, 1> origin;
    const Vector<TypeParam, 1> u{origin, make1DTestPoint<TypeParam>(1)};
    const Vector<TypeParam, 1> v{origin, make1DTestPoint<TypeParam>(-1)};

    const TypeParam expectedResult{cxutil::narrow_cast<TypeParam>(-1)};

    const TypeParam result{dotProduct(u, v)};

    ASSERT_EQ(result, expectedResult);
}


TYPED_TEST(VectorTest, DotProduct_Two2DVectors_ReturnsDotProductValue)
{
    using namespace cxutil::math;

    const Point<TypeParam, 2> origin;
    const Vector<TypeParam, 2> u{origin, make2DTestPoint<TypeParam>(1, 2)};
    const Vector<TypeParam, 2> v{origin, make2DTestPoint<TypeParam>(-1, -2)};

    const TypeParam expectedResult{cxutil::narrow_cast<TypeParam>(-5)};

    const TypeParam result{dotProduct(u, v)};

    ASSERT_EQ(result, expectedResult);
}


TYPED_TEST(VectorTest, DotProduct_Two3DVectors_ReturnsDotProductValue)
{
    using namespace cxutil::math;

    const Point<TypeParam, 3> origin;
    const Vector<TypeParam, 3> u{origin, make3DTestPoint<TypeParam>(1, 2, 3)};
    const Vector<TypeParam, 3> v{origin, make3DTestPoint<TypeParam>(-1, -2, -3)};

    const TypeParam expectedResult{cxutil::narrow_cast<TypeParam>(-14)};

    const TypeParam result{dotProduct(u, v)};

    ASSERT_EQ(result, expectedResult);
}


/***************************************************************************************************
 * A note to the developers...
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

namespace
{

/***************************************************************************************************
 * @brief Chooses a distribution at compile time.
 *
 * Chosses a uniform random number distrubytion at compile time and returns it.
 *
 * @tparam T            The number type to be generated.
 * @tparam Distribution The uniform random number distribution.
 *
 * @param p_min The minimum value for number generation.
 * @param p_max The maximum value for number generation.
 *
 * @return A distribution respecting @c T and operating over the needed range.
 *
 **************************************************************************************************/
template <typename T,
          typename Distribution = typename std::conditional<
              std::is_integral<T>::value,
              std::uniform_int_distribution<T>,
              std::uniform_real_distribution<T>>::type>
Distribution getValidUniformDistribution(const T p_min, const T p_max)
{
    return Distribution(p_min, p_max);
}


/***************************************************************************************************
 * @brief Generates a random vector.
 *
 * A random vector, in this context, is a vector whose origin and destination point are
 * composed of random coordinates. Note that these coordinates are between -5 and +5 to
 * make sure smaller types are compatible.
 *
 * @tparam T The coordinate type.
 * @tparam N The vector dimension.
 *
 * @return Th(e random vector.
 *
 **************************************************************************************************/
template<typename T, std::size_t N>
cxutil::math::Vector<T, N> makeRandomTestVector()
{
    using namespace cxutil::math;

    // Limits
    const T min{cxutil::narrow_cast<T>(-5)};
    const T max{cxutil::narrow_cast<T>(5)};

    // Get the right distribution, depending on type:
    static std::default_random_engine generator;
    auto distribution{getValidUniformDistribution<T>(min, max)};

    // Generate a random origin point:
    Point<T, N> origin;

    for(std::size_t i = 0; i < N; ++i)
    {
        // This ugly line fixes the floating point rounding errors in the tests
        // by rounding them to the nearest integer value. This is enough for this
        // Vector class.
        origin[i] = cxutil::narrow_cast<T>(std::round(distribution(generator)));
    }

    // Generate a random destination point:
    Point<T, N> destination;

    for(std::size_t i = 0; i < N; ++i)
    {
        destination[i] = cxutil::narrow_cast<T>(std::round(distribution(generator)));
    }

    // Making the random vector:
    return Vector<T, N>{origin, destination};
}

} // unamed namespace


TYPED_TEST(VectorTest, Vector1DAdditionAssociativity)
{
    using namespace cxutil::math;

    const Vector<TypeParam, 1> u{makeRandomTestVector<TypeParam, 1>()};
    const Vector<TypeParam, 1> v{makeRandomTestVector<TypeParam, 1>()};
    const Vector<TypeParam, 1> w{makeRandomTestVector<TypeParam, 1>()};

    ASSERT_TRUE(u + (v + w) == (u + v) + w);
}


TYPED_TEST(VectorTest, Vector2DAdditionAssociativity)
{
    using namespace cxutil::math;

    const Vector<TypeParam, 2> u{makeRandomTestVector<TypeParam, 2>()};
    const Vector<TypeParam, 2> v{makeRandomTestVector<TypeParam, 2>()};
    const Vector<TypeParam, 2> w{makeRandomTestVector<TypeParam, 2>()};

    ASSERT_TRUE(u + (v + w) == (u + v) + w);
}


TYPED_TEST(VectorTest, Vector3DAdditionAssociativity)
{
    using namespace cxutil::math;

    const Vector<TypeParam, 3> u{makeRandomTestVector<TypeParam, 3>()};
    const Vector<TypeParam, 3> v{makeRandomTestVector<TypeParam, 3>()};
    const Vector<TypeParam, 3> w{makeRandomTestVector<TypeParam, 3>()};

    ASSERT_TRUE(u + (v + w) == (u + v) + w);
}


TYPED_TEST(VectorTest, Vector1DAdditionCommutativity)
{
    using namespace cxutil::math;

    const Vector<TypeParam, 1> u{makeRandomTestVector<TypeParam, 1>()};
    const Vector<TypeParam, 1> v{makeRandomTestVector<TypeParam, 1>()};

    ASSERT_TRUE(u + v == v + u);
}


TYPED_TEST(VectorTest, Vector2DAdditionCommutativity)
{
    using namespace cxutil::math;

    const Vector<TypeParam, 2> u{makeRandomTestVector<TypeParam, 2>()};
    const Vector<TypeParam, 2> v{makeRandomTestVector<TypeParam, 2>()};

    ASSERT_TRUE(u + v == v + u);
}


TYPED_TEST(VectorTest, Vector3DAdditionCommutativity)
{
    using namespace cxutil::math;

    const Vector<TypeParam, 3> u{makeRandomTestVector<TypeParam, 3>()};
    const Vector<TypeParam, 3> v{makeRandomTestVector<TypeParam, 3>()};

    ASSERT_TRUE(u + v == v + u);
}


TYPED_TEST(VectorTest, Vector1DAdditionIdentityElement)
{
    using namespace cxutil::math;

    const Vector<TypeParam, 1> u{makeRandomTestVector<TypeParam, 1>()};

    ASSERT_TRUE((u + additionIdentity<TypeParam, 1>()) == u);
}


TYPED_TEST(VectorTest, Vector2DAdditionIdentityElement)
{
    using namespace cxutil::math;

    const Vector<TypeParam, 2> u{makeRandomTestVector<TypeParam, 2>()};

    ASSERT_TRUE((u + additionIdentity<TypeParam, 2>()) == u);
}


TYPED_TEST(VectorTest, Vector3DAdditionIdentityElement)
{
    using namespace cxutil::math;

    const Vector<TypeParam, 3> u{makeRandomTestVector<TypeParam, 3>()};

    ASSERT_TRUE((u + additionIdentity<TypeParam, 3>()) == u);
}


TYPED_TEST(VectorTest, Vector1DAdditionInverseElement)
{
    using namespace cxutil::math;

    const Vector<TypeParam, 1> u{makeRandomTestVector<TypeParam, 1>()};

    ASSERT_TRUE((u + (-u) == additionIdentity<TypeParam, 1>()));
}


TYPED_TEST(VectorTest, Vector2DAdditionInverseElement)
{
    using namespace cxutil::math;

    const Vector<TypeParam, 2> u{makeRandomTestVector<TypeParam, 2>()};

    ASSERT_TRUE((u + (-u) == additionIdentity<TypeParam, 2>()));
}


TYPED_TEST(VectorTest, Vector3DAdditionInverseElement)
{
    using namespace cxutil::math;

    const Vector<TypeParam, 3> u{makeRandomTestVector<TypeParam, 3>()};

    ASSERT_TRUE((u + (-u) == additionIdentity<TypeParam, 3>()));
}


TYPED_TEST(VectorTest, Vector1DScalarAndFieldMultiplicationsCompatibility)
{
    using namespace cxutil::math;

    const TypeParam a{cxutil::narrow_cast<TypeParam>(3)};
    const TypeParam b{cxutil::narrow_cast<TypeParam>(-4)};

    const Vector<TypeParam, 1> u{makeRandomTestVector<TypeParam, 1>()};

    ASSERT_TRUE(a * (b * u) == (a * b) * u);
}


TYPED_TEST(VectorTest, Vector2DScalarAndFieldMultiplicationsCompatibility)
{
    using namespace cxutil::math;

    const TypeParam a{cxutil::narrow_cast<TypeParam>(3)};
    const TypeParam b{cxutil::narrow_cast<TypeParam>(-4)};

    const Vector<TypeParam, 2> u{makeRandomTestVector<TypeParam, 2>()};

    ASSERT_TRUE(a * (b * u) == (a * b) * u);
}


TYPED_TEST(VectorTest, Vector3DScalarAndFieldMultiplicationsCompatibility)
{
    using namespace cxutil::math;

    const TypeParam a{cxutil::narrow_cast<TypeParam>(3)};
    const TypeParam b{cxutil::narrow_cast<TypeParam>(-4)};

    const Vector<TypeParam, 3> u{makeRandomTestVector<TypeParam, 3>()};

    ASSERT_TRUE(a * (b * u) == (a * b) * u);
}


TYPED_TEST(VectorTest, Vector1DScalarMultiplicationIdentityElement)
{
    using namespace cxutil::math;

    const TypeParam multIdentity{cxutil::narrow_cast<TypeParam>(1)};

    const Vector<TypeParam, 1> u{makeRandomTestVector<TypeParam, 1>()};

    ASSERT_TRUE(multIdentity * u == u);
}


TYPED_TEST(VectorTest, Vector2DScalarMultiplicationIdentityElement)
{
    using namespace cxutil::math;

    const TypeParam multIdentity{cxutil::narrow_cast<TypeParam>(1)};

    const Vector<TypeParam, 2> u{makeRandomTestVector<TypeParam, 2>()};

    ASSERT_TRUE(multIdentity * u == u);
}


TYPED_TEST(VectorTest, Vector3DScalarMultiplicationIdentityElement)
{
    using namespace cxutil::math;

    const TypeParam multIdentity{cxutil::narrow_cast<TypeParam>(1)};

    const Vector<TypeParam, 3> u{makeRandomTestVector<TypeParam, 3>()};

    ASSERT_TRUE(multIdentity * u == u);
}


TYPED_TEST(VectorTest, Vector1DScalarMultiplicationDistributivityWithRespectToVectorAddition)
{
    using namespace cxutil::math;

    const TypeParam a{cxutil::narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 1> u{makeRandomTestVector<TypeParam, 1>()};
    const Vector<TypeParam, 1> v{makeRandomTestVector<TypeParam, 1>()};

    ASSERT_TRUE(a * (u + v) == a * v + a * u);
}


TYPED_TEST(VectorTest, Vector2DScalarMultiplicationDistributivityWithRespectToVectorAddition)
{
    using namespace cxutil::math;

    const TypeParam a{cxutil::narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 2> u{makeRandomTestVector<TypeParam, 2>()};
    const Vector<TypeParam, 2> v{makeRandomTestVector<TypeParam, 2>()};

    ASSERT_TRUE(a * (u + v) == a * v + a * u);
}


TYPED_TEST(VectorTest, Vector3DScalarMultiplicationDistributivityWithRespectToVectorAddition)
{
    using namespace cxutil::math;

    const TypeParam a{cxutil::narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 3> u{makeRandomTestVector<TypeParam, 3>()};
    const Vector<TypeParam, 3> v{makeRandomTestVector<TypeParam, 3>()};

    ASSERT_TRUE(a * (u + v) == a * v + a * u);
}


TYPED_TEST(VectorTest, Vector1DScalarMultiplicationDistributivityWithRespectToFieldAddition)
{
    using namespace cxutil::math;

    const TypeParam a{cxutil::narrow_cast<TypeParam>(-1)};
    const TypeParam b{cxutil::narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 1> u{makeRandomTestVector<TypeParam, 1>()};
    const Vector<TypeParam, 1> v{makeRandomTestVector<TypeParam, 1>()};

    ASSERT_TRUE((a + b) * u == a * u + b * u);
}


TYPED_TEST(VectorTest, Vector2DScalarMultiplicationDistributivityWithRespectToFieldAddition)
{
    using namespace cxutil::math;

    const TypeParam a{cxutil::narrow_cast<TypeParam>(-1)};
    const TypeParam b{cxutil::narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 2> u{makeRandomTestVector<TypeParam, 2>()};
    const Vector<TypeParam, 2> v{makeRandomTestVector<TypeParam, 2>()};

    ASSERT_TRUE((a + b) * u == a * u + b * u);
}


TYPED_TEST(VectorTest, Vector3DScalarMultiplicationDistributivityWithRespectToFieldAddition)
{
    using namespace cxutil::math;

    const TypeParam a{cxutil::narrow_cast<TypeParam>(-1)};
    const TypeParam b{cxutil::narrow_cast<TypeParam>(2)};

    const Vector<TypeParam, 3> u{makeRandomTestVector<TypeParam, 3>()};
    const Vector<TypeParam, 3> v{makeRandomTestVector<TypeParam, 3>()};

    ASSERT_TRUE((a + b) * u == a * u + b * u);
}
