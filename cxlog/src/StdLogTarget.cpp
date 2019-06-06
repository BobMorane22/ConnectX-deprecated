#include <cxinv/include/assertion.h>

#include "../include/StdLogTarget.h"


void cxlog::StdLogTarget::log(const std::string& p_message)
{
    ASSERT_MSG(stdStream().good(), "Standard stream is in a bad state.");

    if(&stdStream())
    {
        stdStream() << p_message;
    }
}