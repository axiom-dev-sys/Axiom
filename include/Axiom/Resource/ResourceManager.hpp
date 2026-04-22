#pragma once
#include <unordered_map>
#include <string>
#include <memory>

#include "Axiom/Renderer/Texture.hpp"

namespace Axiom {

    class ResourceManager
    {
    public:
        static void init();
        static void shutdown();

        static Texture* loadTexture(const std::string& path);
        static Texture* getTexture(const std::string& path);

    private:
        static std::unordered_map<std::string, std::unique_ptr<Texture>> s_Textures;
        static Texture* s_FallbackTexture; // ?? добавь
    };

}