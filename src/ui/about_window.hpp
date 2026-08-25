#ifndef ABOUT_WINDOW_HPP
#define ABOUT_WINDOW_HPP

#include <glib/gi18n.h>

#include <peel/GLib/functions.h>

#include "peel/Gtk/Window.h"
#include <peel/Gtk/Application.h>
#include <peel/Gtk/License.h>

#include <peel/Adw/AboutDialog.h>

#include <peel/RefPtr.h>

using namespace peel;

namespace UI {
    RefPtr<Adw::AboutDialog> CreateAboutDialog(Gtk::Window * parent);
};

#endif // ABOUT_WINDOW_HPP