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
#include <gtkmm/window.h>

#include <cxgui/include/SectionTitle.h>

//#include "../include/PlayersTable.h"

namespace cx
{

namespace ui
{

class NewGame final : public Gtk::Window
{
public:

///@{ @name Object Construction and Destruction

    NewGame();
    ~NewGame();

///@}

private:

///@{ @name Layouts and widgets configuration

    void registerLayouts();
    void registerMenu(){};
    void registerWidgets();
    void configureLayoutsAndWidgets();

///@}

    // Widget layouts:
    Gtk::Grid            m_mainLayout;
    Gtk::Grid            m_gameSectionLayout;
    Gtk::Grid            m_gameBoardSectionLayout;
    Gtk::Grid            m_playersSectionLayout;
    Gtk::HButtonBox      m_startGameSectionLayout;

    // Visible widgets:
    cxgui::SectionTitle  m_gameSectionTitle        {"Game:"};
    Gtk::Label           m_inARowValueLabel        {"In-a-row value:"};
    Gtk::Entry           m_inARowValueEntry;

    cxgui::SectionTitle  m_gameBoardSectionTitle   {"Game board:"};
    Gtk::Label           m_nbRowsLabel             {"Number of rows:"};
    Gtk::Entry           m_nbRowsEntry;
    Gtk::Label           m_nbColumnsLabel          {"Number of columns:"};
    Gtk::Entry           m_nbColumnsEntry;

    cxgui::SectionTitle  m_playersSectionTitle     {"Players:"};
    //cx::ui::PlayersTable m_playersTable;
    Gtk::Button m_playersTable{"Players table!"};
    Gtk::Button          m_addPlayerButton         {"Add player..."};

    Gtk::Button          m_startButton             {"Start"};
};

} // namespace ui

} // namespace cx

#endif // NEWGAME_H_03166B40_CAFF_4659_9310_F225AFB4F9CC

