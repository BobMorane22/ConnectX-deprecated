#include "../include/assertion.h"

#ifndef NDEBUG
#include <iostream>

void cxinv::handleAssert(const cxinv::AssertLabel  p_label,
                         const bool                p_conditionRes,
                         const char*               p_conditionExpr,
                         const char*               p_fileName,
                         const char*               p_functionName,
                         const long                p_lineNumber,
                         const char*               p_message)
{
    if(!(p_conditionRes))
    {
        if(p_label == AssertLabel::ASSERTION)
        {
            std::cerr << "Assertion failed at ";
        }
        else
        {
            std::cerr << getLabelAsString(p_label) << " violation at ";
        }

        std::cerr << p_fileName << ": line " << p_lineNumber << "." << std::endl;
        std::cerr << "  Function   : " << p_functionName << std::endl;
        std::cerr << "  Expression : " << p_conditionExpr << std::endl;

        if(p_message)
        {
            std::cerr << "  Message    : " << p_message << std::endl;
        }

        std::cerr << std::endl;

        abortIfNeeded();
    }
}

void cxinv::abortIfNeeded()
{
#ifdef ABORT_ON_ERROR
    std::abort();
#endif // ABORT_ON_ASSERTION
}

const char* cxinv::getLabelAsString(const AssertLabel p_label)
{
    switch(p_label)
    {
    case AssertLabel::ASSERTION:     return "Assertion";
    case AssertLabel::PRECONDITION:  return "Precondition";
    case AssertLabel::POSTCONDITION: return "Postcondition";
    case AssertLabel::INVARIANT:     return "Invariant";
    default:
        std::abort(); // Label type unknown...
    }
}

#endif // NDEBUG
