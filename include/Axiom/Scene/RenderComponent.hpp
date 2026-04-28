#pragma once
#include "Axiom/Scene/Component.hpp"
#include "Axiom/Scene/Transform.hpp"
#include "Axiom/Scene/SpriteComponent.hpp"
#include "Axiom/Scene/AnimationComponent.hpp"
#include "Axiom/Renderer/Renderer.hpp"

namespace Axiom {

    class RenderComponent : public Component
    {
    public:
        RenderComponent(Transform* transform,
            SpriteComponent* sprite,
            AnimationComponent* animation = nullptr)
            : m_Transform(transform),
            m_Sprite(sprite),
            m_Animation(animation) {}

        Texture* getTexture() const
        {
            if (m_Animation)
                return m_Animation->getCurrentFrame();

            if (m_Sprite)
                return m_Sprite->getTexture();

            return nullptr;
        }

        Transform* getTransform() const
        {
            return m_Transform;
        }

    private:
        Transform* m_Transform;
        SpriteComponent* m_Sprite;
        AnimationComponent* m_Animation;
    };

}