#include <cxlog/include/CSVMessageFormatter.h>
#include <cxlog/include/IncrementalLogger.h>
#include <cxlog/include/IMessageFormatter.h>
#include <cxlog/include/StringStreamLogTarget.h>

#include "CVSLoggerUtil.h"


std::string generateLineToLog()
{
    return BASIC_STRING_TO_LOG;
}


std::string fatalResult()
{
    return FATAL_PREFIX + BASIC_STRING_TO_LOG + END_OF_LINE;
}


std::string errorResult()
{
    return ERROR_PREFIX + BASIC_STRING_TO_LOG + END_OF_LINE;
}


std::string warningResult()
{
    return WARNING_PREFIX + BASIC_STRING_TO_LOG + END_OF_LINE;
}


std::string infoResult()
{
    return INFO_PREFIX + BASIC_STRING_TO_LOG + END_OF_LINE;
}


std::string debugResult()
{
    return DEBUG_PREFIX + BASIC_STRING_TO_LOG + END_OF_LINE;
}


std::unique_ptr<cxlog::ILogger> createCVSStringStreamLogger(std::ostringstream& p_stream)
{
    // Creating logger dependencies:
    std::unique_ptr<cxlog::IMessageFormatter> t_formatter{new cxlog::CSVMessageFormatter};

    std::unique_ptr<cxlog::ILogTarget> t_target{new cxlog::StringStreamLogTarget{p_stream}};

    // Creating CSV string logger:
    std::unique_ptr<cxlog::ILogger> t_logger{new cxlog::StringLogger{std::move(t_formatter),
                                                                     std::move(t_target)}};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::DEBUG);

    return std::move(t_logger);
}