#include "Axiom/Core/Log.hpp"

#include <iostream>

namespace Axiom {

    void Log::info(const std::string& message)
    {
        std::cout << "[Axiom] " << message << std::endl;
    }

    void Log::error(const std::string& message)
    {
        std::cout << "[Axiom ERROR] " << message << std::endl;
    }

}