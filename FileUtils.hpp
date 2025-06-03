#pragma once
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <string>
namespace FileUtils {
inline size_t countLines(std::ifstream &f) {
    size_t n_lines = std::count(std::istreambuf_iterator<char>(f.rdbuf()),
                                std::istreambuf_iterator<char>(), '\n');
    f.clear();  // Clear EOF flag
    f.seekg(0); // Reset the stream position to the beginning
    return n_lines;
}

inline size_t countLines(const std::filesystem::path &file_path) {
    std::string cmd = "wc -l " + file_path.string();

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    size_t n_lines;
    char buffer[1024];

    // Parse "n_lines filename" output
    if (fscanf(pipe.get(), "%ld %s", &n_lines, buffer) != 2) {
        throw std::runtime_error("Failed to parse wc output");
    }

    return n_lines;
}
} // namespace FileUtils