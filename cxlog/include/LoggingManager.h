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
 * @file    LoggingManager.h
 * @author  Eric Poirier
 * @date    July 2019
 * @version 1.0
 *
 * A logging manager.
 *
 **************************************************************************************************/

#ifndef LOGGINGMANAGER_H_09744F1B_6148_45D0_8C0C_F7927B92039F
#define LOGGINGMANAGER_H_09744F1B_6148_45D0_8C0C_F7927B92039F


#include <string>
#include <memory>
#include <vector>

#include "ILogger.h"
#include "ILoggingManager.h"


namespace cxlog
{

/***********************************************************************************************//**
 * @typedef A list of addresses of unique instances of loggers.
 *
 **************************************************************************************************/
using LoggerUptrList = std::vector<std::unique_ptr<ILogger>>;


/***********************************************************************************************//**
 * @brief A logging manager.
 *
 * A concrete and generic manager.
 *
 **************************************************************************************************/
class LoggingManager : public ILoggingManager
{

public:

    /*******************************************************************************************//**
     * @brief Multiple loggers management constructor.
     *
     * @param p_loggers A list of addresses to unique logger instances.
     *
     * @pre All addresses must be valid.
     *
     **********************************************************************************************/
    LoggingManager(LoggerUptrList&& p_loggers);


    /*******************************************************************************************//**
     * @brief Single logger management constructor.
     *
     * @param An address to a unique logger instance.
     *
     * @pre The address must be valid.
     *
     **********************************************************************************************/
    LoggingManager(std::unique_ptr< ILogger >&& p_logger);


    /*******************************************************************************************//**
     * @brief Destructor.
     *
     **********************************************************************************************/
    ~LoggingManager() override;


    /*******************************************************************************************//**
     * @brief Global verbosity level mutator.
     *
     * @param The new verbosity level.
     *
     **********************************************************************************************/
    void setVerbosityLevel(const cxlog::VerbosityLevel p_level) override;


    /*******************************************************************************************//**
     * @brief Global verbosity level accessor.
     *
     * @return The current verbosity level.
     *
     **********************************************************************************************/
    VerbosityLevel verbosityLevel() const override;


    /*******************************************************************************************//**
     * @brief Logs an entry for all managed loggers.
     *
     * Logs an entry using the information injected as parameters.
     *
     * @param p_verbosityLevel The message verbosity level.
     * @param p_fileName       The source file in which the logging occured.
     * @param p_functionName   The function name in which the logging occured.
     * @param p_lineNumber     The line number in the source file where the logging occured.
     * @param p_message        The message to log.
     *
     **********************************************************************************************/
    void log( const VerbosityLevel p_verbosityLevel,
              const std::string&   p_fileName,
              const std::string&   p_functionName,
              const size_t         p_lineNumber,
              const std::string&   p_message ) override;

private:

    LoggerUptrList m_loggers;                     ///< The logger list.
    VerbosityLevel m_level{VerbosityLevel::NONE}; ///< The global verbosity level.
};

} // namespace cxlog

#endif // LOGGINGMANAGER_H_09744F1B_6148_45D0_8C0C_F7927B92039F
