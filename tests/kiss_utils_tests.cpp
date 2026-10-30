#include "../src/connection/kiss/kiss_utils.hpp"

#include <cassert>

int main() {
    std::vector<std::uint8_t> data = {0xDB, 0xA0, 0xFA, 0xC0, 0x12, 0x52, 0xDB, 0xAC, 0x16};

    std::vector<std::uint8_t> escaped_data = KissUtils::Escape(data);

    std::vector<std::uint8_t> unescaped_data = KissUtils::Unescape(escaped_data);

    assert(unescaped_data == data);
}