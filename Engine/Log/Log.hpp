// https://github.com/EQMG/Acid.git
#pragma once

#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string_view>

#include "Common/BaseDefines.hpp"

FLYENGINE_BEGIN_NAMESPACE

class Log
{
public:
    class Styles
    {
    public:
        static constexpr std::string_view Default    = "\033[0m";
        static constexpr std::string_view Bold       = "\033[1m";
        static constexpr std::string_view Dim        = "\033[2m";
        static constexpr std::string_view Underlined = "\033[4m";
        static constexpr std::string_view Blink      = "\033[5m";
        static constexpr std::string_view Reverse    = "\033[7m";
        static constexpr std::string_view Hidden     = "\033[8m";
    };

    class Colours
    {
    public:
        static constexpr std::string_view Default      = "\033[39m";
        static constexpr std::string_view Black        = "\033[30m";
        static constexpr std::string_view Red          = "\033[31m";
        static constexpr std::string_view Green        = "\033[32m";
        static constexpr std::string_view Yellow       = "\033[33m";
        static constexpr std::string_view Blue         = "\033[34m";
        static constexpr std::string_view Magenta      = "\033[35m";
        static constexpr std::string_view Cyan         = "\033[36m";
        static constexpr std::string_view LightGrey    = "\033[37m";
        static constexpr std::string_view DarkGrey     = "\033[90m";
        static constexpr std::string_view LightRed     = "\033[91m";
        static constexpr std::string_view LightGreen   = "\033[92m";
        static constexpr std::string_view LightYellow  = "\033[93m";
        static constexpr std::string_view LightBlue    = "\033[94m";
        static constexpr std::string_view LightMagenta = "\033[95m";
        static constexpr std::string_view LightCyan    = "\033[96m";
        static constexpr std::string_view White        = "\033[97m";
    };

    static constexpr auto TimestampFormat = "%H:%M:%S";

    template <typename... Args>
    static void Out(const std::string_view &style, const std::string_view &colour, Args... args)
    {
        Printf(style, colour, args..., Styles::Default);
        Write(args...);
    }

    template <typename... Args>
    static void Debug(Args... args)
    {
        Out(Styles::Default, Colours::LightBlue, args...);
    }

    template <typename... Args>
    static void Info(Args... args)
    {
        Out(Styles::Default, Colours::Green, args...);
    }

    template <typename... Args>
    static void Warning(Args... args)
    {
        Out(Styles::Default, Colours::Yellow, args...);
    }

    template <typename... Args>
    static void Error(Args... args)
    {
        Out(Styles::Default, Colours::Red, args...);
    }

    template <typename... Args>
    static void Assert(bool expr, Args... args)
    {
        if (expr)
        {
            Out(Styles::Default, Colours::Magenta, args...);
            assert(false);
        }
    }

    static void OpenLog(const std::filesystem::path &filepath)
    {
        if (auto parentPath = filepath.parent_path(); !parentPath.empty())
            std::filesystem::create_directories(parentPath);
        FileStream.open(filepath);
    }
    static void CloseLog() { FileStream.close(); }

private:
    static std::mutex    WriteMutex;
    static std::ofstream FileStream;

    template <typename... Args>
    static void Write(Args... args)
    {
        std::unique_lock<std::mutex> lock(WriteMutex);

        if (FileStream.is_open())
        {
            ((FileStream << std::forward<Args>(args)), ...) << std::endl;
        }
    }

    template <typename... Args>
    static void Printf(Args... args)
    {
        ((std::cout << std::forward<Args>(args)), ...) << std::endl;
    }
};
FLYENGINE_END_NAMESPACE