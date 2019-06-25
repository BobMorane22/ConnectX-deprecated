#define GTEST_HAS_STD_TUPLE_ 1
#define GTEST_HAS_TR1_TUPLE  0

#include <gtest/gtest.h>

#include <cxlog/include/CSVMessageFormatter.h>
#include <cxlog/include/IncrementalChainedLogger.h>
#include <cxlog/include/StringStreamLogTarget.h>

#include "CSVLoggerUtil.h"

namespace
{

void logAtAllLevels(std::unique_ptr<cxlog::ILogger> p_logger)
{
    p_logger->log(cxlog::VerbosityLevel::NONE,    _FILE_, _FUNCTION_, _LINE_, generateLineToLog());
    p_logger->log(cxlog::VerbosityLevel::FATAL,   _FILE_, _FUNCTION_, _LINE_, generateLineToLog());
    p_logger->log(cxlog::VerbosityLevel::ERROR,   _FILE_, _FUNCTION_, _LINE_, generateLineToLog());
    p_logger->log(cxlog::VerbosityLevel::WARNING, _FILE_, _FUNCTION_, _LINE_, generateLineToLog());
    p_logger->log(cxlog::VerbosityLevel::INFO,    _FILE_, _FUNCTION_, _LINE_, generateLineToLog());
    p_logger->log(cxlog::VerbosityLevel::DEBUG,   _FILE_, _FUNCTION_, _LINE_, generateLineToLog());
}

} // unamed namespace

TEST(CSVIncrementalLogging, CSVStringLogger_TargetNONE_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::NONE);

    logAtAllLevels(std::move(t_logger));

    ASSERT_TRUE(t_stream.str().empty());
}


TEST(CSVIncrementalLogging, CSVStringLogger_TargetFATAL_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::FATAL);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult());
}


TEST(CSVIncrementalLogging, CSVStringLogger_TargetERROR_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::ERROR);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult() + errorResult());
}


TEST(CSVIncrementalLogging, CSVStringLogger_TargetWARNING_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::WARNING);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult() + errorResult() + warningResult());
}


TEST(CSVIncrementalLogging, CSVStringLogger_TargetINFO_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::INFO);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult() + errorResult() + warningResult() + infoResult());
}


TEST(CSVIncrementalLogging, CSVStringLogger_TargetDEBUG_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::DEBUG);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult() + errorResult() + warningResult() + infoResult() + debugResult());
}


TEST(CSVIncrementalLogging, CSVStringChainedLogger_TargetNONE_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamChainLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::NONE);

    logAtAllLevels(std::move(t_logger));

    ASSERT_TRUE(t_stream.str().empty());
}


TEST(CSVIncrementalLogging, CSVStringChainedLogger_TargetFATAL_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamChainLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::FATAL);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult());
}


TEST(CSVIncrementalLogging, CSVStringChainedLogger_TargetERROR_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamChainLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::ERROR);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult() + errorResult());
}


TEST(CSVIncrementalLogging, CSVStringChainedLogger_TargetWARNING_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamChainLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::WARNING);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult() + errorResult() + warningResult());
}


TEST(CSVIncrementalLogging, CSVStringChainedLogger_TargetINFO_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamChainLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::INFO);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult() + errorResult() + warningResult() + infoResult());
}


TEST(CSVIncrementalLogging, CSVStringChainedLogger_TargetDEBUG_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamChainLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::DEBUG);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult() + errorResult() + warningResult() + infoResult() + debugResult());
}
