#pragma once

namespace Axiom {

    class Time
    {
    public:
        static float deltaTime;
        static float lastFrame;

        static void update();
    };

}