#pragma once
#include <sstream>
#include <string>
#include <vector>
using index_t = int64_t;
namespace StringUtils {


inline std::vector<std::string> split(const std::string &str, const std::string &delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    tokens.push_back(str.substr(start, end));
    return tokens;
}

inline std::string replace(const std::string &str, const std::string &_old, const std::string &_new,
                           const index_t &count = -1) {
    std::string result = str;
    size_t pos = 0;
    index_t replaced_count = 0;
    while ((pos = result.find(_old, pos)) != std::string::npos) {
        result.replace(pos, _old.length(), _new);
        pos += _new.length();
        if (count != -1 && ++replaced_count >= count) {
            break;
        }
    }
    return result;
}

inline bool contains(const std::string &str, const std::string &substr) {
    return str.find(substr) != std::string::npos;
}

template <typename T> T cast(const std::string &str) {
    std::istringstream iss(str);
    T value;
    iss >> value;
    return value;
}
} // namespace StringUtils
