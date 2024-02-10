#pragma once

#include <cstring>
#include <sstream>
#include <string>
#include <vector>

namespace Helper {
    std::vector<std::string> Split(const std::string text, const std::string delim);

    std::string Join(const std::vector<std::string> texts, const char *delim);
}  // namespace Helper