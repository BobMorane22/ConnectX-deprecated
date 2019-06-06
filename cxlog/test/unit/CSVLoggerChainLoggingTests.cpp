#define GTEST_HAS_STD_TUPLE_ 1
#define GTEST_HAS_TR1_TUPLE  0

#include <gtest/gtest.h>

#include <cxlog/include/CSVMessageFormatter.h>
#include <cxlog/include/IncrementalLogger.h>
#include <cxlog/include/StringStreamLogTarget.h>

#include "CVSLoggerUtil.h"


TEST(Logger, ChainLogging_TwoSuccessiveLoggers_FirstHasSuccessorSecondDoesNot)
{
    std::ostringstream t_stream;
    std::ostringstream t_streamSuccessor;

    auto t_logger{createCVSStringStreamLogger(t_stream)};
    auto t_loggerSuccessor{createCVSStringStreamLogger(t_streamSuccessor)};

    ASSERT_FALSE(t_logger->hasSucessor());

    t_logger->setSucessor(std::move(t_loggerSuccessor));

    ASSERT_TRUE(t_logger->hasSucessor());
}


TEST(Logger, ChainLogging_ValidStringAsInfo_AllLoggersLog)
{
    std::ostringstream t_stream;
    std::ostringstream t_streamSuccessor;

    auto t_logger{createCVSStringStreamLogger(t_stream)};
    auto t_loggerSuccessor{createCVSStringStreamLogger(t_streamSuccessor)};

    t_logger->setSucessor(std::move(t_loggerSuccessor));

    // Log a string:
    t_logger->log(cxlog::VerbosityLevel::INFO, "CSV logger test");

    // Get log results:
    const std::string loggedLine{t_stream.str()};
    const std::string loggedLineSuccessor{t_streamSuccessor.str()};
    const std::string expectedLine{"INFO, CSV logger test\n"};

    ASSERT_EQ(loggedLine, "INFO, CSV logger test\n");
    ASSERT_EQ(loggedLineSuccessor, "INFO, CSV logger test\n");
}
