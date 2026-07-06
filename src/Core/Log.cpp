#include "Axiom/Core/Log.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace Axiom {

    static std::string getCurrentTime()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);

        std::tm localTime{};

#ifdef _WIN32
        localtime_s(&localTime, &time);
#else
        localTime = *std::localtime(&time);
#endif

        std::ostringstream stream;

        stream << std::put_time(&localTime, "%H:%M:%S");

        return stream.str();
    }

    void Log::message(Level level, const std::string& msg)
    {
        switch (level)
        {
        case Level::Info:
            std::cout << "[" << getCurrentTime() << "] " << "[INFO] "  << msg << std::endl;
            break;

        case Level::Warn:
            std::cout << "[" << getCurrentTime() << "] " << "[WARNING] " << msg << std::endl;
            break;

        case Level::Error:
            std::cerr << "[" << getCurrentTime() << "] " << "[ERROR] " << msg << std::endl;
            break;
        }
    }

    void Log::info(const std::string& msg)
    {
        message(Level::Info, msg);
    }

    void Log::warn(const std::string& msg)
    {
        message(Level::Warn, msg);
    }

    void Log::error(const std::string& msg)
    {
        message(Level::Error, msg);
    }

}