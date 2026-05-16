#pragma once

#include "Axiom/Math/Vec2.hpp"

namespace Axiom {

    struct Texture;

    struct RenderCommand
    {
        Texture* texture = nullptr;
        Vec2 position{ 0.0f, 0.0f };
    };

}