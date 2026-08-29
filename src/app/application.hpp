#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <peel/Adw/Application.h>
#include <peel/Gio/ApplicationFlags.h>

#include <peel/RefPtr.h>

#include "../ui/main_window.hpp"

using namespace peel;

class Application : public Adw::Application {
    PEEL_SIMPLE_CLASS(Application, Adw::Application)
    friend class Gio::Application;

    public:
        static RefPtr<Application> create(String id);

    private:
        void init(Class *);
        
        void vfunc_activate();

        RefPtr<MainWindow> main_window;
};

#endif // APPLICATION_HPP