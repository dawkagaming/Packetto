#include "aprsis_utils.hpp"

std::string APRSISUtils::GenerateAPRSISPasscode(std::string callsign) {
    std::size_t minus_index = callsign.find('-');

    callsign = callsign.substr(0, minus_index);

    std::uint16_t hash = 0x73e2;

    for (std::size_t i = 0; i < callsign.length(); i += 2) {
        hash ^= callsign[i] << 8;

        if (i + 1 < callsign.length()) {
            hash ^= callsign[i + 1];
        }
    };

    return std::to_string(hash & 0x7fff);
}