#pragma once
#include "Axiom/Scene/Component.hpp"
#include "Axiom/Renderer/Texture.hpp"

namespace Axiom {

    class SpriteComponent : public Component
    {
    public:
        Texture* texture = nullptr;
        SpriteComponent(Texture* texture,
            float r = 1.0f,
            float g = 1.0f,
            float b = 1.0f)
            : m_Texture(texture), m_R(r), m_G(g), m_B(b) {
        }

        Texture* getTexture() const { return m_Texture; }

        float getR() const { return m_R; }
        float getG() const { return m_G; }
        float getB() const { return m_B; }

    private:
        Texture* m_Texture;
        float m_R, m_G, m_B;
    };

}