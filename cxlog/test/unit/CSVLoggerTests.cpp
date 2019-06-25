#define GTEST_HAS_STD_TUPLE_ 1
#define GTEST_HAS_TR1_TUPLE  0

#include <gtest/gtest.h>

#include <cxlog/include/CSVMessageFormatter.h>
#include <cxlog/include/IncrementalChainedLogger.h>
#include <cxlog/include/StringStreamLogTarget.h>

#include "CSVLoggerUtil.h"


TEST(CSVLogger, CVSStringLogger_ValidStringAsInfo_LoggingIsAdequate)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    // Log a string:
    t_logger->log(cxlog::VerbosityLevel::INFO, _FILE_, _FUNCTION_, _LINE_, generateLineToLog());

    // Get log result:
    const std::string loggedLine{t_stream.str()};

    ASSERT_EQ(loggedLine, infoResult());
}


TEST(CSVLogger, CVSStringLogger_ValidStringAsError_LoggingIsAdequate)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    // Log a string:
    t_logger->log(cxlog::VerbosityLevel::ERROR, _FILE_, _FUNCTION_, _LINE_, generateLineToLog());

    // Get log result:
    const std::string loggedLine{t_stream.str()};

    ASSERT_EQ(loggedLine, errorResult());
}


TEST(CSVLogger, CVSStringLogger_ValidStringAsFatal_LoggingIsAdequate)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    // Log a string:
    t_logger->log(cxlog::VerbosityLevel::FATAL, _FILE_, _FUNCTION_, _LINE_, generateLineToLog());

    // Get log result:
    const std::string loggedLine{t_stream.str()};

    ASSERT_EQ(loggedLine, fatalResult());
}


TEST(CSVLogger, CVSStringLogger_ValidStringAsDebug_LoggingIsAdequate)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    // Log a string:
    t_logger->log(cxlog::VerbosityLevel::DEBUG, _FILE_, _FUNCTION_, _LINE_, generateLineToLog());

    // Get log result:
    const std::string loggedLine{t_stream.str()};

    ASSERT_EQ(loggedLine, debugResult());
}


TEST(CSVLogger, CVSStringLogger_ValidStrings_AllLinesLoggued)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    // Log a string:
    t_logger->log(cxlog::VerbosityLevel::INFO,  _FILE_, _FUNCTION_, _LINE_, generateLineToLog());
    t_logger->log(cxlog::VerbosityLevel::ERROR, _FILE_, _FUNCTION_, _LINE_, generateLineToLog());
    t_logger->log(cxlog::VerbosityLevel::FATAL, _FILE_, _FUNCTION_, _LINE_, generateLineToLog());

    // Get log result:
    const std::string loggedLines{t_stream.str()};

    const std::string expectedLines{infoResult() + errorResult() + fatalResult()};

    ASSERT_EQ(loggedLines, expectedLines);
}


TEST(CSVLogger, CVSStringLogger_GenerateHeadersTrue_HeadersGenerated)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream, true)};

    // Get log result:
    const std::string loggedLines{t_stream.str()};

    ASSERT_EQ(loggedLines, headerLine());
}