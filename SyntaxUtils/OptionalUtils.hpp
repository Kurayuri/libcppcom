#pragma once
#include <optional>
#include <sstream>
#include <string>

namespace OptionalUtils {
template <typename T>
std::string to_string(const std::optional<T> &opt, const std::string &null_str = "None") {
    if (opt.has_value()) {
        if constexpr (std::is_same_v<T, std::string>) {
            // for std::string, directly return the value
            return *opt;
        } else {
            // for other types, use std::to_string or stringstream
            if constexpr (std::is_arithmetic_v<T>) {
                return std::to_string(*opt);
            } else {
                // for other types, use stringstream
                std::ostringstream ss;
                ss << *opt;
                return ss.str();
            }
        }
    } else {
        return null_str;
    }
}
} // namespace OptionalUtils
