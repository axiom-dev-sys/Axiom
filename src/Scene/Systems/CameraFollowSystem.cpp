#include "Axiom/Scene/Systems/CameraFollowSystem.hpp"

#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"

namespace Axiom {

    void CameraFollowSystem::follow(Scene& scene, Entity* target)
    {
        if (!target)
            return;

        auto* transform =
            target->getComponent<TransformComponent>();

        if (!transform)
            return;

        scene.camera.position =
            transform->position;
    }
}