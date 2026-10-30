#include "settings_window.hpp"

PEEL_CLASS_IMPL(SettingsWindow, "SettingsWindow", Adw::PreferencesDialog)

RefPtr<SettingsWindow> SettingsWindow::create() {
    return Object::create<SettingsWindow>();
}

void SettingsWindow::Class::init() {}

void SettingsWindow::init(Class *) {

}