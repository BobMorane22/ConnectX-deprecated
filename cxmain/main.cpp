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

#include <iostream>
#include <memory>
#include <string>

#include <gtkmm/application.h>

#include <cxutil/include/cxutilAPI.h>

// Refactored:
#include <cxexec/include/About.h>
#include <cxexec/include/Credits.h>
#include <cxexec/include/Help.h>
#include <cxexec/include/License.h>
#include <cxexec/include/MessageBox.h>
#include <cxexec/include/NewPlayersList.h>
#include <cxexec/include/NewGame.h>

// To be refactored:
#include <cxexec/include/GameWindow.h>


int main(int argc, char** argv)
{
    Glib::RefPtr<Gtk::Application> app{Gtk::Application::create(argc, argv, "com.github.bobmorane22.connectx")};

    cx::ui::NewGame w;

    w.show_all();

    return app->run(w);
}
