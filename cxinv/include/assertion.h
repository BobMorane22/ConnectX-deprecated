#pragma once

#ifndef NDEBUG
namespace cxinv
{

enum class AssertLabel
{
    ASSERTION,
    PRECONDITION,
    POSTCONDITION,
    INVARIANT,
};

// Comment
void abortIfNeeded();

// Comment
const char* getLabelAsString(const AssertLabel p_label);

// Comment
void handleAssert(const AssertLabel  p_label,
                  const bool         p_conditionRes,
                  const char*        p_conditionExpr,
                  const char*        p_fileName,
                  const char*        p_functionName,
                  const long         p_lineNumber,
                  const char*        p_message = nullptr);

} // namespace cxinv

#endif // NDEBUG


/*************************************************************************************************************/
/******************************************** Standard assertions ********************************************/
/*************************************************************************************************************/

#ifndef NDEBUG
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
#define ASSERT_FALSE ASSERT(false)
#else
#define ASSERT_FALSE ((void)0)
#endif // NDEBUG

#ifndef NDEBUG
#define ASSERT_FALSE_MSG(p_message) ASSERT_MSG(false, p_message)
#else
#define ASSERT_FALSE_MSG(p_message) ((void)0)
#endif // NDEBUG


/*************************************************************************************************************/
/******************************************** Contract assertions ********************************************/
/*************************************************************************************************************/

#ifndef NDEBUG
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
