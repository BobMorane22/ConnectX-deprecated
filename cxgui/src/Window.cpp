#include "../include/Window.h"

#include <iostream>

cxgui::dlg::Window::Window()
{
    signal_realize().connect([this]()
                             {
                                 init();
                             });

    add(m_mainLayout);
}


cxgui::dlg::Window::~Window() = default;


/***************************************************************************************************
 * @brief Window initialisation.
 *
 * This method is automatically called when the @c Window::signal_realize is sent by the window,
 * i.e. when every data structure used by the window is constructed and ready for use. It is hence
 * called after construction of the window and is therefore not subject to the constructor
 * restriction to avoid virtual methods. You can call anything you want from here because you
 * have the guarantee the window is fully constructed.
 *
 * @note Many windows and dialogs may depend on this method, so be careful when modifying it.
 *       Run all the tests!
 *
 **************************************************************************************************/
void cxgui::dlg::Window::init()
{
    setWindowIcon();
    configureWindow();
    registerLayouts();
    registerWidgets();
    configureLayouts();
    configureWidgets();
}

