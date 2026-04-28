#include "Axiom/Core/Log.hpp"

namespace Axiom {

    void Log::message(Level level, const std::string& msg)
    {
        switch (level)
        {
        case Level::Info:
            std::cout << "[INFO] " << msg << std::endl;
            break;

        case Level::Warn:
            std::cout << "[WARN] " << msg << std::endl;
            break;

        case Level::Error:
            std::cerr << "[ERROR] " << msg << std::endl;
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