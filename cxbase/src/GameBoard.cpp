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
 * @file    GameBoard.cpp
 * @author  Eric Poirier
 * @date    December 2016
 * @version 1.0
 *
 * Implementation for a GameBoard utility.
 *
 **************************************************************************************************/


#include "../include/GameBoard.h"


using namespace cxbase;


GameBoard::~GameBoard() = default;


GameBoard::GameBoard(): m_grid(NB_ROWS_MIN, std::vector<std::shared_ptr<Disc>>(NB_COLUMNS_MIN, std::make_shared<Disc>())),
                        m_nbRows{NB_ROWS_MIN}, m_nbColumns{NB_COLUMNS_MIN}

{
    int nbPositionsGameBoard{0};

    for(auto& row : m_grid)
    {
        for(auto& disc : row)
        {
            if(*disc == Disc::noDisc())
            {
                ++nbPositionsGameBoard;
            }
        }
    }

    ASSERTION(nbPositionsGameBoard >= NB_ROWS_MIN * NB_COLUMNS_MIN);
    ASSERTION(nbPositionsGameBoard <= NB_ROWS_MAX * NB_COLUMNS_MAX);
    ASSERTION(nbPositionsGameBoard ==  m_nbRows * m_nbColumns);

    INVARIANTS();
}


GameBoard::GameBoard(int p_nbRows, int p_nbColumns): m_grid(p_nbRows, std::vector<std::shared_ptr<Disc>>(p_nbColumns, std::make_shared<Disc>())),
                                                     m_nbRows{p_nbRows}, m_nbColumns{p_nbColumns}

{
    PRECONDITION(p_nbRows >= NB_ROWS_MIN);
    PRECONDITION(p_nbRows <= NB_ROWS_MAX);

    PRECONDITION(p_nbColumns >= NB_COLUMNS_MIN);
    PRECONDITION(p_nbColumns <= NB_COLUMNS_MAX);

    int nbPositionsGameBoard{0};

    for(auto& row : m_grid)
    {
        for(auto& disc : row)
        {
            if(*disc == Disc::noDisc())
            {
                ++nbPositionsGameBoard;
            }
        }
    }

    ASSERTION(nbPositionsGameBoard >= NB_ROWS_MIN * NB_COLUMNS_MIN);
    ASSERTION(nbPositionsGameBoard <= NB_ROWS_MAX * NB_COLUMNS_MAX);
    ASSERTION(nbPositionsGameBoard == m_nbRows * m_nbColumns);

    INVARIANTS();
}


int GameBoard::nbColumns() const
{
    return m_nbColumns;
}


int GameBoard::nbRows() const
{
    return m_nbRows;
}


int GameBoard::nbPositions() const
{
    return m_nbColumns * m_nbRows;
}


Position GameBoard::placeDisc(const Column& p_column, const Disc& p_disc)
{
    PRECONDITION(p_disc != Disc::noDisc());
    PRECONDITION(p_column >= Column{0});
    PRECONDITION(p_column < Column{m_nbColumns});

    int        rowSubscript{0};

    for(auto row = m_grid.begin(); row != m_grid.end(); ++row)
    {
        std::shared_ptr<Disc> currentDiscAddress{std::make_shared<Disc>((*this)(Position{Row{rowSubscript}, p_column}))};
        
        if(*currentDiscAddress == Disc::noDisc())
        {
            m_grid[rowSubscript][p_column.value()] = std::make_shared<Disc>(p_disc);
            break;
        }

        ++rowSubscript;
    }

    INVARIANTS();

    return Position{Row{rowSubscript}, p_column};
}


bool GameBoard::isColumnFull(const Column& p_column) const
{
    PRECONDITION(p_column >= Column{0});
    PRECONDITION(p_column < Column{NB_COLUMNS_MAX});

    bool isPlayable{false};
    int  rowSubscript{m_nbRows - 1};

    for(auto row = m_grid.rbegin(); row != m_grid.rend(); ++row)
    {
        std::shared_ptr<Disc> currentDiscAddress{std::make_shared<Disc>((*this)(Position{Row{rowSubscript}, p_column}))};
    
        if(*currentDiscAddress == Disc::noDisc())
        {
            isPlayable = true;
            break;
        }

        --rowSubscript;
    }

    return !isPlayable;
}


bool GameBoard::operator==(const GameBoard& p_gameBoard) const
{
    PRECONDITION(m_nbColumns == p_gameBoard.m_nbColumns);
    PRECONDITION(m_nbRows == p_gameBoard.m_nbRows);

    bool isEqual{true};
    int rowSubscript{0};
    int columnSubscript{0};

    for(auto& row : m_grid)
    {
        for(auto& disc :row)
        {
            if(*disc != p_gameBoard(Position{Row{rowSubscript}, Column{columnSubscript}}))
            {
                isEqual = false;
                break;
            }

            ++columnSubscript;
        }

        if(isEqual)
        {
            break;
        }

        columnSubscript = 0;
        ++rowSubscript;
    }

    return isEqual;
}


bool GameBoard::operator!=(const GameBoard &p_gameBoard) const
{
    PRECONDITION(m_nbColumns == p_gameBoard.m_nbColumns);
    PRECONDITION(m_nbRows == p_gameBoard.m_nbRows);

    return !(*this == p_gameBoard);
}


Disc GameBoard::operator()(const Position& p_position) const
{
    PRECONDITION(p_position.row()    >= Row{0}   );
    PRECONDITION(p_position.column() >= Column{0});

    PRECONDITION(p_position.row()    < Row{m_nbRows}      );
    PRECONDITION(p_position.column() < Column{m_nbColumns});

    return *m_grid[p_position.rowValue()][p_position.columnValue()];
}


void GameBoard::checkInvariant() const
{
    INVARIANT(m_nbRows >= NB_ROWS_MIN);
    INVARIANT(m_nbRows < NB_ROWS_MAX + 1);

    INVARIANT(m_nbColumns >= NB_COLUMNS_MIN);
    INVARIANT(m_nbColumns < NB_COLUMNS_MAX + 1);
}

