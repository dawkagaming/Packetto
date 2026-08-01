#ifndef PROJECT_NAME
    #define PROJPROJECT_NAME "Packetto"
#endif

#ifndef PROJECT_VERSION
    #define PROJECT_VERSION "0.1"
#endif

#include <peel/RefPtr.h>

#include "app/application.hpp"

int main(int argc, char *argv[]) {
    RefPtr<Application> app = Application::create("com.github.dawkagaming." PROJECT_NAME);

    app -> set_version(PROJECT_VERSION);

    return app -> run(argc, argv);
}