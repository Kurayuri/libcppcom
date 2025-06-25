#pragma once
#include <map>
#include <unordered_map>
#include <string>

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