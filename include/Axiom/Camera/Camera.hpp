#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Axiom {

    class Camera {
    public:
        glm::vec2 position{ 0, 0 };
        
        glm::vec2 minBounds{ -100000.0f, -100000.0f };
        glm::vec2 maxBounds{  100000.0f,  100000.0f };
        
        glm::vec2 offset{ 0, 0 };

        float zoom = 1.0f;
        
        glm::mat4 getViewMatrix() const
        {
            return glm::translate(
                glm::mat4(1.0f),
                glm::vec3(-position.x, -position.y, 0.0f)
            );
        }
        
        glm::mat4 getProjectionMatrix() const
        {
            return glm::ortho(
                -640.0f * zoom, 640.0f * zoom,
                -360.0f * zoom, 360.0f * zoom,
                -1.0f, 1.0f
            );
        }
};

}