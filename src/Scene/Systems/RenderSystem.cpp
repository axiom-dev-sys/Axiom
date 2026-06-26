#include "Axiom/Scene/Systems/RenderSystem.hpp"

#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Entity.hpp"

#include "Axiom/Scene/Components/TransformComponent.hpp"
#include "Axiom/Scene/Components/SpriteComponent.hpp"

#include "Axiom/Renderer/Renderer.hpp"

namespace Axiom {

void RenderSystem::render(Scene& scene)
{    
    scene.forEach([&](Entity* entity)
    {

        auto* transform =
            entity->getComponent<TransformComponent>();

        auto* sprite =
            entity->getComponent<SpriteComponent>();

        if (!transform || !sprite)
            return;

        if (!sprite->getTexture())
            return;

        Renderer::submit(
            sprite->getTexture(),
            transform->position,
            transform->scale,
            transform->rotation
        );
    });
}

}