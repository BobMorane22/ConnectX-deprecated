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
 * @file    IncrementalLogger.h
 * @author  Eric Poirier
 * @date    July 2019
 * @version 1.0
 *
 * A simple incremental logger.
 *
 **************************************************************************************************/

#ifndef INCREMENTALLOGGER_H_8B296618_F3FB_4858_B8B3_845E261A3B9F
#define INCREMENTALLOGGER_H_8B296618_F3FB_4858_B8B3_845E261A3B9F


#include "IMessageFormatter.h"

#include "Logger.h"

namespace cxlog
{

/***********************************************************************************************//**
 * @brief A simple incremental logger.
 *
 * The logger is incremental in the sense that is has many successive logging verbosity level.
 * One can increase the logger verbosity incrementally if needed.
 *
 **************************************************************************************************/
class IncrementalLogger : public Logger
{

public:

    /*******************************************************************************************//**
     * Constructor.
     *
     * @param p_msgFormatter An address to a unique message formatter.
     * @param p_logTarget    An address to a unique log target.
     * @param p_addHeader    A flag indicatiing if the logger needs a header to be added on first
     *                       log event.
     *
     **********************************************************************************************/
    IncrementalLogger(std::unique_ptr<IMessageFormatter>&& p_msgFormatter,
                      std::unique_ptr<ILogTarget>&&        p_logTarget,
                      bool                                 p_addHeader = false);


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
    void log(const VerbosityLevel p_verbosityLevel,
             const std::string&   p_fileName,
             const std::string&   p_functionName,
             const size_t         p_lineNumber,
             const std::string&   p_message) override;

private:

    std::unique_ptr<IMessageFormatter> m_msgFormatter; ///< An address to the unique message formatter.
    std::unique_ptr<ILogTarget>        m_logTarget;    ///< An address to the unique log target.
};

} // namespace cxlog

#endif // INCREMENTALLOGGER_H_8B296618_F3FB_4858_B8B3_845E261A3B9F
