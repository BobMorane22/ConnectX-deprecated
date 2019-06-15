#include <cxinv/include/assertion.h>

#include "../include/StringStreamLogTarget.h"

cxlog::StringStreamLogTarget::StringStreamLogTarget(std::ostringstream& p_stringStream)
 : m_stringStream{p_stringStream}
{
}

void cxlog::StringStreamLogTarget::log(const std::string& p_message)
{
    if(stringStream())
    {
        stringStream() << p_message;

        return;
    }

    ASSERT_FALSE_MSG("String stream not valid.");
}