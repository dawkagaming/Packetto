#ifndef PROJECT_NAME
    #define PROJECT_NAME "Packetto"
#endif

#ifndef PROJECT_VERSION
    #define PROJECT_VERSION "0.1"
#endif

#include <clocale>
#include <glib/gi18n.h>

#if defined(_WIN32)
    #include <glib.h>
#endif

#include <peel/GLib/functions.h>

#include <peel/RefPtr.h>

#include "app/application.hpp"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    bind_textdomain_codeset(PROJECT_NAME, "UTF-8");

    #if defined(_WIN32)

    auto install_location = g_win32_get_package_installation_directory_of_module(NULL);
    auto localedir = g_build_filename(install_location, "..", "share", "locale", NULL);

    bindtextdomain(PROJECT_NAME, localedir);

    g_free(install_location);
    g_free(localedir);

    #else

    textdomain(PROJECT_NAME);

    #endif

    RefPtr<Application> app = Application::create("com.github.dawkagaming." PROJECT_NAME);

    GLib::set_application_name(PROJECT_NAME);
    app -> set_version(PROJECT_VERSION);

    return app -> run(argc, argv);
}