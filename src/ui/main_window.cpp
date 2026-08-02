#include "main_window.hpp"

PEEL_CLASS_IMPL(MainWindow, "MainWindow", Adw::Window)

void MainWindow::Class::init() {};

RefPtr<MainWindow> MainWindow::create(Gtk::Application * app) {
    return Object::create<MainWindow>(prop_application(), app);
}

void MainWindow::init(Class *) {
    this -> set_default_size(800, 600);

    this -> toolbar_view = Adw::ToolbarView::create();

    this -> set_content(this -> toolbar_view);

    // Header bar and title

    this -> header = Adw::HeaderBar::create();
    
    this -> title = Adw::WindowTitle::create(GLib::get_application_name(), "");

    this -> header -> set_title_widget(this -> title);

    this -> toolbar_view -> add_top_bar(this -> header);

    //

    this -> stack_view = Adw::ViewStack::create();

    this -> stack_switcher = Adw::ViewSwitcherBar::create();
    this -> stack_switcher -> set_stack(stack_view);
    this -> stack_switcher -> set_reveal(true);

    this -> toolbar_view -> set_content(this -> stack_view);

    this -> toolbar_view -> add_bottom_bar(this -> stack_switcher);

    // Map

    this -> map = Shumate::SimpleMap::create();

    this -> stack_view -> add_titled(this -> map, "Map", "Map");

    RefPtr<Gtk::Label> label = Gtk::Label::create("Text");

    this -> stack_view -> add_titled(label, "Text", "Text");

    
}