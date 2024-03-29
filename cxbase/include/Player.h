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
 * @file    Player.h
 * @author  Eric Poirier
 * @date    November 2016
 * @version 0.1
 *
 * Interface for a Player utility.
 *
 **************************************************************************************************/

#ifndef PLAYER_H_9B43C099_9307_4C05_956D_3F12FE5F1A1F
#define PLAYER_H_9B43C099_9307_4C05_956D_3F12FE5F1A1F

#include <string>

#include <cxutil/include/ContractException.h>
#include <cxutil/include/Name.h>

#include "Disc.h"


namespace cxbase
{

/***********************************************************************************************//**
 * @class Player
 *
 * @brief A utility to manage Players of a Disc related game.
 *
 * A Player object is a Name and Disc pair.
 *
 * @invariant A Player's Disc cannot have @c TRANSPARENT and the space (@c ' ') character as their
 *            Color attributes. In other words, a Player cannot possess a @c TRANSPARENT Disc, 
 *            which is seen as no disc.
 *
 * @see cxutil::Name
 * @see Disc
 *
 **************************************************************************************************/
class Player
{

public:

///@{ @name Object construction and destruction

    /*******************************************************************************************//**
     * Default destructor.
     *
     **********************************************************************************************/
    virtual ~Player();


    /*******************************************************************************************//**
     * Constructor with parameters.
     *
     * Joins a Name and a Disc to construct a Player.
     *
     * @param[in] p_name The new Player's Name.
     * @param[in] p_disc The new Player's Disc.
     * @post @c p_name is the new Player's Name.
     * @post @c p_disc is the new Player's Disc.
     *
     **********************************************************************************************/
    Player(const cxutil::Name& p_name, const Disc& p_disc);

///@}


///@{ @name Data access

    /*******************************************************************************************//**
     * Name accessor.
     *
     * @return The Player's Name.
     *
     **********************************************************************************************/
    cxutil::Name name() const {return m_name;}


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
     * Equal-to operator.
     *
     * Two Players are considered equal <em> if and only if </em> both their Name and Disc are
     * equal respectively.
     *
     * @param[in] p_player The Player to compare with.
     *
     **********************************************************************************************/
    virtual bool operator==(const Player& p_player) const;


    /*******************************************************************************************//**
     * Not-equal-to operator.
     *
     * Two Players are considered @b NOT equal <em> if and ony if </em> their Name or their Disc
     * (or both) are @b NOT equal respectively.
     *
     * @param[in] p_player The Player to compare with.
     *
     **********************************************************************************************/
    virtual bool operator!=(const Player& p_player) const;

///@}

protected:

    void checkInvariant() const;

private:

    cxutil::Name m_name;    ///< The Player's Name.
    Disc         m_disc;    ///< The Player's Disc.

};

} // namespace cxbase

#endif /* PLAYER_H_9B43C099_9307_4C05_956D_3F12FE5F1A1F */
