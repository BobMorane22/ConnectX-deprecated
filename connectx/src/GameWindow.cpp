#include "GameWindow.h"

GameWindow::GameWindow()
{
    // Window setup:
    set_title("Connect X");
    set_icon_from_file("./connectx/img/icons/cxicon16.png");
    set_position(Gtk::WIN_POS_CENTER);

    // Layouts registration:
    registerLayouts();

    // Widgets registration:
    registerWidgets();

    // Layout and Widgets look:
    configureLayoutsAndWidgets();

    // Display all widgets:
    show_all();
}


GameWindow::~GameWindow()
{
}


void GameWindow::registerLayouts()
{
    // Window main layout:
    add(m_mainLayout);

    // Principal section layouts used in this window:
    m_mainLayout.pack_start(m_gameInfoLayout);
    m_mainLayout.pack_start(m_gameBoardLayout);

    // Game information layout:
    m_gameInfoLayout.pack_start(m_gameInfoDataLayout);
    m_gameInfoLayout.pack_start(m_activePlayerInfoLayout);
    m_gameInfoLayout.pack_start(m_nextPlayerInfoLayout);
    m_gameInfoLayout.pack_start(m_inARowInfoLayout);
    m_gameInfoLayout.pack_start(m_nbMovesLeftInfoLayout);

    // Game board layout:
    m_gameBoardLayout.pack_start(m_nextDiscAreaLayout);
    m_gameBoardLayout.pack_start(m_gameBoardGridLayout);
    m_gameBoardLayout.pack_start(m_reinitializeLayout);
}


void GameWindow::registerWidgets()
{
    // Game information section:
    m_gameInfoDataLayout.pack_start(m_gameInfoSection);

    m_activePlayerInfoLayout.pack_start(m_activePlayer);
    m_activePlayerInfoLayout.pack_start(m_activePlayerName);
    m_activePlayerInfoLayout.pack_start(m_activePlayerColor);

    m_nextPlayerInfoLayout.pack_start(m_nextPlayer);
    m_nextPlayerInfoLayout.pack_start(m_nextPlayerName);
    m_nextPlayerInfoLayout.pack_start(m_nextPlayerColor);

    m_inARowInfoLayout.pack_start(m_inARowValue);
    m_inARowInfoLayout.pack_start(m_inARowValueNumber);

    m_nbMovesLeftInfoLayout.pack_start(m_nbMovesLeft);
    m_nbMovesLeftInfoLayout.pack_start(m_nbMovesLeftNumber);

    // Game board section:
    for(int i{0}; i < 7; ++i)
    {
        Gtk::Button* btn = new Gtk::Button("Jeton");
        m_nextDiscAreaLayout.pack_start(*btn);
    }

    for(int rowNb{0}; rowNb < 6; ++rowNb)
    {
        for(int colNb{0}; colNb < 7; ++colNb)
        {
            Gtk::Button* btn = new Gtk::Button("Jeton");
            m_gameBoardGridLayout.attach(*btn, colNb, rowNb, 1, 1);
        }
    }

    m_reinitializeLayout.pack_start(m_reinitialize);
}


void GameWindow::configureLayoutsAndWidgets()
{
    m_reinitializeLayout.set_layout(Gtk::BUTTONBOX_END);
}
