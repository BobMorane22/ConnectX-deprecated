/***************************************************************************************************
 * 
 * Copyright (C) 2016 Connect X team
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
 * @file    ContractException.cpp
 * @author  ULaval
 * @author  Eric Poirier (translation)
 * @date    January 2014
 * @version 1.0
 *
 * Implementation for the <a href="https://en.wikipedia.org/wiki/Design_by_contract">
 * design-by-contract </a> exceptions classes and MACROs.
 *
 **************************************************************************************************/

#include "ContractException.h"

#include <sstream>


std::string ContractException::getTextException() const
 {
     std::ostringstream os;

     os << "Message : " << what()       << std::endl;
     os << "File    : " << m_file       << std::endl;
     os << "Line    : " << m_line       << std::endl;
     os << "Test    : " << m_expression << std::endl;

     return os.str();

 }
