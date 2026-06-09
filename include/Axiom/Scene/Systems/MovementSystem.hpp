#pragma once

namespace Axiom {

    class Scene;

    class MovementSystem
    {
    public:
        void update(Scene& scene, float dt);
    };

}