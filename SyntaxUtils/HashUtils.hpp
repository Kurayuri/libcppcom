#pragma once
#include <functional>
#include <map>
#include <tuple>
#include <unordered_map>
#include <utility>

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