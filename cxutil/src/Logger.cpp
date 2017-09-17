/***************************************************************************************************
 *
 * Copyright (C) 2017 Connect X team
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
 * @file    Logger.cpp
 * @author  Eric Poirier
 * @date    August 2017
 * @version 1.0
 *
 * Implementation for a logger utility.
 *
 **************************************************************************************************/

#include <iostream>
#include <sstream>

#include "Assertion.h"
#include "Date.h"
#include "Logger.h"
#include "Time.h"


using namespace cxutil;

Logger::Logger(std::ostream* p_outStream) : m_outStream{p_outStream}
{
    PRECONDITION(p_outStream->good());

#if !defined(NDEBUG)
    CX_ASSERT_MSG(m_outStream != &std::cout, "std::cout is already set as a secondary stream in degub mode.")
#endif

    INVARIANTS();
}

Logger::~Logger()
{
}

void Logger::log(const std::string& p_message, Severity p_severity)
{
    PRECONDITION(!p_message.empty());

    (*m_outStream) << formatLogLine(p_message, p_severity) << std::endl;
    
    #if !defined(NDEBUG)
    std::cout << formatLogLine(p_message, p_severity) << std::endl;
    #endif
    
    m_lineNumber++;
    
    INVARIANTS();
}

double Logger::execTime() const
{
    double timeInMs = (static_cast<double>(clock()) / CLOCKS_PER_SEC) * 1000;
    
    return timeInMs;
}

std::string Logger::timeAndDate() const
{
    Date currentDate;
    Time currentTime;

    std::ostringstream date;
    std::ostringstream time;


    date << currentDate;
    time << currentTime;

    return date.str() + m_separator + time.str();
}

std::string Logger::formatLogHeader() const
{
    std::ostringstream timeExec;
    timeExec << execTime();
    
    std::ostringstream lineNumber;
    lineNumber << m_lineNumber;

    INVARIANTS();

    return lineNumber.str() + m_separator + 
           timeExec.str()   + m_separator + 
           timeAndDate();
}

std::string Logger::formatLogLine(const std::string& p_message, Logger::Severity p_severity) const
{
    PRECONDITION(!p_message.empty());

    std::string logLine;
    
    switch(p_severity)
    {
        case Severity::INFO:
        {
            logLine = formatLogHeader() + m_separator + "INFO    :" + m_separator + p_message;
            break;
        }
        case Severity::WARNING:
        {
            logLine = formatLogHeader() + m_separator + "WARNING :" + m_separator + p_message;
            break;
        }
        case Severity::ERROR:
        {
            logLine = formatLogHeader() + m_separator + "ERROR   :" + m_separator + p_message;
            break;
        }
        #if !defined(NDEBUG)
        case Severity::DEBUG:
        {
            logLine = formatLogHeader() + m_separator + "DEBUG   :" + m_separator + p_message;
            break;
        }
        #endif
        default:
        {
            assert(false && "Impossible severity value...");
            break;
        }
    }

    INVARIANTS();

    return logLine;
}

void Logger::checkInvariant() const
{
    INVARIANT(m_lineNumber > 0);
    INVARIANT(m_outStream->good());
}
