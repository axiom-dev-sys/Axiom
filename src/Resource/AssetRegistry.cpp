#include "Axiom/Resource/AssetRegistry.hpp"

namespace Axiom {

    std::unordered_map<std::string, std::string>
        AssetRegistry::s_Textures;

    void AssetRegistry::registerTexture(
        const std::string& id,
        const std::string& filename
    )
    {
        s_Textures[id] = filename;
    }

    std::string AssetRegistry::getTexturePath(
        const std::string& id
    )
    {
        auto it = s_Textures.find(id);

        if (it == s_Textures.end())
            return id;

        return it->second;
    }

}