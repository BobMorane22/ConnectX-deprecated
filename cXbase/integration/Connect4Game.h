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
