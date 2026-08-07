#ifndef SETTINGS_WINDOW_HPP
#define SETTINGS_WINDOW_HPP

#include <peel/class.h>

#include "peel/Gtk/Window.h"

#include <peel/Adw/PreferencesDialog.h>

using namespace peel;

class SettingsWindow : public Adw::PreferencesDialog {
    PEEL_SIMPLE_CLASS(SettingsWindow, Adw::PreferencesDialog)

    public:
        static RefPtr<SettingsWindow> create(Gtk::Window * window);

    private:
        void init(Class *);
};

#endif // SETTINGS_WINDOW_HPP