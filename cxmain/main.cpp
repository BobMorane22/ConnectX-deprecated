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
 * @file    main.cpp
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Implementation for the Connect X main function.
 *
 **************************************************************************************************/

#include <string>

#include <gtkmm/application.h>

#include <cxutil/include/Assertion.h>
#include <cxutil/include/util.h>

// Refactored:
#include <cxexec/include/About.h>
#include <cxexec/include/Credits.h>
#include <cxexec/include/Help.h>
#include <cxexec/include/License.h>
#include <cxexec/include/MessageBox.h>

// To be refactored:
#include <cxexec/include/GameWindow.h>
#include <cxexec/include/NewGame.h>


int main(int argc, char** argv)
{
    using namespace cxgui::dlg;

    Glib::RefPtr<Gtk::Application> app{Gtk::Application::create(argc, argv, "com.github.bobmorane22.connectx")};

    // Parent window (of type cxgui::dlg::Window):
    cx::ui::About w;

    {
        // Message box:
        cx::ui::MessageBox mb{w, MessageType::QUESTION, "A test", "Some more description..."};

        // Show the message box and get the user response:
        const ResponseType response = mb.invoke();

        // Handle user response:
        switch(response)
        {
            case ResponseType::NONE         : std::cout << "Response : NONE"         << std::endl; break;
            case ResponseType::REJECT       : std::cout << "Response : REJECT"       << std::endl; break;
            case ResponseType::ACCEPT       : std::cout << "Response : ACCEPT"       << std::endl; break;
            case ResponseType::DELETE_EVENT : std::cout << "Response : DELETE_EVENT" << std::endl; break;
            case ResponseType::OK           : std::cout << "Response : OK"           << std::endl; break;
            case ResponseType::CANCEL       : std::cout << "Response : CANCEL"       << std::endl; break;
            case ResponseType::CLOSE        : std::cout << "Response : CLOSE"        << std::endl; break;
            case ResponseType::YES          : std::cout << "Response : YES"          << std::endl; break;
            case ResponseType::NO           : std::cout << "Response : NO"           << std::endl; break;
            case ResponseType::APPLY        : std::cout << "Response : APPLY"        << std::endl; break;
            case ResponseType::HELP         : std::cout << "Response : HELP"         << std::endl; break;

            default:
                CX_ASSERT_MSG(false, "Unknown response type...");
        }

    } // Destroy the message box...

    return app->run(w);
}
