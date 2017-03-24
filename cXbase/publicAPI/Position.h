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
 * @file    Position.h
 * @author  Eric Poirier
 * @date    October 2016
 * @version 0.1
 *
 * Interface for a two dimensional position tool (using rows and columns).
 *
 **************************************************************************************************/

#ifndef POSITION_H_
#define POSITION_H_

#include "../source/Coordinate.h"

BEGIN_CXBASE_NAMESPACE

/***********************************************************************************************//**
 * class Row
 *
 * An integer coordinate used as a row.
 *
 **************************************************************************************************/
class Row : public Coordinate <int>
{

public:

///@{ @name Object construction and destruction.
    Row()           = delete;
    virtual ~Row()  = default;


    /*******************************************************************************************//**
     * Constructor with parameter.
     *
     * @param[in] p_row An integer containing the wanted Row value.
     *
     **********************************************************************************************/
    Row(int p_row): Coordinate<int>{p_row} {};
///@}

};


/***********************************************************************************************//**
 * class Column
 *
 * An integer coordinate used as a column.
 *
 **************************************************************************************************/
class Column : public Coordinate<int>
{

public:

///@{ @name Object construction and destruction.
    Column()            = delete;
    virtual ~Column()   = default;


    /*******************************************************************************************//**
     * Constructor with parameter.
     *
     * @param[in] p_column An integer containing the wanted Column value.
     *
     **********************************************************************************************/
    Column(int p_column): Coordinate<int>{p_column} {};
///@}

};


/***********************************************************************************************//**
 * class Position
 *
 * A Position is nothing but an (Row, Column) tuple with a special meaning attached to it: that
 * of a 2D location on a grid. To that effect, the tuple mentionned above
 *
 * @see Row
 * @see Column
 *
 **************************************************************************************************/
class Position
{

public:

///@{ @name Object construction and destruction
    Position()  = delete;
    ~Position() = default;

    /*******************************************************************************************//**
     * Constructor with parameters.
     *
     * Constructs a Position object from a Row and a Column object respectively.
     *
     * @param[in] p_row     The Row Coordinate of the Position.
     * @param[in] p_column  The Column Coordinate of the Position.
     * @post @c p_row is the Position's Row element.
     * @post @c p_column is the Position's Column value.
     *
     **********************************************************************************************/
    Position(const Row& p_row, const Column& p_column);
///@}

///@{ @name access
    /*******************************************************************************************//**
     * Row accessor.
     *
     * @return The Position's Row element.
     *
     **********************************************************************************************/
    Row     row() const         { return m_row; }


    /*******************************************************************************************//**
     * Column accessor.
     *
     * @return The Position's Column element.
     *
     **********************************************************************************************/
    Column  column() const      { return m_column; }


    /*******************************************************************************************//**
     * Row value accessor.
     *
     * @return The Position's Row element integer value.
     *
     **********************************************************************************************/
    int     rowValue() const    { return m_row.value(); }


    /*******************************************************************************************//**
     * Column value accessor.
     *
     * @return The Position's Column element integer value.
     *
     **********************************************************************************************/
    int     columnValue() const { return m_column.value(); }
///@}

///@{ @name Operators
    /*******************************************************************************************//**
     * Equal-to operator.
     *
     * Two Positions are considered equal <em> if and only if </em> both the Row and the Column
     * values are equal to those of the compared Position.
     *
     * @param[in] p_position The Position to compare with.
     *
     **********************************************************************************************/
    bool operator==(const Position& p_position) const { return (m_row == p_position.m_row) && (m_column == p_position.m_column); }


    /*******************************************************************************************//**
     * Not-equal-to operator.
     *
     * Two Positions are considered @b NOT equal <em> if and only if </em> the Row or the Column
     * (or both) value is not equal to that of the compared Position.
     *
     * @param[in] p_position The Position to compare with.
     *
     **********************************************************************************************/
    bool operator!=(const Position& p_position) const { return !(*this == p_position); };
///@}

private:

    Row     m_row;      // The Row of the Position (vertical entity).
    Column  m_column;   // The Column of the Position (horizontal entity).

};

END_CXBASE_NAMESPACE

#endif /* POSITION_H_ */
