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
