#pragma once
#include <functional>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

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

namespace MapUtils {
template <typename K, typename V>
inline V get(const std::map<K, V> &m, const K &key, const V &default_value = V{}) {
    auto it = m.find(key);
    return (it != m.end()) ? it->second : default_value;
}
template <typename K, typename V>
inline V get(const std::unordered_map<K, V> &m, const K &key, const V &default_value = V{}) {
    auto it = m.find(key);
    return (it != m.end()) ? it->second : default_value;
}

} // namespace MapUtils

namespace HashUtils {
template <typename T1, typename T2> struct pair_hash {
    std::size_t operator()(const std::pair<T1, T2> &p) const {
        std::size_t h1 = std::hash<T1>{}(p.first);
        std::size_t h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

// tuple 的 hash（递归展开）
namespace tuple_hash_detail {
template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1> struct HashValueImpl {
    static void apply(size_t &seed, const Tuple &tuple) {
        HashValueImpl<Tuple, Index - 1>::apply(seed, tuple);
        seed ^=
            std::hash<typename std::tuple_element<Index, Tuple>::type>()(std::get<Index>(tuple)) +
            0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
};

template <class Tuple> struct HashValueImpl<Tuple, 0> {
    static void apply(size_t &seed, const Tuple &tuple) {
        seed ^= std::hash<typename std::tuple_element<0, Tuple>::type>()(std::get<0>(tuple)) +
                0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
};
} // namespace tuple_hash_detail

struct tuple_hash {
    template <typename... TT> std::size_t operator()(const std::tuple<TT...> &tt) const {
        size_t seed = 0;
        tuple_hash_detail::HashValueImpl<std::tuple<TT...>>::apply(seed, tt);
        return seed;
    }
};
} // namespace HashUtils

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

template <typename T> T cast(const std::string &str) {
    std::istringstream iss(str);
    T value;
    iss >> value;
    return value;
}
} // namespace StringUtils

namespace VectorUtils {
template <typename T> std::vector<T> range(T start, T end, T step = 1) {
    std::vector<T> vec;
    size_t size = (end - start) / step;
    vec.reserve(size);
    for (T i = start; i < end; i += step) {
        vec.push_back(i);
    }

    return vec;
}
} // namespace VectorUtils