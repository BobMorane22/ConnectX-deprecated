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
 * @file    NewGame.cpp
 * @author  Eric Poirier
 * @date    May 2018
 * @version 1.0
 *
 * Implementation for the Connect X "New Game" dialog.
 *
 **************************************************************************************************/

#include <cxutil/include/util.h>
#include <cxgui/include/enums.h>

#include "../include/NewGame.h"

namespace
{

enum WindowSection
{
    GAME,
    GAME_BOARD,
    PLAYERS,
    START_GAME,
};

} // unnamed namespace


cx::ui::NewGame::NewGame()
{
    // Window setup:
    set_title("New game");

    std::string iconPath{cxutil::path::currentExecutablePath()};
    iconPath.append("/icons/cxicon16.png");

    set_icon_from_file(iconPath);
    set_position(Gtk::WIN_POS_CENTER);

    // Layouts registration:
    registerLayouts();

    // Menu bar items registration:
    registerMenu();

    // Widgets registration in layouts:
    registerWidgets();

    // Layout and Widgets look:
    configureLayoutsAndWidgets();

    // Display all widgets:
    show_all();
}


cx::ui::NewGame::~NewGame() = default;


void cx::ui::NewGame::registerLayouts()
{
    // Window main layout:
    add(m_mainLayout);

    // Principal sub-layouts used in this window:
    m_mainLayout.attach(m_gameSectionLayout,      0, GAME,       cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_mainLayout.attach(m_gameBoardSectionLayout, 0, GAME_BOARD, cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_mainLayout.attach(m_playersSectionLayout,   0, PLAYERS,    cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_mainLayout.attach(m_startGameSectionLayout, 0, START_GAME, cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);

    // Special sub-layout for the "Add player..." button:
    m_addPlayerButtonLayout.pack_start(m_addPlayerButton);
}


void cx::ui::NewGame::registerWidgets()
{
    // Game section:
    m_mainLayout.insert_next_to(m_gameSectionLayout, Gtk::PositionType::POS_TOP);
    m_mainLayout.attach_next_to(m_gameSectionTitle, m_gameSectionLayout, Gtk::PositionType::POS_TOP, cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_gameSectionLayout.attach(m_inARowValueLabel,           0, 0, cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_gameSectionLayout.attach(m_inARowValueEntry,           1, 0, cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);

    // Game board section:
    m_mainLayout.insert_next_to(m_gameBoardSectionLayout, Gtk::PositionType::POS_TOP);
    m_mainLayout.attach_next_to(m_gameBoardSectionTitle, m_gameBoardSectionLayout, Gtk::PositionType::POS_TOP, cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_gameBoardSectionLayout.attach(m_nbRowsLabel,           0, 0, cxgui::GridWidth::ONE_COLUMN,  cxgui::GridHeight::ONE_ROW);
    m_gameBoardSectionLayout.attach(m_nbRowsEntry,           1, 0, cxgui::GridWidth::ONE_COLUMN,  cxgui::GridHeight::ONE_ROW);
    m_gameBoardSectionLayout.attach(m_nbColumnsLabel,        0, 1, cxgui::GridWidth::ONE_COLUMN,  cxgui::GridHeight::ONE_ROW);
    m_gameBoardSectionLayout.attach(m_nbColumnsEntry,        1, 1, cxgui::GridWidth::ONE_COLUMN,  cxgui::GridHeight::ONE_ROW);

    // Players section:
    m_mainLayout.insert_next_to(m_playersSectionLayout, Gtk::PositionType::POS_TOP);
    m_mainLayout.attach_next_to(m_playersSectionTitle, m_playersSectionLayout, Gtk::PositionType::POS_TOP, cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_playersSectionLayout.attach(m_playersTable,            0, 0, cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);
    m_playersSectionLayout.attach(m_addPlayerButtonLayout,   0, 1, cxgui::GridWidth::ONE_COLUMN, cxgui::GridHeight::ONE_ROW);

    // Start game:
    m_startGameSectionLayout.pack_start(m_startButton);
}


void cx::ui::NewGame::configureLayoutsAndWidgets()
{
    const int spacing{15};

    m_mainLayout.set_border_width(spacing);

    m_inARowValueLabel.set_halign(Gtk::Align::ALIGN_START);
    m_nbRowsLabel.set_halign(Gtk::Align::ALIGN_START);
    m_nbColumnsEntry.set_halign(Gtk::Align::ALIGN_START);

    // Make sure that EditBoxes are not too wide, and do not expand horizontally:
    m_inARowValueEntry.set_max_width_chars(8);
    m_inARowValueEntry.set_width_chars(8);
    m_inARowValueEntry.set_margin_left(4* spacing);

    m_nbRowsEntry.set_max_width_chars(8);
    m_nbRowsEntry.set_width_chars(8);
    m_nbRowsEntry.set_margin_left(3* spacing);

    m_nbColumnsEntry.set_max_width_chars(8);
    m_nbColumnsEntry.set_width_chars(8);
    m_nbColumnsEntry.set_margin_left(3* spacing);

    m_addPlayerButtonLayout.set_layout(Gtk::BUTTONBOX_END);
    m_addPlayerButtonLayout.set_hexpand(true); // Otherwise the main layout does not expand horizontally.

    m_startGameSectionLayout.set_layout(Gtk::BUTTONBOX_END);
    m_startGameSectionLayout.set_margin_top(spacing);
}
