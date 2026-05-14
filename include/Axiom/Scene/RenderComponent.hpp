#pragma once
#include "Axiom/Scene/Component.hpp"
#include "Axiom/Renderer/Texture.hpp"

namespace Axiom {

    class Texture;
    class Transform;
    class SpriteComponent;
    class AnimationComponent;

    struct RenderComponent : public Component
    {
    public:
        RenderComponent() = default;

        void setTexture(Texture* tex);
        Texture* getTexture() const;

        Transform* getTransform()
        {
            return m_Transform;
        }

    public:
        Texture* texture = nullptr;

    private:
        Transform* m_Transform;
        SpriteComponent* m_Sprite;
        AnimationComponent* m_Animation;
    };

}