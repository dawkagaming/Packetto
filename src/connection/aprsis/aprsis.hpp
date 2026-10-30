#ifndef APRSIS_HPP
#define APRSIS_HPP

#include <cstdint>

#include <peel/class.h>
#include <peel/RefPtr.h>

#include <peel/Gio/SocketClient.h>

using namespace peel;

class APRSIS_Socket : public Gio::SocketClient {
    PEEL_SIMPLE_CLASS(APRSIS_Socket, Gio::SocketClient)

    static RefPtr<APRSIS_Socket> create();

    private:
        void init(Class *);

        String host;
        std::uint16_t port;
};

#endif // APRSIS_HPP