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
 * @file    ILogger.h
 * @author  Eric Poirier
 * @date    July 2019
 * @version 1.0
 *
 * Interface to implement loggers.
 *
 **************************************************************************************************/

#ifndef ILOGGER_H_C23F1D75_6DA4_499E_A502_FBEC85D074DB
#define ILOGGER_H_C23F1D75_6DA4_499E_A502_FBEC85D074DB

#include <string>

#include "ILogTarget.h"
#include "VerbosityLevel.h"


namespace cxlog
{

/***********************************************************************************************//**
 * @brief Interface to implement loggers.
 *
 **************************************************************************************************/
class ILogger
{

public:

    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    virtual ~ILogger() = default;


    /*******************************************************************************************//**
     * @brief Logs an entry.
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
    virtual void log(const VerbosityLevel p_verbosityLevel,
                     const std::string&   p_fileName,
                     const std::string&   p_functionName,
                     const size_t         p_lineNumber,
                     const std::string&   p_message) = 0;


    /*******************************************************************************************//**
     * @brief Mutates the logger general verbosity level.
     *
     * @param p_verbosityLevel The new logger-wide verbosity level.
     *
     *********************************************************************************************/
    virtual void setVerbosityLevel(const VerbosityLevel p_verbosityLevel) = 0;


    /*******************************************************************************************//**
     * @brief Indicates the logger general verbosity level.
     *
     * @return The verbosity level.
     *
     *********************************************************************************************/
    virtual VerbosityLevel verbosityLevel() const = 0;

};

} // namespace cxlog

#endif // ILOGGER_H_C23F1D75_6DA4_499E_A502_FBEC85D074DB
