#pragma once
#include "Axiom/Scene/Component.hpp"
#include "Axiom/Scene/Transform.hpp"
#include "Axiom/Scene/SpriteComponent.hpp"
#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Scene/AnimationComponent.hpp"



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

        void onUpdate() override
        {
            if (!m_Transform) return;

            Texture* texture = nullptr;

                if (m_Animation)
                    texture = m_Animation->getCurrentFrame();
                else if (m_Sprite)
                    texture = m_Sprite->getTexture();

            if (!texture) return;

            texture->bind();

            Renderer::draw(*texture, { m_Transform->x, m_Transform->y });
        }

    private:
        Transform* m_Transform;
        SpriteComponent* m_Sprite;
        AnimationComponent* m_Animation;
    };

}