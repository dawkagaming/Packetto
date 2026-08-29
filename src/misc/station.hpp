#ifndef STATION_HPP
#define STATION_HPP

#include <memory>
#include <string>
#include <vector>

#include <peel/Shumate/Coordinate.h>

#include "packet.hpp"

using namespace peel;

struct Station {
    std::string callsign;
    std::vector<std::shared_ptr<Packet>> packets;
    std::vector<Shumate::Coordinate> path;
};

#endif // STATION_HPP