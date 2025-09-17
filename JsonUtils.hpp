#pragma once
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
namespace JsonUtils {
inline const nlohmann::json EMPTY_JSON = nlohmann::json::object();

template <typename T>
std::string dump(const T &obj, const int indent = -1, const char indent_char = ' ',
                 const bool ensure_ascii = false) {
    return nlohmann::json(obj).dump(indent, indent_char, ensure_ascii);
}

inline const nlohmann::json &get(const nlohmann::json &j, const std::string &key) {
    if (j.contains(key)) {
        return j.at(key);
    } else {
        return EMPTY_JSON;
    }
}

inline std::vector<std::string> splitMultiJson(const std::string &json_str) {
    std::vector<std::string> result;
    std::istringstream iss(json_str);
    std::string line, buffer;
    size_t brace_count = 0;

    while (std::getline(iss, line)) {
        for (char c : line) {
            if (c == '{')
                ++brace_count;
            if (c == '}')
                --brace_count;
        }
        buffer += line + "\n";
        if (brace_count == 0 && !buffer.empty()) {
            result.push_back(buffer);
            buffer.clear();
        }
    }
    return result;
}

inline std::vector<nlohmann::json> parseMultiJson(const std::string &json_str) {
    std::vector<nlohmann::json> result;
    std::vector<std::string> json_lines = splitMultiJson(json_str);
    for (const auto &line : json_lines) {
        try {
            result.push_back(nlohmann::json::parse(line));
        } catch (const nlohmann::json::parse_error &e) {
            std::cerr << "JSON parse error: " << e.what() << " in line: " << line << std::endl;
        }
    }
    return result;
}


inline nlohmann::json load(const std::string &path) {
    std::ifstream f(path);
    if (!f.is_open()) {
        throw std::runtime_error("Failed to open JSON file: " + path);
    }
    nlohmann::json j;
    f >> j;
    f.close();
    return j;
}

inline void
convertJsonFileToJsonLinesFile(const std::string &input_path,
                               const std::string &output_path,
                               const std::string &key = "key",
                               const std::string &value = "value") {
    nlohmann::json input_json = std::move(load(input_path));
    std::ofstream outfile(output_path);
    if (!outfile.is_open()) {
        throw std::runtime_error("Failed to open output file: " + output_path);
    }
    if (input_json.is_array()) {
        for (const auto &item : input_json) {
            outfile << item.dump() << std::endl;
        }
    } else if (input_json.is_object()) {
        for (const auto &[key, value] : input_json.items()) {
            nlohmann::json line = {{"key", key}, {"value", value}};
            outfile << line.dump() << std::endl;
        }
    } else {
        throw std::runtime_error("Input JSON is neither an object nor an array.");
    }

    outfile.close();
}

class JSONLineLogger {
    // LEVEL and STYLE enums similar to Python constants
    struct LEVEL {
        static constexpr int DEBUG = 0;
        static constexpr int INFO = 1;
        static constexpr int WARNING = 2;
        static constexpr int ERROR = 3;
    };

    struct STYLE {
        static constexpr const char *RESET = "\033[0m";
        static constexpr const char *GREEN = "\033[32m";
        static constexpr const char *RED = "\033[31m";
        static constexpr const char *YELLOW = "\033[33m";
        static constexpr const char *BLUE = "\033[34m";
    };

  public:
    JSONLineLogger(const std::string &log_filename)
        : log_filename_(log_filename), message_level_(LEVEL::DEBUG) {
        file_.open(log_filename, std::ios::app);
        if (!file_.is_open()) {
            throw std::runtime_error("Failed to open log file: " + log_filename);
        }
    }

    ~JSONLineLogger() {
        if (file_.is_open()) {
            file_.close();
        }
    }

    // MessageLevel property getters and setters
    int getMessageLevel() const { return message_level_; }

    int setMessageLevel(int level) {
        int prev_level = message_level_;
        message_level_ = level;
        return prev_level;
    }

    void _write_log(const nlohmann::json &log_entry) {
        if (file_.is_open()) {
            file_ << log_entry.dump() << std::endl;
            file_.flush();
        }
    }

    void log(const nlohmann::json &message, bool with_entry = true, int level = LEVEL::DEBUG) {
        if (with_entry) {
            // Create timestamp in ISO format
            auto now = std::chrono::system_clock::now();
            auto now_c = std::chrono::system_clock::to_time_t(now);
            auto now_ms =
                std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) %
                1000;

            std::stringstream ss;
            ss << std::put_time(std::localtime(&now_c), "%Y-%m-%dT%H:%M:%S");
            ss << '.' << std::setfill('0') << std::setw(3) << now_ms.count();

            nlohmann::json log_entry = {
                {"timestamp", ss.str()}, {"level", level}, {"message", message}};
            _write_log(log_entry);
        } else {
            _write_log(message);
        }
    }

    void log_info(const nlohmann::json &message) { log(message, true, LEVEL::INFO); }

    void log_warning(const nlohmann::json &message) { log(message, true, LEVEL::WARNING); }

    void log_error(const nlohmann::json &message) { log(message, true, LEVEL::ERROR); }

    template <typename... Args>
    void message(Args &&...args, int level = LEVEL::DEBUG, const char *style = STYLE::RESET,
                 const std::string &end = "\n", const std::string &separator = " ") {
        if (level >= message_level_) {
            // Convert args to string and join with separator
            std::stringstream ss;
            ((ss << args << separator), ...);
            std::string text = ss.str();

            // Remove the last separator if it exists
            if (!text.empty() && text.size() >= separator.size()) {
                text = text.substr(0, text.size() - separator.size());
            }

            std::cout << style << text << STYLE::RESET << end;
            log(text, true, level);
        }
    }

    void kv(const std::string &key, const nlohmann::json &value, int level) {
        if (level >= message_level_) {
            tmp_kv_[key] = value;
        }
    }

    void flush() {
        log(tmp_kv_);
        tmp_kv_.clear();
    }

  private:
    std::string log_filename_;
    std::ofstream file_;
    int message_level_;
    nlohmann::json tmp_kv_;
};
} // namespace JsonUtils
