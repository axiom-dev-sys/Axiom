#include "Axiom/Scene/Systems/PlayerInputSystem.hpp"

#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Entity.hpp"

#include "Axiom/Scene/Components/VelocityComponent.hpp"
#include "Axiom/Scene/Components/PlayerControllerComponent.hpp"

#include "Axiom/Input/Input.hpp"
#include <GLFW/glfw3.h>

namespace Axiom {

    void PlayerInputSystem::update(Scene& scene, float dt)
    {
        scene.forEach([&](Entity* entity)
        {
                (void)dt;

            auto* controller =
            entity->getComponent<PlayerControllerComponent>();
            
            auto* velocity = 
            entity->getComponent<VelocityComponent>();
            
            if (!controller || !velocity)
            return;
        
            float speed = controller->speed;
            
            velocity->velocity = glm::vec2(0.0f);
            
            if (Input::isKeyPressed(GLFW_KEY_W))
            velocity->velocity.y = speed;

            if (Input::isKeyPressed(GLFW_KEY_S))
            velocity->velocity.y = -speed;

            if (Input::isKeyPressed(GLFW_KEY_A))
            velocity->velocity.x = -speed;

            if (Input::isKeyPressed(GLFW_KEY_D))
            velocity->velocity.x = speed;

        });
    }
}