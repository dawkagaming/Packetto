
#include "peel/GLib/functions.h"
#ifndef PROJECT_NAME
    #define PROJPROJECT_NAME "Packetto"
#endif

#ifndef PROJECT_VERSION
    #define PROJECT_VERSION "0.1"
#endif

#include <peel/GLib/functions.h>
#include <peel/String.h>
#include <peel/RefPtr.h>

#include "app/application.hpp"

int main(int argc, char *argv[]) {
    RefPtr<Application> app = Application::create("com.github.dawkagaming." PROJECT_NAME);

    GLib::set_application_name(PROJECT_NAME);
    app -> set_version(PROJECT_VERSION);

    return app -> run(argc, argv);
}