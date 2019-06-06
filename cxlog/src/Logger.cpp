#include <chrono>
#include <iomanip>
#include <sstream>

#include "../include/Logger.h"

void cxlog::Logger::setVerbosityLevel(const cxlog::VerbosityLevel p_verbosityLevel)
{
    m_verbosityLevel = p_verbosityLevel;
}

cxlog::VerbosityLevel cxlog::Logger::verbosityLevel() const
{
    return m_verbosityLevel;
}

void cxlog::Logger::setSucessor(std::unique_ptr<ILogger>&& p_sucessor)
{
    m_successor = std::move(p_sucessor);
}

bool cxlog::Logger::hasSucessor() const
{
    if(m_successor != nullptr)
    {
        return true;
    }

    return false;
}
