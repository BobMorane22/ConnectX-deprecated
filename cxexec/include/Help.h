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
 * @file    Help.h
 * @author  Eric Poirier
 * @date    August 2018
 * @version 1.0
 *
 * Interface for the Connect X help dialog.
 *
 **************************************************************************************************/

#ifndef HELP_H_48874F1D_5857_49B1_84D5_3B8B0091C25A
#define HELP_H_48874F1D_5857_49B1_84D5_3B8B0091C25A

#include <cxgui/include/Help.h>

#include "../include/util.h"

namespace cx
{

namespace ui
{

/***********************************************************************************************//**
 * @class Help
 *
 * This class represents the Help dialog presented to the user for the Connect X application.
 *
 **************************************************************************************************/
class Help final : public cxgui::dlg::Help
{

public:

    /*******************************************************************************************//**
     * Default constructor.
     *
     **********************************************************************************************/
    Help();


    /*******************************************************************************************//**
     * Default destructor.
     *
     **********************************************************************************************/
    ~Help();


protected:

///@{ @name Window Setup

    virtual void setWindowIcon()           override;
    virtual void registerLayouts()         override;
    virtual void configureLayouts()        override;
    virtual void configureSignalHandlers() override;

///@}

private:

///@{ @name Signal Handlers

    void onConsultOnlineHelp();

///@}

};

} // namespace ui

} // namespace cx

#endif // HELP_H_48874F1D_5857_49B1_84D5_3B8B0091C25A
