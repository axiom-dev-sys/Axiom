#include "Axiom/Resource/ResourceManager.hpp"
#include "Axiom/Resource/AssetRegistry.hpp"
#include "Axiom/Core/Paths.hpp"
#include <iostream>

namespace Axiom {

    std::unordered_map<std::string, std::unique_ptr<Texture>> ResourceManager::s_Textures;
    std::unique_ptr<Texture> ResourceManager::s_FallbackTexture = nullptr;

    void ResourceManager::init()
    {
        std::cout << "[ResourceManager] init\n";

        s_Textures.clear();

        s_FallbackTexture = nullptr;

        AssetRegistry::registerTexture(
            "player",
            "player.png"
        );

        AssetRegistry::registerTexture(
            "test",
            "test.png"
        );

        AssetRegistry::registerTexture(
            "fallback",
            "fallback.png"
        );
    }

    void ResourceManager::shutdown()
    {
        std::cout << "[ResourceManager] shutdown\n";

        s_Textures.clear();

        s_FallbackTexture = nullptr;
    }

    Texture* ResourceManager::loadTexture(const std::string& name)
    {
        auto it = s_Textures.find(name);
        if (it != s_Textures.end())
            return it->second.get();

        std::string file =
            AssetRegistry::getTexturePath(name);

        std::string fullPath =
            Paths::getAsset(file);

        std::unique_ptr<Texture> tex = std::make_unique<Texture>(fullPath);

        if (!tex || tex->getID() == 0)
        {
            std::cout << "[ResourceManager] Failed: "
                << fullPath << std::endl;

            return getFallback();
        }

        Texture* rawPtr = tex.get();

        s_Textures[name] = std::move(tex);

        std::cout << "[ResourceManager] Loaded: "
            << fullPath << std::endl;

        return rawPtr;
    }

    Texture* ResourceManager::getTexture(const std::string& name)
    {
        auto it = s_Textures.find(name);
        if (it != s_Textures.end())
            return it->second.get();

        return loadTexture(name);
    }

    Texture* ResourceManager::getFallback()
    {
        if (!s_FallbackTexture)
            s_FallbackTexture =
            std::make_unique<Texture>(Paths::getAsset("fallback.png"));

        return s_FallbackTexture.get();
    }

}