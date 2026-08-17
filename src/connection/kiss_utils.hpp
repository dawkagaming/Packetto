#ifndef KISS_UTILS_HPP
#define KISS_UTILS_HPP

#include <cstdint>
#include <vector>
#include <cstddef>

namespace KissUtils {
    std::vector<std::uint8_t> Escape(const std::vector<std::uint8_t> & input);
    std::vector<std::uint8_t> Unescape(const std::vector<std::uint8_t> & input);

    std::uint8_t PortToHex(std::uint8_t port);

    namespace Frames {
        constexpr std::uint8_t FEND = 0xC0;
        constexpr std::uint8_t FESC = 0xDB;
        constexpr std::uint8_t TFEND = 0xDC;
        constexpr std::uint8_t TFESC = 0xDD;
    }

    namespace Commands {
        constexpr std::uint8_t DATA = 0x00;
        constexpr std::uint8_t TX_DELAY = 0x01;
        constexpr std::uint8_t SLOT_TIME = 0x03;
        constexpr std::uint8_t DUPLEX = 0x05;
        constexpr std::uint8_t RETURN = 0xFF;
    }
};

#endif // KISS_UTILS_HPP