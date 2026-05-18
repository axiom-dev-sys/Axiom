#pragma once
#include "Axiom/Scene/Component.hpp"
#include "Axiom/Renderer/Texture.hpp"

namespace Axiom {

    class SpriteComponent : public Component
    {
    public:
        SpriteComponent(Texture* texture,
            float r = 1.0f,
            float g = 1.0f,
            float b = 1.0f)
            : m_Texture(texture), m_R(r), m_G(g), m_B(b) {
        }

        Texture* getTexture() const { return m_Texture; }

    private:
        Texture* m_Texture = nullptr;
        float m_R, m_G, m_B;
    };

}