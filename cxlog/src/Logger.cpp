#include "../include/Logger.h"

void cxlog::Logger::setVerbosityLevel(const cxlog::VerbosityLevel p_verbosityLevel)
{
    m_verbosityLevel = p_verbosityLevel;
}

cxlog::VerbosityLevel cxlog::Logger::verbosityLevel() const
{
    return m_verbosityLevel;
}