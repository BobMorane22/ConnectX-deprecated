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

#include <cxutil/include/util.h>

#include <gtkmm/application.h>

#include <cxexec/include/GameWindow.h>
#include <cxexec/include/NewGame.h>
#include <cxexec/include/Help.h>
#include <cxexec/include/About.h>
#include <cxexec/include/Credits.h>
#include <cxexec/include/License.h>
#include <cxgui/include/MessageBox.h>


int main(int argc, char** argv)
{
    using namespace cxgui::dlg;

    Glib::RefPtr<Gtk::Application> app{Gtk::Application::create(argc, argv, "com.github.bobmorane22.connectx")};

    // Parent window:
    Gtk::Window parent;

    // Message box:
    /*cxgui::dlg::MessageBox w{parent,
                             cxgui::dlg::MessageType::INFORMATION,
                             6,
                             cxutil::path::currentExecutablePath() + "/ressources/cxmessages",
                             false};*/

    cxgui::dlg::MessageBox w{parent,
                             cxgui::dlg::MessageType::QUESTION,
                             "Are you okay?"};

    w.show_all();

   return app->run(w);
}
