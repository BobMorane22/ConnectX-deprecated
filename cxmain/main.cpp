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

// To be refactored:
#include <cxexec/include/NewGame.h>
#include <cxexec/include/GameWindow.h>


int main(int argc, char** argv)
{
    using namespace cxgui::dlg;

    Glib::RefPtr<Gtk::Application> app{Gtk::Application::create(argc, argv, "com.github.bobmorane22.connectx")};

    Gtk::Window w;
    std::unique_ptr<cx::ui::NewPlayersList> npl{new cx::ui::NewPlayersList()};

    w.add(*npl);

    //-------------------------------------- TESTS -------------------------------------------------
    std::cout << "TEST 1: Adding a player (error: color already in use):" << std::endl;
    {
        std::cout << "\tSize before :" << npl->size() << std::endl;

        auto res = npl->addRow("A new player", cxutil::Color::black());
        CX_ASSERT_MSG(!res.isOk(), "An error should occur...");

        std::cout << "\tSize after :" << npl->size() << std::endl;
    }
    // ---------------------------------------------------------------------------------------------
    std::cout << "TEST 2: Adding a player:" << std::endl;
    {
        std::cout << "\tSize before :" << npl->size() << std::endl;

        auto res = npl->addRow("A new player", cxutil::Color::yellow());
        if(res.isOk())
        {
            std::cout << "\tNew player name :" << npl->rowPlayerName(2) << std::endl;
        }

        std::cout << "\tSize after :" << npl->size() << std::endl;
    }
    // ---------------------------------------------------------------------------------------------
    std::cout << "TEST 3: Adding yet another player:" << std::endl;
    {
        std::cout << "\tSize before :" << npl->size() << std::endl;

        auto res = npl->addRow("Another player", cxutil::Color::green());
        if(res.isOk())
        {
            std::cout << "\tNew player name :" << npl->rowPlayerName(2) << std::endl;
        }

        std::cout << "\tSize after :" << npl->size() << std::endl;
    }
    // ---------------------------------------------------------------------------------------------
    std::cout << "TEST 4: Removing a player (error: player does not exist by name):" << std::endl;
    {
        std::cout << "\tSize before :" << npl->size() << std::endl;

        auto res = npl->removeRow("An unknown player", cxutil::Color::yellow());
        CX_ASSERT_MSG(!res.isOk(), "An error should occur...");

        std::cout << "\tSize after :" << npl->size() << std::endl;
    }
    // ---------------------------------------------------------------------------------------------
    std::cout << "TEST 5: Removing a player (error: player does not exist by color):" << std::endl;
    {
        std::cout << "\tSize before :" << npl->size() << std::endl;

        auto res = npl->removeRow("Another player", cxutil::Color::blue());
        CX_ASSERT_MSG(!res.isOk(), "An error should occur...");

        std::cout << "\tSize after :" << npl->size() << std::endl;
    }
    // ---------------------------------------------------------------------------------------------
    std::cout << "TEST 6: Removing a player (by row number):" << std::endl;
    {
        std::cout << "\tSize before :" << npl->size() << std::endl;

        auto res = npl->removeRow(2);
        CX_ASSERT_MSG(res.isOk(), "No error should occur...");

        std::cout << "\tSize after :" << npl->size() << std::endl;
    }
    // ---------------------------------------------------------------------------------------------
    std::cout << "TEST 7: Removing a player (by name and color):" << std::endl;
    {
        std::cout << "\tSize before :" << npl->size() << std::endl;

        auto res = npl->removeRow("Another player", cxutil::Color::green());
        CX_ASSERT_MSG(res.isOk(), "No error should occur...");

        std::cout << "\tSize after :" << npl->size() << std::endl;
    }
    // ---------------------------------------------------------------------------------------------
    std::cout << "TEST 8: Updating a player (error: color already in use):" << std::endl;
    {
        std::cout << "\tSize before :" << npl->size() << std::endl;

        auto res = npl->updateRow(0, "Bob", cxutil::Color::red());
        CX_ASSERT_MSG(!res.isOk(), "An error should occur...");

        std::cout << "\tSize after :" << npl->size() << std::endl;
    }
    // ---------------------------------------------------------------------------------------------
    std::cout << "TEST 9: Updating a player:" << std::endl;
    {
        std::cout << "\tSize before :" << npl->size() << std::endl;

        auto res = npl->updateRow(0, "Bob", cxutil::Color::yellow());
        CX_ASSERT_MSG(res.isOk(), "No error should occur...");

        std::cout << "\tSize after :" << npl->size() << std::endl;
    }
    //------------------------------------ END TESTS -----------------------------------------------

    w.show_all();

    return app->run(w);
}
