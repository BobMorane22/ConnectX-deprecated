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
 * @file    MessageBox.h
 * @author  Eric Poirier
 * @date    September 2018
 * @version 1.0
 *
 * Interface for a Connect X message box feeding from a message file.
 *
 **************************************************************************************************/

#ifndef MESSAGEBOX_H_468EF8E4_3AEB_462A_8BE3_94CC620376CD
#define MESSAGEBOX_H_468EF8E4_3AEB_462A_8BE3_94CC620376CD

#include <cxgui/include/MessageBox.h>


namespace cx
{

namespace ui
{

/***********************************************************************************************//**
 * @class MessageBox
 *
 * @brief Simple message box widget feeding from a message file.
 *
 * This is simply the Connect X wrapper for the @c cxgui MessageBox widget.
 *
 **************************************************************************************************/
class MessageBox final : public cxgui::dlg::MessageBox
{

public:

///@{ @name Object construction and destruction

    /*******************************************************************************************//**
     * @brief Constructor with parameters.
     *
     * Constructs a message box for which the messages are taken from the @c cxmessage file. See
     * the base class documentation for the message file syntax. Note that the buttons are
     * automatically set to match the message type you specify.
     *
     * @param p_parent           A reference to the parent window (i.e. the window from which
     *                           the dialog is invoked).
     * @param p_messageType      The type of message. This will influence the buttons that are
     *                           added to the message box.
     * @param p_messageNumber    The tag number of the message(s) in the message file.
     * @param p_makeModal        @c true is the message box should be modal, @c false otherwise.
     *
     * @pre The message file path must point to a valid file on the disc.
     *
     **********************************************************************************************/
    MessageBox(Gtk::Window&                   p_parent,
               const cxgui::dlg::MessageType  p_messageType,
               const int                      p_messageNumber,
               const bool                     p_makeModal = false);

///@}

};

} // namespace ui

} // namespace cx

#endif // MESSAGEBOX_H_468EF8E4_3AEB_462A_8BE3_94CC620376CD
