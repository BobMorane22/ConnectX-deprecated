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

#include <gtkmm/application.h>

#include "../include/GameWindow.h"
#include "../include/NewGame.h"


int main(int argc, char** argv)
{
    Glib::RefPtr<Gtk::Application> app{Gtk::Application::create(argc, argv, "com.github.bobmorane22.connectx")};

   //cx::ui::GameWindow w;
   //w.show_all();

    cx::ui::NewGame w;
    w.show_all();

   return app->run(w);
}

/*int main(int argc, char** argv)
{
    Glib::RefPtr<Gtk::Application> app{Gtk::Application::create(argc, argv, "com.github.bobmorane22.connectx")};

    Gtk::Grid grid;
    Gtk::Label label("My label:");
    Gtk::Entry entry;

    grid.attach(label, 0, 0, 1, 1);
    grid.attach(entry, 1, 0, 1, 1);

    entry.set_alignment(Gtk::Align::ALIGN_START); // Left align
    entry.set_max_width_chars(4);
    entry.set_hexpand_set(true);                  // Override with hexpand
    entry.set_hexpand(false);                     // No horizontal expansion

    Gtk::Window w;
    w.add(grid);
    w.show_all();

   return app->run(w);
}*/

