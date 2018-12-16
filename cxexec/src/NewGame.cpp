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

#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>

#include <gdk/gdkkeysyms.h>

#include <cxutil/include/Assertion.h>
#include <cxutil/include/narrow_cast.h>
#include <cxutil/include/util.h>
#include <cxgui/include/enums.h>
#include <cxgui/include/util.h>

#include "../include/MessageBox.h"
#include "../include/NewGame.h"

namespace
{

enum
{
    GAME,
    GAME_BOARD,
    PLAYERS,
    START_GAME,
};

// https://developer.gnome.org/gtkmm-tutorial/stable/sec-keyboardevents-propagation.html.en
const bool STOP_EVENT_PROPAGATION {true};
const bool ALLOW_EVENT_PROPAGATION{false};

const std::size_t NB_MIN_PLAYERS{2};
const std::size_t NB_MAX_PLAYERS{10};

const std::size_t NB_ROWS_MIN       {6};
const std::size_t NB_ROWS_MAX       {64};
const std::size_t NB_COLUMNS_MIN    {7};
const std::size_t NB_COLUMNS_MAX    {64};

const std::size_t IN_A_ROW_VALUE_MIN{2};


/***********************************************************************************************//**
 * @brief
 *
 * <Description>
 *
 * @return
 *
 **************************************************************************************************/
cxgui::dlg::ResponseType tooManyPlayersToAddMsg(cx::ui::NewGame& p_parent)
{
    std::ostringstream primaryMsg;

    primaryMsg << "You cannot register more than " << NB_MAX_PLAYERS << " players.";
    
    // Show message:
    cx::ui::MessageBox msgBox{p_parent,
                              cxgui::dlg::MessageType::INFORMATION,
                              primaryMsg.str(),
                              "You can unregister players by selecting rows and pressing the DEL key.",
                              true};

    return msgBox.invoke();
}


/***********************************************************************************************//**
 * @brief
 *
 * <Description>
 *
 * @return
 *
 **************************************************************************************************/
cxgui::dlg::ResponseType tooFewPlayersToUnregisterMsg(cx::ui::NewGame& p_parent)
{
    // Only the minimum amount of players are left, we can proceed. We warn the user:
    cx::ui::MessageBox msgBox{p_parent,
                              cxgui::dlg::MessageType::INFORMATION,
                              6,
                              true};

    return msgBox.invoke();
}


/***********************************************************************************************//**
 * @brief
 *
 * <Description>
 *
 * @param
 *
 * @return
 *
 **************************************************************************************************/
cxgui::dlg::ResponseType invalidEditBoxContentMsg(cx::ui::NewGame& p_parent, const std::string p_invalidContent)
{
    std::ostringstream primaryMsg;
    std::ostringstream secondaryMsg;
    
    if(p_invalidContent.empty())
    {
        primaryMsg   << "You must specify all parameters.";
    }
    else
    {
        primaryMsg << p_invalidContent << " is not a valid integer number.";
    }

    secondaryMsg << "Enter a valid positive integer value.";

    // Show message:
    cx::ui::MessageBox msgBox{p_parent,
                              cxgui::dlg::MessageType::INFORMATION,
                              primaryMsg.str(),
                              secondaryMsg.str(),
                              true};

    return msgBox.invoke();
}


/***********************************************************************************************//**
 * @brief
 *
 * <Description>
 *
 * @return
 *
 **************************************************************************************************/
cxgui::dlg::ResponseType invalidInARowValueMsg(cx::ui::NewGame& p_parent, std::size_t p_inARowValueMax)
{
    std::ostringstream primaryMsg;
    std::ostringstream secondaryMsg;

    primaryMsg   << "In-a-row value is not valid.";
    secondaryMsg << "Minimum is 3, maximum is " << p_inARowValueMax << ".";

    // Show message:
    cx::ui::MessageBox msgBox{p_parent,
                              cxgui::dlg::MessageType::INFORMATION,
                              primaryMsg.str(),
                              secondaryMsg.str(),
                              true};

    return msgBox.invoke();
}


/***********************************************************************************************//**
 * @brief
 *
 * <Description>
 *
 * @return
 *
 **************************************************************************************************/
cxgui::dlg::ResponseType invalidGameBoardDimensionsMsg(cx::ui::NewGame& p_parent)
{
    std::ostringstream primaryMsg;

    primaryMsg << "Game board dimensions are not valid.";
    
    // Show message:
    cx::ui::MessageBox msgBox{p_parent,
                              cxgui::dlg::MessageType::INFORMATION,
                              primaryMsg.str(),
                              "Minimum dimensions are 6x7, maximum are 64x64.",
                              true};

    return msgBox.invoke();
}


/*******************************************************************************************//**
 * @brief
 *
 * <Description>
 *
 *
 * @param
 * @param
 *
 * @pre
 * @pre
 * @post
 * @post
 *
 * @return
 *
 * @note
 *
 * @see
 *
 **********************************************************************************************/
cxgui::dlg::ResponseType twoSameColorMsg(cx::ui::NewGame& p_parent)
{
    std::ostringstream primaryMsg;
    std::ostringstream secondaryMsg;

    primaryMsg   << "Two or more players cannot share the same disc color.";
    secondaryMsg << "Please choose a different color for every player.";

    // Show message:
    cx::ui::MessageBox msgBox{p_parent,
                              cxgui::dlg::MessageType::INFORMATION,
                              primaryMsg.str(),
                              secondaryMsg.str(),
                              true};

    return msgBox.invoke();
}


} // unnamed namespace


cx::ui::NewGame::NewGame()
{
    // Add keyboard events:
    add_events(Gdk::KEY_PRESS_MASK);

    // Display all widgets:
    show_all();
}


cx::ui::NewGame::~NewGame() = default;


void cx::ui::NewGame::configureWindow()
{
    set_title("New game");
    set_position(Gtk::WIN_POS_CENTER);
}


void cx::ui::NewGame::registerLayouts()
{
    using namespace cxgui;

    // Principal sub-layouts used in this window:
    m_mainLayout.attach(m_gameSectionLayout,      0, GAME,       GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);
    m_mainLayout.attach(m_gameBoardSectionLayout, 0, GAME_BOARD, GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);
    m_mainLayout.attach(m_playersSectionLayout,   0, PLAYERS,    GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);
    m_mainLayout.attach(m_startGameSectionLayout, 0, START_GAME, GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);

    // Special sub-layout for the "Add player..." button:
    m_addPlayerButtonLayout.pack_start(m_addPlayerButton);
}


void cx::ui::NewGame::registerWidgets()
{
    using namespace cxgui;

    // Game section:
    m_mainLayout.insert_next_to(m_gameSectionLayout, Gtk::PositionType::POS_TOP);
    m_mainLayout.attach_next_to(m_gameSectionTitle, m_gameSectionLayout, Gtk::PositionType::POS_TOP, GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);

    m_gameSectionLayout.attach(m_inARowValueLabel, 0, 0, GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);
    m_gameSectionLayout.attach(m_inARowValueEntry, 1, 0, GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);

    // Game board section:
    m_mainLayout.insert_next_to(m_gameBoardSectionLayout, Gtk::PositionType::POS_TOP);
    m_mainLayout.attach_next_to(m_gameBoardSectionTitle, m_gameBoardSectionLayout, Gtk::PositionType::POS_TOP, GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);

    m_gameBoardSectionLayout.attach(m_nbRowsLabel,    0, 0, GridWidth::ONE_COLUMN,  GridHeight::ONE_ROW);
    m_gameBoardSectionLayout.attach(m_nbRowsEntry,    1, 0, GridWidth::ONE_COLUMN,  GridHeight::ONE_ROW);
    m_gameBoardSectionLayout.attach(m_nbColumnsLabel, 0, 1, GridWidth::ONE_COLUMN,  GridHeight::ONE_ROW);
    m_gameBoardSectionLayout.attach(m_nbColumnsEntry, 1, 1, GridWidth::ONE_COLUMN,  GridHeight::ONE_ROW);

    // Players section:
    m_mainLayout.insert_next_to(m_playersSectionLayout, Gtk::PositionType::POS_TOP);
    m_mainLayout.attach_next_to(m_playersSectionTitle, m_playersSectionLayout, Gtk::PositionType::POS_TOP, GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);

    m_playersSectionLayout.attach(m_playersTable,          0, 0, GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);
    m_playersSectionLayout.attach(m_addPlayerButtonLayout, 0, 1, GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);

    // Start game:
    m_startGameSectionLayout.pack_start(m_startButton);
}


void cx::ui::NewGame::configureLayouts()
{
    m_mainLayout.set_border_width(m_spacing);

    m_addPlayerButtonLayout.set_layout(Gtk::BUTTONBOX_END);
    m_addPlayerButtonLayout.set_hexpand(true);

    m_startGameSectionLayout.set_layout(Gtk::BUTTONBOX_END);
    m_addPlayerButtonLayout.set_hexpand(true);
    m_startGameSectionLayout.set_margin_top(m_spacing);
}


void cx::ui::NewGame::configureWidgets()
{
    // Make sure labels are aligned left:
    m_inARowValueLabel.set_halign(Gtk::Align::ALIGN_START);
    m_nbRowsLabel.set_halign(Gtk::Align::ALIGN_START);

    // Add some space between label and edit boxes:
    m_inARowValueLabel.set_margin_right(m_spacing);
    m_nbRowsLabel.set_margin_right(m_spacing);
    m_nbColumnsLabel.set_margin_right(m_spacing);

    // Make sure comboboxes are scalling with the window:
    m_inARowValueEntry.set_hexpand(true);
    m_nbRowsEntry.set_hexpand(true);
    m_nbColumnsEntry.set_hexpand(true);

    // The player list should scale as well:
    m_playersTable.set_hexpand(true);
    
    // Leave some space between the list and the buttons:
    m_playersTable.set_margin_bottom(m_spacing);

    // Allow multiple item selection:
    m_playersTable.set_selection_mode(Gtk::SELECTION_MULTIPLE);
}


void cx::ui::NewGame::configureSignalHandlers()
{
    // Button handlers:
    m_addPlayerButton.signal_clicked().connect([this](){onAddPlayersBtnClicked();} );
    m_startButton    .signal_clicked().connect([this](){onStartBtnClicked();}      );
}


/*******************************************************************************************//**
 * @brief
 *
 * <Description>
 *
 * @note
 *
 * @see
 *
 **********************************************************************************************/
void cx::ui::NewGame::onAddPlayersBtnClicked()
{
    const std::size_t currentNbPlayers{m_playersTable.size()};

    if(currentNbPlayers >= NB_MIN_PLAYERS && currentNbPlayers < NB_MAX_PLAYERS)
    {
        const std::size_t newRowIndex{m_playersTable.size() + 1};

        // We construct the new name:
        std::ostringstream newPlayerName;
        newPlayerName << "-- Player " << newRowIndex << " --";

        // Now, we need a color. We use yellow:
        const cxutil::Color newPlayerColor{cxutil::Color::yellow()};

        // We add the player:
        CX_ASSERT(m_playersTable.addRow(newPlayerName.str(), newPlayerColor).isOk());

        // resize window:
        m_playersTable.show_all();
    }
    else if(currentNbPlayers == NB_MAX_PLAYERS)
    {
        tooManyPlayersToAddMsg(*this);
    }
    else
    {
        CX_ASSERT_MSG(currentNbPlayers >= NB_MIN_PLAYERS, "Not enough players. There should always be at least two.");
    }
}


/*******************************************************************************************//**
 * @brief Handler for the @c DEL key.
 *
 * Handles the removal of players from the list when the @c DEL key is pressed.
 *
 **********************************************************************************************/
void cx::ui::NewGame::onRemovePlayerKeyPressed()
{
    std::vector< Gtk::ListBoxRow* > playersToRemove{m_playersTable.get_selected_rows()};

    if(playersToRemove.size() == 0)
    {
        // No rows have been selected: nothing to do.
        return;
    }

    CX_ASSERT(std::none_of(std::begin(playersToRemove),
                           std::end(playersToRemove),
                           [](const Gtk::ListBoxRow* p_player)
                           {
                               return p_player == nullptr;
                           }));

    const std::size_t currentNbPlayers{m_playersTable.size()};

    if(currentNbPlayers > NB_MIN_PLAYERS &&
       currentNbPlayers <= NB_MAX_PLAYERS &&
       m_playersTable.size() - playersToRemove.size() >= 2)
    {
        // Ok, we can proceed with the operation:
        for(Gtk::ListBoxRow* player : playersToRemove)
        {
            cx::ui::NewPlayerRow* newPlayer{cxutil::narrow_cast<cx::ui::NewPlayerRow*>(player)};

            cxutil::ReturnCode returnCode{m_playersTable.removeRow(newPlayer->playerName(),
                                                                   newPlayer->playerDiscColor())};

            CX_ASSERT_MSG(returnCode.isOk(), "An error occured while removing a player.");
        }

        // First, get the preferred heights values:
        int minimumHeight, naturalHeight;
        get_preferred_height(minimumHeight, naturalHeight);

        // Then make a size request using the minimum height. Notice the '20'
        // that is removed. This was added to make sure Gtkmm did not leave any
        // extra blank space by resizing smaller than the minimum value:
        set_size_request(get_width(), minimumHeight - 20);

        // Then resize accordinly:
        resize(get_width(), naturalHeight);

        show_all();

        return;
    }
    else if(currentNbPlayers == NB_MIN_PLAYERS ||
            m_playersTable.size() - playersToRemove.size() < 2)
    {
        tooFewPlayersToUnregisterMsg(*this);
    }
    else
    {
        CX_ASSERT_MSG(false, "You have exceeded the maximum player amount for the Connect X game.");
    }
}


/*******************************************************************************************//**
 * @brief Handler for the start button.
 *
 * Handle the start of the game. This is where all the fields are validated.
 *
 **********************************************************************************************/
void cx::ui::NewGame::onStartBtnClicked()
{
    // Get the edit box information:
    std::size_t inARowValue, nbRows, nbColumns;

    try
    {
        inARowValue = cxutil::narrow_cast<std::size_t>(std::stoi(m_inARowValueEntry.get_text()));
    }
    catch(std::exception& p_exception)
    {
        invalidEditBoxContentMsg(*this, m_inARowValueEntry.get_text());

        return;
    }

    try
    {
        nbRows = cxutil::narrow_cast<std::size_t>(std::stoi(m_nbRowsEntry.get_text()));
    }
    catch(std::exception& p_exception)
    {
        invalidEditBoxContentMsg(*this, m_nbRowsEntry.get_text());

        return;
    }

    try
    {
        nbColumns = cxutil::narrow_cast<std::size_t>(std::stoi(m_nbColumnsEntry.get_text()));
    }
    catch(std::exception& p_exception)
    {
        invalidEditBoxContentMsg(*this, m_nbColumnsEntry.get_text());

        return;
    }

    // Validate the In-a-row value:
    const std::size_t inARowValueMax{std::min(nbRows, nbColumns)};
    const bool inARowValueIsValid{inARowValue >= IN_A_ROW_VALUE_MIN &&
                                  inARowValue < inARowValueMax + 1};

    if(!inARowValueIsValid)
    {
        invalidInARowValueMsg(*this, inARowValueMax);

        return;
    }

    // Validate the game board dimentsions:
    const bool gameBoardDimensionsAreValid{nbRows >= NB_ROWS_MIN          &&
                                           nbRows < NB_ROWS_MAX + 1       &&
                                           nbColumns >= NB_COLUMNS_MIN    &&
                                           nbColumns < NB_COLUMNS_MAX + 1};

    if(!gameBoardDimensionsAreValid)
    {
        invalidGameBoardDimensionsMsg(*this);

        return;
    }

    // Validate the player list. No same color should be used twice:
    const std::vector<cxutil::Color> colors{m_playersTable.rowColors()};
    for(auto& color : m_playersTable.rowColors())
    {
        const long int colorOccurences{std::count_if(colors.cbegin(),
                                                     colors.cend(),
                                                     [color](const cxutil::Color& p_color)
                                                     {
                                                         return color == p_color;
                                                     })};

        if(colorOccurences > 1)
        {
            twoSameColorMsg(*this);

            return;
        }
    }

    // Everything is valid, the game can be started:
    std::cout << "Game started!" << std::endl;
}


/*******************************************************************************************//**
 * @brief Default key pressed signal handler.
 *
 * This handler must be overriden to allow key evens to be caught.
 *
 * @return @c true to stop other handlers from being invoked for the event. @c false to
 *         propagate the event further.
 *
 **********************************************************************************************/
bool cx::ui::NewGame::on_key_press_event(GdkEventKey* p_event)
{
    if(p_event->keyval == GDK_KEY_Delete)
    {
        onRemovePlayerKeyPressed();

        return STOP_EVENT_PROPAGATION;
    }

    // Call base class handler (to get the normal behaviour):
    return Gtk::Window::on_key_release_event(p_event);
}
