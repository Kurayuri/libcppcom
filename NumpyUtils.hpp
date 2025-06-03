#pragma once
#include <cmath>
#include <vector>
#include <numeric> 

namespace NumpyUtils {
template <typename T> bool isclose(const T &a, const T &b, double rtol = 1e-5, double atol = 1e-8) {
    return std::fabs(a - b) <= (atol + rtol * std::fabs(b));
}

template <typename T>
bool allclose(const std::vector<T> &a, const std::vector<T> &b, double rtol = 1e-5,
              double atol = 1e-8) {
    if (a.size() != b.size())
        return false;
    for (std::size_t i = 0; i < a.size(); ++i) {
        if (std::fabs(a[i] - b[i]) > (atol + rtol * std::fabs(b[i]))) {
            return false;
        }
    }
    return true;
}

template <typename T> T sum(const std::vector<T> &vec) {
    return std::accumulate(vec.begin(), vec.end(), static_cast<T>(0));
}
template <typename T> T mean(const std::vector<T> &vec) {
    // if (vec.empty()) {
    //     throw std::invalid_argument("Cannot calculate mean of an empty vector");
    // }
    return sum(vec) / static_cast<T>(vec.size());
}
template <typename T> T median(std::vector<T> vec) {
    // if (vec.empty()) {
    //     throw std::invalid_argument("Cannot calculate median of an empty vector");
    // }
    std::sort(vec.begin(), vec.end());
    size_t n = vec.size();
    if (n % 2 == 0) {
        return (vec[n / 2 - 1] + vec[n / 2]) / static_cast<T>(2);
    } else {
        return vec[n / 2];
    }
}
} // namespace NumpyUtils