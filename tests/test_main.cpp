#include "sbu.hpp"

#include <cassert>
#include <cmath>
#include <limits>
#include <optional>

int main() {
    assert(sbuToEuro(1000.0f) == 17.0f);
    assert(sbuToEuro(0.0f) == 0.0f);
    assert(std::fabs(sbuToEuro(100.0f) - 1.7f) < std::numeric_limits<float>::epsilon());

    assert(parseSbu("1000") == std::optional<float>(1000.0f));
    assert(parseSbu("  42.5 ") == std::optional<float>(42.5f));
    assert(!parseSbu("-1").has_value());
    assert(!parseSbu("abc").has_value());
    assert(!parseSbu("nan").has_value());
    assert(!parseSbu("inf").has_value());
    return 0;
}
