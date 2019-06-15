#define GTEST_HAS_STD_TUPLE_ 1
#define GTEST_HAS_TR1_TUPLE  0

#include <gtest/gtest.h>

#include <cxlog/include/CSVMessageFormatter.h>
#include <cxlog/include/IncrementalLogger.h>
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

TEST(CSVIncrementalLogger, CVSStringLogger_TargetNONE_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::NONE);

    logAtAllLevels(std::move(t_logger));

    ASSERT_TRUE(t_stream.str().empty());
}


TEST(CSVIncrementalLogger, CVSStringLogger_TargetFATAL_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::FATAL);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult());
}


TEST(CSVIncrementalLogger, CVSStringLogger_TargetERROR_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::ERROR);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult() + errorResult());
}


TEST(CSVIncrementalLogger, CVSStringLogger_TargetWARNING_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::WARNING);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult() + errorResult() + warningResult());
}


TEST(CSVIncrementalLogger, CVSStringLogger_TargetINFO_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::INFO);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult() + errorResult() + warningResult() + infoResult());
}


TEST(CSVIncrementalLogger, CVSStringLogger_TargetDEBUG_VerbosityLevelRespected)
{
    std::ostringstream t_stream;
    auto t_logger{createCVSStringStreamLogger(t_stream)};

    t_logger->setVerbosityLevel(cxlog::VerbosityLevel::DEBUG);

    logAtAllLevels(std::move(t_logger));

    const std::string result{t_stream.str()};

    ASSERT_EQ(result, fatalResult() + errorResult() + warningResult() + infoResult() + debugResult());
}
