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

/***************************************************************************************************
 * @file    Connect4Game.h
 * @author  Eric Poirier
 * @date    April 2017
 * @version 1.0
 *
 * Interface and implementation for a customized Connect 4 Game object. This object is a 
 * specialization of the cxbase::Game object.
 *
 **************************************************************************************************/

#ifndef CONNECT4GAME_H_
#define CONNECT4GAME_H_

#include <iostream>

#include <cxbaseAPI.h>

///! [Custom Connect 4 class]

// Connect4Game class: needed to customize th game... 
class Connect4Game : public cxbase::Game
{
public:
    // Regular Game class, plus a specialized stream operator for
    // my own needs (none defined in the Game class):
    Connect4Game(const std::vector< std::shared_ptr<cxbase::Player> >& p_players,
                 const std::shared_ptr<cxbase::GameBoard> p_gameboard,
                 int p_inARow):
                 Game(p_players, p_gameboard, p_inARow) {}

    // Stream operator to make the Game printable:
	friend std::ostream& operator<<(std::ostream& p_stream, const Connect4Game& p_game);

};

///! [Custom Connect 4 class]

///! [Personalized ASCII printing]

std::ostream& operator<<(std::ostream& p_stream, const Connect4Game& p_game)
{
    using namespace cxbase;

    std::shared_ptr<GameBoard> gameboard = p_game.m_gameboard;

    int rowSubscript     {gameboard->nbRows() - 1};
    int columnSubscript  {0};

    for(int row{gameboard->nbRows() - 1}; row >= 0; --row)
    {
        p_stream << rowSubscript << " ";

        if(rowSubscript < 10)
            p_stream << " ";

        p_stream << "|";

        for(int col{0}; col < gameboard->nbColumns(); ++col)
        {
            if((*gameboard)(Position{Row{row}, Column{col}}) == Disc::redDisc())
            {
                p_stream << " R ";
            }
            else if((*gameboard)(Position{Row{row}, Column{col}}) == Disc::blackDisc())
            {
                p_stream << " B ";
            }
            else
            {
                p_stream << "   ";
            }

            p_stream << "|";

            ++columnSubscript;
        }

        p_stream << std::endl;

        columnSubscript = 0;
        --rowSubscript;
    }

    p_stream << "  ";

    for(int columnSubscript{0}; columnSubscript < gameboard->nbColumns(); ++columnSubscript)
    {
        p_stream << "   " << columnSubscript;
    }

    p_stream << std::endl;

    return p_stream;
}

///! [Personalized ASCII printing]

#endif /* CONNECT4GAME_H */
