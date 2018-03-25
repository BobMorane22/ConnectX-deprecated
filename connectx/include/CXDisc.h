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
 * @file    CXDisc.h
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Interface for a Connect X GUI disc utility.
 *
 **************************************************************************************************/

#ifndef CXDISC_H_72172974_77FE_4634_97FA_FB68CB3954CB
#define CXDISC_H_72172974_77FE_4634_97FA_FB68CB3954CB

#include <cxgui/include/Disc.h>

namespace cxbase {class Disc;}

namespace cx
{

namespace ui
{

/**********************************************************************************************//**
 * @brief Abstract base class for Connect X discs.
 *
 * This class provides the minimum requirements needed to have a disc that is usable in
 * Connect X.
 *
 *************************************************************************************************/
class CXDisc : public cxgui::Disc
{

public:

    /******************************************************************************************//**
     * @brief Constructor with parameters.
     *
     * @param[in] The disc's fill color.
     * @param[in] The disc's background color.
     * @param[in] The disc's border color (opaque black by default).
     *
     *********************************************************************************************/
    CXDisc(const cxutil::Color& p_fillColor,
           const cxutil::Color& p_backgroundColor,
           const cxutil::Color& p_borderColor = cxutil::Color::black());


    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    virtual ~CXDisc() override;


    /******************************************************************************************//**
     * @brief Highlights the disc.
     *
     * Both the disc's fill region and its background are highlighted. Calling this method twice
     * is not dangerous: the disc will only be highlighted once on the first call.
     *
     * @see removeHighlighting
     *
     *********************************************************************************************/
    void highlight();


    /******************************************************************************************//**
     * @brief Removes highlighting from the disc.
     *
     * Both the the highlighting of the disc's fill region and its background are removed.
     * Calling this method twice is not dangerous: the disc will only have its highlighting
     * removed once on the first call.
     *
     * @see highlight
     *
     *********************************************************************************************/
    void removeHighlighting();


    /******************************************************************************************//**
     * @brief Visually hides the disc.
     *
     * Puts the disc in a state in which it can be visually considered absent. It is the
     * responsability of the implementer to define what an <em>absent disc</em> should look
     * like.
     *
     *********************************************************************************************/
    virtual void hide() = 0;


    /******************************************************************************************//**
     * @brief Updates the disc's visual representation.
     *
     * Updates the disc's visual representation according to a backend disc object holding
     * the disc's logic.
     *
     * @param[in] p_newBackEndDisc A backend disc.
     *
     * @note This method can be used to @a unhide hidden discs.
     *
     *********************************************************************************************/
    virtual void update(const cxbase::Disc& p_newBackEndDisc) = 0;

private:

    bool m_isHighlighted{false}; ///< Flag for the disc's highlighting status.

};

} // namespace ui

} // namespace cx

#endif // CXDISC_H_72172974_77FE_4634_97FA_FB68CB3954CB
