/***********************************************************************************************//**
 * @file    test_Name.cpp
 * @author  Eric Poirier
 * @date    November 2016
 * @version 0.1
 *
 * Unit tests for a the Name class.
 *
 **************************************************************************************************/

#include <publicAPI/Name.h>
#include <gtest/gtest.h>


USING_NAMESPACE_CXBASE

TEST(Name, Constructor_ValidName_NoExceptionThrown)
{
    ASSERT_NO_THROW(Name t_name{"Test"});
}

TEST(Name, Constructor_FeedEmptyString_ExceptionThrown)
{
    ASSERT_THROW(Name t_name{""}, PreconditionException);
}

TEST(Name, NameStringAccessor_GetTheName_NameReturned)
{
    Name t_name{"Test"};

    ASSERT_EQ(t_name.toString(), "Test");
}

class NameTests : public ::testing::Test
{

public:

    Name t_name{"Test"};
};

TEST_F(NameTests, EqualOperator_TwoEqualNames_TrueReturned)
{
    Name t_name2{"Test"};

    ASSERT_TRUE(t_name == t_name);
}

TEST_F(NameTests, EqualOperator_TwoNonEqualNames_FalseReturned)
{
    Name t_name2{"Other"};

    ASSERT_FALSE(t_name == t_name2);
}

TEST_F(NameTests, NotEqualOperator_TwoNonEqualNames_TrueReturned)
{
    Name t_name2{"Other"};

    ASSERT_TRUE(t_name != t_name2);
}

TEST_F(NameTests, NotEqualOperator_TwoEqualNames_FalseReturned)
{
    Name t_name2{"Test"};

    ASSERT_FALSE(t_name != t_name);
}
