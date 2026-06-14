#include "Axiom/Scene/Systems/CameraFollowSystem.hpp"

#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"

namespace Axiom {

    void CameraFollowSystem::follow(Scene& scene, Entity* target, float dt)
    {
        if (!target)
            return;

        auto* transform =
            target->getComponent<TransformComponent>();

        if (!transform)
            return;

        auto targetPos = transform->position + scene.camera.offset;

        scene.camera.position +=
        (targetPos - scene.camera.position) * 5.0f * dt;
        
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