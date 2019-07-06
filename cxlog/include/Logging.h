#pragma once

#include "LoggingManager.h"
#include "IncrementalLogger.h"

// Log through this macro interface to reduce verbosity:
#define LOG_FATAL(p_message)   cxlog::theLoggerManager().log(cxlog::VerbosityLevel::FATAL,   __FILE__, __LINE__, __FUNCTION__, p_message)
#define LOG_ERROR(p_message)   cxlog::theLoggerManager().log(cxlog::VerbosityLevel::ERROR,   __FILE__, __LINE__, __FUNCTION__, p_message)
#define LOG_WARNING(p_message) cxlog::theLoggerManager().log(cxlog::VerbosityLevel::WARNING, __FILE__, __LINE__, __FUNCTION__, p_message)
#define LOG_INFO(p_message)    cxlog::theLoggerManager().log(cxlog::VerbosityLevel::INFO,    __FILE__, __LINE__, __FUNCTION__, p_message)
#define LOG_DEBUG(p_message)   cxlog::theLoggerManager().log(cxlog::VerbosityLevel::DEBUG,   __FILE__, __LINE__, __FUNCTION__, p_message)


namespace cxlog
{

class Logging final
{

public:

    static Logging& theLoggerManager();

    void log(const VerbosityLevel p_verbosityLevel,
             const std::string&   p_fileName,
             const std::string&   p_functionName,
             const size_t         p_lineNumber,
             const std::string&   p_message);

    Logging(Logging const&)         = delete;
    void operator=(Logging const&)  = delete;
    Logging(Logging const&&)        = delete;
    void operator=(Logging const&&) = delete;


private:

    Logging();

    std::unique_ptr<ILoggingManager> m_loggers;
};

} // namespace cxlog