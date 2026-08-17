#include "kiss_utils.hpp"

std::vector<std::uint8_t> KissUtils::Escape(const std::vector<std::uint8_t> & input) {
    std::vector<std::uint8_t> output;

    for (std::size_t i = 0; i < input.size(); i++) {
        if (input[i] == KissUtils::Frames::FEND) {
            output.push_back(KissUtils::Frames::FESC);
            output.push_back(KissUtils::Frames::TFEND);
        } else if (input[i] == KissUtils::Frames::FESC) {
            output.push_back(KissUtils::Frames::FESC);
            output.push_back(KissUtils::Frames::TFESC);
        } else {
            output.push_back(input[i]);
        };
    };

    return output;
}

std::vector<std::uint8_t> KissUtils::Unescape(const std::vector<std::uint8_t> & input) {
    std::vector<std::uint8_t> output;

    for (std::size_t i = 0; i < input.size(); i++) {
        if (input[i] == KissUtils::Frames::FESC) {
            if ((i + 1) < input.size()) {
                if (input[i + 1] == KissUtils::Frames::TFEND) {
                    output.push_back(KissUtils::Frames::FEND);
                } else if (input[i + 1] == KissUtils::Frames::TFESC) {
                    output.push_back(KissUtils::Frames::FESC);
                } else {
                    output.clear();

                    break;
                };

                i++;
            } else {
                output.clear();

                break;
            }
        } else {
            output.push_back(input[i]);
        };
    };

    return output;
}

std::uint8_t KissUtils::PortToHex(std::uint8_t port) {
    return port << 4;
}