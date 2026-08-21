#include "Axiom/Resource/AssetRegistry.hpp"

#include <algorithm>

namespace Axiom {

    std::unordered_map<std::string, std::string>
        AssetRegistry::s_Textures;

    void AssetRegistry::init()
    {
        s_Textures.clear();
            
        registerTexture("fallback", "textures/fallback.png");
        registerTexture("player", "textures/player.png");
        registerTexture("test", "textures/test.png");
        registerTexture("office", "textures/office.png");
        registerTexture("office_door_closed", "textures/office_door_closed.png");
        registerTexture("office_enemy_close", "textures/office_enemy_close.png");
        registerTexture("office_enemy_far", "textures/office_enemy_far.png");
        registerTexture("office_empty", "textures/office_empty.png");
        registerTexture("camera_1_empty", "textures/camera_1_empty.png");
        registerTexture("camera_1_enemy", "textures/camera_1_enemy.png");
        registerTexture("camera_2_empty", "textures/camera_2_empty.png");
        registerTexture("camera_2_enemy", "textures/camera_2_enemy.png");
        registerTexture("teaser", "textures/teaser.png");
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

    int AssetRegistry::getRegisteredTextureCount()
    {
        return static_cast<int>(s_Textures.size());
    }

    std::vector<std::string>
        AssetRegistry::getRegisteredTextureIDs()
    {
        std::vector<std::string> ids;

        ids.reserve(s_Textures.size());

        for (const auto& [id, path] : s_Textures)
        {
            ids.push_back(id);
        }

        std::sort(ids.begin(), ids.end());

        return ids;
    }

    bool AssetRegistry::isTextureRegistered(
        const std::string& id)
    {
        return s_Textures.find(id) !=
            s_Textures.end();
    }

}