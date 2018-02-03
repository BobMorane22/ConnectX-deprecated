#include <gtkmm/main.h>
#include <gtkmm/window.h>

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    Gtk::Main app(argc, argv);

    Gtk::Window w;

    Gtk::Main::run(w);

    return 0;
}

