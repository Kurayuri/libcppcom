#pragma once
#include "FileUtils.hpp"
#include <algorithm>
#include <deque>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <variant>
namespace fs = std::filesystem;
class CacheFile {
  public:
    static constexpr const char *FILENAME_PATTERN = "{path}.cache";

    CacheFile(const fs::path &path, const std::string &filename_pattern = FILENAME_PATTERN,
              std::optional<int64_t> fn_cache = std::nullopt)
        : filename_pattern(filename_pattern), fn_cache(fn_cache), path(path) {
        cache_path = get_cache_path(path);
    }

    void cache() {
        std::cout << "Generate Cache" << std::endl;
        if (fn_cache.has_value()) {
            std::cout << "Cache size: " << *fn_cache << std::endl;
            std::ifstream f(path, std::ios::binary);
            std::ofstream cache_f(cache_path, std::ios::binary);
            std::string line;
            if (*fn_cache >= 0) {
                // Read only the first fn_cache lines
                size_t n = *fn_cache;
                size_t idx = 0;
                while (std::getline(f, line) && idx < n) {
                    cache_f << line << std::endl;
                    ++idx;
                }
            } else {
                // Read the last -fn_cache lines
                size_t n = -(*fn_cache);
                std::deque<std::string> buffer;
                while (std::getline(f, line)) {
                    buffer.push_back(line);
                    if (buffer.size() > n)
                        buffer.pop_front();
                }
                for (const auto &l : buffer) {
                    cache_f << l << std::endl;
                }
            }

            f.close();
            cache_f.close();
        }
    }

    std::fstream &open(std::variant<std::nullptr_t, std::string, bool> mode = nullptr) {
        if (cache_f.is_open()) {
            cache_f.close();
        }

        if (std::holds_alternative<std::nullptr_t>(mode)) {
            if (check()) {
                read_mode = true;
            } else {
                if (fn_cache.has_value()) { // if fn_cache is not null
                    // Auto Create cache
                    cache();
                    read_mode = true;
                } else {
                    // Manual Create cache
                    read_mode = false;
                }
            }
        } else if (std::holds_alternative<std::string>(mode)) {
            read_mode = std::get<std::string>(mode) == "rb";
        } else if (std::holds_alternative<bool>(mode)) {
            read_mode = std::get<bool>(mode);
        }

        cache_f.open(cache_path, read_mode ? std::ios::in | std::ios::binary
                                           : std::ios::out | std::ios::binary);

        return cache_f;
    }

    bool cache_read() const { return read_mode; }

    bool cache_write() const { return !read_mode; }

    fs::path get_cache_path(const fs::path &path) const {
        // std::string cache_filename = std::format(filename_pattern, path.string());
        std::string cache_filename = filename_pattern;
        std::string match_pattern = "{path}";

        size_t pos = filename_pattern.find(match_pattern);
        if (pos != std::string::npos) {
            cache_filename.replace(pos, match_pattern.size(), path.string());
        } else {
            cache_filename = path.string() + ".cache";
        }
        return fs::path(cache_filename);
    }

    bool check(bool strict = false) {
        if (fs::exists(cache_path) && fs::last_write_time(cache_path) > fs::last_write_time(path)) {
            if (strict) {
                bool valid = true;
                auto cache_line_count = FileUtils::countLines(cache_path);
                if (fn_cache.has_value()) {
                    size_t fn_cache_line = std::abs(fn_cache.value());
                    std::cout << "fn_Cache " + std::to_string(fn_cache_line) +
                                     ", Cache: " + std::to_string(cache_line_count)
                              << std::endl;
                    valid = (cache_line_count == fn_cache_line) && valid;
                } else {
                    auto file_line_count = FileUtils::countLines(path);
                    std::cout << "File: " + std::to_string(file_line_count) +
                                     ", Cache: " + std::to_string(cache_line_count)
                              << std::endl;
                    valid = (file_line_count == cache_line_count) && valid;
                }
                return valid;
            } else {
                return true;
            }
        } else {
            return false;
        }
    }

    std::fstream cache_f;

    // private:
    std::string filename_pattern;
    std::optional<int64_t> fn_cache;
    bool read_mode;
    fs::path path;
    fs::path cache_path;
};
