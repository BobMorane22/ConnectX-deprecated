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
 * @file    MainWindow.h
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Interface for a Connect X GUI main window.
 *
 **************************************************************************************************/

#ifndef MAINWINDOW_H_1900DBCF_E1B9_43A8_9FFC_94376406279E
#define MAINWINDOW_H_1900DBCF_E1B9_43A8_9FFC_94376406279E

#include <memory>

#include <gtkmm/applicationwindow.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/imagemenuitem.h>
#include <gtkmm/label.h>
#include <gtkmm/menu.h>
#include <gtkmm/menubar.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/stock.h>

#include <cxbase/include/Game.h>

#include <cxgui/include/SectionTitle.h>

#include "GameBoard.h"


namespace cx
{

namespace ui
{

/***************************************************************************************************
 * @class MainWindow
 *
 * @brief Main Connect X window.
 *
 * This special window encapsulate many necessary goodies to be used with a Gtk::Application
 * object. There should only be one such window in the whole code base, and it should be the
 * window used as an argument in @c Gtk::Application::run() .
 *
 * @todo Automate the window layout creation process.
 *
 **************************************************************************************************/
class MainWindow : public Gtk::ApplicationWindow
{

public:

///@{ @name Object Construction and Destruction

    /***********************************************************************************************
     * Default constructor.
     *
     **********************************************************************************************/
    MainWindow();


    /***********************************************************************************************
     * Default destructor.
     *
     **********************************************************************************************/
    virtual ~MainWindow() override;

///@}



private:

///@{ @name Layout and widgets configuration

    void setWindowIcon();
    void configureWindow();
    void registerMenu();
    void registerLayouts();
    void registerWidgets();
    void configureLayouts();
    void configureWidgets();
    void configureSignalHandlers();

    void init();

///@}


///@{ @name Data members:

    // Widget layouts:
    Gtk::Grid       m_mainLayout;                 // The main window layout.

    Gtk::Grid       m_menuBarLayout;
    Gtk::Grid       m_gameInfoLayout;             ///< Contains all widgets in
                                                  ///< the 'Game information' section.
                                                  ///<

    Gtk::Grid       m_gameBoardLayout;            ///< Contains all widgets in the
                                                  ///< 'Game board' section.
                                                  ///<

    Gtk::HButtonBox m_reinitializeLayout;         ///< Layout for the 'Reinitialize' button.

    // Visible widgets:
    Gtk::MenuBar        m_menuBar;
    Gtk::Menu           m_gameMenu;
    Gtk::MenuItem       m_gameMenuItem               {"_Game", true          };
    Gtk::ImageMenuItem  m_newGameMenuItem            {Gtk::Stock::NEW        };
    Gtk::MenuItem       m_reinitializeGameMenuItem   {"_Reinitialize Game", true};
    Gtk::ImageMenuItem  m_quitMenuItem               {Gtk::Stock::QUIT       };

    Gtk::Menu           m_helpMenu;
    Gtk::MenuItem       m_helpMenuItem               {"_Help", true};
    Gtk::ImageMenuItem  m_showHelpMenuItem           {Gtk::Stock::HELP       };
    Gtk::ImageMenuItem  m_aboutMenuItem              {Gtk::Stock::ABOUT      };

    cxgui::SectionTitle m_gameInfoSection            {"Game information:"    };
    Gtk::Label          m_activePlayer               {"Active player:"       };
    Gtk::Label          m_activePlayerName           {"John Doe"             };
    cx::ui::NDADisc     m_activePlayerColor          {cxbase::Disc{cxutil::Color::red()}};
    Gtk::Label          m_nextPlayer                 {"Next player:"         };
    Gtk::Label          m_nextPlayerName             {"Jane Hardy"           };
    cx::ui::NDADisc     m_nextPlayerColor            {cxbase::Disc{cxutil::Color::green()}};
    Gtk::Label          m_inARowValue                {"In-a-row value:"      };
    Gtk::Label          m_inARowValueNumber          {"4"                    };
    Gtk::Label          m_nbMovesLeft                {"Number of moves left:"};
    Gtk::Label          m_nbMovesLeftNumber          {"21"                   };

    cxgui::SectionTitle m_gameBoardSection           {"Game board:"          };
    cx::ui::GameBoard   m_gameBoard                  {std::make_shared<cxbase::GameBoard>(10, 10)};

    Gtk::Button         m_reinitialize               {"Reinitialize"         };

///@}

};

} // namespace ui

} // namespace cx

#endif // MAINWINDOW_H_1900DBCF_E1B9_43A8_9FFC_94376406279E
