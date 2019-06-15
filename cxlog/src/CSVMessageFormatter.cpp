#include <cxinv/include/assertion.h>

#include "../include/CSVMessageFormatter.h"

namespace
{

const std::string NEWLINE  {"\n"};
const std::string SEPARATOR{", "};

std::string makeLine(const std::string& p_timestamp,
                     const std::string& p_verbosityLevel,
                     const std::string& p_fileName,
                     const std::string& p_functionName,
                     const size_t       p_lineNumber,
                     const std::string& p_message)
{
    return p_timestamp                  + SEPARATOR +
           p_verbosityLevel             + SEPARATOR +
           p_fileName                   + SEPARATOR +
           p_functionName               + SEPARATOR +
           std::to_string(p_lineNumber) + SEPARATOR +
           p_message                    + NEWLINE;
}

} // unamed namespace


cxlog::CSVMessageFormatter::CSVMessageFormatter(std::unique_ptr<cxlog::ITimestampFormatter>&& p_timeFormatter)
 : m_timeFormatter{std::move(p_timeFormatter)}
{
    PRECONDITION(m_timeFormatter != nullptr);
}

cxlog::CSVMessageFormatter::~CSVMessageFormatter() = default;

std::string cxlog::CSVMessageFormatter::formatHeaders() const
{
    return "Timestamp"       + SEPARATOR +
           "File name"       + SEPARATOR +
           "Function name"   + SEPARATOR +
           "Line number"     + SEPARATOR +
           "Verbosity level" + SEPARATOR +
           "Message"         + NEWLINE;
}

std::string cxlog::CSVMessageFormatter::formatMessage(const VerbosityLevel p_verbosityLevel,
                                                      const std::string&   p_fileName,
                                                      const std::string&   p_functionName,
                                                      const size_t         p_lineNumber,
                                                      const std::string&   p_message) const
{
    switch(p_verbosityLevel)
    {
        case cxlog::VerbosityLevel::NONE:
        {
            ASSERT_FALSE_MSG("Do this check in higher level functions.");
            return {};
        }
        case cxlog::VerbosityLevel::FATAL:
        {
            return makeLine(m_timeFormatter->formatTimestamp(), "FATAL", p_fileName, p_functionName, p_lineNumber, p_message);
        }
        case cxlog::VerbosityLevel::ERROR:
        {
            return makeLine(m_timeFormatter->formatTimestamp(), "ERROR", p_fileName, p_functionName, p_lineNumber, p_message);
        }
        case cxlog::VerbosityLevel::WARNING:
        {
            return makeLine(m_timeFormatter->formatTimestamp(), "WARNING", p_fileName, p_functionName, p_lineNumber, p_message);
        }
        case cxlog::VerbosityLevel::INFO:
        {
            return makeLine(m_timeFormatter->formatTimestamp(), "INFO", p_fileName, p_functionName, p_lineNumber, p_message);
        }
        case cxlog::VerbosityLevel::DEBUG:
        {
            return makeLine(m_timeFormatter->formatTimestamp(), "DEBUG", p_fileName, p_functionName, p_lineNumber, p_message);
        }
    }

    ASSERT_FALSE_MSG("Unknown verbosity level");
    return {};
}
