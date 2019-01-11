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
 * @file    Chip.h
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Interface for a Connect X GUI chip utility.
 *
 **************************************************************************************************/

#ifndef CHIP_H_72172974_77FE_4634_97FA_FB68CB3954CB
#define CHIP_H_72172974_77FE_4634_97FA_FB68CB3954CB


#include <cxgui/include/SimpleAndClosedGeometricShape.h>

namespace cxbase {class Disc;}

namespace cx
{

namespace ui
{

/**********************************************************************************************//**
 * @brief Abstract base class for Connect X chip.
 *
 * This class provides the minimum requirements needed to have a chip that is usable in
 * a Connect X game.
 *
 *************************************************************************************************/
class Chip : public cxgui::SimpleAndClosedGeometricShape
{

public:

    /******************************************************************************************//**
     * @brief Constructor with parameters.
     *
     * @param[in] The chip's fill color.
     * @param[in] The chip's background color.
     * @param[in] The chip's border color (opaque black by default).
     *
     *********************************************************************************************/
    Chip(const cxutil::Color& p_fillColor,
         const cxutil::Color& p_backgroundColor,
         const cxutil::Color& p_borderColor = cxutil::Color::black());


    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    virtual ~Chip() override;


    /******************************************************************************************//**
     * @brief Highlights the chip.
     *
     * Both the chip's fill region and its background are highlighted. Calling this method twice
     * is not dangerous: the chip will only be highlighted once on the first call.
     *
     * @see removeHighlighting
     *
     *********************************************************************************************/
    void highlight();


    /******************************************************************************************//**
     * @brief Removes highlighting from the chip.
     *
     * Both the the highlighting of the chip's fill region and its background are removed.
     * Calling this method twice is not dangerous: the chip will only have its highlighting
     * removed once on the first call.
     *
     * @see highlight
     *
     *********************************************************************************************/
    void removeHighlighting();


    /******************************************************************************************//**
     * @brief Visually hides the chip.
     *
     * Puts the chip in a state in which it can be visually considered absent. It is the
     * responsability of the implementer to define what an <em>absent chip</em> should look
     * like.
     *
     *********************************************************************************************/
    virtual void hide() = 0;


    /******************************************************************************************//**
     * @brief Updates the chip's visual representation.
     *
     * Updates the chip's visual representation according to a @c cxbase::Disc object holding
     * the chip's logic.
     *
     * @param[in] p_newBackEndDisc A a @c cxbase::Disc object.
     *
     * @note This method can be used to @a unhide hidden chips.
     *
     *********************************************************************************************/
    virtual void update(const cxbase::Disc& p_newBackEndDisc) = 0;

private:

    bool m_isHighlighted{false}; ///< Flag for the chip's highlighting status.

};

} // namespace ui

} // namespace cx

#endif // CHIP_H_72172974_77FE_4634_97FA_FB68CB3954CB
