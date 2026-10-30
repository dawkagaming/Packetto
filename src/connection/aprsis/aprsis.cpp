#include "aprsis.hpp"

PEEL_CLASS_IMPL(APRSIS_Socket, "APRSIS_Socket", Gio::SocketClient)

void APRSIS_Socket::Class::init() {

}

RefPtr<APRSIS_Socket> APRSIS_Socket::create() {
    return Object::create<APRSIS_Socket>();
}

void APRSIS_Socket::init(Class *) {

}