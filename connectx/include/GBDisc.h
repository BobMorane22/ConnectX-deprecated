/***************************************************************************************************
 *
 * Copyright (C) 2018 Connect X team
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
 * @file    GBDisc.h
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Interface for a Connect X GUI gameboard disc utility.
 *
 **************************************************************************************************/

#ifndef GBDISC_H_A420217C_733E_4157_916A_8AAE9E1F028C
#define GBDISC_H_A420217C_733E_4157_916A_8AAE9E1F028C

#include <cxbase/include/Disc.h>

#include "CXDisc.h"

namespace cx
{

namespace ui
{

/***********************************************************************************************//**
 * @brief Connect X disc for the game board area.
 *
 * This is a special variant of the a Connect X disc specialized to behave according to the
 * requirements of the Connect X game board area. More specifically:
 *
 *     @li it has the classic Connect X blue background;
 *     @li when hidden, the disc's fill area becomes black.
 *
 **************************************************************************************************/
class GBDisc : public CXDisc
{

public:

    /*******************************************************************************************//**
     * @brief Default constructor.
     *
     * Constructs a opaque black disc with the classic Connect X blue background.
     *
     **********************************************************************************************/
    GBDisc();


    /*******************************************************************************************//**
     * @brief Constructor with parameters.
     *
     * Constructs a disc visually representing the backend disc passed as an argument. The
     * background color for the disc is the classic Connect X blue.
     *
     * @param[in] p_backEndDisc A backend disc.
     *
     * @see cxbase::Disc
     *
     **********************************************************************************************/
    GBDisc(const cxbase::Disc& p_backEndDisc);


    /*******************************************************************************************//**
     * @brief Destructor.
     *
     **********************************************************************************************/
    virtual ~GBDisc() override;


    /******************************************************************************************//**
     * @brief Visually hides the disc.
     *
     * Changes the disc current appearance to an opaque disc with the classic Connect X blue as
     * background.
     *
     *********************************************************************************************/
    virtual void hide() override;


    /*******************************************************************************************//**
     * @brief Updates the disc's visual representation.
     *
     * Updates the disc's visual representation according to a backend disc object holding
     * the disc's logic.
     *
     * @param[in] p_newBackEndDisc A backend disc.
     *
     **********************************************************************************************/
    virtual void update(const cxbase::Disc& p_newBackEndDisc) override;


private:

    cxbase::Disc m_backEndDisc;   ///< The backend (from @c cxbase ) disc visually represented.
                                  ///< the current GUI disc.
                                  ///<
};

} // namespace ui

} // namespace cx

#endif // GBDISC_H_A420217C_733E_4157_916A_8AAE9E1F028C
