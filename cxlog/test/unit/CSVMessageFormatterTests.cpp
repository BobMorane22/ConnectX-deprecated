#define GTEST_HAS_STD_TUPLE_ 1
#define GTEST_HAS_TR1_TUPLE  0

#include <gtest/gtest.h>

#include <cxlog/include/CSVMessageFormatter.h>

#include "CSVLoggerUtil.h"
#include "TimestampFormatterMock.h"

TEST(CSVMessageFormatter, FormatHeaders_ValidMessageFormatter_FormatsHeadersAccordingly)
{
    std::unique_ptr<TimestampFormatterMock> tsmpFormatter{new TimestampFormatterMock()};
    std::unique_ptr<cxlog::IMessageFormatter> formatter{new cxlog::CSVMessageFormatter{std::move(tsmpFormatter)}};

    const std::string result  {formatter->formatHeaders()};
    const std::string expected{headerLine()};

    ASSERT_EQ(result, expected);
}


TEST(CSVMessageFormatter, FormatMessage_ValidLineAsFatal_FormatsCSVMessageAccordingly)
{
    std::unique_ptr<TimestampFormatterMock> tsmpFormatter{new TimestampFormatterMock()};
    std::unique_ptr<cxlog::IMessageFormatter> formatter{new cxlog::CSVMessageFormatter{std::move(tsmpFormatter)}};

    const std::string result{formatter->formatMessage(cxlog::VerbosityLevel::FATAL,
                                                      _FILE_,
                                                      _FUNCTION_,
                                                      _LINE_,
                                                      generateLineToLog())};
    const std::string expected{fatalResult()};

    ASSERT_EQ(result, expected);
}


TEST(CSVMessageFormatter, FormatMessage_ValidLineAsError_FormatsCSVMessageAccordingly)
{
    std::unique_ptr<TimestampFormatterMock> tsmpFormatter{new TimestampFormatterMock()};
    std::unique_ptr<cxlog::IMessageFormatter> formatter{new cxlog::CSVMessageFormatter{std::move(tsmpFormatter)}};

    const std::string result{formatter->formatMessage(cxlog::VerbosityLevel::ERROR,
                                                      _FILE_,
                                                      _FUNCTION_,
                                                      _LINE_,
                                                      generateLineToLog())};
    const std::string expected{errorResult()};

    ASSERT_EQ(result, expected);
}


TEST(CSVMessageFormatter, FormatMessage_ValidLineAsWarning_FormatsCSVMessageAccordingly)
{
    std::unique_ptr<TimestampFormatterMock> tsmpFormatter{new TimestampFormatterMock()};
    std::unique_ptr<cxlog::IMessageFormatter> formatter{new cxlog::CSVMessageFormatter{std::move(tsmpFormatter)}};

    const std::string result{formatter->formatMessage(cxlog::VerbosityLevel::WARNING,
                                                      _FILE_,
                                                      _FUNCTION_,
                                                      _LINE_,
                                                      generateLineToLog())};
    const std::string expected{warningResult()};

    ASSERT_EQ(result, expected);
}


TEST(CSVMessageFormatter, FormatMessage_ValidLineAsInfo_FormatsCSVMessageAccordingly)
{
    std::unique_ptr<TimestampFormatterMock> tsmpFormatter{new TimestampFormatterMock()};
    std::unique_ptr<cxlog::IMessageFormatter> formatter{new cxlog::CSVMessageFormatter{std::move(tsmpFormatter)}};

    const std::string result{formatter->formatMessage(cxlog::VerbosityLevel::INFO,
                                                      _FILE_,
                                                      _FUNCTION_,
                                                      _LINE_,
                                                      generateLineToLog())};
    const std::string expected{infoResult()};

    ASSERT_EQ(result, expected);
}


TEST(CSVMessageFormatter, FormatMessage_ValidLineAsDebug_FormatsCSVMessageAccordingly)
{
    std::unique_ptr<TimestampFormatterMock> tsmpFormatter{new TimestampFormatterMock()};
    std::unique_ptr<cxlog::IMessageFormatter> formatter{new cxlog::CSVMessageFormatter{std::move(tsmpFormatter)}};

    const std::string result{formatter->formatMessage(cxlog::VerbosityLevel::DEBUG,
                                                      _FILE_,
                                                      _FUNCTION_,
                                                      _LINE_,
                                                      generateLineToLog())};
    const std::string expected{debugResult()};

    ASSERT_EQ(result, expected);
}