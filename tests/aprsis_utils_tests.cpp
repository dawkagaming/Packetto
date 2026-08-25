#include "../src/connection/aprsis/aprsis_utils.hpp"

#include <cassert>

int main() {
    assert(APRSISUtils::GenerateAPRSISPasscode("NO0CAL") == "19618");
    assert(APRSISUtils::GenerateAPRSISPasscode("WA9APV") == "19892");
    assert(APRSISUtils::GenerateAPRSISPasscode("SP1AWS") == "18080");
    assert(APRSISUtils::GenerateAPRSISPasscode("F7HAM") == "12436");
}