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
 * @file    main.cpp
 * @author  Eric Poirier
 * @date    April 2017
 * @version 0.1
 *
 * Connect 4 minimal example.
 *
 **************************************************************************************************/

#include <iostream>
#include <vector>

#include "Connect4Game.h" // Custom Game class

USING_NAMESPACE_STD
USING_NAMESPACE_CXBASE

int main()
{
	int IN_A_ROW {4};

	// Create discs:
	AsciiColorCode RED_COLOR_CODE      {'R'};
	AsciiColorCode YELLOW_COLOR_CODE   {'Y'};

	Color          RED                 {255, 0  , 0  , 255, RED_COLOR_CODE};
	Color          YELLOW              {255, 255, 0  , 255, YELLOW_COLOR_CODE};

	Disc           RED_DISC            {RED};
	Disc           YELLOW_DISC         {YELLOW};

	// Create players:
	string nameP1, nameP2;

	cout << "Enter the players' names:" << endl;

	cout << "First player: ";
	getline(cin, nameP1);

	cout << "Second player: ";
	getline(cin, nameP2);

	shared_ptr<Player> player1{new Player{nameP1, RED_DISC}};
	shared_ptr<Player> player2{new Player{nameP2, YELLOW_DISC}};

	// Create gameboard:
	shared_ptr<GameBoard> classicGameBoard{new GameBoard};

	// Create game:
    vector< shared_ptr<Player> >   players   {player1, player2};
	Connect4Game                   game      {players, classicGameBoard, IN_A_ROW};

	int chosenColumn {0};

	// Game loop:
	while(!game.isWon() && !game.isDraw())
	{
		cout << "Select column to play: ";
		cin >> chosenColumn;

		game.playTurn(chosenColumn);
        cout << game;

        game.nextTurn();
	}

	// Game ending:
	if(game.isWon())
	{
		Player winner {game.activePlayer()};

		// Active player is not the winner:
		if(*players[0] == game.activePlayer())
		{
			cout <<  *players[1] << " has won!" << endl;
		}
		else
		{
		    cout << *players[0] << " has won!" << endl;
		}
	}
	else
	{
		cout << "It's a tie!" << endl;
	}

	return 0;
}
