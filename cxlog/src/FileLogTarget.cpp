#include <cxinv/include/assertion.h>

#include "../include/FileLogTarget.h"


cxlog::FileLogTarget::FileLogTarget(const std::string& p_logFileName)
{
    m_fileStream.open(p_logFileName, std::ios_base::out);

    ASSERT_MSG(fileStream().good(), "File stream is in a bad state.");
}


void cxlog::FileLogTarget::log(const std::string& p_message)
{
    ASSERT_MSG(fileStream().good(), "File stream is in a bad state.");

    if(fileStream())
    {
        fileStream() << p_message;
    }
}