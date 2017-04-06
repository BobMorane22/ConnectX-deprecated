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
 * @file    Connect4Game.h
 * @author  Eric Poirier
 * @date    April 2017
 * @version 0.1
 *
 * Interface and implementation for a customized Connect 4 Game object. This object is a 
 * specialization of the cXbase::Game object.
 *
 **************************************************************************************************/

#ifndef CONNECT4GAME_H_
#define CONNECT4GAME_H_

#include <iostream>
#include <cxbaseAPI.h>

// Connect4Game class: needed to customize th game... 
class Connect4Game : public cXbase::Game
{
public:
    // Regular Game class, plus a specialized stream operator for
    // my own needs (none defined in the Game class):
    Connect4Game(const std::vector< std::shared_ptr<cXbase::Player> >& p_players,
			     const std::shared_ptr<cXbase::GameBoard> p_gameboard,
				 int p_inARow):
		         Game(p_players, p_gameboard, p_inARow) {}

    // Stream operator specific for this particular game:
	friend std::ostream& operator<<(std::ostream& p_flux, const Connect4Game& p_game);

};

std::ostream& operator<<(std::ostream& p_flux, const Connect4Game& p_game)
{
    // In this case, only the board is printed:
    p_flux << *(p_game.m_gameboard) << std::endl;
	
	return p_flux;
}

#endif /* CONNECT4GAME_H */_