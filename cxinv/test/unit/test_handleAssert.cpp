/***************************************************************************************************
 *
 * Copyright (C) 2019 Connect X team
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
 * @file    test_handleAssert.cpp
 * @author  Eric Poirier
 * @date    July 2019
 * @version 1.0
 *
 * Unit tests for the assertion method.
 *
 **************************************************************************************************/

#include <iosfwd>
#include <sstream>

#include <gtest/gtest.h>

#include <cxinv/include/assertion.h>

namespace
{
    const char* _FILE_              {"File.cpp"};
    const char* _FUNCTION_          {"Function()"};
    const long  _LINE_              {10};
    const char* CONDITION_EXPRESSION{"(3 > 5)"};
    const char* VALID_MESSAGE       {"A valid message"};


/***********************************************************************************************//**
 * @class StderrRedirectorRAII
 *
 * Redirects the @c std::cerr buffer to a new buffer. Since this is RAII, upon destruction, the
 * previous @c std::cerr buffer will automatically be restored.
 *
 *
 **************************************************************************************************/
class StderrRedirectorRAII final
{

public:

    /*******************************************************************************************//**
     * Constructor.
     *
     * @param p_newBuffer The new buffer adress.
     *
     **********************************************************************************************/
    StderrRedirectorRAII(std::streambuf* p_newBuffer)
    : m_previousBuffer{std::cerr.rdbuf(p_newBuffer)}
    {
    }


    /*******************************************************************************************//**
     * Destructor.
     *
     * Restores previous buffer.
     *
     **********************************************************************************************/
    ~StderrRedirectorRAII()
    {
        std::cerr.rdbuf(m_previousBuffer);
    }

private:

    std::streambuf* m_previousBuffer;
};


/***********************************************************************************************//**
 * Creates an expected message string.
 *
 * @param p_label   The assertion label.
 * @param p_message The message (if any).
 *
 * @return The expected message, assuming all @c cxinv::handleAssert preconditions are met.
 *
 **************************************************************************************************/
std::string makeExpectedMessage(cxinv::AssertLabel p_label, const char* p_message = nullptr)
{
    std::ostringstream stream;

    if(p_label == cxinv::AssertLabel::ASSERTION)
    {
        stream << "Assertion failed at ";
    }
    else
    {
        switch(p_label)
        {
            case cxinv::AssertLabel::PRECONDITION:
                stream << "Precondition";
                break;

            case cxinv::AssertLabel::POSTCONDITION:
                stream << "Postcondition";
                break;

            case cxinv::AssertLabel::INVARIANT:
                stream << "Invariant";
                break;

            default:
                return {};
        }

        stream << " violation at ";
    }

    stream << _FILE_ << ": line " << _LINE_ << "." << std::endl;
    stream << "  Function   : " << _FUNCTION_ << std::endl;
    stream << "  Expression : " << CONDITION_EXPRESSION << std::endl;

    if(p_message)
    {
        stream << "  Message    : " << p_message << std::endl;
    }

    stream << std::endl;

    return stream.str();
}


/***********************************************************************************************//**
 * Creates an expected message string for when the basic @c cxinv::handleAssert preconditions are
 * not met.
 *
 * @return The expected message, assuming at least one @c cxinv::handleAssert precondition is not
 *         met.
 *
 **************************************************************************************************/
std::string makeDeathMessage()
{
    return "assertion.cpp: Assertion error. Invalid arguments given to cxinv::handleAssert.";
}


} // namespace


TEST(Invariant, HandleAssert_AllValidInputsNoMessageAssertion_ValidMessages)
{
    std::ostringstream t_stream;
    StderrRedirectorRAII redirectorRAII{t_stream.rdbuf()};

    cxinv::handleAssert(cxinv::AssertLabel::ASSERTION,
                        (3 > 5),
                        CONDITION_EXPRESSION,
                        _FILE_,
                        _FUNCTION_,
                        _LINE_);

    const std::string result{t_stream.str()};
    const std::string expected{makeExpectedMessage(cxinv::AssertLabel::ASSERTION)};

    ASSERT_EQ(result, expected);
}


TEST(Invariant, HandleAssert_AllValidInputsNoMessagePrecondition_ValidMessages)
{
    std::ostringstream t_stream;
    StderrRedirectorRAII redirectorRAII{t_stream.rdbuf()};

    cxinv::handleAssert(cxinv::AssertLabel::PRECONDITION,
                        (3 > 5),
                        CONDITION_EXPRESSION,
                        _FILE_,
                        _FUNCTION_,
                        _LINE_);

    const std::string result{t_stream.str()};
    const std::string expected{makeExpectedMessage(cxinv::AssertLabel::PRECONDITION)};

    ASSERT_EQ(result, expected);
}


TEST(Invariant, HandleAssert_AllValidInputsNoMessagePostcondition_ValidMessages)
{
    std::ostringstream t_stream;
    StderrRedirectorRAII redirectorRAII{t_stream.rdbuf()};

    cxinv::handleAssert(cxinv::AssertLabel::POSTCONDITION,
                        (3 > 5),
                        CONDITION_EXPRESSION,
                        _FILE_,
                        _FUNCTION_,
                        _LINE_);

    const std::string result{t_stream.str()};
    const std::string expected{makeExpectedMessage(cxinv::AssertLabel::POSTCONDITION)};

    ASSERT_EQ(result, expected);
}


TEST(Invariant, HandleAssert_AllValidInputsNoMessageInvariant_ValidMessages)
{
    std::ostringstream t_stream;
    StderrRedirectorRAII redirectorRAII{t_stream.rdbuf()};

    cxinv::handleAssert(cxinv::AssertLabel::INVARIANT,
                        (3 > 5),
                        CONDITION_EXPRESSION,
                        _FILE_,
                        _FUNCTION_,
                        _LINE_);

    const std::string result{t_stream.str()};
    const std::string expected{makeExpectedMessage(cxinv::AssertLabel::INVARIANT)};

    ASSERT_EQ(result, expected);
}


TEST(Invariant, HandleAssert_AllValidInputsWithMessageAssertion_ValidMessages)
{
    std::ostringstream t_stream;
    StderrRedirectorRAII redirectorRAII{t_stream.rdbuf()};

    cxinv::handleAssert(cxinv::AssertLabel::ASSERTION,
                        (3 > 5),
                        CONDITION_EXPRESSION,
                        _FILE_,
                        _FUNCTION_,
                        _LINE_,
                        VALID_MESSAGE);

    const std::string result{t_stream.str()};
    const std::string expected{makeExpectedMessage(cxinv::AssertLabel::ASSERTION, VALID_MESSAGE)};

    ASSERT_EQ(result, expected);
}


TEST(Invariant, HandleAssert_AllValidInputsWithMessagePrecondition_ValidMessages)
{
    std::ostringstream t_stream;
    StderrRedirectorRAII redirectorRAII{t_stream.rdbuf()};

    cxinv::handleAssert(cxinv::AssertLabel::PRECONDITION,
                        (3 > 5),
                        CONDITION_EXPRESSION,
                        _FILE_,
                        _FUNCTION_,
                        _LINE_,
                        VALID_MESSAGE);

    const std::string result{t_stream.str()};
    const std::string expected{makeExpectedMessage(cxinv::AssertLabel::PRECONDITION, VALID_MESSAGE)};

    ASSERT_EQ(result, expected);
}


TEST(Invariant, HandleAssert_AllValidInputsWithMessagePostcondition_ValidMessages)
{
    std::ostringstream t_stream;
    StderrRedirectorRAII redirectorRAII{t_stream.rdbuf()};

    cxinv::handleAssert(cxinv::AssertLabel::POSTCONDITION,
                        (3 > 5),
                        CONDITION_EXPRESSION,
                        _FILE_,
                        _FUNCTION_,
                        _LINE_,
                        VALID_MESSAGE);

    const std::string result{t_stream.str()};
    const std::string expected{makeExpectedMessage(cxinv::AssertLabel::POSTCONDITION, VALID_MESSAGE)};

    ASSERT_EQ(result, expected);
}


TEST(Invariant, HandleAssert_AllValidInputsWithMessageInvariant_ValidMessages)
{
    std::ostringstream t_stream;
    StderrRedirectorRAII redirectorRAII{t_stream.rdbuf()};

    cxinv::handleAssert(cxinv::AssertLabel::INVARIANT,
                        (3 > 5),
                        CONDITION_EXPRESSION,
                        _FILE_,
                        _FUNCTION_,
                        _LINE_,
                        VALID_MESSAGE);

    const std::string result{t_stream.str()};
    const std::string expected{makeExpectedMessage(cxinv::AssertLabel::INVARIANT, VALID_MESSAGE)};

    ASSERT_EQ(result, expected);
}


TEST(Invariant, HandleAssert_invalidConditionExpression_ExecutionAborted)
{
    ASSERT_DEATH(cxinv::handleAssert(cxinv::AssertLabel::INVARIANT,
                                     (3 > 5),
                                     nullptr,
                                     _FILE_,
                                     _FUNCTION_,
                                     _LINE_),
                                     makeDeathMessage());
}


TEST(Invariant, HandleAssert_invalidFileName_ExecutionAborted)
{
    ASSERT_DEATH(cxinv::handleAssert(cxinv::AssertLabel::INVARIANT,
                                     (3 > 5),
                                     CONDITION_EXPRESSION,
                                     nullptr,
                                     _FUNCTION_,
                                     _LINE_),
                                     makeDeathMessage());
}


TEST(Invariant, HandleAssert_invalidFunctionName_ExecutionAborted)
{
    ASSERT_DEATH(cxinv::handleAssert(cxinv::AssertLabel::INVARIANT,
                                     (3 > 5),
                                     CONDITION_EXPRESSION,
                                     _FILE_,
                                     nullptr,
                                     _LINE_),
                                     makeDeathMessage());
}
