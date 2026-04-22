#include "Axiom/Resource/ResourceManager.hpp"
#include <iostream>

namespace Axiom {

    std::unordered_map<std::string, std::unique_ptr<Texture>> ResourceManager::s_Textures;
    Texture* ResourceManager::s_FallbackTexture = nullptr;

    void ResourceManager::init()
    {
        s_FallbackTexture = new Texture(); // простой fallback (пустой)
    }

    void ResourceManager::shutdown()
    {
        s_Textures.clear();
        delete s_FallbackTexture;
    }

    Texture* ResourceManager::loadTexture(const std::string& path)
    {
        if (auto it = s_Textures.find(path); it != s_Textures.end())
            return it->second.get();

        auto tex = std::make_unique<Texture>(path);

        if (tex->getID() == 0)
        {
            std::cout << "Failed to load texture: " << path << std::endl;
            return s_FallbackTexture;
        }

        Texture* ptr = tex.get();
        s_Textures[path] = std::move(tex);

        return ptr;
    }

    Texture* ResourceManager::getTexture(const std::string& path)
    {
        if (auto it = s_Textures.find(path); it != s_Textures.end())
            return it->second.get();

        return s_FallbackTexture;
    }

}