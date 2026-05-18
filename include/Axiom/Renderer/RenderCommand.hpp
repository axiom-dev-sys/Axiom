#pragma once

#include <glm/glm.hpp>

namespace Axiom {

    struct Texture;

    struct RenderCommand
    {
        Texture* texture = nullptr;
        glm::vec2 position{ 0.0f, 0.0f };
    };

}