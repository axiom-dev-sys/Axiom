#pragma once
#include <iostream>
#include <string>

namespace Axiom {

    class Log
    {
    public:
        enum class Level
        {
            Info,
            Warn,
            Error
        };

        static void message(Level level, const std::string& msg);

        static void info(const std::string& msg);
        static void warn(const std::string& msg);
        static void error(const std::string& msg);
    };

}