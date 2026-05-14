#pragma once
#include "Axiom/Math/Vec2.hpp"
#include "Component.hpp"

namespace Axiom {

    struct Transform: public Component
    {
        Vec2 position{ 0.0f, 0.0f };
        Vec2 scale{ 1.0f, 1.0f };

        float rotation = 0.0f;
    };

}