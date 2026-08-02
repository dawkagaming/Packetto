#include "application.hpp"

PEEL_CLASS_IMPL (Application, "Application", Adw::Application)

void Application::Class::init() {
    override_vfunc_activate<Application>();
};

RefPtr<Application> Application::create(String id) {
    return Object::create<Application> (prop_application_id(), id, prop_flags(), Gio::Application::Flags::DEFAULT_FLAGS);
}

void Application::init(Class *) {}

void Application::vfunc_activate()
{
    parent_vfunc_activate<Application>();

    main_window = MainWindow::create(this);

    main_window -> present();
}