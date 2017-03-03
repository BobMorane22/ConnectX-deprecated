/***********************************************************************************************//**
 * @file    Player.cpp
 * @author  Eric Poirier
 * @date    November 2016
 * @version 0.1
 *
 * Implementation for a Player utility.
 *
 **************************************************************************************************/

#include "../publicAPI/Player.h"

USING_NAMESPACE_STD
USING_NAMESPACE_CXBASE


Player::Player(const Name& p_name, const Disc& p_disc): m_name{p_name}, m_disc{p_disc}
{
    POSTCONDITION(m_name == p_name);
    POSTCONDITION(m_disc == p_disc);

    INVARIANTS();
}

bool Player::operator==(const Player& p_player) const
{
    bool areEqual{false};

    if(m_name == p_player.name() && m_disc == p_player.disc())
    {
        areEqual = true;
    }

    return areEqual;
}

bool Player::operator!=(const Player& p_player) const
{
    return !(*this == p_player);
}

BEGIN_CXBASE_NAMESPACE

ostream& operator<<(ostream& p_flux, const Player& p_player)
{
    p_flux << p_player.name().toString();

    return p_flux;
}

END_CXBASE_NAMESPACE

void Player::checkInvariant() const
{
    INVARIANT(m_disc != NO_DISC);
}
