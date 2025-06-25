#pragma once
#include <vector>

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