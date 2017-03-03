/***********************************************************************************************//**
 * @file    test_AsciiColorCode.cpp
 * @author  Eric Poirier
 * @date    November 2016
 * @version 0.1
 *
 * Unit tests for a the AsciiColorCode class.
 *
 **************************************************************************************************/

#include <publicAPI/AsciiColorCode.h>
#include <gtest/gtest.h>

#include <sstream>


USING_NAMESPACE_CXBASE

TEST(AciiColorCode, Constructor_ValidCode_NoExceptionThrown)
{
    ASSERT_NO_THROW('M');
    ASSERT_NO_THROW(' ');
    ASSERT_NO_THROW('m');
}

TEST(AsciiColorCode, Constructor_InavlidAsciiBelow65_ExceptionThrown)
{
    ASSERT_THROW(AsciiColorCode t_asciiColorCode{'@'}, PreconditionException);
}

TEST(AsciiColorCode, Constructor_InavlidAsciiBetween133And140Lower_ExceptionThrown)
{
    ASSERT_THROW(AsciiColorCode t_asciiColorCode{'['}, PreconditionException);
}

TEST(AsciiColorCode, Constructor_InavlidAsciiBetween133And140Upper_ExceptionThrown)
{
    ASSERT_THROW(AsciiColorCode t_asciiColorCode{'`'}, PreconditionException);
}

TEST(AsciiColorCode, Constructor_InavlidAsciiOver172_ExceptionThrown)
{
    ASSERT_THROW(AsciiColorCode t_asciiColorCode{'{'}, PreconditionException);
}

class AsciiColorCodeTests : public ::testing::Test
{
public:

    AsciiColorCode t_asciiColorCode{'a'};
};

TEST_F(AsciiColorCodeTests, CodeCharAccessor_GetTheCode_CodeReturned)
{
    ASSERT_EQ(t_asciiColorCode.toChar(), 'a');
}

TEST_F(AsciiColorCodeTests, OperatorEqual_TwoEqualCodes_ReturnTrue)
{
    AsciiColorCode t_asciiColorCode2{'a'};

    ASSERT_TRUE(t_asciiColorCode == t_asciiColorCode2);
}

TEST_F(AsciiColorCodeTests, OperatorEqual_TwoNotEqualCodes_ReturnFalse)
{
    AsciiColorCode t_asciiColorCode2{'b'};

    ASSERT_FALSE(t_asciiColorCode == t_asciiColorCode2);
}

TEST_F(AsciiColorCodeTests, OperatorNotEqual_TwoNotEqualCodes_ReturnTrue)
{
    AsciiColorCode t_asciiColorCode2{'b'};

    ASSERT_TRUE(t_asciiColorCode != t_asciiColorCode2);
}

TEST_F(AsciiColorCodeTests, OperatorNotEqual_TwoEqualCodes_ReturnFalse)
{
    AsciiColorCode t_asciiColorCode2{'a'};

    ASSERT_FALSE(t_asciiColorCode != t_asciiColorCode2);
}

TEST_F(AsciiColorCodeTests, StreamInsertionOperator_ACode_InsertCodeCharInStream)
{
    std::ostringstream t_flux;

    t_flux << t_asciiColorCode;

    ASSERT_EQ(t_flux.str(), "a");
}
