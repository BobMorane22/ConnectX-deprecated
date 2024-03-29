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
 * @file    assertion.h
 * @author  Eric Poirier
 * @date    July 2019
 * @version 1.0
 *
 * Specific macros used to assert conditions in the code and to enfore proramming by contract.
 *
 **************************************************************************************************/

#ifndef ASSERTION_H_0470D299_880C_415F_BEE0_57ED14327B58
#define ASSERTION_H_0470D299_880C_415F_BEE0_57ED14327B58


#ifndef NDEBUG
namespace cxinv
{

/***********************************************************************************************//**
 * @enum AssertLabel
 *
 * @brief Assertion label types.
 *
 * Defines different label (i.e. 'kinds') of assertions.
 *
 ***************************************************************************************************/
enum class AssertLabel
{
    ASSERTION,
    PRECONDITION,
    POSTCONDITION,
    INVARIANT,
};


/***********************************************************************************************//**
 * @brief Handles assertions of various types.
 *
 * Handles assertions of various types by formatting a proper error message and aborting, if
 * needed. Never call this function directly, but always through the appropriate assertion
 * macros.
 *
 * @param p_label         The assertion label. This defines what kind of assertion is
 *                        treated.
 * @param p_conditionRes  The logical condition that is asserted.
 * @param p_conditionExpr The logical expression (as a readable C++ string) that is asserted.
 * @param p_fileName      The file name into which the assertion is located.
 * @param p_functionName  The function name into which the assertion is located.
 * @param p_lineNumber    The line number at which the assertion is located.
 * @param p_message       An optional assertion message.
 *
 * @warning Never use this function by itself! Use assertion macros instead.
 *
 ***************************************************************************************************/
void handleAssert(const AssertLabel  p_label,
                  const bool         p_conditionRes,
                  const char*        p_conditionExpr,
                  const char*        p_fileName,
                  const char*        p_functionName,
                  const long         p_lineNumber,
                  const char*        p_message = nullptr);

} // namespace cxinv

#endif // NDEBUG


#ifndef NDEBUG
/***********************************************************************************************//**
 * @brief Standard assertion MACRO (no message attached)
 *
 * Asserts that @c p_condition is @c true. If you @c #define the @c ABORT_ON_ERROR flag, this
 * MACRO will also abort on a false condition.
 *
 * @param p_condition The condition to assert.
 *
 ***************************************************************************************************/
#define ASSERT(p_condition) cxinv::handleAssert(cxinv::AssertLabel::ASSERTION, \
                                                ( p_condition ),               \
                                                #p_condition,                  \
                                                __FILE__,                      \
                                                __FUNCTION__,                  \
                                                __LINE__,                      \
                                                nullptr                        \
                                                )
#else
#define ASSERT(p_condition) ((void)0)
#endif // NDEBUG

#ifndef NDEBUG
/***********************************************************************************************//**
 * @brief Standard assertion MACRO (with message attached)
 *
 * Asserts that @c p_condition is @c true. If you @c #define the @c ABORT_ON_ERROR flag, this
 * MACRO will also abort on a @c false condition. On assertion, a custom message defined by the
 * programmer will be printed out along with the assertion information.
 *
 * @param p_condition The condition to assert.
 * @param p_message   The message to print.
 *
 ***************************************************************************************************/
#define ASSERT_MSG(p_condition, p_message) cxinv::handleAssert(cxinv::AssertLabel::ASSERTION, \
                                                               ( p_condition ),               \
                                                               #p_condition,                  \
                                                               __FILE__,                      \
                                                               __FUNCTION__,                  \
                                                               __LINE__,                      \
                                                               p_message                      \
                                                               )
#else
#define ASSERT_MSG(p_condition, p_message) ((void)0)
#endif // NDEBUG

#ifndef NDEBUG
/***********************************************************************************************//**
 * @brief Inconditional assertion MACRO (no message attached).
 *
 * Will assert inconditionally. Use this when you know something went wrong and an assertion
 * must occur. If you @c #define the @c ABORT_ON_ERROR flag, this MACRO will also abort.
 *
 ***************************************************************************************************/
#define ASSERT_ERROR() ASSERT(false)
#else
#define ASSERT_ERROR() ((void)0)
#endif // NDEBUG

#ifndef NDEBUG
/***********************************************************************************************//**
 * @brief Inconditional assertion MACRO (no message attached).
 *
 * Will assert inconditionally. Use this when you know something went wrong and an assertion
 * must occur. If you @c #define the @c ABORT_ON_ERROR flag, this MACRO will also abort.
 * On assertion, a custom message defined by the programmer will be printedout along with the
 * assertion information.
 *
 * @param p_message   The message to print.
 *
 ***************************************************************************************************/
#define ASSERT_ERROR_MSG(p_message) ASSERT_MSG(false, p_message)
#else
#define ASSERT_ERROR_MSG(p_message) ((void)0)
#endif // NDEBUG

#ifndef NDEBUG
/***********************************************************************************************//**
 * @brief Standard precondition MACRO.
 *
 * Asserts that @c p_condition is @c true. If you @c #define the @c ABORT_ON_ERROR flag, this
 * MACRO will also abort on a @c false condition.
 *
 * @param p_condition The condition to assert.
 *
 ***************************************************************************************************/
#define PRECONDITION(p_preCondition) cxinv::handleAssert(cxinv::AssertLabel::PRECONDITION, \
                                                           ( p_preCondition ),             \
                                                           #p_preCondition,                \
                                                           __FILE__,                       \
                                                           __FUNCTION__,                   \
                                                           __LINE__                        \
                                                           )
#else
#define PRECONDITION(p_preCondition) ((void)0)
#endif // NDEBUG

#ifndef NDEBUG
/***********************************************************************************************//**
 * @brief Standard postcondition MACRO.
 *
 * Asserts that @c p_condition is @c true. If you @c #define the @c ABORT_ON_ERROR flag, this
 * MACRO will also abort on a @c false condition.
 *
 * @param p_condition The condition to assert.
 *
 ***************************************************************************************************/
#define POSTCONDITION(p_postCondition) cxinv::handleAssert(cxinv::AssertLabel::POSTCONDITION, \
                                                           ( p_postCondition ),               \
                                                           #p_postCondition,                  \
                                                           __FILE__,                          \
                                                           __FUNCTION__,                      \
                                                           __LINE__                           \
                                                           )
#else
#define POSTCONDITION(p_postCondition) ((void)0)
#endif // NDEBUG

#ifndef NDEBUG
/***********************************************************************************************//**
 * @brief Standard invariant MACRO.
 *
 * Asserts that @c p_condition is @c true. If you @c #define the @c ABORT_ON_ERROR flag, this
 * MACRO will also abort on a @c false condition.
 *
 * @param p_condition The condition to assert.
 *
 ***************************************************************************************************/
#define INVARIANT(p_invariant) cxinv::handleAssert(cxinv::AssertLabel::INVARIANT, \
                                                   ( p_invariant ),               \
                                                   #p_invariant,                  \
                                                   __FILE__,                      \
                                                   __FUNCTION__,                  \
                                                   __LINE__                       \
                                                   )
#else
#define INVARIANT(p_invariant) ((void)0)
#endif // NDEBUG

#endif // ASSERTION_H_0470D299_880C_415F_BEE0_57ED14327B58
