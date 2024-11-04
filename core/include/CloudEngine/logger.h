#pragma once

#include "fmt/format.h"
#include <chrono>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

enum LogLevel
{
    INFO,
    WARN,
    ERROR,
    DEBUG
};

class Logger
{
public:
    Logger();
    ~Logger();

    static Logger &Get();

    const std::string &GetLayout() { return layout; }
    void SetLayout(std::string layout) { this->layout = layout; }

    template <typename... Args>
    void Log(LogLevel level, std::string message, Args &&...args)
    {
        std::string newLayout = layout;

        auto now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

        // Convert time_t to a tm structure that holds the hour, minute, etc.
        std::tm time = *std::localtime(&now_time_t);

        replacePlaceholder(newLayout, "%t", message);
        replacePlaceholder(newLayout, "%l", getLevelString(level));
        replacePlaceholder(newLayout, "%h", std::to_string(time.tm_hour));
        replacePlaceholder(newLayout, "%m", std::to_string(time.tm_min));
        replacePlaceholder(newLayout, "%s", std::to_string(time.tm_sec));

        std::string newMessage = fmt::format(newLayout, args...);

        std::cout << newMessage << "\n";
    }

    static const std::stringstream &GetBuffer();

private:
    void replacePlaceholder(std::string &string, std::string wordToReplace, std::string replacement)
    {
        if (string.find(wordToReplace) != std::string::npos)
        {
            string.replace(string.find(wordToReplace), wordToReplace.length(), replacement);
        }
    }

    std::string getLevelString(LogLevel level)
    {
        switch (level)
        {
        case INFO:
            return "INFO";
        case WARN:
            return "WARN";
        case ERROR:
            return "ERROR";
        case DEBUG:
            return "DEBUG";
        default:
            return "";
        };
    }

private:
    std::string layout = "[%l] [%h:%m:%s]: %t";
};

#define LOG_INFO(...) Logger::Get().Log(LogLevel::INFO, __VA_ARGS__)
#define LOG_WARN(...) Logger::Get().Log(LogLevel::WARN, __VA_ARGS__)
#define LOG_ERROR(...) Logger::Get().Log(LogLevel::ERROR, __VA_ARGS__)
#define LOG_DEBUG(...) Logger::Get().Log(LogLevel::DEBUG, __VA_ARGS__)
