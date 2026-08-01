cmake_minimum_required(VERSION 3.31)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Packetto
    VERSION "0.1"
    LANGUAGES CXX
)

option(USE_PREGENERATED_PEEL "Use pregenerated peel headers instead of on-demand generation" OFF)
if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR/include/peel})
    set(USE_PREGENERATED_PEEL ON)
endif()

add_executable(${PROJECT_NAME}
    src/main.cpp
    # App
    src/app/application.cpp src/app/application.hpp
    # UI
    src/ui/main_window.cpp src/ui/main_window.hpp
    # Connection
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    PROJECT_NAME="${PROJECT_NAME}"
    PROJECT_VERSION="${PROJECT_VERSION}"
)

# Find required C libraries
find_package(PkgConfig REQUIRED)

pkg_check_modules(Gtk REQUIRED IMPORTED_TARGET gtk4)
pkg_check_modules(Adw REQUIRED IMPORTED_TARGET libadwaita-1)
pkg_check_modules(Shumate REQUIRED IMPORTED_TARGET shumate-1.0)

target_link_libraries(${PROJECT_NAME} PRIVATE
    PkgConfig::Gtk
    PkgConfig::Adw
    PkgConfig::Shumate
)

if(USE_PREGENERATED_PEEL)
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
else()
    # Generate C++ bindings using peel
    find_package(peel REQUIRED)

    peel_generate(Gtk 4.0 RECURSIVE)
    peel_generate(Adw 1 RECURSIVE)
    peel_generate(Shumate 1.0 RECURSIVE)

    target_link_libraries(${PROJECT_NAME} PRIVATE
        peel::Gtk
        peel::Adw
        peel::Shumate
    )
endif()