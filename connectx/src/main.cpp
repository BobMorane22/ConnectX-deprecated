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

#include <gtkmm/main.h>
#include <gtkmm/window.h>

#include <cxgui/include/Disc.h>

#include "../include/GameBoard.h"

int main(int argc, char* argv[])
{
    Gtk::Main app(argc, argv);

    Gtk::Window w;

    const cxutil::Color fill{125, 0, 0, 255};
    const cxutil::Color background{0, 125, 0, 255};
    const cxutil::Color border{0, 0, 125, 255};
    cxgui::Disc disc{fill, background, border};

    w.add(disc);
    w.show_all();

    Gtk::Main::run(w);

    return 0;
}

