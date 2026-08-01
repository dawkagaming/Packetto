#ifndef UI_HPP
#define UI_HPP

#include "main_window.hpp"
#include "settings_window.hpp"

class UI {
    public:
        UI() {
            this -> MainWindow = new class MainWindow;
            this -> SettingsWindow = new class SettingsWindow;
        };
        ~UI() {
            delete this -> MainWindow;
            delete this -> SettingsWindow;
        };

        MainWindow * MainWindow;
        SettingsWindow * SettingsWindow;
};

#endif // UI_HPP