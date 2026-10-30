#include "main_window.hpp"

PEEL_CLASS_IMPL(MainWindow, "MainWindow", Adw::Window)

void MainWindow::Class::init() {
    install_action("win.about", nullptr, [](Gtk::Widget *widget, const char *, GLib::Variant *) {
        widget -> cast<MainWindow>() -> action_about(nullptr, nullptr);
    });

    install_action("win.settings", nullptr, [](Gtk::Widget *widget, const char *, GLib::Variant *) {
        widget -> cast<MainWindow>() -> action_settings_window(nullptr, nullptr);
    });
}

RefPtr<MainWindow> MainWindow::create(Gtk::Application * app) {
    return Object::create<MainWindow>(prop_application(), app);
}

void MainWindow::init(Class *) {
    // Creating UI

    // Toolbar view

    toolbar_view = Adw::ToolbarView::create();

    // Split view

    split_view = Adw::OverlaySplitView::create();

    // Header bar

    header_bar = Adw::HeaderBar::create();

    // Sidebar button

    RefPtr<Gtk::ToggleButton> sidebar_button = Gtk::ToggleButton::create();

    sidebar_button -> set_icon_name("sidebar-show-symbolic");

    header_bar -> pack_start(sidebar_button);

    // Right top menu

    RefPtr<Gio::Menu> model_menu = Gio::Menu::create();

    model_menu -> append(_("Settings"), "win.settings");
    model_menu -> append(_("About"), "win.about");

    FloatPtr<Gtk::PopoverMenu> popover_menu = Gtk::PopoverMenu::create_from_model(model_menu);

    FloatPtr<Gtk::MenuButton> menu_button = Gtk::MenuButton::create();

    menu_button -> set_popover(std::move(popover_menu));
    menu_button -> set_icon_name("open-menu-symbolic");
    menu_button -> set_tooltip_text(_("Menu"));
    menu_button -> set_focus_on_click(false);

    header_bar -> pack_end(std::move(menu_button));

    // Map

    map = Shumate::SimpleMap::create();
    RefPtr<Shumate::TileDownloader> tile_downloader = Shumate::TileDownloader::create("https://tile.openstreetmap.org/{z}/{x}/{y}.png");
    RefPtr<Shumate::RasterRenderer> map_source = Shumate::RasterRenderer::create(tile_downloader);
    map -> set_map_source(map_source);
    
    // Packing the UI up

    set_default_size(800, 600);
    set_content(toolbar_view);

    toolbar_view -> set_content(split_view);
    toolbar_view -> add_top_bar(header_bar);

    split_view -> set_content(map);

    // Binding properties

    peel::GObject::Object::bind_property(split_view, split_view -> prop_show_sidebar(), sidebar_button, sidebar_button -> prop_active(), peel::GObject::BindingFlags::BIDIRECTIONAL | peel::GObject::BindingFlags::SYNC_CREATE);
}

void MainWindow::action_settings_window(Gio::SimpleAction *, GLib::Variant *) {
    RefPtr<SettingsWindow> settings_window = SettingsWindow::create();

    settings_window -> present(this);
}

void MainWindow::action_about(Gio::SimpleAction *, GLib::Variant *) {
    RefPtr<Adw::AboutDialog> about_window = AboutWindow::create(this);

    about_window -> present(this);
}