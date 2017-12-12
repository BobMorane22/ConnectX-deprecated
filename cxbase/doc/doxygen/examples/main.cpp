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

/***************************************************************************************************
 * @file    main.cpp
 * @author  Eric Poirier
 * @date    April 2017
 * @version 1.0
 *
 * Connect 4 minimal example.
 *
 **************************************************************************************************/


///! [Minimal Connect 4 example]

#include "Connect4Game.h" // Custom Game class

using namespace cxbase;


int main()
{
    const int IN_A_ROW{4};

    // Create players:
    std::string nameP1, nameP2;

    std::cout << "Enter the players' names:" << std::endl;

    std::cout << "First player: ";
    std::getline(std::cin, nameP1);

    std::cout << "Second player: ";
    std::getline(std::cin, nameP2);

    std::shared_ptr<Player> player1{std::make_shared<Player>(nameP1, Disc::redDisc())  };
    std::shared_ptr<Player> player2{std::make_shared<Player>(nameP2, Disc::blackDisc())};

    // Create gameboard:
    std::shared_ptr<GameBoard> classicGameBoard{std::make_shared<GameBoard>()};

    // Create game:
    std::vector<std::shared_ptr<Player>>   players   {player1, player2};
    Connect4Game                           game      {players, classicGameBoard, IN_A_ROW};

    int chosenColumn{0};
    bool isMoveCompleted{false};

    // Game loop:
    while(!game.isWon() && !game.isEarlyDraw() && !game.isDraw())
    {
        isMoveCompleted = false;

        // Make a move until successfull:
        while(!isMoveCompleted)
        {
            std::cout << "Select column to play: ";
            std::cin  >> chosenColumn;

            isMoveCompleted = game.makeMove(Column{chosenColumn});
        }

        // Show the board in ASCII:
        std::cout << game;
    }

    // Game ending:
    if(game.isWon())
    {
        Player winner{game.activePlayer()};

        // Active player is not the winner, the the player that comes
        // before him that won:
        if(*players[0] == game.activePlayer())
        {
            std::cout <<  *players[1] << " has won!" << std::endl;
        }
        else
        {
            std::cout << *players[0] << " has won!" << std::endl;
        }
    }
    else
    {
        std::cout << "It's a draw!" << std::endl;
    }

    return 0;
}

///! [Minimal Connect 4 example]

