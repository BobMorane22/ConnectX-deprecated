/***********************************************************************************************//**
 * @file    Player.h
 * @author  Eric Poirier
 * @date    November 2016
 * @version 0.1
 *
 * Interface for a Player utility.
 *
 **************************************************************************************************/

#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <sstream>

#include "Disc.h"


BEGIN_CXBASE_NAMESPACE

/***********************************************************************************************//**
 * @class Player
 *
 * A utility to manage Players of a Disc related game.
 *
 * A Player object is a Name and Disc pair.
 *
 * @invariant A Player's Disc cannot have @c NO_COLOR and the space (@c ' ') character as their
 * Color attributes. In other words, a Player cannot possess a @c NO_COLOR Disc, which is seen
 * as no disc.
 *
 * @see Name
 * @see Disc
 *
 **************************************************************************************************/
class Player : IEnforceContract
{

public:

///@{ @name Object construction and destruction
    Player()            = delete;
    virtual ~Player()   = default;


    /*******************************************************************************************//**
     * Constructor with parameters.
     *
     * Joins a Name and a Disc to construct a Player.
     *
     * @param[in] p_name The new Player's Name.
     * @param[in] p_disc The new Player's Disc.
     * @post @c p_name is now the Player's Name.
     * @post @c p_disc is now the Player's Disc.
     *
     **********************************************************************************************/
    Player(const Name& p_name, const Disc& p_disc);
///@}


///@{ @name Data access
    /*******************************************************************************************//**
     * Name accessor.
     *
     * @return The Player's Name.
     *
     **********************************************************************************************/
    Name name() const {return m_name;}


    /*******************************************************************************************//**
     * Disc accessor.
     *
     * @return The Player's Disc.
     *
     **********************************************************************************************/
    Disc disc() const {return m_disc;}
///@}


///@{ @name Operators
    /*******************************************************************************************//**
     * Equal operator.
     *
     * Two Players are considered equal <em> if and only if </em> both their Name and Disc are
     * equal respectively.
     *
     * @param[in] p_player The Player to compare with.
     *
     **********************************************************************************************/
    virtual bool operator==(const Player& p_player) const;


    /*******************************************************************************************//**
     * Not equal operator.
     *
     * Two Players are considered @b NOT equal <em> if and ony if </em> their Name or their Disc
     * (or both) are @b NOT equal respectively.
     *
     * @param[in] p_player The Player to compare with.
     *
     **********************************************************************************************/
    virtual bool operator!=(const Player& p_player) const;


    /*******************************************************************************************//**
     * Stream-insertion operator.
     *
     * Simply inserts the Player's Name into the stream.
     *
     * @param[in] p_flux    The stream in which to insert.
     * @param[in] p_player  The Player to insert into the stream.
     *
     * @todo Add an indirection such that subclasses can use polymorphic behaviour with
     * <tt> operator<< </tt>. See <a href="http://stackoverflow.com/questions/4571611/
     * making-operator-virtual"> this </a> for a nice hot-to example.
     *
     **********************************************************************************************/
    friend std::ostream& operator<<(std::ostream& p_flux, const Player& p_player);
///@}

private:

    void checkInvariant() const;

    const Disc NO_DISC{Color{Name{"No color"}, AsciiColorCode{' '}}};

    Name m_name;    ///< The Player's Name.
    Disc m_disc;    ///< The Player's Disc.

};

END_CXBASE_NAMESPACE

#endif /* PLAYER_H_ */
