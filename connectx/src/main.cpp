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
#include <gtkmm/box.h>

#include <cxbase/include/Disc.h>

#include "../include/GBDisc.h"
#include "../include/NDADisc.h"


int main(int argc, char* argv[])
{
    Gtk::Main app(argc, argv);

    Gtk::Window w;

    const cxutil::Color fill{cxutil::RGBA{12, 175, 55, 255}};

    const cxbase::Disc d1{fill};
    const cxbase::Disc d2{fill};

    cx::ui::GBDisc disc1{d1};
    cx::ui::GBDisc disc2{d2};
    disc2.highlight();
    cx::ui::GBDisc disc3{d2};
    disc3.highlight();
    disc3.removeHighlighting();

    Gtk::HBox b;
    b.pack_start(disc1);
    b.pack_start(disc2);
    b.pack_start(disc3);

    w.add(b);
    w.show_all();

    Gtk::Main::run(w);

    return 0;
}

