#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Axiom {

    class Camera {
    public:
        glm::vec2 position{ 0, 0 };

    glm::mat4 getViewMatrix() const
    {
        return glm::translate(
            glm::mat4(1.0f),
            glm::vec3(-position.x, -position.y, 0.0f)
        );
    }

};

}