#define GTEST_HAS_STD_TUPLE_ 1
#define GTEST_HAS_TR1_TUPLE  0

#include <gtest/gtest.h>

#include <cxlog/include/StringStreamLogTarget.h>

#include "CSVLoggerUtil.h"

TEST(LogTarget, StringStreamTarget_ValidMessageAndValidStream_LineLogged)
{
    std::ostringstream stream;
    std::unique_ptr<cxlog::ILogTarget> target{new cxlog::StringStreamLogTarget{stream}};

    target->log(generateLineToLog());

    const std::string result  {stream.str()};
    const std::string expected{generateLineToLog()};

    ASSERT_EQ(result, expected);
}