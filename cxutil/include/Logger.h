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
 * @file    Logger.h
 * @author  Eric Poirier
 * @date    August 2017
 * @version 1.0
 *
 * Interface for a logger utility.
 *
 **************************************************************************************************/

#ifndef LOGGER_H_96F6CF7D_75F8_450A_A335_86BEEE723B83
#define LOGGER_H_96F6CF7D_75F8_450A_A335_86BEEE723B83

#include <fstream>
#include <string>

namespace cxutil
{

/***********************************************************************************************//**
 * @class Logger
 *
 * A logger utility to document program executions.
 *
 * Once a Logger object has been instanciated, you can log messages to document the program's
 * execution. All messages are coupled with one of the three Severity levels: INFO, WARNING and
 * ERROR. If you are in degub mode (i.e. if NDEBUG is not defined) a fourth Severity level is
 * available: DEBUG.
 *
 * If you log something in release mode (NDEGUG set), all entries will be redirected only to the 
 * log file. In the other hand, if you log something in debug mode, all entries go in the log file 
 * as well as in the standard output (usually a terminal). To log something, use the @c logInfo(), 
 * @c logWarning(), @c logError() and @c logDebug() 
 * methods. For example:
 *
 * @verbatim
 *   Logger logger("execution.log")
 *
 *   logger.logInfo("Logger activated...");
 *
 *   // Some execution...
 *
 *   if( aPtr == nullptr)
 *   {
 *       logger.logWarning("aPtr points to nothing!");
 *
 *       // Handle problem...
 *   }
 *
 *   //...
 *
 * @endverbatim
 *
 * Will produce an output like:
 * 
 * @verbatim
 *   0	3.203	2017/8/12	17:27:4	INFO    :	Logger activated...
 *   1	11.476	2017/8/12	17:27:4	WARNING :	aPtr points to nothing!
 * @endverbatim
 *
 * The columns represent, from left to right:
 *   - the entry number;
 *   - the program's execution time up to the related entry (in milliseconds);
 *   - the entry date;
 *   - the entry hour;
 *   - the entry severity;
 *   - the entry message.
 *
 * Every column is separated by a tab (@c '\t') character, which makes is possible for most
 * spreadsheet software (i.e. LibreOffice) to import the log file for surther analysis.
 *
 * @note A Logger object is not thread-safe.
 *
 * @invariant The line numbers are always positive
 * @invariant The file stream is opened from the beginning of the Logger object's life until
 *            its destruction.
 *
 * @see Severity
 *
 **************************************************************************************************/
class Logger final
{
public:

    Logger() = delete;

    /*******************************************************************************************//**
     * Constructor with parameter.
     *
     * It is through the constructor that a filename can be specified into which log all entries.
     *
     * @param[in]   p_logFile   The file name (with path) in which to output the log entries.
     * 
     * @pre     p_logFile must be a valid file name.
     *
     **********************************************************************************************/
    Logger(const std::string& p_logFile);


    /*******************************************************************************************//**
     * Destructor.
     *
     **********************************************************************************************/
    ~Logger();


    /*******************************************************************************************//**
     * Log a message as an information.
     *
     * Logs p_message as an INFO severity message to the log file (and to the standard output if 
     * in debug mode).
     *
     * @param[in]   p_message   The message to log.
     *
     * @pre  p_message is a non empty string.
     * @post The message is logged as an INFO severity message.
     *
     **********************************************************************************************/
    void logInfo(const std::string& p_message);


    /*******************************************************************************************//**
     * Log a message as a warning.
     *
     * Logs p_message as a WARNING severity message to the log file (and to the standard output if 
     * in debug mode).
     *
     * @param[in]   p_message   The message to log.
     *
     * @pre     p_message is a non empty string.
     * @post    The message is logged as a WARNING severity message.
     *
     **********************************************************************************************/
    void logWarning(const std::string& p_message);


    /*******************************************************************************************//**
     * Log a message as an error.
     *
     * Log a message as an ERROR severity message to the log file (and to the standard output if
     * in debug mode).
     *
     * @param[in]   p_message   The message to log.
     * 
     * @pre     p_message is a non-empty string.
     * @post    The message is logged as an ERROR severity message.
     *
     **********************************************************************************************/
    void logError(const std::string& p_message);


    #if !defined(NDEBUG)
    /*******************************************************************************************//**
     * Log a message as a debug message (debug mode only).
     *
     * Log a message as a DEBUG severity message to the log file and to the standard input. This
     * facility is only available is in debug mode.
     *
     * @param[in]   p_message   The message to log.
     * 
     * @pre     p_message is a non-empty string.
     * @post    The message is logged as a DEBUG severity message.
     *
     **********************************************************************************************/
    void logDebug(const std::string& p_message);
    #endif

private:

    /*******************************************************************************************//**
     * @enum The three (or four in debug) different severity levels for logging. These level appear 
     *       next to the logged message in the log output for more clarity and enhanced sorting.
     *
     **********************************************************************************************/
    enum class Severity : int
    {  
        INFO,       ///< Information about the execution (the executable remains stable).
        WARNING,    ///< Warning about some action that may endanger the execution (executable may become unstable).
        ERROR       ///< Execution error (executable enters an unstable state).
        
        #if !defined(NDEBUG)
        ,DEBUG      ///< Information that may be useful for debugging porposes; not useful to the end user.
        #endif
    };

    /*******************************************************************************************//**
     * Log a message.
     *
     * Log a message to the wanted Severity level.
     *
     * @param[in] p_message     The message to log.
     * @param[in] p_severity    The Severity level for the message.
     *
     * @pre     p_message is a non-empty string.
     * @post    The message is logged to the wanted severity level.
     *
     **********************************************************************************************/
    void log(const std::string& p_message, Severity p_severity);


    /*******************************************************************************************//**
     * Calculates the time elapsed (in ms) since the beginning of the application execution.
     *
     * @return The execution time since the beginning of execution of the application.
     *
     **********************************************************************************************/
    double execTime() const;


    /*******************************************************************************************//**
     * Formats a string containing the time and the date of the logged message.
     *
     * @return A string containing the time and the date of the logged message.
     *
     **********************************************************************************************/
    std::string timeAndDate() const;


    /*******************************************************************************************//**
     * Formats all the necessary information to be loggued with the message in the log file.
     *
     * @return A string containing all the necessary information to be loggued with the message 
     *         in the log file.
     *
     **********************************************************************************************/
    std::string formatLogHeader() const;


    /*******************************************************************************************//**
     * Formats a line printable to the log file directly.
     *
     * @param[in] p_message     The message to log.
     * @param[in] p_severity    The message severity level.
     * 
     * @pre     p_message is a non-empty string.
     * @post    The line is adequatly formatted for logging.
     *
     * @return  The formatted log line.
     *
     **********************************************************************************************/
    std::string formatLogLine(const std::string& p_message, Severity p_severity) const;

    char          m_separator   {'\t'};     ///< The colum separator character.
    unsigned int  m_lineNumber  {0   };     ///< The entry line number.
    std::string   m_logFile;                ///< The full log file name (with path).
    std::ofstream m_fileStream;             ///< The file stream.
};

inline void Logger::logInfo(const std::string& p_message)
{
    log(p_message, Logger::Severity::INFO);
}

inline void Logger::logWarning(const std::string& p_message)
{
    log(p_message, Logger::Severity::WARNING);
}

inline void Logger::logError(const std::string& p_message)
{
    log(p_message, Logger::Severity::ERROR);
}

#if !defined(NDEBUG)
inline void Logger::logDebug(const std::string& p_message)
{
    log(p_message, Logger::Severity::DEBUG);
}
#endif

} // namespace cxutil

#endif // LOGGER_H_96F6CF7D_75F8_450A_A335_86BEEE723B83
