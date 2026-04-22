#pragma once
#include <string>

namespace Axiom
{
    class Paths
    {
    public:
        static std::string getAsset(const std::string& name)
        {
            return "assets/" + name;
        }
    };
}