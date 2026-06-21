#pragma once

#include <string>
#include <unordered_map>

namespace Axiom {

    class AssetRegistry
    {
    public:
        static void registerTexture(
            const std::string& id,
            const std::string& filename
        );

        static std::string getTexturePath(
            const std::string& id
        );

    private:
        static std::unordered_map<std::string, std::string> s_Textures;
    };

}