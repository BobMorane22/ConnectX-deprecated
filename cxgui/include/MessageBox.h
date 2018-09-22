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
 * Interface for a message box.
 *
 **************************************************************************************************/

#ifndef MESSAGEBOX_H_6256E4D9_32B1_4721_BD55_860CD2EE81C4
#define MESSAGEBOX_H_6256E4D9_32B1_4721_BD55_860CD2EE81C4

#include <gtkmm/messagedialog.h>


namespace Gtk { class Window; }


namespace cxgui
{

namespace dlg
{

/***********************************************************************************************//**
 * @enum MessageType
 *
 * @brief Types of messages.
 *
 * This list the major message types one can use in a MessageBox widget.
 *
 **************************************************************************************************/
enum class MessageType
{
    INFORMATION, ///< Inform the user.
    WARNING,     ///< Warn the user.
    QUESTION,    ///< Question the user. The user has to make a choice.
    ERROR,       ///< Report an error to the user.
    OTHER,       ///< Other message types.
};


/***********************************************************************************************//**
 * @class MessageBox
 *
 * @brief A simplified message box.
 *
 * Presents two options to easily generate message box widgets. The first option is the usual
 * one: create a message box and its message(s) on the spot, directly in the code. The second
 * approach permits to feed the message box messages stored in a file. This is mostly useful
 * if your application has static messages which can be used in more than one place in the
 * application. It also lets you modify messages without having to recompile.
 *
 * The syntax for the message file is the following:
 *
 * @verbatim
 *
 *   CX_MSG-n PRIMARY Some primary message string.
 *   CX_MSG-n SECONDARY Some secondary, optional message.
 *
 * @endverbatim
 *
 * where @c n is an integer. The secondary message is, of course, optional. Note that if you
 * have two sets of messages with the same @c n value, the first set of message will be fed to
 * the message box and the second set will simply be ignored.
 *
 * You can add comments using @c # at the beginning of a line. All empty lines are ignored.
 *
 **************************************************************************************************/
class MessageBox : public Gtk::MessageDialog
{

public:

///@{ @name Object construction and destruction

    /*******************************************************************************************//**
     * @brief Constructor with parameters.
     *
     * Constructs a message box for which you can specify the message directly in the source code.
     * Use this for non standard messages (i.e. a message that is only used once). Note that the
     * buttons are automatically set to match the message type you specify.
     *
     * @param p_parent           A reference to the parent window (i.e. the window from which
     *                           the dialog is invoked).
     * @param p_messageType      The type of message. This will influence the buttons that are
     *                           added to the message box.
     * @param p_primaryMessage   The message to add to the message box. This is what the user will
     *                           read.
     * @param p_secondaryMessage A secondary, optional message to complement the primary message.
     *                           The user will see this.
     * @param p_makeModal        @c true is the message box should be modal, @c false otherwise.
     *
     * @pre The primary message is not an empty string.
     *
     **********************************************************************************************/
    MessageBox(Gtk::Window&       p_parent,
               const MessageType  p_messageType,
               const std::string& p_primaryMessage,
               const std::string& p_secondaryMessage = std::string(),
               const bool         p_makeModal = false);


    /*******************************************************************************************//**
     * @brief Constructor with parameters.
     *
     * Constructs a message box for which the messages are taken from a file. See the class
     * documentation for the message file syntax. Note that the buttons are automatically set to
     * match the message type you specify.
     *
     * @param p_parent           A reference to the parent window (i.e. the window from which
     *                           the dialog is invoked).
     * @param p_messageType      The type of message. This will influence the buttons that are
     *                           added to the message box.
     * @param p_messageNumber    The tag number of the message(s) in the message file.
     * @param p_messagesFilePath A path to the message file on the disc.
     * @param p_makeModal        @c true is the message box should be modal, @c false otherwise.
     *
     * @pre The message file path must point to a valid file on the disc.
     *
     **********************************************************************************************/
    MessageBox(Gtk::Window&       p_parent,
               const MessageType  p_messageType,
               const int          p_messageNumber,
               const std::string& p_messagesFilePath,
               const bool         p_makeModal = false);


    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    virtual ~MessageBox();

///@}

};

} // namespace dlg

} // namespace cxgui

#endif // MESSAGEBOX_H_6256E4D9_32B1_4721_BD55_860CD2EE81C4
