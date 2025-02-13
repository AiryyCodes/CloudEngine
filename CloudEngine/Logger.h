#pragma once

#include "CloudEngine/Core.h"

#include <chrono>
#include <iostream>
#include <string>
#include <fmt/format.h>
#include <utility>
#include <format>

enum class LogLevel
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
};

class Logger
{
public:
    template <typename... Args>
    void Log(LogLevel level, const std::string &message, Args &&...args)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm time = *std::localtime(&now_time_t);

        std::string newPattern = m_Pattern;
        replacePlaceholder(newPattern, "%t", message);
        replacePlaceholder(newPattern, "%l", GetLevelName(level));
        replacePlaceholder(newPattern, "%h", std::to_string(time.tm_hour));
        replacePlaceholder(newPattern, "%m", std::to_string(time.tm_min));
        replacePlaceholder(newPattern, "%s", std::to_string(time.tm_sec));

        std::string format = fmt::format(fmt::runtime(newPattern), std::forward<Args>(args)...);
        std::cout << format << std::endl;
    }

    std::string GetLevelName(LogLevel level)
    {
        switch (level)
        {
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARNING:
            return "WARNING";
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::DEBUG:
            return "DEBUG";
        default:
            return "";
        };
    }

    void SetPattern(const std::string &pattern) { this->m_Pattern = pattern; }

    static const Ref<Logger> &GetGlobalLogger()
    {
        if (m_GlobalLogger == nullptr)
            m_GlobalLogger = CreateRef<Logger>();

        return m_GlobalLogger;
    }

private:
    void replacePlaceholder(std::string &string, std::string wordToReplace, std::string replacement)
    {
        if (string.find(wordToReplace) != std::string::npos)
        {
            string.replace(string.find(wordToReplace), wordToReplace.length(), replacement);
        }
    }

private:
    std::string m_Pattern = "[%l] [%h:%m:%s]: %t";

    static Ref<Logger> m_GlobalLogger;
};

#define LOG_DEBUG(...) Logger::GetGlobalLogger()->Log(LogLevel::DEBUG, __VA_ARGS__);
#define LOG_INFO(...) Logger::GetGlobalLogger()->Log(LogLevel::INFO, __VA_ARGS__);
#define LOG_WARNING(...) Logger::GetGlobalLogger()->Log(LogLevel::WARNING, __VA_ARGS__);
#define LOG_ERROR(...) Logger::GetGlobalLogger()->Log(LogLevel::ERROR, __VA_ARGS__);
