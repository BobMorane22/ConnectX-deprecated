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
 * @file    Logging.cpp
 * @author  Eric Poirier
 * @date    July 2019
 * @version 1.0
 *
 * A singleton logging manager.
 *
 **************************************************************************************************/

#include <cxinv/include/assertion.h>

#include "../include/Logging.h"


namespace
{

/***********************************************************************************************//**
 * @brief Creates a Comma Separated Value (CSV) logger that outputs to a file.
 *
 * @return The address of the newly created logger.
 *
 **************************************************************************************************/
std::unique_ptr<cxlog::ILogger> createCSVFileLogger()
{
    ASSERT_ERROR_MSG("Not yet implemented.");

    return nullptr;
}


/***********************************************************************************************//**
 * @brief Creates a Comma Separated Value (CSV) logger that outputs to the standard output.
 *
 * @return The address of the newly created logger.
 *
 **************************************************************************************************/
std::unique_ptr<cxlog::ILogger> createCSVStdoutLogger()
{
    ASSERT_ERROR_MSG("Not yet implemented.");

    return nullptr;
}

} // namespace


/***********************************************************************************************//**
 * @brief Constructor.
 *
 **************************************************************************************************/
cxlog::Logging::Logging()
 : m_loggers{nullptr}
{
    // Create loggers:
    LoggerUptrList loggers;
    loggers.push_back(std::move(createCSVFileLogger()));
    loggers.push_back(std::move(createCSVStdoutLogger()));

    // Register them with the manager:
    m_loggers.reset(new LoggingManager{std::move(loggers)});
}


cxlog::Logging& cxlog::Logging::theLoggerManager()
{
    static Logging INSTANCE;

    return INSTANCE;
}


void cxlog::Logging::log(const cxlog::VerbosityLevel p_verbosityLevel,
                         const std::string&          p_fileName,
                         const std::string&          p_functionName,
                         const size_t                p_lineNumber,
                         const std::string&          p_message)
{
    if(m_loggers)
    {
        m_loggers->log(p_verbosityLevel, p_fileName, p_functionName, p_lineNumber, p_message);

        return;
    }

    ASSERT_ERROR();
}
