#include "Axiom/Resource/AssetRegistry.hpp"

namespace Axiom {

    std::unordered_map<std::string, std::string>
        AssetRegistry::s_Textures;

    void AssetRegistry::init()
    {
        s_Textures.clear();
            
        registerTexture("player", "player.png");
        
        registerTexture("test", "test.png");
        
        registerTexture("fallback", "fallback.png");
    }

    void AssetRegistry::shutdown()
    {
        s_Textures.clear();
    }

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