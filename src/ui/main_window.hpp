#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP


#include <peel/Adw/Application.h>
#include <peel/Adw/Window.h>
#include <peel/Adw/HeaderBar.h>
#include <peel/Gtk/Label.h>
#include <peel/class.h>
#include <peel/RefPtr.h>

using namespace peel;

class MainWindow : public Adw::Window {
    PEEL_SIMPLE_CLASS(MainWindow, Adw::Window)

    public:
        static RefPtr<MainWindow> create(Adw::Application * app);

        RefPtr<Adw::HeaderBar> header;

    private:
        void init();
};

#endif // MAIN_WINDOW_HPP