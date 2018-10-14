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
 * @file    Credits.h
 * @author  Eric Poirier
 * @date    September 2018
 * @version 1.0
 *
 * Interface for the Connect X 'credits' dialog.
 *
 **************************************************************************************************/

#ifndef CREDITS_H_79F6EAC0_0B34_4F83_A151_D3D5212E6E08
#define CREDITS_H_79F6EAC0_0B34_4F83_A151_D3D5212E6E08

#include <cxgui/include/Credits.h>

namespace cx
{

namespace ui
{

/***********************************************************************************************//**
 * @class Credits
 *
 * @brief Credits dialog for the Connect X project.
 *
 * This class is mainly a wrapper around the cxgui::dlg::Credits class. The only difference is
 * that this class uses a fixed path to a file to generate the contributor lists.
 *
 **************************************************************************************************/
class Credits final : public cxgui::dlg::Credits
{

public:

///@{ @name Object construction and destruction

    /*******************************************************************************************//**
     * @brief Default constructor.
     *
     **********************************************************************************************/
    Credits();


    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     ***********************************************************************************************/
    ~Credits();

///@}


private:

///@{ @name Window setup

    virtual void setWindowIcon()    override;
    virtual void registerLayouts()  override;
    virtual void configureLayouts() override;

///@}

    virtual void configureSignalHandlers() {}

};

} // namespace ui

} // namespace cx

#endif // CREDITS_H_79F6EAC0_0B34_4F83_A151_D3D5212E6E08
