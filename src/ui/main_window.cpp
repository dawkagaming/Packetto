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
    this -> set_default_size(800, 600);

    // Toolbar view

    this -> toolbar_view = Adw::ToolbarView::create();

    this -> set_content(this -> toolbar_view);

    // Split view

    this -> outer_split_view = Adw::OverlaySplitView::create();
    this -> outer_split_view -> set_show_sidebar(true);
    this -> outer_split_view -> set_min_sidebar_width(40);
    this -> outer_split_view -> set_max_sidebar_width(60);

    this -> toolbar_view -> set_content(this -> outer_split_view);

    // Outer split

    this -> nav_rail_box = Gtk::Box::create(Gtk::Orientation::VERTICAL, 15);

    this -> outer_split_view -> set_sidebar(this -> nav_rail_box);

    this -> inner_split_view = Adw::OverlaySplitView::create();

    this -> outer_split_view -> set_content(this -> inner_split_view);

    // Inner split

    this -> nav_menu_box = Gtk::Box::create(Gtk::Orientation::VERTICAL, 15);

    this -> inner_split_view -> set_sidebar(this -> nav_menu_box);

    // Header bar

    this -> header = Adw::HeaderBar::create();

    this -> toolbar_view -> add_top_bar(this -> header);

    // Sidebar switch

    RefPtr<Gtk::ToggleButton> sidebar_button = Gtk::ToggleButton::create();

    sidebar_button -> set_icon_name("sidebar-show-symbolic");
    
    peel::GObject::Object::bind_property(this -> inner_split_view, this -> inner_split_view -> prop_show_sidebar(), sidebar_button, sidebar_button -> prop_active(), peel::GObject::BindingFlags::BIDIRECTIONAL | peel::GObject::BindingFlags::SYNC_CREATE);

    this -> header -> pack_start(sidebar_button);

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

    this -> header -> pack_end(std::move(menu_button));

    // Map

    this -> map = Shumate::SimpleMap::create();

    RefPtr<Shumate::TileDownloader> tile_downloader = Shumate::TileDownloader::create("https://tile.openstreetmap.org/{z}/{x}/{y}.png");

    RefPtr<Shumate::RasterRenderer> map_source = Shumate::RasterRenderer::create(tile_downloader);

    this -> map -> set_map_source(map_source);

    this -> inner_split_view -> set_content(this -> map);
}

void MainWindow::action_settings_window(Gio::SimpleAction *, GLib::Variant *) {
    RefPtr<Adw::PreferencesDialog> preferences_dialog = Adw::PreferencesDialog::create();

    preferences_dialog -> present(this);
}

void MainWindow::action_about(Gio::SimpleAction *, GLib::Variant *) {
    // AboutDialog configuration is done in src/ui/about_window.cpp

    RefPtr<Adw::AboutDialog> about_dialog = CreateAboutDialog(this);

    about_dialog -> present(this);
}