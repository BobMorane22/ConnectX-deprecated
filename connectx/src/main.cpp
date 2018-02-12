#include <gtkmm/main.h>
#include <gtkmm/window.h>

#include <cxgui/include/Disc.h>

int main(int argc, char* argv[])
{
    Gtk::Main app(argc, argv);

    Gtk::Window w;
    cxgui::Disc disc{cxutil::Color::red(),
                     cxutil::Color::yellow(),
                     true,
                     cxutil::Color::green(),
                     0.02,
                     cxgui::BorderStyle::SOLID};

    w.add(disc);
    w.show_all();

    Gtk::Main::run(w);

    return 0;
}

