#pragma once

#include "Axiom/Scene/Component.hpp"

namespace Axiom {

    class TimerComponent : public Component
    {
    public:
        float time = 0.0f;
        float duration = 1.0f;

        bool loop = false;
        bool finished = false;
    };

}