#include "Axiom/Scene/Systems/RenderSystem.hpp"

#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Entity.hpp"

#include "Axiom/Scene/Components/TransformComponent.hpp"
#include "Axiom/Scene/Components/SpriteComponent.hpp"

#include "Axiom/Renderer/Renderer.hpp"

#include <iostream>

namespace Axiom {

void RenderSystem::render(Scene& scene)
{

    int count = 0;

    count++;
    
    scene.forEach([&](Entity* entity)
    {
        std::cout << "Entity\n";

        auto* transform =
            entity->getComponent<TransformComponent>();

        auto* sprite =
            entity->getComponent<SpriteComponent>();

        std::cout << "Transform: "
              << (transform != nullptr)
              << std::endl;

        std::cout << "Sprite: "
              << (sprite != nullptr)
              << std::endl;

        if (!transform || !sprite)
            return;

        if (!sprite->getTexture())
            return;

        std::cout << "SUBMIT\n";

        Renderer::submit(
            sprite->getTexture(),
            transform->position,
            transform->scale,
            transform->rotation
        );
    });
}

}