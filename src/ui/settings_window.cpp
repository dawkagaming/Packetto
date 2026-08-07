#include "settings_window.hpp"

PEEL_CLASS_IMPL(SettingsWindow, "SettingsWindow", Adw::PreferencesDialog)

void SettingsWindow::Class::init() {};

RefPtr<SettingsWindow> SettingsWindow::create(Gtk::Window * window) {
    return Object::create<SettingsWindow>(prop_parent(), window);
}

void SettingsWindow::init(Class *) {

}