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
 * @file    Logging.h
 * @author  Eric Poirier
 * @date    July 2019
 * @version 1.0
 *
 * A singleton logging manager.
 *
 **************************************************************************************************/

#ifndef LOGGING_H_CDD92FCE_99C9_4514_A5EA_4437C7224018
#define LOGGING_H_CDD92FCE_99C9_4514_A5EA_4437C7224018

#include "LoggingManager.h"
#include "IncrementalLogger.h"


/***********************************************************************************************//**
 * @brief Log a @c FATAL entry.
 *
 * All of the neccessary context is automatically added by this MACRO (i.e: file name, line number,
 * etc.)
 *
 * @param p_message The message to log.
 *
 **************************************************************************************************/
#define LOG_FATAL(p_message) cxlog::theLoggerManager().log(cxlog::VerbosityLevel::FATAL,   __FILE__, __LINE__, __FUNCTION__, p_message)


/***********************************************************************************************//**
 * @brief Log a @c ERROR entry.
 *
 * All of the neccessary context is automatically added by this MACRO (i.e: file name, line number,
 * etc.)
 *
 * @param p_message The message to log.
 *
 **************************************************************************************************/
#define LOG_ERROR(p_message) cxlog::theLoggerManager().log(cxlog::VerbosityLevel::ERROR,   __FILE__, __LINE__, __FUNCTION__, p_message)

/***********************************************************************************************//**
 * @brief Log a @c WARNING entry.
 *
 * All of the neccessary context is automatically added by this MACRO (i.e: file name, line number,
 * etc.)
 *
 * @param p_message The message to log.
 *
 **************************************************************************************************/
#define LOG_WARNING(p_message) cxlog::theLoggerManager().log(cxlog::VerbosityLevel::WARNING, __FILE__, __LINE__, __FUNCTION__, p_message)


/***********************************************************************************************//**
 * @brief Log a @c INFO entry.
 *
 * All of the neccessary context is automatically added by this MACRO (i.e: file name, line number,
 * etc.)
 *
 * @param p_message The message to log.
 *
 **************************************************************************************************/
#define LOG_INFO(p_message) cxlog::theLoggerManager().log(cxlog::VerbosityLevel::INFO,    __FILE__, __LINE__, __FUNCTION__, p_message)


/***********************************************************************************************//**
 * @brief Log a @c DEBUG entry.
 *
 * All of the neccessary context is automatically added by this MACRO (i.e: file name, line number,
 * etc.)
 *
 * @param p_message The message to log.
 *
 **************************************************************************************************/
#define LOG_DEBUG(p_message) cxlog::theLoggerManager().log(cxlog::VerbosityLevel::DEBUG,   __FILE__, __LINE__, __FUNCTION__, p_message)


namespace cxlog
{

/***********************************************************************************************//**
 * @brief A singleton logging manager.
 *
 * Helps logging from everywhere through a single instance interface using various logging
 * macros to reduce verbosity.
 *
 **************************************************************************************************/
class Logging final
{

public:

    /*******************************************************************************************//**
     * @brief Single instance access.
     *
     **********************************************************************************************/
    static Logging& theLoggerManager();


    /*******************************************************************************************//**
     * @brief Logs an entry.
     *
     * Logs an entry using the information injected as parameters. The entry is logged for
     * every registered logger.
     *
     * @param p_verbosityLevel The message verbosity level.
     * @param p_fileName       The source file in which the logging occured.
     * @param p_functionName   The function name in which the logging occured.
     * @param p_lineNumber     The line number in the source file where the logging occured.
     * @param p_message        The message to log.
     *
     **********************************************************************************************/
    void log(const VerbosityLevel p_verbosityLevel,
             const std::string&   p_fileName,
             const std::string&   p_functionName,
             const size_t         p_lineNumber,
             const std::string&   p_message);


private:

    // Deleted:
    Logging(Logging const&)         = delete;
    void operator=(Logging const&)  = delete;
    Logging(Logging&&)              = delete;
    void operator=(Logging&&)       = delete;

    Logging();

    std::unique_ptr<ILoggingManager> m_loggers; ///< A list of all loggers to log to.

};

} // namespace cxlog

#endif // LOGGING_H_CDD92FCE_99C9_4514_A5EA_4437C7224018
