#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include "Axiom/Core/Time.hpp"



namespace Axiom {

    float Time::s_DeltaTime = 0.0f;
    float Time::s_LastTime = 0.0f;

    void Time::update()
    {
        float currentFrame = glfwGetTime();
        s_DeltaTime = currentFrame - s_LastTime;
        s_LastTime = currentFrame;
    }

    float Time::getDeltaTime()
    {
        return s_DeltaTime;
    }

}