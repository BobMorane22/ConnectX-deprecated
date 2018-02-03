#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/frame.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>
#include <gtkmm/grid.h>
#include <gtkmm/window.h>

class GameWindow : public Gtk::Window
{
public:
    GameWindow();
    virtual ~GameWindow();

private:

    void registerLayouts();
    void registerWidgets();
    void configureLayoutsAndWidgets();

///@{ @name Data members:

    // Layouts:
    Gtk::VBox       m_mainLayout;             ///< Contains all window widgets.

    Gtk::VBox       m_gameInfoLayout{"Game information"};         ///< Contains all widgets in the 'Game information' section.
    Gtk::HBox       m_gameInfoDataLayout;
    Gtk::HBox       m_activePlayerInfoLayout;
    Gtk::HBox       m_nextPlayerInfoLayout;
    Gtk::HBox       m_inARowInfoLayout;
    Gtk::HBox       m_nbMovesLeftInfoLayout;

    Gtk::VBox       m_gameBoardLayout{"Game board"};        ///< Contains all widgets in the 'Game board' section.
    Gtk::HBox       m_nextDiscAreaLayout;
    Gtk::Grid       m_gameBoardGridLayout;
    Gtk::HButtonBox m_reinitializeLayout;

    // Widgets:
    Gtk::Label      m_gameInfoSection  {"Game information:"};
    Gtk::Label      m_activePlayer     {"Active player:"};
    Gtk::Label      m_activePlayerName {"John Doe"};
    Gtk::Label      m_activePlayerColor{"Orange"};
    Gtk::Label      m_nextPlayer       {"Next player:"};
    Gtk::Label      m_nextPlayerName   {"Jane Hardy"};
    Gtk::Label      m_nextPlayerColor  {"Red"};
    Gtk::Label      m_inARowValue      {"In-a-row value:"};
    Gtk::Label      m_inARowValueNumber{"4"};
    Gtk::Label      m_nbMovesLeft      {"Number of moves left:"};
    Gtk::Label      m_nbMovesLeftNumber{"21"};
    Gtk::Button     m_reinitialize     {"Reinitialize"};

///@}
};
