#pragma once

namespace Axiom {

    class Scene;

    class TimerSystem
    {
    public:
        void update(Scene& scene, float dt);
    };

}