#include "main_window.hpp"

RefPtr<MainWindow> MainWindow::create(Adw::Application * app) {
    MainWindow * window = Object::create<MainWindow>(prop_application(), app);
    
    return window;
}

void MainWindow::init() {
    this -> header = Adw::HeaderBar::create();

    this->header->set_title_widget(Gtk::Label::create(this -> get_name()));

    this -> set_content(this -> header);
}