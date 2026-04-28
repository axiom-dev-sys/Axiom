#pragma once
#include "Axiom/Math/Vec2.hpp"

namespace Axiom {

    class Camera {
    public:
        Vec2 position;

        static void set(float x, float y);
    };

}