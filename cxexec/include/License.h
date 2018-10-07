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
 * @file    License.h
 * @author  Eric Poirier
 * @date    August 2018
 * @version 1.0
 *
 * Interface for the Connect X 'license' dialog.
 *
 **************************************************************************************************/

#ifndef LICENSE_H_D3FE2F1F_9845_4EB2_A3FE_34FFBE60E565
#define LICENSE_H_D3FE2F1F_9845_4EB2_A3FE_34FFBE60E565

#include <cxgui/include/License.h>


namespace cx
{

namespace ui
{


/***********************************************************************************************//**
 * @class License
 *
 * @brief The Connect X license dialog.
 *
 * The Connect X license dialog show the GNU GPL 3 license text, unformatted. It is merely a
 * convenience wrapper around the @c cxgui::dlg::Licence utility.
 *
 **************************************************************************************************/
class License final : public cxgui::dlg::License
{

public:

///@{ @name Object Construction and Destruction

    /*******************************************************************************************//**
     * @brief Default constructor.
     *
     * The constructor is fed from a file located at <tt>connectx/files/license</tt>. It is the
     * plain text version of the GNU GPL 3 license.
     *
     **********************************************************************************************/
    License();


    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    ~License();

///@}


private:

///@{ @name Window setup

    virtual void setWindowIcon()    override;
    virtual void registerLayouts()  override;
    virtual void configureLayouts() override;

///@}

};

} // namespace ui

} // namespace cx

#endif // LICENSE_H_D3FE2F1F_9845_4EB2_A3FE_34FFBE60E565
