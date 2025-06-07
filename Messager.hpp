#pragma once

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string>
#include <variant>
#include <vector>

class Messager {
  public:
    enum { NOSET = 0, DEBUG = 10, INFO = 20, WARNING = 30, ERROR = 40, CRITICAL = 50 };

    using Level = int;
    enum Style { UNSET, NORMAL, RED, YELLOW, GREEN, BLUE,};

    explicit Messager(Level level = NOSET) : messageLevel(level) {}

    Level setLevel(Level level) {
        Level old = setMessageLevel(level);
        setMessageProgressLevel(level);
        return old;
    }

    Level setMessageLevel(Level level) {
        Level old = messageLevel;
        messageLevel = level;
        return old;
    }

    Level setMessageProgressLevel(Level level) {
        Level old = messageLevel;
        messageLevel = level;
        return old;
    }

    template <typename... Args>
    inline void message(Args &&...args, Level level = INFO) const {
        if (level >= messageLevel) {
            _log(std::forward<Args>(args)...);
        }
    }

    template <typename... Args> inline void _log(Args &&...args) const {
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args)); // Fold expression to concatenate all arguments
        std::cout << oss.str() << std::endl;
    }

    template <typename... Args> inline void debug(Args &&...args) const {
        if (messageLevel <= DEBUG) {
            if (enableFmt) {
                _log("[DEBUG] " + styleString(std::forward<Args>(args)...));
            } else {
                _log(std::forward<Args>(args)...);
            }
        }
    }
    template <typename... Args> inline void info(Args &&...args) const {
        if (messageLevel <= INFO) {
            if (enableFmt) {
                _log("[INFO] " + styleString(std::forward<Args>(args)...));
            } else {
                _log(std::forward<Args>(args)...);
            }
        }
    }
    template <typename... Args> inline void warning(Args &&...args) const {
        if (messageLevel <= WARNING) {
            if (enableFmt) {
                _log("[WARNING] " + styleString(std::forward<Args>(args)...));
            } else {
                _log(std::forward<Args>(args)...);
            }
        }
    }
    template <typename... Args> inline void error(Args &&...args) const {
        if (messageLevel <= ERROR) {
            if (enableFmt) {
                _log("[ERROR] " + styleString(std::forward<Args>(args)...));
            } else {
                _log(std::forward<Args>(args)...);
            }
        }
    }
    template <typename... Args> inline void critical(Args &&...args) const {
        if (messageLevel <= CRITICAL) {
            if (enableFmt) {
                _log("[CRITICAL] " + styleString(std::forward<Args>(args)...));
            } else {
                _log(std::forward<Args>(args)...);
            }
        }
    }
    // template <typename... Args> inline void debug(Args &&...args) const {
    //     debug(std::forward<Args>(args)..., NORMAL);
    // }
    // template <typename... Args> inline void info(Args &&...args) const {
    //     info(std::forward<Args>(args)..., NORMAL);
    // }
    // template <typename... Args> inline void warning(Args &&...args) const {
    //     warning(std::forward<Args>(args)..., NORMAL);
    // }
    // template <typename... Args> inline void error(Args &&...args) const {
    //     error(std::forward<Args>(args)..., NORMAL);
    // }
    // template <typename... Args> inline void critical(Args &&...args) const {
    //     critical(std::forward<Args>(args)..., NORMAL);
    // }

    template <typename T>
    void message_progress(const std::vector<T> &items, const std::string &description) {
        if (messageLevel <= INFO) {
            std::cout << description << " (0/" << items.size() << ")" << std::endl;
            // In a real implementation, you'd show progress as the loop continues
        }
    }

    template <typename T>
    std::vector<std::pair<size_t, T>> message_enumprogress(const std::vector<T> &items,
                                                           const std::string &description) {
        std::vector<std::pair<size_t, T>> result;
        for (size_t i = 0; i < items.size(); ++i) {
            result.push_back({i, items[i]});
        }
        if (messageLevel <= INFO) {
            std::cout << description << " (items: " << items.size() << ")" << std::endl;
        }
        return result;
    }
    Level messageLevel = NOSET;
    Level messageProgressLevel = NOSET;
    bool enableFmt = true;

  private:
    template <typename... Args> inline std::string styleString(Args &&...args) const {
        // In a real implementation, you'd add ANSI color codes
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args)); // Fold expression to concatenate all arguments
        std::string styledString = oss.str();
        Style style = UNSET; // Default style
        switch (style) {
        case RED:
            return "\033[31m" + styledString + "\033[0m"; // Red
        case YELLOW:
            return "\033[33m" + styledString + "\033[0m"; // Yellow
        case GREEN:
            return "\033[32m" + styledString + "\033[0m"; // Green
        case BLUE:
            return "\033[34m" + styledString + "\033[0m"; // Blue
        case NORMAL:
            return "\033[0m" + styledString + "\033[0m"; // Normal
        default:
            return styledString; // No style
        }
    }
};