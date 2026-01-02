#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <mutex>

// Define Log Levels
enum class LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class Logger {
public:
    // Get the singleton instance
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    // Thread-safe log function
    void log(LogLevel level, const char* file, int line, const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        
        // 1. Level
        std::cout << "[" << getLevelString(level) << "] ";

        // 2. Time
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::cout << std::put_time(std::localtime(&in_time_t), "%H:%M:%S") << " ";

        // 3. File:Line
        std::cout << "[" << getFileName(file) << ":" << line << "] ";

        // 4. Message
        std::cout << message << std::endl;
    }

private:
    std::mutex mutex_;

    // Helper to strip path from filename (e.g., /src/main.cpp -> main.cpp)
    std::string getFileName(const char* path) {
        std::string file = path;
        size_t pos = file.find_last_of("/\\");
        return (pos == std::string::npos) ? file : file.substr(pos + 1);
    }

    std::string getLevelString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO:  return "INFO ";
            case LogLevel::WARN:  return "WARN ";
            case LogLevel::ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }
};

// -----------------------------------------------------------------------------
// MACROS (The usage interface)
// -----------------------------------------------------------------------------

// Helper macro to convert stream-style inputs to string
// Example: LOG_INFO("Value: " << 10) -> "Value: 10"
#define LOG_INTERNAL(level, msg_stream) \
    do { \
        std::ostringstream oss; \
        oss << msg_stream; \
        Logger::getInstance().log(level, __FILE__, __LINE__, oss.str()); \
    } while (0)

// Public Macros
#ifdef DEBUG_MODE
    #define LOG_DEBUG(msg) LOG_INTERNAL(LogLevel::DEBUG, msg)
#else
    #define LOG_DEBUG(msg) do {} while(0)
#endif

#define LOG_INFO(msg)  LOG_INTERNAL(LogLevel::INFO, msg)
#define LOG_WARN(msg)  LOG_INTERNAL(LogLevel::WARN, msg)
#define LOG_ERROR(msg) LOG_INTERNAL(LogLevel::ERROR, msg)
