/***************************************************************************************************
 *
 * Copyright (C) 2019 Connect X team
 *
 * This file is part of Connect X.
 *
 * Connect X is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Connect X is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Connect X.  If not, see <http://www.gnu.org/licenses/>.
 *
 **************************************************************************************************/

/***********************************************************************************************//**
 * @file    CSVMessageFormatter.cpp
 * @author  Eric Poirier
 * @date    July 2019
 * @version 1.0
 *
 * Comma Separated Values (CSV) message formatter.
 *
 **************************************************************************************************/

#include <cxinv/include/assertion.h>

#include "../include/CSVMessageFormatter.h"

namespace
{

const std::string NEWLINE  {"\n"}; ///< CSV end of line character.
const std::string SEPARATOR{", "}; ///< CSV separator character.


/***********************************************************************************************//**
 * @brief Format parameters to CSV.
 *
 * Creates a string of every parameters, in order, and separated by commas.
 *
 * @param p_timestamp      The message timestamp.
 * @param p_verbosityLevel The message verbosity level.
 * @param p_fileName       The source file in which the logging occured.
 * @param p_functionName   The function name in which the logging occured.
 * @param p_lineNumber     The line number in the source file where the logging occured.
 * @param p_message        The message to log.
 *
 * @return The formatted message.
 *
 **************************************************************************************************/
std::string makeCSV(const std::string& p_timestamp,
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
            ASSERT_ERROR_MSG("Do this check in higher level functions.");
            return {};
        }
        case cxlog::VerbosityLevel::FATAL:
        {
            return makeCSV(m_timeFormatter->formatTimestamp(), "FATAL", p_fileName, p_functionName, p_lineNumber, p_message);
        }
        case cxlog::VerbosityLevel::ERROR:
        {
            return makeCSV(m_timeFormatter->formatTimestamp(), "ERROR", p_fileName, p_functionName, p_lineNumber, p_message);
        }
        case cxlog::VerbosityLevel::WARNING:
        {
            return makeCSV(m_timeFormatter->formatTimestamp(), "WARNING", p_fileName, p_functionName, p_lineNumber, p_message);
        }
        case cxlog::VerbosityLevel::INFO:
        {
            return makeCSV(m_timeFormatter->formatTimestamp(), "INFO", p_fileName, p_functionName, p_lineNumber, p_message);
        }
        case cxlog::VerbosityLevel::DEBUG:
        {
            return makeCSV(m_timeFormatter->formatTimestamp(), "DEBUG", p_fileName, p_functionName, p_lineNumber, p_message);
        }
    }

    ASSERT_ERROR_MSG("Unknown verbosity level");
    return {};
}
