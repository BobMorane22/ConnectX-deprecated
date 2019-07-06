#include <cxlog/include/CSVMessageFormatter.h>
#include <cxlog/include/IncrementalChainedLogger.h>
#include <cxlog/include/IMessageFormatter.h>
#include <cxlog/include/StringStreamLogTarget.h>

#include "CSVLoggerUtil.h"
#include "TimestampFormatterMock.h"


std::string generateLineToLog()
{
    return BASIC_STRING_TO_LOG;
}

std::string generateResult(const std::string p_prefix)
{
    return "AAAA:MM:JJTHH:MM:SS:mm"   + SEPARATOR +
           p_prefix                   +
           _FILE_                     + SEPARATOR +
           _FUNCTION_                 + SEPARATOR +
           std::to_string(_LINE_)     + SEPARATOR +
           BASIC_STRING_TO_LOG        + END_OF_LINE;
}

std::string fatalResult()
{
    return generateResult(FATAL_PREFIX);
}


std::string errorResult()
{
    return generateResult(ERROR_PREFIX);
}


std::string warningResult()
{
    return generateResult(WARNING_PREFIX);
}


std::string infoResult()
{
    return generateResult(INFO_PREFIX);
}


std::string debugResult()
{
    return generateResult(DEBUG_PREFIX);
}


std::string headerLine()
{
    return "Timestamp"       + SEPARATOR +
           "File name"       + SEPARATOR +
           "Function name"   + SEPARATOR +
           "Line number"     + SEPARATOR +
           "Verbosity level" + SEPARATOR +
           "Message"         + END_OF_LINE;
}

std::unique_ptr<cxlog::ILogger> createCVSStringStreamLogger(std::ostringstream& p_stream,
                                                            const bool          p_generateHeader)
{
    // Creating logger dependencies:
    std::unique_ptr<cxlog::ITimestampFormatter> t_timeFormatter{new TimestampFormatterMock};
    std::unique_ptr<cxlog::IMessageFormatter> t_msgFormatter{new cxlog::CSVMessageFormatter{std::move(t_timeFormatter)}};

    std::unique_ptr<cxlog::ILogTarget> t_target{new cxlog::StringStreamLogTarget{p_stream}};

    // Creating CSV string logger:
    std::unique_ptr<cxlog::ILogger> t_logger{new cxlog::IncrementalChainedLogger{std::move(t_msgFormatter),
                                             std::move(t_target),
                                             p_generateHeader}};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::DEBUG);

    return std::move(t_logger);
}

std::unique_ptr<cxlog::ChainLogger> createCVSStringStreamChainLogger(std::ostringstream& p_stream,
                                                                     const bool          p_generateHeader)
{
    // Creating logger dependencies:
    std::unique_ptr<cxlog::ITimestampFormatter> t_timeFormatter{new TimestampFormatterMock};
    std::unique_ptr<cxlog::IMessageFormatter> t_msgFormatter{new cxlog::CSVMessageFormatter{std::move(t_timeFormatter)}};

    std::unique_ptr<cxlog::ILogTarget> t_target{new cxlog::StringStreamLogTarget{p_stream}};

    // Creating CSV string logger:
    std::unique_ptr<cxlog::ChainLogger> t_logger{new cxlog::IncrementalChainedLogger{std::move(t_msgFormatter),
                                                                                     std::move(t_target),
                                                                                     p_generateHeader}};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::DEBUG);

    return std::move(t_logger);
}