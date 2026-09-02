#pragma once

#include <optional>
#include <string_view>

float sbuToEuro(float sbus);
std::string_view trim(std::string_view s);
std::optional<float> parseSbu(std::string_view raw);
