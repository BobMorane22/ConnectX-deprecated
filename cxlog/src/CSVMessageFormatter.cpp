#include <cxinv/include/assertion.h>

#include "../include/CSVMessageFormatter.h"

namespace
{

const std::string NEWLINE{"\n"};
const std::string SEPARATOR{", "};

const std::string NOTHING{{}};

} // unamed namespace


std::string cxlog::CSVMessageFormatter::formatHeaders() const
{
    return std::string{"Verbosity level"} + SEPARATOR +
           std::string{"Message"} + NEWLINE;
}

std::string cxlog::CSVMessageFormatter::formatMessage(const VerbosityLevel p_verbosityLevel, const std::string& p_message) const
{
    switch(p_verbosityLevel)
    {
        case cxlog::VerbosityLevel::NONE:
        {
            //ASSERT_FALSE_MSG("Do this check in higher level functions.");
            return {};
        }
        case cxlog::VerbosityLevel::FATAL:
        {
            return std::string{"FATAL"} + SEPARATOR + p_message + NEWLINE;
        }
        case cxlog::VerbosityLevel::ERROR:
        {
            return std::string{"ERROR"} + SEPARATOR + p_message + NEWLINE;
        }
        case cxlog::VerbosityLevel::WARNING:
        {
            return std::string{"WARNING"} + SEPARATOR + p_message + NEWLINE;
        }
        case cxlog::VerbosityLevel::INFO:
        {
            return std::string{"INFO"} + SEPARATOR + p_message + NEWLINE;
        }
        case cxlog::VerbosityLevel::DEBUG:
        {
            return std::string{"DEBUG"} + SEPARATOR + p_message + NEWLINE;
        }
    }
}
