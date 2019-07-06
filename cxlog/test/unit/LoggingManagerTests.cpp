#define GTEST_HAS_STD_TUPLE_ 1
#define GTEST_HAS_TR1_TUPLE  0

#include <gtest/gtest.h>

#include <cxlog/include/LoggingManager.h>

#include "CSVLoggerUtil.h"


TEST(LoggingManager, Log_ValidLogger_ManagerCanLog)
{
    // Create manager:
    std::ostringstream t_stream;
    std::unique_ptr<cxlog::ILoggingManager> t_mgr{new cxlog::LoggingManager(std::move(createCVSStringStreamLogger(t_stream)))};

    t_mgr->setVerbosityLevel(cxlog::VerbosityLevel::DEBUG);
    t_mgr->log(cxlog::VerbosityLevel::DEBUG, _FILE_, _FUNCTION_, _LINE_, generateLineToLog());

    const std::string expected{debugResult()};
    const std::string result{t_stream.str()};

    ASSERT_EQ(result, expected);
}


TEST(LoggingManager, Log_ValidLoggerList_ManagerCanLog)
{
    // Create manager:
    std::ostringstream t_stream1, t_stream2;

    cxlog::LoggerUptrList loggers;
    loggers.push_back(std::move(createCVSStringStreamLogger(t_stream1)));
    loggers.push_back(std::move(createCVSStringStreamLogger(t_stream2)));

    std::unique_ptr<cxlog::ILoggingManager> t_mgr{new cxlog::LoggingManager(std::move(loggers))};

    t_mgr->setVerbosityLevel(cxlog::VerbosityLevel::DEBUG);
    t_mgr->log(cxlog::VerbosityLevel::DEBUG, _FILE_, _FUNCTION_, _LINE_, generateLineToLog());

    const std::string expected{debugResult()};
    const std::string result1{t_stream1.str()};
    const std::string result2{t_stream2.str()};

    ASSERT_EQ(result1, expected);
    ASSERT_EQ(result2, expected);
}