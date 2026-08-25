#include "settings_window.hpp"

RefPtr<Adw::PreferencesDialog> UI::CreatePreferencesDialog() {
    RefPtr<Adw::PreferencesDialog> preferences_dialog = Adw::PreferencesDialog::create();

    return preferences_dialog;
}