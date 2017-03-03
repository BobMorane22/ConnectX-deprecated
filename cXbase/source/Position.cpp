/***********************************************************************************************//**
 * @file    Position.cpp
 * @author  Eric Poirier
 * @date    October 2016
 * @version 0.1
 *
 * Implementation for a two dimensional position tool (using rows and columns).
 *
 **************************************************************************************************/

#include "../publicAPI/Position.h"

USING_NAMESPACE_CXBASE


Position::Position(const Row& p_row, const Column& p_column): m_row{p_row}, m_column{p_column}
{
    POSTCONDITION(m_row == p_row);
    POSTCONDITION(m_column == p_column);
}
