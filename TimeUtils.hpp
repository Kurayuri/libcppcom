#pragma once
#include<string>
#include <iomanip>
#include <sstream>

namespace TimeUtils {
inline std::string ts_to_datetime_str(time_t ts) {
    std::tm tm = *std::localtime(&ts);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
inline std::string ts_to_time_str(time_t ts) {
    std::tm tm = *std::localtime(&ts);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%H:%M:%S");
    return oss.str();
}
inline std::string ts_to_date_str(time_t ts) {
    std::tm tm = *std::localtime(&ts);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}
} // namespace TimeUtils