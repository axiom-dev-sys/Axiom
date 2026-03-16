#include "Axiom/Core/Time.hpp"
#include <GLFW/glfw3.h>

namespace Axiom {

    float Time::deltaTime = 0.0f;
    float Time::lastFrame = 0.0f;

    void Time::update()
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }

}