#include <gtkmm/main.h>

#include "GameWindow.h"

int main(int argc, char* argv[])
{
    Gtk::Main app(argc, argv);

    // Main window creation:
    GameWindow mainWindow;

    // Main loop:
    Gtk::Main::run(mainWindow);

    return 0;
}

