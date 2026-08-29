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
    set_default_size(800, 600);

    // Toolbar view
    toolbar_view = Adw::ToolbarView::create();

    set_content(toolbar_view);

    // Split view

    outer_split_view = Adw::OverlaySplitView::create();
    outer_split_view -> set_show_sidebar(true);
    outer_split_view -> set_min_sidebar_width(40);
    outer_split_view -> set_max_sidebar_width(60);

    toolbar_view -> set_content(outer_split_view);

    // Outer split

    nav_rail_box = Gtk::Box::create(Gtk::Orientation::VERTICAL, 15);

    outer_split_view -> set_sidebar(nav_rail_box);

    inner_split_view = Adw::OverlaySplitView::create();

    outer_split_view -> set_content(inner_split_view);

    // Inner split

    nav_menu_box = Gtk::Box::create(Gtk::Orientation::VERTICAL, 15);

    inner_split_view -> set_sidebar(nav_menu_box);

    // Header bar

    header = Adw::HeaderBar::create();

    toolbar_view -> add_top_bar(header);

    // Sidebar switch

    RefPtr<Gtk::ToggleButton> sidebar_button = Gtk::ToggleButton::create();

    sidebar_button -> set_icon_name("sidebar-show-symbolic");
    
    peel::GObject::Object::bind_property(inner_split_view, inner_split_view -> prop_show_sidebar(), sidebar_button, sidebar_button -> prop_active(), peel::GObject::BindingFlags::BIDIRECTIONAL | peel::GObject::BindingFlags::SYNC_CREATE);

    header -> pack_start(sidebar_button);

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

    header -> pack_end(std::move(menu_button));

    // Map

    map = Shumate::SimpleMap::create();

    RefPtr<Shumate::TileDownloader> tile_downloader = Shumate::TileDownloader::create("https://tile.openstreetmap.org/{z}/{x}/{y}.png");

    RefPtr<Shumate::RasterRenderer> map_source = Shumate::RasterRenderer::create(tile_downloader);

    map -> set_map_source(map_source);

    inner_split_view -> set_content(map);
}

void MainWindow::action_settings_window(Gio::SimpleAction *, GLib::Variant *) {
    // PreferencesDialog configuration is done in src/ui/settings_window.cpp

    RefPtr<Adw::PreferencesDialog> preferences_dialog = UI::CreatePreferencesDialog();

    preferences_dialog -> present(this);
}

void MainWindow::action_about(Gio::SimpleAction *, GLib::Variant *) {
    // AboutDialog configuration is done in src/ui/about_window.cpp

    RefPtr<Adw::AboutDialog> about_dialog = UI::CreateAboutDialog(this);

    about_dialog -> present(this);
}