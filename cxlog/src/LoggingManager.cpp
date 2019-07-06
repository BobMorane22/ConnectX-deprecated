#include <algorithm>

#include <cxinv/include/assertion.h>

#include "../include/LoggingManager.h"


cxlog::LoggingManager::LoggingManager(LoggerUptrList&& p_loggers)
{
    PRECONDITION(!p_loggers.empty());
    PRECONDITION(std::none_of(p_loggers.cbegin(),
                              p_loggers.cend(),
                             [](const std::unique_ptr<cxlog::ILogger>& p_logger)
                             {
                                 return p_logger == nullptr;
                             }));

    for(auto& logger : p_loggers)
    {
        m_loggers.push_back(std::move(logger));
    }

    POSTCONDITION(!m_loggers.empty());
    POSTCONDITION(std::none_of(m_loggers.cbegin(),
                               m_loggers.cend(),
                               [](const std::unique_ptr<cxlog::ILogger>& p_logger)
                               {
                                   return p_logger == nullptr;
                               }));
}


cxlog::LoggingManager::LoggingManager(std::unique_ptr<ILogger>&& p_logger)
{
    PRECONDITION(p_logger != nullptr);

    m_loggers.push_back(std::move(p_logger));

    POSTCONDITION(m_loggers.back() != nullptr);
    POSTCONDITION(!m_loggers.empty());
}


cxlog::LoggingManager::~LoggingManager() = default;


void cxlog::LoggingManager::setVerbosityLevel(const cxlog::VerbosityLevel p_level)
{
    for(auto& logger : m_loggers)
    {
        logger->setVerbosityLevel(p_level);
    }

    m_level = p_level;
}


cxlog::VerbosityLevel cxlog::LoggingManager::verbosityLevel() const
{
    return m_level;
}


void cxlog::LoggingManager::log(const cxlog::VerbosityLevel p_verbosityLevel,
                                const std::string&          p_fileName,
                                const std::string&          p_functionName,
                                const size_t                p_lineNumber,
                                const std::string&          p_message)
{
    for(auto& logger : m_loggers)
    {
        if(logger)
        {
            logger->log(p_verbosityLevel,
                        p_fileName,
                        p_functionName,
                        p_lineNumber,
                        p_message);
        }
    }
}
