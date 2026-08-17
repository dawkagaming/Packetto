#ifndef PACKET_HPP
#define PACKET_HPP

#include <cstdint>
#include <string>
#include <vector>

#include <peel/GLib/DateTime.h>

using namespace peel;

// Packets types:
// 0
// 1

struct Packet {
    GLib::DateTime timestamp;
    std::string from;
    std::string to;
    std::vector<std::string> repeaters;
    std::uint8_t type;
    std::string content;
};

#endif // PACKET_HPP