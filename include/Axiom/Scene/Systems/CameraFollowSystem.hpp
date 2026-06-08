#pragma once

#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"

namespace Axiom {

class CameraFollowSystem
{
public:
    void follow(Scene& scene, Entity* target)
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
};

}