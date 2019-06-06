#define GTEST_HAS_STD_TUPLE_ 1
#define GTEST_HAS_TR1_TUPLE  0

#include <gtest/gtest.h>

#include <cxlog/include/CSVMessageFormatter.h>
#include <cxlog/include/IncrementalLogger.h>
#include <cxlog/include/StringStreamLogTarget.h>

#include "CVSLoggerUtil.h"

namespace
{

void logAtAllLevels(std::unique_ptr<cxlog::ILogger> p_logger)
{
    p_logger->log(cxlog::VerbosityLevel::NONE,    generateLineToLog());
    p_logger->log(cxlog::VerbosityLevel::FATAL,   generateLineToLog());
    p_logger->log(cxlog::VerbosityLevel::ERROR,   generateLineToLog());
    p_logger->log(cxlog::VerbosityLevel::WARNING, generateLineToLog());
    p_logger->log(cxlog::VerbosityLevel::INFO,    generateLineToLog());
    p_logger->log(cxlog::VerbosityLevel::DEBUG,   generateLineToLog());
}

} // unamed namespace

TEST(Logger, CVSStringLogger_TargetNONE_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::NONE);

    logAtAllLevels(std::move(t_logger));

    ASSERT_TRUE(t_stream.str().empty());
}


TEST(Logger, CVSStringLogger_TargetFATAL_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::FATAL);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult());
}


TEST(Logger, CVSStringLogger_TargetERROR_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::ERROR);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult() + errorResult());
}


TEST(Logger, CVSStringLogger_TargetWARNING_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::WARNING);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult() + errorResult() + warningResult());
}


TEST(Logger, CVSStringLogger_TargetINFO_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::INFO);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult() + errorResult() + warningResult() + infoResult());
}


TEST(Logger, CVSStringLogger_TargetDEBUG_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::DEBUG);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult() + errorResult() + warningResult() + infoResult() + debugResult());
}