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


cx::ui::MessageBox::MessageBox(Gtk::Window&                   p_parent,
                               const cxgui::dlg::MessageType  p_messageType,
                               const int                      p_messageNumber,
                               const bool                     p_makeModal)
 : cxgui::dlg::MessageBox(p_parent,
                          p_messageType,
                          p_messageNumber,
                          cxutil::path::currentExecutablePath() + "/ressources/cxmessages",
                          p_makeModal)
{
}
