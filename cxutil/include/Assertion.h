#ifndef ASSERTION_H_5E16567F_34E8_438C_A425_49FF0BC97A1C
#define ASSERTION_H_5E16567F_34E8_438C_A425_49FF0BC97A1C

#if !defined(NDEBUG)

#include <cassert>
#include <iostream>

#define CX_ASSERT(__condition__)                                          \
{                                                                         \
    if(!(__condition__))                                                  \
    {                                                                     \
        std::cerr << "Assertion failed!"                 << std::endl;    \
        std::cerr <<   "  Condition : " << #__condition__ << std::endl;   \
        std::cerr <<   "  File      : " << __FILE__       << std::endl;   \
        std::cerr <<   "  Line      : " << __LINE__       << std::endl;   \
        std::cerr <<   "  Function  : " << __FUNCTION__   << std::endl;   \
        abort();                                                          \
    }                                                                     \
}

#define CX_ASSERT_MSG(__condition__, __message__)                         \
{                                                                         \
    if(!(__condition__))                                                  \
    {                                                                     \
        std::cerr << "Assertion failed!"                 << std::endl;    \
        std::cerr <<   "  Condition : " << #__condition__ << std::endl;   \
        std::cerr <<   "  Message   : " << __message__    << std::endl;   \
        std::cerr <<   "  File      : " << __FILE__       << std::endl;   \
        std::cerr <<   "  Line      : " << __LINE__       << std::endl;   \
        std::cerr <<   "  Function  : " << __FUNCTION__   << std::endl;   \
        abort();                                                          \
    }                                                                     \
}                                                                         \

#else

#define CX_ASSERT(__condition__)                                  (__condition__)
#define CX_ASSERT_MSG(__condition__, __message__)                 (__condition__)

#endif

// Source: http://thesoftwarecondition.com/blog/2010/08/01/cc-assertions-and-defining-your-own-assert-macro/

#endif /* ASSERTION_H_5E16567F_34E8_438C_A425_49FF0BC97A1C */