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
 * Unit tests for the cxutil utilities.
 *
 * @file    test_util.cpp
 * @author  Eric Poirier
 * @date    August 2018
 * @version 1.0
 *
 **************************************************************************************************/


#include <gtest/gtest.h>

#include <cxutil/include/ContractException.h>
#include <cxutil/include/util.h>


TEST(StringTests, Vectorize_EmptyDelimiter_ThrowsException)
{
    const std::string text     {"Some text"};
    const std::string delimiter{""         };

    ASSERT_THROW(cxutil::string::vectorize(text, delimiter), PreconditionException);
}


TEST(StringTests, Vectorize_EmptyTextValidDelimiter_ReturnsEmptyVector)
{
    const std::string text     {""  };
    const std::string delimiter{"\n"};

    const std::vector<std::string> vectorized{cxutil::string::vectorize(text, delimiter)};

    ASSERT_TRUE(vectorized.empty());
}


TEST(StringTests, Vectorize_ValidTextValidButDelimiterNotFound_ReturnsTextInVector)
{
    // Data:
    const std::string text     {"Line1\n"
                                "Line2"};
    const std::string delimiter{"aa"};

    // Expected result:
    const std::vector<std::string> vectorized{"Line1\n"
                                              "Line2"};

    // Test:
    ASSERT_EQ(vectorized, cxutil::string::vectorize(text, delimiter));
}


TEST(StringTests, Vectorize_TextWithTwoLinesValidAndKeptDelimiter_VectorHasTheTwoLines)
{
    // Data:
    const std::string text1    {"Line1\n"
                                "Line2"};
    const std::string text2    {"Line1\n"
                                "Line2\n"};
    const std::string delimiter{"\n"};

    // Expected result:
    const std::vector<std::string> vectorized1{"Line1\n", "Line2"  };
    const std::vector<std::string> vectorized2{"Line1\n", "Line2\n"};

    // Test:
    ASSERT_EQ(vectorized1, cxutil::string::vectorize(text1, delimiter, true));
    ASSERT_EQ(vectorized2, cxutil::string::vectorize(text2, delimiter, true));
}


TEST(StringTests, Vectorize_TextWithTwoLinesValidAndNotKeptDelimiter_VectorHasTheTwoLines)
{
    // Data:
    const std::string text1    {"Line1\n"
                                "Line2"};
    const std::string text2    {"Line1\n"
                                "Line2\n"};
    const std::string delimiter{"\n"};

    // Expected result:
    const std::vector<std::string> vectorized1{"Line1", "Line2"};
    const std::vector<std::string> vectorized2{"Line1", "Line2"};

    // Test:
    ASSERT_EQ(vectorized1, cxutil::string::vectorize(text1, delimiter));
    ASSERT_EQ(vectorized2, cxutil::string::vectorize(text2, delimiter));
}


TEST(StringTests, Vectorize_OneTextTwoValidNotKeptDelimiters_TwoRespectivelyMatchingVectors)
{
    // Data:
    const std::string text1    {"Line1\n"
                                "Line2"};
    const std::string text2    {"Line1\n\r"
                                "Line2"};

    // Expected result:
    const std::vector<std::string> vectorized{"Line1", "Line2"};

    // Test:
    ASSERT_EQ(vectorized, cxutil::string::vectorize(text1, "\n"  ));
    ASSERT_EQ(vectorized, cxutil::string::vectorize(text2, "\n\r"));
}
