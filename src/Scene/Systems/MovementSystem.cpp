#include "Axiom/Scene/Systems/MovementSystem.hpp"

#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"
#include "Axiom/Scene/Components/VelocityComponent.hpp"

namespace Axiom {

    void MovementSystem::update(Scene& scene, float dt)
    {
        scene.forEach([&](Entity* entity)
        {
            auto* transform =
            entity->getComponent<TransformComponent>();
            
            auto* velocity =
            entity->getComponent<VelocityComponent>();
            
            if (!transform || !velocity)
            return;
        
            transform->position += velocity->velocity * dt;
        });
    }
}