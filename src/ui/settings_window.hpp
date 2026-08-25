#ifndef SETTINGS_WINDOW_HPP
#define SETTINGS_WINDOW_HPP

#include <glib/gi18n.h>

#include <peel/Adw/PreferencesDialog.h>
#include <peel/Adw/PreferencesPage.h>
#include <peel/Adw/PreferencesGroup.h>
#include <peel/Adw/PreferencesRow.h>

#include <peel/RefPtr.h>

using namespace peel;

namespace UI {
    RefPtr<Adw::PreferencesDialog> CreatePreferencesDialog();
};

#endif // SETTINGS_WINDOW_HPP