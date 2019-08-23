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
 * @file    IChainLogging.h
 * @author  Eric Poirier
 * @date    July 2019
 * @version 1.0
 *
 * Interface to implement logging as a chain of responsability.
 *
 **************************************************************************************************/

#ifndef ICHAINLOGGING_H_6EBF284E_68F3_4217_A3CB_C3665E9EA8D5
#define ICHAINLOGGING_H_6EBF284E_68F3_4217_A3CB_C3665E9EA8D5

#include <memory>

#include "ILogger.h"

namespace cxlog
{

/***********************************************************************************************//**
 * @brief Interface to implement logging as a chain of responsability.
 *
 * It adds the successor concept to a general logger.
 *
 **************************************************************************************************/
class IChainLogging
{

public:

    /*******************************************************************************************//**
     * @brief Set which logger (if any) will log the message after the current logger.
     *
     * @param p_sucessor The sucessor logger.
     *
     **********************************************************************************************/
    virtual void setSucessor(std::unique_ptr<ILogger>&& p_sucessor) = 0;


    /*******************************************************************************************//**
     * @brief Indicates wether the current logger has a sucessor.
     *
     * @return @c true if the current logger has a sucessor, @c false otherwise.
     *
     **********************************************************************************************/
    virtual bool hasSucessor() const = 0;

};

} // namespace cxlog

#endif // ICHAINLOGGING_H_6EBF284E_68F3_4217_A3CB_C3665E9EA8D5
