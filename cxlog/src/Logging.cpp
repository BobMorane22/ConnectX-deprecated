#include <cxinv/include/assertion.h>

#include "../include/Logging.h"


namespace
{

std::unique_ptr<cxlog::ILogger> createCSVFileLogger()
{
    ASSERT_FALSE_MSG("Not yet implemented.");

    return nullptr;
}

std::unique_ptr<cxlog::ILogger> createCSVStdoutLogger()
{
    ASSERT_FALSE_MSG("Not yet implemented.");

    return nullptr;
}

} // namespace


cxlog::Logging::Logging()
 : m_loggers{nullptr}
{
    // Create loggers:
    LoggerUptrList loggers;
    loggers.push_back(std::move(createCSVFileLogger()));
    loggers.push_back(std::move(createCSVStdoutLogger()));

    // Register them with the manager:
    m_loggers.reset(new LoggingManager{std::move(loggers)});
}


cxlog::Logging& cxlog::Logging::theLoggerManager()
{
    static Logging INSTANCE;

    return INSTANCE;
}


void cxlog::Logging::log(const cxlog::VerbosityLevel p_verbosityLevel,
                         const std::string&          p_fileName,
                         const std::string&          p_functionName,
                         const size_t                p_lineNumber,
                         const std::string&          p_message)
{
    if(m_loggers)
    {
        m_loggers->log(p_verbosityLevel, p_fileName, p_functionName, p_lineNumber, p_message);

        return;
    }

    ASSERT_FALSE();
}