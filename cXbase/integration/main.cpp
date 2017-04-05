#include <iostream>
#include <cxbaseAPI.h>

USING_NAMESPACE_STD
USING_NAMESPACE_CXBASE

int main()
{
	int IN_A_ROW {4};
	
	// Create discs:
	AsciiColorCode RED_COLOR_CODE      {'R'};
	AsciiColorCode YELLOW_COLOR_CODE   {'Y'};

	Name           RED_NAME            {"Red"};
	Name           YELLOW_NAME         {"Yellow"};

	Color          RED                 {RED_NAME, RED_COLOR_CODE};
	Color          YELLOW              {YELLOW_NAME, YELLOW_COLOR_CODE};

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
	vector<shared_ptr<Player>> players  {player1, player2};
	Game game                           {players, classicGameBoard, IN_A_ROW};

	// Game loop:
	
	
	return 0;
}
