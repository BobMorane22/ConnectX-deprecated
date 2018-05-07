#include <iostream>

#include "../include/GameWindow.h"
#include "../include/util.h"

namespace
{

enum GridWidth
{
    ONE_COLUMN = 1,
    TWO_COLUMNS,
    THREE_COLUMNS,

};

enum GridHeight
{
    ONE_ROW = 1,
    TWO_ROWS,
    THREE_ROWS,
};

enum WindowSection
{
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

cx::ui::GameWindow::GameWindow()
{
    // Window setup:
    set_title("Connect X");

    std::string iconPath{currentExecutablePath()};
    iconPath.append("/icons/cxicon16.png");
    std::cout << iconPath << std::endl;

    set_icon_from_file(iconPath);
    set_position(Gtk::WIN_POS_CENTER);

    // Layouts registration:
    registerLayouts();

    // Widgets registration in layouts:
    registerWidgets();

    // Layout and Widgets look:
    configureLayoutsAndWidgets();

    // Display all widgets:
    show_all();
}


cx::ui::GameWindow::~GameWindow()
{
}


void cx::ui::GameWindow::registerLayouts()
{
    // Sets padding around the window edges. This cases the contained widgets not to
    // stick to the sides of the window, which is more elegant:
    set_border_width(15);

    // Window main layout:
    add(m_mainLayout);

    // Principal section layouts used in this window:
    m_mainLayout.attach(m_gameInfoLayout,     0, GAME_INFORMATION, GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);
    m_mainLayout.attach(m_gameBoardLayout,    0, GAME_BOARD,       GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);
    m_mainLayout.attach(m_reinitializeLayout, 0, REINITIALIZE,     GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);
}


void cx::ui::GameWindow::registerWidgets()
{
    // Game information section:
    m_gameInfoLayout.attach(m_gameInfoSection, TITLE,  GAME_INFORMATION_SECTION_TITLE, GridWidth::THREE_COLUMNS, GridHeight::ONE_ROW);

    m_gameInfoLayout.attach(m_activePlayer,      LABEL,          ACTIVE_PLAYER,      GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);
    m_gameInfoLayout.attach(m_activePlayerName,  PRIMARY_INFO,   ACTIVE_PLAYER,      GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);
    m_gameInfoLayout.attach(m_activePlayerColor, SECONDARY_INFO, ACTIVE_PLAYER,      GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);
    m_gameInfoLayout.attach(m_nextPlayer,        LABEL,          NEXT_PLAYER,        GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);
    m_gameInfoLayout.attach(m_nextPlayerName,    PRIMARY_INFO,   NEXT_PLAYER,        GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);
    m_gameInfoLayout.attach(m_nextPlayerColor,   SECONDARY_INFO, NEXT_PLAYER,        GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);
    m_gameInfoLayout.attach(m_inARowValue,       LABEL,          IN_A_ROW_VALUE,     GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);
    m_gameInfoLayout.attach(m_inARowValueNumber, PRIMARY_INFO,   IN_A_ROW_VALUE,     GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);
    m_gameInfoLayout.attach(m_nbMovesLeft,       LABEL,          NB_MOVES_REMAINING, GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);
    m_gameInfoLayout.attach(m_nbMovesLeftNumber, PRIMARY_INFO,   NB_MOVES_REMAINING, GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);

    // Game board section:
    m_gameBoardLayout.attach(m_gameBoard, 0, 0, GridWidth::ONE_COLUMN, GridHeight::ONE_ROW);

    // Reinitialize button section:
    m_reinitializeLayout.pack_start(m_reinitialize);
}


void cx::ui::GameWindow::configureLayoutsAndWidgets()
{
    const int spacing{15};

    m_mainLayout.set_hexpand();
    m_mainLayout.set_vexpand();
    m_mainLayout.set_row_spacing(spacing);

    // Game information section:

    // Game information section title should be in bold, markup must be enabled:
    m_gameInfoSection.set_use_markup(true);

    // Leave some space between the game information widgets:
    m_gameInfoLayout.set_column_spacing(spacing);

    // Disable expansion:
    m_gameInfoSection.set_hexpand(false);
    m_gameInfoSection.set_vexpand(false);

    // Left-align all the game information widgets:
    m_gameInfoSection  .set_alignment(Gtk::Align::ALIGN_START);
    m_activePlayer     .set_alignment(Gtk::Align::ALIGN_START);
    m_activePlayerName .set_alignment(Gtk::Align::ALIGN_START);
    m_activePlayerColor.set_alignment(Gtk::Align::ALIGN_START);
    m_nextPlayer       .set_alignment(Gtk::Align::ALIGN_START);
    m_nextPlayerName   .set_alignment(Gtk::Align::ALIGN_START);
    m_nextPlayerColor  .set_alignment(Gtk::Align::ALIGN_START);
    m_inARowValue      .set_alignment(Gtk::Align::ALIGN_START);
    m_inARowValueNumber.set_alignment(Gtk::Align::ALIGN_START);
    m_nbMovesLeft      .set_alignment(Gtk::Align::ALIGN_START);
    m_nbMovesLeftNumber.set_alignment(Gtk::Align::ALIGN_START);

    m_gameInfoSection  .set_vexpand(false);
    m_activePlayer     .set_vexpand(false);
    m_activePlayerName .set_vexpand(false);
    m_activePlayerColor.set_vexpand(false);
    m_nextPlayer       .set_vexpand(false);
    m_nextPlayerName   .set_vexpand(false);
    m_nextPlayerColor  .set_vexpand(false);
    m_inARowValue      .set_vexpand(false);
    m_inARowValueNumber.set_vexpand(false);
    m_nbMovesLeft      .set_vexpand(false);
    m_nbMovesLeftNumber.set_vexpand(false);


    // Game board section:
    m_gameBoard.set_hexpand();
    m_gameBoard.set_vexpand();

    m_gameBoardLayout.set_hexpand();
    m_gameBoardLayout.set_vexpand();

    // Reinitialize button section:

    // Button to the left:
    m_reinitializeLayout.set_layout(Gtk::BUTTONBOX_END);
}
