#include "Axiom/Scene/Systems/CameraFollowSystem.hpp"

#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"
#include "Axiom/Scene/Components/VelocityComponent.hpp"

namespace Axiom {

    void CameraFollowSystem::follow(Scene& scene, Entity* target, float dt)
    {
        if (!target)
            return;

        auto* transform =
            target->getComponent<TransformComponent>();

        if (!transform)
            return;

        auto* velocity = target->getComponent<VelocityComponent>();

        auto targetPos = transform->position + scene.camera.offset;

        scene.camera.position +=
        (targetPos - scene.camera.position) * 5.0f * dt;

        glm::vec2 offset = {0.0f, 0.0f};

        if (velocity)
        {
            constexpr float k = 0.1f;
            offset.x = velocity->velocity.x * k;
        }
        
        scene.camera.position.x =
        glm::clamp(scene.camera.position.x,
            scene.camera.minBounds.x,
            scene.camera.maxBounds.x);
            
        scene.camera.position.y =
        glm::clamp(scene.camera.position.y,
            scene.camera.minBounds.y,
            scene.camera.maxBounds.y);
    }
}