#include <iostream>
#include <vector>
#include <cxbaseAPI.h>

USING_NAMESPACE_STD
USING_NAMESPACE_CXBASE

void clearScreen();

// Connect4Game class: needed to customize th game... 
class Connect4Game : public Game
{
public:
    // Regular Game class, plus a specialized stream operator for
    // my own needs (none defined in the Game class):
    Connect4Game(const vector< shared_ptr<Player> >& p_players,
				 const shared_ptr<GameBoard> p_gameboard,
				 int p_inARow):
		         Game(p_players, p_gameboard, p_inARow) {}

    // Stream operator specific for this particular game:
	friend ostream& operator<<(ostream& p_flux, const Connect4Game& p_game)
	{
        // In this case, only the board is printed:
        p_flux << *(p_game.m_gameboard) << endl;

		return p_flux;
	}
};

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
    vector< shared_ptr<Player> >   players   {player1, player2};
	Connect4Game                   game      {players, classicGameBoard, IN_A_ROW};

	int chosenColumn {0};
	
	// Game loop:
	while(!game.isWon() && !game.isDraw())
	{
		cout << "Select column to play: ";
		cin >> chosenColumn;
        clearScreen();

		game.playTurn(chosenColumn);
        cout << game;
		game.nextTurn();
	}
	
	return 0;
}


void clearScreen()
{
	for (int i{0}; i < 50; ++i)
	{
		cout << endl;
	}
}
