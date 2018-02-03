/***************************************************************************************************
 *
 * Copyright (C) 2016 Connect X team
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
 * @file    test_Name.cpp
 * @author  Eric Poirier
 * @date    November 2016
 * @version 1.0
 *
 * Unit tests for a the Name class.
 *
 **************************************************************************************************/

#include <gtest/gtest.h>

#include <cxutil/include/Name.h>

using namespace cxutil;

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
