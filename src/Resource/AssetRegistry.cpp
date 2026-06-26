#include "Axiom/Resource/AssetRegistry.hpp"

namespace Axiom {

    std::unordered_map<std::string, std::string>
        AssetRegistry::s_Textures;

    void AssetRegistry::init()
    {
        s_Textures.clear();
            
        registerTexture("player", "textures/player.png");
        registerTexture("test", "textures/test.png");
        registerTexture("office", "textures/office.png");
        registerTexture("fallback", "textures/fallback.png");
        registerTexture("camera", "textures/camera.png");
        registerTexture("camera_2", "textures/camera_2.png");
        registerTexture("office_empty", "textures/office_empty.png");
        registerTexture("office_enemy_close", "textures/office_enemy_close.png");
        registerTexture("office_enemy_far", "textures/office_enemy_far.png");
        registerTexture("teaser", "textures/teaser.png");
        registerTexture("the_enemy_is_started", "textures/the_enemy_is_started.png");
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