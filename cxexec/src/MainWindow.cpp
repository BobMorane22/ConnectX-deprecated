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
 * @file    MainWindow.cpp
 * @author  Eric Poirier
 * @date    February 2018
 * @version 1.0
 *
 * Implementation for a Connect X GUI main window.
 *
 **************************************************************************************************/

#include <iostream>

#include <cxutil/include/util.h>
#include <cxgui/include/enums.h>

#include "../include/MainWindow.h"

namespace
{

enum WindowSection
{
    MENU_BAR,
    GAME_INFORMATION,
    GAME_BOARD,
    REINITIALIZE,
};

enum GameInformationRows
{
    GAME_INFORMATION_SECTION_TITLE,
    ACTIVE_PLAYER,
    NEXT_PLAYER,
    IN_A_ROW_VALUE,
    NB_MOVES_REMAINING,
};

enum GameInformationColumns
{
    TITLE,
    LABEL = TITLE,
    PRIMARY_INFO,
    SECONDARY_INFO,
};

} // unamed namespace

cx::ui::MainWindow::MainWindow()
{
    // Automate the layout process:
    signal_realize().connect([this]()
                             {
                                 init();
                             });

    add(m_mainLayout);

    // Menu bar items registration:
    registerMenu();

    // Display all widgets:
    show_all();
}


cx::ui::MainWindow::~MainWindow() = default;


void cx::ui::MainWindow::setWindowIcon()
{
    // The framework can't be used here, so we have to detail everything:
    std::string iconPath{cxutil::path::currentExecutablePath()};
    iconPath.append("/icons/cxicon16.png");

    set_icon_from_file(iconPath);
}


void cx::ui::MainWindow::configureWindow()
{
    // Window setup:
    set_title("Connect X");

    //set_icon_from_file(iconPath);
    set_position(Gtk::WIN_POS_CENTER);
}


void cx::ui::MainWindow::registerMenu()
{
    m_menuBar.append(m_gameMenuItem);
    m_gameMenuItem.set_submenu(m_gameMenu);
    m_gameMenu.append(m_newGameMenuItem);
    m_gameMenu.append(m_reinitializeGameMenuItem);
    m_gameMenu.append(m_quitMenuItem);

    m_menuBar.append(m_helpMenuItem);
    m_helpMenuItem.set_submenu(m_helpMenu);
    m_helpMenu.append(m_showHelpMenuItem);
    m_helpMenu.append(m_aboutMenuItem);
}


void cx::ui::MainWindow::registerLayouts()
{
    // Principal sub-layouts used in this window:
    m_mainLayout.attach(m_menuBarLayout,      0, MENU_BAR,         cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_mainLayout.attach(m_gameInfoLayout,     0, GAME_INFORMATION, cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_mainLayout.attach(m_gameBoardLayout,    0, GAME_BOARD,       cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_mainLayout.attach(m_reinitializeLayout, 0, REINITIALIZE,     cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
}


void cx::ui::MainWindow::registerWidgets()
{
    //Menu bar:
    m_menuBarLayout.attach(m_menuBar,            0,              0,                              cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);

    // Game information section:
    m_gameInfoLayout.attach(m_gameInfoSection,   TITLE,          GAME_INFORMATION_SECTION_TITLE, cxgui::GridWidth::THREE_COLUMNS, cxgui::GridHeight::ONE_ROW);

    m_gameInfoLayout.attach(m_activePlayer,      LABEL,          ACTIVE_PLAYER,                  cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_gameInfoLayout.attach(m_activePlayerName,  PRIMARY_INFO,   ACTIVE_PLAYER,                  cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_gameInfoLayout.attach(m_activePlayerColor, SECONDARY_INFO, ACTIVE_PLAYER,                  cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_gameInfoLayout.attach(m_nextPlayer,        LABEL,          NEXT_PLAYER,                    cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_gameInfoLayout.attach(m_nextPlayerName,    PRIMARY_INFO,   NEXT_PLAYER,                    cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_gameInfoLayout.attach(m_nextPlayerColor,   SECONDARY_INFO, NEXT_PLAYER,                    cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_gameInfoLayout.attach(m_inARowValue,       LABEL,          IN_A_ROW_VALUE,                 cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_gameInfoLayout.attach(m_inARowValueNumber, PRIMARY_INFO,   IN_A_ROW_VALUE,                 cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_gameInfoLayout.attach(m_nbMovesLeft,       LABEL,          NB_MOVES_REMAINING,             cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_gameInfoLayout.attach(m_nbMovesLeftNumber, PRIMARY_INFO,   NB_MOVES_REMAINING,             cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);

    // Game board section:
    m_gameBoardLayout.attach(m_gameBoardSection, 0,              0,                              cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_gameBoardLayout.attach(m_gameBoard,        0,              1,                              cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);

    // Reinitialize button section:
    m_reinitializeLayout.pack_start(m_reinitialize);
}


void cx::ui::MainWindow::configureLayouts()
{
    const int spacing{15};

    m_mainLayout.set_hexpand(true);
    m_mainLayout.set_vexpand(true);
    m_mainLayout.set_row_spacing(spacing);

    m_gameInfoLayout.set_margin_left(spacing);
    m_gameInfoLayout.set_margin_right(spacing);
    m_gameBoardLayout.set_margin_left(spacing);
    m_gameBoardLayout.set_margin_right(spacing);
    m_reinitializeLayout.set_margin_left(spacing);
    m_reinitializeLayout.set_margin_right(spacing);
    m_reinitializeLayout.set_margin_bottom(spacing);
}


void cx::ui::MainWindow::configureWidgets()
{
    const int spacing{15};

    m_menuBar.set_hexpand(true);

    // Leave some space between the game information widgets:
    m_gameInfoLayout.set_column_spacing(spacing);

    // For every game information widget, remove vertical expansion.
    for(Widget* widget : m_gameInfoLayout.get_children())
    {
        Gtk::Label* label{static_cast<Gtk::Label*>(widget)};

        label->set_alignment(Gtk::Align::ALIGN_START);
        label->set_vexpand(false);
    }

    m_gameBoard.set_hexpand(true);
    m_gameBoard.set_vexpand(true);

    m_gameBoardLayout.set_hexpand(true);
    m_gameBoardLayout.set_vexpand(true);


    // Button to the left:
    m_reinitializeLayout.set_layout(Gtk::BUTTONBOX_END);
}


void cx::ui::MainWindow::configureSignalHandlers()
{
    // Nothing so far...
}


/***************************************************************************************************
 * @brief Window initialisation.
 *
 * This method is automatically called when the @c Window::signal_realize is sent by the window,
 * i.e. when every data structure used by the window is constructed and ready for use. It is hence
 * called after construction of the window and is therefore not subject to the constructor
 * restriction to avoid virtual methods. You can call anything you want from here because you
 * have the guarantee the window is fully constructed.
 *
 * @note Once again, the cxgui::dlg::Window framework for automating the layout could not be
 *       be used because of multiple inheritance issues...
 *
 **************************************************************************************************/
void cx::ui::MainWindow::init()
{
    setWindowIcon();
    configureWindow();
    registerLayouts();
    registerWidgets();
    configureLayouts();
    configureWidgets();
    configureSignalHandlers();
}
