#define GTEST_HAS_STD_TUPLE_ 1
#define GTEST_HAS_TR1_TUPLE  0

#include <gtest/gtest.h>

#include <cxlog/include/CSVMessageFormatter.h>
#include <cxlog/include/IncrementalLogger.h>
#include <cxlog/include/StringStreamLogTarget.h>

#include "CSVLoggerUtil.h"


TEST(ChainLogging, ChainLogging_TwoSuccessiveLoggers_FirstHasSuccessorSecondDoesNot)
{
    std::ostringstream t_stream;
    std::ostringstream t_streamSuccessor;

    auto t_logger{createCVSStringStreamLogger(t_stream)};
    auto t_loggerSuccessor{createCVSStringStreamLogger(t_streamSuccessor)};

    ASSERT_FALSE(t_logger->hasSucessor());

    t_logger->setSucessor(std::move(t_loggerSuccessor));

    ASSERT_TRUE(t_logger->hasSucessor());
}


TEST(ChainLogging, ChainLogging_ValidStringAsInfo_AllLoggersLog)
{
    std::ostringstream t_stream;
    std::ostringstream t_streamSuccessor;

    auto t_logger{createCVSStringStreamLogger(t_stream)};
    auto t_loggerSuccessor{createCVSStringStreamLogger(t_streamSuccessor)};

    t_logger->setSucessor(std::move(t_loggerSuccessor));

    // Log a string:
    t_logger->log(cxlog::VerbosityLevel::INFO, _FILE_, _FUNCTION_, _LINE_, generateLineToLog());

    // Get log results:
    const std::string loggedLine{t_stream.str()};
    const std::string loggedLineSuccessor{t_streamSuccessor.str()};
    const std::string expectedLine{infoResult()};

    ASSERT_EQ(loggedLine, infoResult());
    ASSERT_EQ(loggedLineSuccessor, infoResult());
}

TEST(ChainLogging, ChainLogging_ValidStringAsInfo_AllLoggersLogExceptNone)
{
    std::ostringstream t_stream,
                       t_streamFirstSuccessor,
                       t_streamSecondSuccessor;

    auto t_logger               {createCVSStringStreamLogger(t_stream)};
    auto t_loggerFirstSuccessor {createCVSStringStreamLogger(t_streamFirstSuccessor)};
    auto t_loggerSecondSuccessor{createCVSStringStreamLogger(t_streamSecondSuccessor)};

    // Middle successor is silenced:
    t_loggerFirstSuccessor->setVerbosityLevel(cxlog::VerbosityLevel::NONE);

    // Set two successors:
    t_loggerFirstSuccessor->setSucessor(std::move(t_loggerSecondSuccessor));
    t_logger->setSucessor(std::move(t_loggerFirstSuccessor));

    // Log a string:
    t_logger->log(cxlog::VerbosityLevel::INFO, _FILE_, _FUNCTION_, _LINE_, generateLineToLog());

    // Get log results:
    const std::string loggedLine               {t_stream.str()};
    const std::string loggedLineFirstSuccessor {t_streamFirstSuccessor.str()};
    const std::string loggedLineSecondSuccessor{t_streamSecondSuccessor.str()};

    const std::string expectedLine{infoResult()};

    ASSERT_EQ(loggedLine,                infoResult());
    ASSERT_EQ(loggedLineFirstSuccessor,  EMPTY_STRING);
    ASSERT_EQ(loggedLineSecondSuccessor, infoResult());
}