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
 * @file    LoggingManager.cpp
 * @author  Eric Poirier
 * @date    July 2019
 * @version 1.0
 *
 * A logging manager.
 *
 **************************************************************************************************/

#include <algorithm>

#include <cxinv/include/assertion.h>

#include "../include/LoggingManager.h"


cxlog::LoggingManager::LoggingManager(LoggerUptrList&& p_loggers)
{
    PRECONDITION(!p_loggers.empty());
    PRECONDITION(std::none_of(p_loggers.cbegin(),
                              p_loggers.cend(),
                             [](const std::unique_ptr<cxlog::ILogger>& p_logger)
                             {
                                 return p_logger == nullptr;
                             }));

    for(auto& logger : p_loggers)
    {
        m_loggers.push_back(std::move(logger));
    }

    POSTCONDITION(!m_loggers.empty());
    POSTCONDITION(std::none_of(m_loggers.cbegin(),
                               m_loggers.cend(),
                               [](const std::unique_ptr<cxlog::ILogger>& p_logger)
                               {
                                   return p_logger == nullptr;
                               }));
}


cxlog::LoggingManager::LoggingManager(std::unique_ptr<ILogger>&& p_logger)
{
    PRECONDITION(p_logger != nullptr);

    m_loggers.push_back(std::move(p_logger));

    POSTCONDITION(m_loggers.back() != nullptr);
    POSTCONDITION(!m_loggers.empty());
}


cxlog::LoggingManager::~LoggingManager() = default;


void cxlog::LoggingManager::setVerbosityLevel(const cxlog::VerbosityLevel p_level)
{
    for(auto& logger : m_loggers)
    {
        logger->setVerbosityLevel(p_level);
    }

    m_level = p_level;
}


cxlog::VerbosityLevel cxlog::LoggingManager::verbosityLevel() const
{
    return m_level;
}


void cxlog::LoggingManager::log(const cxlog::VerbosityLevel p_verbosityLevel,
                                const std::string&          p_fileName,
                                const std::string&          p_functionName,
                                const size_t                p_lineNumber,
                                const std::string&          p_message)
{
    for(auto& logger : m_loggers)
    {
        if(logger)
        {
            logger->log(p_verbosityLevel,
                        p_fileName,
                        p_functionName,
                        p_lineNumber,
                        p_message);
        }
    }
}
