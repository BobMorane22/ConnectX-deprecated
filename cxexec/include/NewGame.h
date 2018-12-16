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
 * @file    NewGame.h
 * @author  Eric Poirier
 * @date    May 2018
 * @version 1.0
 *
 * Interface for the Connect X "New Game" dialog.
 *
 **************************************************************************************************/

#ifndef NEWGAME_H_03166B40_CAFF_4659_9310_F225AFB4F9CC
#define NEWGAME_H_03166B40_CAFF_4659_9310_F225AFB4F9CC

#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/entry.h>
#include <gtkmm/hvbuttonbox.h>

#include <cxgui/include/SectionTitle.h>

#include "../include/NewPlayersList.h"
#include "../include/Window.h"


namespace cx
{

namespace ui
{

class NewGame final : public cx::ui::Window
{

public:

///@{ @name Object Construction and Destruction

    /*******************************************************************************************//**
     * @brief Default constructor.
     *
     **********************************************************************************************/
    NewGame();


    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    virtual ~NewGame();

///@}

private:


///@{ @name Window setup

    virtual void configureWindow()         override;
    virtual void registerLayouts()         override;
    virtual void registerWidgets()         override;
    virtual void configureLayouts()        override;
    virtual void configureWidgets()        override;
    virtual void configureSignalHandlers() override;

///@}

///@{ @name Signal handlers

    void onAddPlayersBtnClicked();
    void onRemovePlayerKeyPressed();
    void onStartBtnClicked();

    // Default signal handler.
    virtual bool on_key_press_event(GdkEventKey* p_event) override;

///@}


///@{ @name Data members

    // Layouts:
    Gtk::Grid              m_gameSectionLayout;       ///< The layout for the "Game" section.
    Gtk::Grid              m_gameBoardSectionLayout;  ///< The layout for the "Game board" section.
    Gtk::Grid              m_playersSectionLayout;    ///< The layout for the "Players" section.

    Gtk::HButtonBox        m_addPlayerButtonLayout;   ///< The label containing the "Add player" button.
    Gtk::HButtonBox        m_startGameSectionLayout;  ///< The label containing the "Start" button.

    // Visible widgets:
    cxgui::SectionTitle    m_gameSectionTitle        {"Game:"};               ///< The "Game" section title.
    
    Gtk::Label             m_inARowValueLabel        {"In-a-row value:"};     ///< The label telling the user to enter
                                                                              ///< a specific "in-a-row" value for the game.

    Gtk::Entry             m_inARowValueEntry;                                ///< The "in-a-row" combobox.

    cxgui::SectionTitle    m_gameBoardSectionTitle   {"Game board:"};         ///< The "Game board" section title.

    Gtk::Label             m_nbRowsLabel             {"Number of rows:"};     ///< The label telling the user to enter
                                                                              ///< a specific number of rows for the game.

    Gtk::Entry             m_nbRowsEntry;                                     ///< The number of rows combobox.

    Gtk::Label             m_nbColumnsLabel          {"Number of columns:"};  ///< The label telling the user to enter

                                                                              ///< a specific number of columns for the game.

    Gtk::Entry             m_nbColumnsEntry;                                  ///< The number of columns combobox.

    cxgui::SectionTitle    m_playersSectionTitle     {"Players:"};       ///< The "Players" section title.

    cx::ui::NewPlayersList m_playersTable;                               ///< The list of players (names and disc colors).

    Gtk::Button            m_addPlayerButton         {"Add player..."};  ///< The button used to add players.

    Gtk::Button            m_startButton             {"Start"};          ///< The button used to start a game.

    const int              m_spacing                 {15};  ///< Value used to space out widgets
                                                            ///< appart if they feel to close to
                                                            ///< one another.

///@}

};

} // namespace ui

} // namespace cx

#endif // NEWGAME_H_03166B40_CAFF_4659_9310_F225AFB4F9CC

