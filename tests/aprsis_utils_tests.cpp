#include "../src/connection/aprsis/aprsis_utils.hpp"

#include <array>

int main() {
    std::array<std::string, 4> callsigns = {"NO0CAL", "WA9APV", "SP1AWS", "F7HAM"};
    std::array<std::string, 4> passcodes = {"19618", "19892", "18080", "12436"};

    for (std::size_t i = 0; i < 4; i++) {
        if (APRSISUtils::GenerateAPRSISPasscode(callsigns[i]) != passcodes[i]) {
            return 1;
        };
    };

    return 0;    
}