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
 *
 * @file    Logger.cpp
 * @author  Eric Poirier
 * @date    August 2017
 * @version 0.1
 *
 * Implementation for a logger utility.
 *
 **************************************************************************************************/

#include <cassert>
#include <iostream>
#include <sstream>

#include "Logger.h"


using namespace cxutil;

Logger::Logger(const std::string& p_logFile) : m_logFile{p_logFile}
{
    m_fileStream.open(m_logFile, std::fstream::out);
    assert(m_fileStream.is_open());
}

Logger::~Logger()
{
    m_fileStream.close();
}

void Logger::log(const std::string& p_message, Severity p_severity)
{
    m_fileStream << formatLogLine(p_message, p_severity) << std::endl;
    
    #if !defined(NDEBUG)
    std::cout << formatLogLine(p_message, p_severity) << std::endl;
    #endif
    
    m_lineNumber++;
}

double Logger::execTime() const
{
    double timeInMs = (static_cast<double>(clock()) / CLOCKS_PER_SEC) * 1000;
    
    return timeInMs;
}

std::string Logger::timeAndDate() const
{
	time_t rawTime {time(nullptr)};
	struct tm* timeInfo {localtime(&rawTime)};

    // Get the current date:
	int year  = timeInfo->tm_year + 1900;
	int month = timeInfo->tm_mon + 1;
	int day   = timeInfo->tm_mday;
	
	std::ostringstream date;
	date << year << '/' << month << '/' << day;

    // Get the time:
    int hours   = timeInfo->tm_hour;
	int minutes = timeInfo->tm_min;
	int seconds = timeInfo->tm_sec;
	
    std::ostringstream time;
	time << hours << ":" << minutes << ":" << seconds;

    return date.str() + m_separator + time.str();
}

std::string Logger::formatLogHeader() const
{
    std::ostringstream timeExec;
    timeExec << execTime();
    
    std::ostringstream lineNumber;
    lineNumber << m_lineNumber;
    
    return lineNumber.str() + m_separator + 
           timeExec.str()   + m_separator + 
           timeAndDate();
}

std::string Logger::formatLogLine(const std::string& p_message, Logger::Severity p_severity) const
{
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

    return logLine;
}
