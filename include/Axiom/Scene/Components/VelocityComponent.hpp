#pragma once
#include "Axiom/Scene/Component.hpp"
#include <glm/glm.hpp>

namespace Axiom {

    struct VelocityComponent : public Component
    {
        glm::vec2 velocity {0.0f, 0.0f};
    };

}