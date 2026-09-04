#include "sbu.hpp"

#include <cmath>
#include <string>

namespace {
    constexpr float kRate = 0.017f;
    constexpr std::string_view kWhitespace = " \t\n\r\v\f";
} // namespace

float sbuToEuro(const float sbus) {
    return sbus * kRate;
}

std::string_view trim(const std::string_view s) {
    const auto first = s.find_first_not_of(kWhitespace);
    if (first == std::string_view::npos) return {};
    const auto last = s.find_last_not_of(kWhitespace);
    return s.substr(first, last - first + 1);
}

std::optional<float> parseSbu(const std::string_view raw) {
    const std::string buf(trim(raw));
    if (buf.empty()) return std::nullopt;

    char *end = nullptr;
    const double value = std::strtod(buf.c_str(), &end);
    if (end != buf.c_str() + buf.size()) return std::nullopt;

    const auto result = static_cast<float>(value);
    if (!std::isfinite(result) || result < 0.0f) return std::nullopt;
    return result;
}
