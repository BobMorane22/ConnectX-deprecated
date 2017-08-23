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
 * @file    ReturnCode.cpp
 * @author  Eric Poirier
 * @date    August 2017
 * @version 1.0
 *
 * Implementation for a return code utility.
 *
 **************************************************************************************************/

#include <cassert>
#include <iostream>

#include "Assertion.h"
#include "ReturnCode.h"

using namespace cxutil;

const std::string ReturnCode::NO_MESSAGE {""};

typedef ReturnCode::Code Code;

ReturnCode::ReturnCode(Code p_code, const std::string p_message): m_code{p_code}, m_message{p_message}
{
}

ReturnCode::~ReturnCode()
{
    // The return code should have been tested at least once:
    CX_ASSERT(m_tested);
}

bool ReturnCode::isOk()
{
    m_tested = true;

    return m_code == Code::OK;
}

bool ReturnCode::isWarning()
{
    m_tested = true;

    return m_code == Code::WARNING;
}

bool ReturnCode::isError()
{
    m_tested = true;

    return m_code == Code::ERROR;
}

bool ReturnCode::isCancelled()
{
    m_tested = true;

    return m_code == Code::CANCEL;
}

bool ReturnCode::holdsMessage() const
{
    return !m_message.empty();
}

bool ReturnCode::isTested() const
{
    return m_tested;
}

std::string ReturnCode::message() const
{
    return m_message;
}

Code ReturnCode::code() const
{
    return m_code;
}
