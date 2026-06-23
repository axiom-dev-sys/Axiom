#pragma once
#include "Axiom/Scene/Component.hpp"
#include "Axiom/Renderer/Texture.hpp"
#include <string>

namespace Axiom {

    class SpriteComponent : public Component
    {
    public:
        SpriteComponent(const std::string& textureID, 
            Texture* texture,
            float r = 1.0f,
            float g = 1.0f,
            float b = 1.0f)
            : m_TextureID(textureID), m_Texture(texture), m_R(r), m_G(g), m_B(b) {
        }

        Texture* getTexture() const { return m_Texture; }

        const std::string& getTextureID() const
        {
            return m_TextureID;
        }

        void setTexture(const std::string& textureID, Texture* texture)
        {
            m_TextureID = textureID;
            m_Texture = texture;
        }

    private:
        std::string m_TextureID;
        Texture* m_Texture = nullptr;
        float m_R, m_G, m_B;
    };

}