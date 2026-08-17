#ifndef PROJECT_NAME
    #define PROJPROJECT_NAME "Packetto"
#endif

#ifndef PROJECT_VERSION
    #define PROJECT_VERSION "0.1"
#endif

#include <clocale>
#include <glib/gi18n.h>

#include <peel/GLib/functions.h>

#include <peel/RefPtr.h>

#include "app/application.hpp"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    // bindtextdomain(PROJECT_NAME, );
    bind_textdomain_codeset(PROJECT_NAME, "UTF-8");
    textdomain(PROJECT_NAME);

    RefPtr<Application> app = Application::create("com.github.dawkagaming." PROJECT_NAME);

    GLib::set_application_name(PROJECT_NAME);
    app -> set_version(PROJECT_VERSION);

    return app -> run(argc, argv);
}