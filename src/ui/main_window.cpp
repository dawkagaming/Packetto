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

    // Bottom sheet

    this -> bottom_sheet = Adw::BottomSheet::create();

    this -> toolbar_view -> set_content(this -> bottom_sheet);

    // Split view

    this -> split_view = Adw::OverlaySplitView::create();
    this -> split_view -> set_show_sidebar(false);
    this -> split_view -> set_sidebar_width_fraction(25);

    this -> bottom_sheet -> set_content(this -> split_view);

    // Header bar and switcher

    this -> header = Adw::HeaderBar::create();

    this -> toolbar_view -> add_top_bar(this -> header);

    // Right top menu

    RefPtr<Gio::Menu> model_menu = Gio::Menu::create();

    model_menu -> append(_("Settings"), "win.settings");
    model_menu -> append(_("About"), "win.about");

    FloatPtr<Gtk::PopoverMenu> popover_menu = Gtk::PopoverMenu::create_from_model(model_menu);

    FloatPtr<Gtk::MenuButton> menu_button = Gtk::MenuButton::create();

    menu_button -> set_popover(std::move(popover_menu));
    menu_button -> set_icon_name("open-menu-symbolic");
    menu_button -> set_tooltip_text("Menu");
    menu_button -> set_focus_on_click(false);

    this -> header -> pack_end(std::move(menu_button));
    
    // Sidebar switch

    RefPtr<Gtk::ToggleButton> sidebar_button = Gtk::ToggleButton::create();

    sidebar_button -> set_icon_name("sidebar-show-symbolic");
    
    peel::GObject::Object::bind_property(split_view, split_view -> prop_show_sidebar(), sidebar_button, sidebar_button -> prop_active(), peel::GObject::BindingFlags::BIDIRECTIONAL | peel::GObject::BindingFlags::SYNC_CREATE);

    this -> header -> pack_start(sidebar_button);

    // Map

    this -> map = Shumate::SimpleMap::create();

    RefPtr<Shumate::TileDownloader> tile_downloader = Shumate::TileDownloader::create("https://tile.openstreetmap.org/{z}/{x}/{y}.png");

    RefPtr<Shumate::RasterRenderer> map_source = Shumate::RasterRenderer::create(tile_downloader);

    this -> map -> set_map_source(map_source);

    this -> split_view -> set_content(this -> map);
}

void MainWindow::action_settings_window(Gio::SimpleAction *, GLib::Variant *) {
    RefPtr<Adw::PreferencesDialog> preferences_dialog = Adw::PreferencesDialog::create();

    preferences_dialog -> present(this);
}

void MainWindow::action_about(Gio::SimpleAction *, GLib::Variant *) {
    RefPtr<Adw::AboutDialog> about_dialog = Adw::AboutDialog::create();

    about_dialog -> set_application_name(GLib::get_application_name());
    about_dialog -> set_application_icon("application-x-executable");
    about_dialog -> set_version(this -> get_application() -> get_version());
    about_dialog -> set_license_type(Gtk::License::APACHE_2_0);
    about_dialog -> set_comments(_("A simple APRS client, written in C++ and libadwaita."));
    about_dialog -> set_support_url("https://github.com/dawkagaming/Packetto/discussions");
    about_dialog -> set_issue_url("https://github.com/dawkagaming/Packetto/issues");
    about_dialog -> set_developer_name("Dawid Kulas");

    about_dialog -> present(this);
}