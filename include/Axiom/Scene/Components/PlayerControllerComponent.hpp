#pragma once
#include "Axiom/Scene/Component.hpp"

namespace Axiom {

    struct PlayerControllerComponent : public Component
    {
        float speed = 500.0f;
    };

}