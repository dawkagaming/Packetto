#ifndef SETTINGS_WINDOW_HPP
#define SETTINGS_WINDOW_HPP

#include <glib/gi18n.h>

#include <peel/Adw/PreferencesDialog.h>
#include <peel/Adw/PreferencesPage.h>
#include <peel/Adw/PreferencesGroup.h>
#include <peel/Adw/PreferencesRow.h>

#include <peel/class.h>
#include <peel/RefPtr.h>

using namespace peel;

class SettingsWindow : public Adw::PreferencesDialog {
    PEEL_SIMPLE_CLASS(SettingsWindow, Adw::PreferencesDialog)

    public:
        static RefPtr<SettingsWindow> create();

    private:
        void init(Class *);
};

#endif // SETTINGS_WINDOW_HPP