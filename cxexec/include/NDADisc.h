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
 * @file    NDADisc.h
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Interface for a Connect X GUI next disc area disc utility.
 *
 **************************************************************************************************/

#ifndef NDADISC_H_CB0208FC_FE9C_44BC_87CC_389C335CE6B7
#define NDADISC_H_CB0208FC_FE9C_44BC_87CC_389C335CE6B7

#include <cxbase/include/Disc.h>

#include "Chip.h"

namespace cx
{

namespace ui
{

/***********************************************************************************************//**
 * @brief Connect X disc for the next disc area.
 *
 * This is a special variant of the Connect X disc specialized to behave according to the
 * requirements of the next disc area. More specifically:
 *
 *     @li it has no background (i.e. transparent);
 *     @li when hidden, the disc's fill area and border become transparent also.
 *
 * in other words, when such a disc is considered hidden, it becomes completely invisible to the
 * user.
 *
 **************************************************************************************************/
class NDADisc : public Chip
{

public:

    /*******************************************************************************************//**
     * @brief Default constructor.
     *
     * Construct a disc for which the fill and background colors are transparent as well as the
     * border color.
     *
     **********************************************************************************************/
    NDADisc();


    /*******************************************************************************************//**
     * @brief Constructor with parameters.
     *
     * Constructs a disc visually representing the backend disc passed as an argument. The
     * background color for the disc is transparent.
     *
     * @param[in] p_backEndDisc A backend disc.
     *
     * @see cxbase::Disc
     *
     **********************************************************************************************/
    NDADisc(const cxbase::Disc& p_backEndDisc);


    /*******************************************************************************************//**
     * @brief Destructor.
     *
     **********************************************************************************************/
    virtual ~NDADisc() override;


    /*******************************************************************************************//**
     * @brief Visually hides the disc.
     *
     * Changes the disc current appearance to a transparent disc with a transparent background
     * and a transparent border (i.e. invisible).
     *
     **********************************************************************************************/
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
    void update(const cxbase::Disc& p_newBackEndDisc) override;


private:

    virtual void drawBorder(const Cairo::RefPtr<Cairo::Context>& p_context) const override;

    cxbase::Disc m_backEndDisc;   ///< The backend (from @c cxbase ) disc visually represented.
                                  ///< the current GUI disc.
};

} // namespace ui

} // namespace cx

#endif // NDADISC_H_CB0208FC_FE9C_44BC_87CC_389C335CE6B7
