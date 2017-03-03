/***********************************************************************************************//**
 * @file    Name.cpp
 * @author  Eric Poirier
 * @date    November 2016
 * @version 0.1
 *
 * Implementation for a name utility.
 *
 **************************************************************************************************/

#include "../publicAPI/Name.h"

USING_NAMESPACE_STD
USING_NAMESPACE_CXBASE

Name::Name(const std::string& p_name): m_name{p_name}
{
    PRECONDITION(!p_name.empty());

    INVARIANTS();
}

void Name::checkInvariant() const
{
    INVARIANT(!m_name.empty());
}
