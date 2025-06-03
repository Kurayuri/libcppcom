#pragma once

#include <map>
#include <any>
// AccessibleDict implementation (similar to Python's dictionary with dot access)
class AccessibleDict {
    public:
    void set(const std::any &key, const std::any &value);
//   public:
//     template <typename K, typename V> void set(const K &key, const V &value) {
//         data[std::make_any<K>(key)] = std::make_any<V>(value);
//     }

//     template <typename K, typename V>
//     void setDefault(const K &key, const V &value, bool lazy = false) {
//         if (!contains(key)) {
//             set(key, value);
//         }
//     }

//     template <typename K, typename V> V get(const K &key, const V &defaultValue = V()) const {
//         auto anyKey = std::make_any<K>(key);
//         auto it = data.find(anyKey);
//         if (it != data.end()) {
//             try {
//                 return std::any_cast<V>(it->second);
//             } catch (const std::bad_any_cast &) {
//                 return defaultValue;
//             }
//         }
//         return defaultValue;
//     }

//     template <typename K> bool contains(const K &key) const {
//         auto anyKey = std::make_any<K>(key);
//         return data.find(anyKey) != data.end();
//     }

//   private:
//     // This is a simplified implementation - a real one would need more sophisticated
//     // handling of any types and equality comparisons
//     std::map<std::any, std::any, std::less<>> data;
};
