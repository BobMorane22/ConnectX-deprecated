#define GTEST_HAS_STD_TUPLE_ 1
#define GTEST_HAS_TR1_TUPLE  0

#include <gtest/gtest.h>

#include <cxlog/include/CSVMessageFormatter.h>
#include <cxlog/include/IncrementalLogger.h>
#include <cxlog/include/StringStreamLogTarget.h>

#include "CVSLoggerUtil.h"


TEST(Logger, CVSStringLogger_ValidStringAsInfo_LoggingIsAdequate)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    // Log a string:
    t_logger->log(cxlog::VerbosityLevel::INFO, generateLineToLog());

    // Get log result:
    const std::string loggedLine{t_stream.str()};

    ASSERT_EQ(loggedLine, infoResult());
}


TEST(Logger, CVSStringLogger_ValidStringAsError_LoggingIsAdequate)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    // Log a string:
    t_logger->log(cxlog::VerbosityLevel::ERROR, generateLineToLog());

    // Get log result:
    const std::string loggedLine{t_stream.str()};

    ASSERT_EQ(loggedLine, errorResult());
}


TEST(Logger, CVSStringLogger_ValidStringAsFatal_LoggingIsAdequate)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    // Log a string:
    t_logger->log(cxlog::VerbosityLevel::FATAL, generateLineToLog());

    // Get log result:
    const std::string loggedLine{t_stream.str()};

    ASSERT_EQ(loggedLine, fatalResult());
}


TEST(Logger, CVSStringLogger_ValidStringAsDebug_LoggingIsAdequate)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    // Log a string:
    t_logger->log(cxlog::VerbosityLevel::DEBUG, generateLineToLog());

    // Get log result:
    const std::string loggedLine{t_stream.str()};

    ASSERT_EQ(loggedLine, debugResult());
}


TEST(Logger, CVSStringLogger_ValidStrings_AllLinesLoggued)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    // Log a string:
    t_logger->log(cxlog::VerbosityLevel::INFO,  generateLineToLog());
    t_logger->log(cxlog::VerbosityLevel::ERROR, generateLineToLog());
    t_logger->log(cxlog::VerbosityLevel::FATAL, generateLineToLog());

    // Get log result:
    const std::string loggedLines{t_stream.str()};

    const std::string expectedLines{infoResult() + errorResult() + fatalResult()};

    ASSERT_EQ(loggedLines, expectedLines);
}