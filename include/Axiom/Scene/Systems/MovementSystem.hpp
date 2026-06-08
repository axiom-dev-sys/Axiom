#pragma once

#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"
#include "Axiom/Scene/Components/VelocityComponent.hpp"

namespace Axiom {

    class MovementSystem
    {
    public:
        void update(Scene& scene, float dt)
        {
            scene.forEach([&](Entity* entity)
            {
                auto* transform =
                    entity->getComponent<TransformComponent>();

                auto* velocity =
                    entity->getComponent<VelocityComponent>();
                    
                    if (!transform || !velocity)
                        return;

                transform->position +=
                    velocity->velocity * dt;
            });
        }
    };

}