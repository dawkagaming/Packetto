#ifndef APRSIS_UTILS_HPP
#define APRSIS_UTILS_HPP

#include <string>
#include <cstddef>
#include <cstdint>

namespace APRSISUtils {
    std::string GenerateAPRSISPasscode(std::string callsign);
};

#endif // APRSIS_UTILS_HPP