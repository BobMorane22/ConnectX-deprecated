#pragma once

#include <string>
#include <memory>
#include <vector>

#include "ILogger.h"
#include "ILoggingManager.h"

namespace cxlog
{

using LoggerUptrList = std::vector<std::unique_ptr<ILogger>>;

class LoggingManager : public ILoggingManager
{
public:
    LoggingManager(LoggerUptrList&& p_loggers);
    LoggingManager(std::unique_ptr< ILogger >&& p_logger);

    ~LoggingManager() override;

    void setVerbosityLevel(const cxlog::VerbosityLevel p_level) override;
    VerbosityLevel verbosityLevel() const override;

    void log( const VerbosityLevel p_verbosityLevel,
              const std::string&   p_fileName,
              const std::string&   p_functionName,
              const size_t         p_lineNumber,
              const std::string&   p_message ) override;

private:

    LoggerUptrList m_loggers;
    VerbosityLevel m_level{VerbosityLevel::NONE};
};

} // namespace cxlog
