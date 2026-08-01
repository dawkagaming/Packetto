#include "application.hpp"

RefPtr<Application> Application::create(String id) {
    return Object::create<Application> (prop_application_id(), id, prop_flags(), Gio::Application::Flags::DEFAULT_FLAGS);
}

void Application::init() {
    this -> window = MainWindow::create(this);

    this -> window -> show();
}