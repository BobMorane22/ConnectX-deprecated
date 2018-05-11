#include <memory>

#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/label.h>
#include <gtkmm/grid.h>
#include <gtkmm/applicationwindow.h>

#include <cxbase/include/Game.h>
#include <cxgui/include/SectionTitle.h>

#include "GameBoard.h"


namespace cx
{

namespace ui
{

class GameWindow : public Gtk::ApplicationWindow
{

public:

///@{ @name Object Construction and Destruction

    GameWindow();
    //GameWindow(const std::shared_ptr<cxbase::Game>& p_game);
    virtual ~GameWindow() override;

///@}

    //bool connect(const std::shared_ptr<cxbase::Game>& p_game);

private:

///@{ @name Layout Configuration

    void registerLayouts();
    void registerWidgets();
    void configureLayoutsAndWidgets();

///@}


///@{ @name Data members:

    // Widget layouts:
    Gtk::Grid       m_mainLayout;                 ///< Contains all window sub-layouts.

    Gtk::Grid       m_gameInfoLayout;             ///< Contains all widgets in
                                                  ///< the 'Game information' section.
                                                  ///<

    Gtk::Grid       m_gameBoardLayout;            ///< Contains all widgets in the
                                                  ///< 'Game board' section.
                                                  ///<

    Gtk::HButtonBox m_reinitializeLayout;         ///< Layout for the 'Reinitialize' button.

    // Visible widgets:
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
    cx::ui::GameBoard   m_gameBoard                  {std::make_shared<cxbase::GameBoard>()};

    Gtk::Button     m_reinitialize               {"Reinitialize"         };

///@}

};

} // namespace ui

} // namespace cx
