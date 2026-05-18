#include "Axiom/Resource/ResourceManager.hpp"
#include "Axiom/Core/Paths.hpp"
#include <iostream>
#include <filesystem>

namespace Axiom {

    std::unordered_map<std::string, std::unique_ptr<Texture>> ResourceManager::s_Textures;
    std::unique_ptr<Texture> ResourceManager::s_FallbackTexture = nullptr;

    void ResourceManager::init()
    {
        std::cout << "[ResourceManager] init\n";

        s_Textures.clear();

        s_FallbackTexture = nullptr;

        std::cout << std::filesystem::current_path() << std::endl;

    }

    void ResourceManager::shutdown()
    {
        std::cout << "[ResourceManager] shutdown\n";

        s_Textures.clear();

        s_FallbackTexture = nullptr;
    }

    Texture* ResourceManager::loadTexture(const std::string& path)
    {

        auto it = s_Textures.find(path);
        if (it != s_Textures.end())
            return it->second.get();

        std::unique_ptr<Texture> tex = std::make_unique<Texture>(path);

        if (!tex || tex->getID() == 0)
        {
            std::cout << "[ResourceManager] Failed: " << path << std::endl;
            return getFallback();
        }

        Texture* rawPtr = tex.get();
        s_Textures[path] = std::move(tex);

        return rawPtr;
    }

    Texture* ResourceManager::getTexture(const std::string& path)
    {
        auto it = s_Textures.find(path);
        if (it != s_Textures.end())
            return it->second.get();

        return loadTexture(path);
    }

    Texture* ResourceManager::getFallback()
    {
    if (!s_FallbackTexture)
        s_FallbackTexture = std::make_unique<Texture>(Paths::getAsset("fallback.png"));

    return s_FallbackTexture.get();
    }

}