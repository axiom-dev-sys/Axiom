#include "Axiom/Scene/Systems/TimerSystem.hpp"

#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Scene/Components/TimerComponent.hpp"

namespace Axiom {

    void TimerSystem::update(Scene& scene, float dt)
    {
        scene.forEach([&](Entity* entity)
        {
            auto* timer =
                entity->getComponent<TimerComponent>();

            if (!timer || timer->finished)
                return;

            timer->time += dt;

            if (timer->time >= timer->duration)
            {
                if (timer->loop)
                {
                    timer->time = 0.0f;
                }
                else
                {
                    timer->finished = true;
                }
            }
        });
    }

}