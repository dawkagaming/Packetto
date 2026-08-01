cmake_minimum_required(VERSION 3.31)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Packetto
    VERSION "0.1"
    LANGUAGES CXX
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    # App
    src/app/application.cpp src/app/application.hpp
    # UI
    src/ui/ui.hpp
    src/ui/main_window.cpp src/ui/main_window.hpp
    src/ui/settings_window.cpp src/ui/settings_window.hpp
    # Connection
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    PROJECT_NAME=${PROJECT_NAME}
    PROJECT_VERSION="${PROJECT_VERSION}"
)

# Find required C libraries
cmake_pkg_config(IMPORT gtk4 REQUIRED NAME Gtk)
cmake_pkg_config(IMPORT libadwaita-1 REQUIRED NAME Adw)
cmake_pkg_config(IMPORT shumate-1.0 REQUIRED NAME Shumate)

# Generate C++ bindings using peel
find_package(peel REQUIRED)

peel_generate(Gtk 4.0 RECURSIVE)
peel_generate(Adw 1 RECURSIVE)
peel_generate(Shumate 1.0 RECURSIVE)

target_link_libraries(${PROJECT_NAME} PRIVATE
    PkgConfig::Gtk
    PkgConfig::Adw
    PKGConfig::Shumate
    peel::Gtk
    peel::Adw
    peel::Shumate
)