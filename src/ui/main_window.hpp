#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <peel/GLib/functions.h>

#include <peel/Gio/ActionMap.h>
#include <peel/Gio/SimpleAction.h>
#include <peel/Gio/Menu.h>

#include <peel/Gtk/MenuButton.h>
#include <peel/Gtk/ToggleButton.h>
#include <peel/Gtk/PopoverMenu.h>
#include <peel/Gtk/License.h>

#include <peel/Adw/Application.h>
#include <peel/Adw/Window.h>
#include <peel/Adw/ToolbarView.h>
#include <peel/Adw/HeaderBar.h>
#include <peel/Adw/WindowTitle.h>
#include <peel/Adw/OverlaySplitView.h>
#include <peel/Adw/ViewStack.h>
#include <peel/Adw/ViewStackPage.h>
#include <peel/Adw/ViewSwitcher.h>
#include <peel/Adw/AboutDialog.h>

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

        RefPtr<Adw::OverlaySplitView> split_view;
        RefPtr<Adw::ViewStack> stack_view;
        RefPtr<Adw::ViewSwitcher> stack_switcher;

        RefPtr<Shumate::SimpleMap> map;

    private:
        void init(Class *);

        void action_settings_window(Gio::SimpleAction *, GLib::Variant *);

        void action_about(Gio::SimpleAction *, GLib::Variant *);
};

#endif // MAIN_WINDOW_HPP