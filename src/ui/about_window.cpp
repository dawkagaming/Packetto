#include "about_window.hpp"

RefPtr<Adw::AboutDialog> UI::CreateAboutDialog(Gtk::Window * parent) {
    RefPtr<Adw::AboutDialog> about_dialog = Adw::AboutDialog::create();

    about_dialog -> set_application_name(GLib::get_application_name());
    about_dialog -> set_application_icon("application-x-executable");
    about_dialog -> set_version(parent -> get_application() -> get_version());
    about_dialog -> set_license_type(Gtk::License::APACHE_2_0);
    about_dialog -> set_comments(_("A simple APRS client, written in C++ and libadwaita."));
    about_dialog -> set_support_url("https://github.com/dawkagaming/Packetto/discussions");
    about_dialog -> set_issue_url("https://github.com/dawkagaming/Packetto/issues");
    about_dialog -> set_developer_name("Dawid Kulas");

    return about_dialog;
}