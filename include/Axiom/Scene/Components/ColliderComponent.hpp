#pragma once

#include "Axiom/Scene/Component.hpp"
#include <glm/glm.hpp>

namespace Axiom {

    class ColliderComponent : public Component
    {
    public:
        glm::vec2 size{1.0f, 1.0f};
        glm::vec2 offset{0.0f, 0.0f};

        bool isTrigger = false;
    };

}