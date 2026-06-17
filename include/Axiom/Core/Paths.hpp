#pragma once

#include <string>
#include <filesystem>
#include <windows.h>

namespace Axiom
{
    class Paths
    {
    public:
        static std::string getAsset(const std::string& name)
        {
            char buffer[MAX_PATH];
            GetModuleFileNameA(nullptr, buffer, MAX_PATH);

            std::filesystem::path exePath(buffer);
            std::filesystem::path exeDir = exePath.parent_path();

            return (exeDir / "assets" / name).string();
        }
    };
}