#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <peel/GLib/functions.h>

#include <peel/Adw/Application.h>
#include <peel/Adw/Window.h>
#include <peel/Adw/ToolbarView.h>
#include <peel/Adw/HeaderBar.h>
#include <peel/Adw/WindowTitle.h>
#include <peel/Adw/ViewStack.h>
#include <peel/Adw/ViewStackPage.h>
#include <peel/Adw/ViewSwitcherBar.h>

#include <peel/Shumate/SimpleMap.h>

#include <peel/class.h>
#include <peel/RefPtr.h>

#include <peel/Gtk/Label.h>

using namespace peel;

class MainWindow : public Adw::Window {
    PEEL_SIMPLE_CLASS(MainWindow, Adw::Window)

    public:
        static RefPtr<MainWindow> create(Gtk::Application * app);

        RefPtr<Adw::ToolbarView> toolbar_view;

        RefPtr<Adw::HeaderBar> header;
        RefPtr<Adw::WindowTitle> title;

        RefPtr<Adw::ViewStack> stack_view;
        RefPtr<Adw::ViewSwitcherBar> stack_switcher;

        RefPtr<Shumate::SimpleMap> map;

    private:
        void init(Class *);
};

#endif // MAIN_WINDOW_HPP