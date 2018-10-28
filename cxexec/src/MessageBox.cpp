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
 * @file    MessageBox.cpp
 * @author  Eric Poirier
 * @date    September 2018
 * @version 1.0
 *
 * Implementation for a Connect X message box feeding from a message file.
 *
 **************************************************************************************************/

#include <cxutil/include/util.h>

#include "../include/MessageBox.h"
#include "../include/util.h"


cx::ui::MessageBox::MessageBox(cxgui::dlg::Window&            p_parent,
                               const cxgui::dlg::MessageType  p_messageType,
                               const std::string&             p_primaryMessage,
                               const std::string&             p_secondaryMessage,
                               const bool                     p_makeModal)
 : cxgui::dlg::MessageBox(p_parent,
                          p_messageType,
                          p_primaryMessage,
                          p_secondaryMessage,
                          p_makeModal)
{
    // Nothing to do...
}


cx::ui::MessageBox::MessageBox(cxgui::dlg::Window&            p_parent,
                               const cxgui::dlg::MessageType  p_messageType,
                               const int                      p_messageNumber,
                               const bool                     p_makeModal)
 : cxgui::dlg::MessageBox(p_parent,
                          p_messageType,
                          p_messageNumber,
                          cxutil::path::currentExecutablePath() + "/ressources/cxmessages",
                          p_makeModal)
{
    // Nothing to do...
}


void cx::ui::MessageBox::setWindowIcon()
{
    // The framework can't be used here, so we have to detail everything:
    std::string iconPath{cxutil::path::currentExecutablePath()};
    iconPath.append("/icons/cxicon16.png");

    set_icon_from_file(iconPath);
}

