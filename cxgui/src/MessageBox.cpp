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
 * Implementation for a message box.
 *
 **************************************************************************************************/

#include <cctype>
#include <fstream>
#include <regex>

#include <cxutil/include/Assertion.h>
#include <cxutil/include/ContractException.h>

#include "../include/MessageBox.h"
#include "../include/Window.h"

namespace
{

/***************************************************************************************************
 * @enum MessageVisibility
 *
 * @brief Visibility or weight of a message.
 *
 * Messages can be compared in terms of their visibility (or weight) in the context in which they
 * are stated. Two visibilities are defined here: primary and secondary.
 *
 **************************************************************************************************/
enum class MessageVisibility
{
    PRIMARY,     ///< Primary message.
    SECONDARY,   ///< Secondary message.
};


/***************************************************************************************************
 * @brief Converts a @c cxgui::dlg::MessageType to a @c Gtk::MessageType .
 *
 * @param p_messageType The @c cxgui::dlg::MessageType to convert.
 *
 **************************************************************************************************/
Gtk::MessageType convertMessageType(const cxgui::dlg::MessageType p_messageType)
{
    Gtk::MessageType gtkMsgType;

    switch(p_messageType)
    {
        case cxgui::dlg::MessageType::INFORMATION:
            gtkMsgType = Gtk::MessageType::MESSAGE_INFO;
            break;

        case cxgui::dlg::MessageType::WARNING:
            gtkMsgType = Gtk::MessageType::MESSAGE_WARNING;
            break;

        case cxgui::dlg::MessageType::QUESTION:
            gtkMsgType = Gtk::MessageType::MESSAGE_QUESTION;
            break;

        case cxgui::dlg::MessageType::ERROR:
            gtkMsgType = Gtk::MessageType::MESSAGE_ERROR;
            break;

        case cxgui::dlg::MessageType::OTHER:
            gtkMsgType = Gtk::MessageType::MESSAGE_OTHER;
            break;

        default:
            CX_ASSERT_MSG(false, "Unknown message type.");
    }

    return gtkMsgType;
}


/***************************************************************************************************
 * @brief Gets the buttons associated to a type of message.
 *
 * @param p_messageType The message type.
 *
 **************************************************************************************************/
Gtk::ButtonsType getButtons(const cxgui::dlg::MessageType p_messageType)
{
    Gtk::ButtonsType gtkBtnType;

    switch(p_messageType)
    {
        case cxgui::dlg::MessageType::INFORMATION:
            gtkBtnType = Gtk::ButtonsType::BUTTONS_OK;
            break;

        case cxgui::dlg::MessageType::WARNING:
            gtkBtnType = Gtk::ButtonsType::BUTTONS_OK;
            break;

        case cxgui::dlg::MessageType::QUESTION:
            gtkBtnType = Gtk::ButtonsType::BUTTONS_YES_NO;
            break;

        case cxgui::dlg::MessageType::ERROR:
            gtkBtnType = Gtk::ButtonsType::BUTTONS_CLOSE;
            break;

        case cxgui::dlg::MessageType::OTHER:
            gtkBtnType = Gtk::ButtonsType::BUTTONS_OK_CANCEL;
            break;

        default:
            CX_ASSERT_MSG(false, "Unknown message type.");
    }

    return gtkBtnType;
}


/***************************************************************************************************
 * @brief Extracts a message in a text line.
 *
 * @param[in]  p_line        A line of text containing a message, formatted according to the
 *                           message file syntax. See the cxgui::dlg::MessageBox class
 *                           documentation for more details.
 * @param[out] p_visibility  The found message's visibility;
 *
 * @returns A string containing the found message and it's visibility as a parameter.
 *
 * @see cxgui::dlg::MessageBox
 *
 **************************************************************************************************/
std::string extractMessage(const std::string& p_line, MessageVisibility& p_visibility)
{
    const std::string primary  {"PRIMARY"  };
    const std::string secondary{"SECONDARY"};

    std::string message;

    const std::size_t primaryIndex{p_line.find(primary, 0)};

    if(primaryIndex == std::string::npos)
    {
        // Not a primary message, we check if it is a secondary message:
        const std::size_t secondaryIndex{p_line.find(secondary, 0)};

        CX_ASSERT_MSG(secondaryIndex != std::string::npos, "There is a syntax error in the "
                                                           "message file.");

        // It is a secondary message, we extract it. First, we find the first character that
        // is not a whitespace, after the secondary tag:
        p_visibility = MessageVisibility::SECONDARY;

        auto it = std::find_if(p_line.begin() + secondaryIndex + secondary.size(),
                               p_line.end(),
                               [](char p_character)
                                 {
                                     return !std::isspace(static_cast<int>(p_character));
                                 });

        // We assign the remaining of the string to the message:
        message.assign(it, p_line.end());
    }
    else
    {
        // It is a primary message, we extract it. First, we find the first character that
        // is not a whitespace, after the primary tag:
        p_visibility = MessageVisibility::PRIMARY;

        auto it = std::find_if(p_line.begin() + primaryIndex + primary.size(),
                               p_line.end(),
                               [](char p_character)
                                 {
                                     return !std::isspace(static_cast<int>(p_character));
                                 });

        // We assign the remaining of the string to the message:
        message.assign(it, p_line.end());

    }

    CX_ASSERT_MSG(!message.empty(), "There is a syntax error in the message file.");

    return message;
}

} // unamed namespace


cxgui::dlg::MessageBox::MessageBox(cxgui::dlg::Window&  p_parent,
                                   const MessageType    p_messageType,
                                   const std::string&   p_primaryMessage,
                                   const std::string&   p_secondaryMessage,
                                   const bool           p_makeModal)
 : Gtk::MessageDialog(p_parent,
                      p_primaryMessage,
                      true,
                      convertMessageType(p_messageType),
                      getButtons(p_messageType),
                      p_makeModal)
{
    PRECONDITION(!p_primaryMessage.empty());

    // First, we connect to the realize signal:
    signal_realize().connect([this]()
                             {
                                 init();
                             });

    // We need to set this because otherwise, the primary message does
    // not appear in bold, which is inconsistent with the next constructor.
    // It seems like the Gtk::MessageDialog constructor does not call this
    // by itself, but does something else...
    set_message(p_primaryMessage);

    if(!p_secondaryMessage.empty())
    {
        set_secondary_text(p_secondaryMessage);
    }
}


cxgui::dlg::MessageBox::MessageBox(cxgui::dlg::Window&  p_parent,
                                   const MessageType    p_messageType,
                                   const int            p_messageNumber,
                                   const std::string&   p_messagesFilePath,
                                   const bool           p_makeModal)
 : Gtk::MessageDialog(p_parent,
                      std::string(),
                      true,
                      convertMessageType(p_messageType),
                      getButtons(p_messageType),
                      p_makeModal)
{
    PRECONDITION(!p_messagesFilePath.empty());

    // First, we connect to the realize signal:
    signal_realize().connect([this]()
                             {
                                 init();
                             });

    // Both messages are empty, we have to go fetch them from the
    // file whose path is given as an argument. First, we make sure
    // the file is valid:
    std::ifstream ifs{p_messagesFilePath};

    CX_ASSERT_MSG(ifs.is_open(), "The stream could not open the specified file.");

    // The stream is working, we can go on. We scan each line ignoring lines that:
    //   1. Start with a '#' character. Those are comments.
    //   2. Lines that are only a combination of spaces and/or tabs.
    const std::regex  ignored   {"((\\t|\\s)+)|#(\\w|\\W)*"                 };
    const std::string messageTag{"CX_MSG-" + std::to_string(p_messageNumber)};

    std::string line;

    bool primaryMsgFound  {false};
    bool secondaryMsgFound{false};
    std::string primaryMsg;
    std::string secondaryMsg;

    while(ifs.good())
    {
        // Get the current line:
        std::getline(ifs, line);

        if(std::regex_match(line.begin(), line.end(), ignored))
        {
            continue;
        }

        if(line.find(messageTag) != std::string::npos)
        {
            // The message tag is located, we now trim the message out
            // of the line:
            MessageVisibility visibility;
            std::string message{extractMessage(line, visibility)};

            switch(visibility)
            {
                case MessageVisibility::PRIMARY:
                {
                    primaryMsg = message;
                    primaryMsgFound = true;
                    break;
                }
                case MessageVisibility::SECONDARY:
                {
                    secondaryMsg = message;
                    secondaryMsgFound = true;
                    break;
                }
                default:
                    CX_ASSERT_MSG(false, "Unknown message visibility.");
            }
        }
    }

    CX_ASSERT_MSG(!primaryMsg.empty(), "The message that was found is empty. "
                                       "Check your message file.");

    if(primaryMsgFound)
    {
        set_message(primaryMsg);
    }

    if(secondaryMsgFound && !secondaryMsg.empty())
    {
        set_secondary_text(secondaryMsg);
    }
}


cxgui::dlg::MessageBox::~MessageBox() = default;


cxgui::dlg::ResponseType cxgui::dlg::MessageBox::invoke()
{
    return static_cast<cxgui::dlg::ResponseType>(run());
}


/***************************************************************************************************
 * @brief Window initialisation.
 *
 * This method is automatically called when the @c Window::signal_realize is sent by the message
 * box, i.e. when every data structure used by the message box is constructed and ready for use.
 * It is hence called after construction of the window and is therefore not subject to the
 * constructor restriction to avoid virtual methods. You can call anything you want from here
 * because you have the guarantee the message box is fully constructed.
 *
 * @note This is a minimal version of the cxgui::dlg::Window framework. I have decided not to
 *       re-use it here because cxgui::dlg::Window is not a pure interface and I fear it could
 *       lead to multiple inheritance issues...
 *
 **************************************************************************************************/
void cxgui::dlg::MessageBox::init()
{
    setWindowIcon();
}

