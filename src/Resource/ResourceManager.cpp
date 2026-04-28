#include "Axiom/Resource/ResourceManager.hpp"
#include <iostream>
#include <filesystem>

namespace Axiom {

    // ?? static members definition
    std::unordered_map<std::string, std::unique_ptr<Texture>> ResourceManager::s_Textures;
    Texture* ResourceManager::s_FallbackTexture = nullptr;

    // ?? init
    void ResourceManager::init()
    {
        std::cout << "[ResourceManager] init\n";

        s_Textures.clear();

        s_FallbackTexture = new Texture("assets/fallback.png");

    }

    // ?? shutdown
    void ResourceManager::shutdown()
    {
        std::cout << "[ResourceManager] shutdown\n";

        s_Textures.clear();

        delete s_FallbackTexture;

        s_FallbackTexture = nullptr;
    }

    // ?? load texture
    Texture* ResourceManager::loadTexture(const std::string& path)
    {

        auto it = s_Textures.find(path);
        if (it != s_Textures.end())
            return it->second.get();

        std::unique_ptr<Texture> tex = std::make_unique<Texture>(path);

        if (!tex || tex->getID() == 0)
        {
            std::cout << "[ResourceManager] Failed: " << path << std::endl;
            return s_FallbackTexture;
        }

        Texture* rawPtr = tex.get();
        s_Textures[path] = std::move(tex);

        return rawPtr;
    }

    // ?? get texture
    Texture* ResourceManager::getTexture(const std::string& path)
    {
        auto it = s_Textures.find(path);
        if (it != s_Textures.end())
            return it->second.get();

        return loadTexture(path);
    }

}