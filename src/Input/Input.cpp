#include "Axiom/Input/Input.hpp"

namespace Axiom {

    GLFWwindow* Input::s_Window = nullptr;

    void Input::setWindow(GLFWwindow* window)
    {
        s_Window = window;
    }

    bool Input::isKeyPressed(int key)
    {
        if (!s_Window)
            return false;

        auto state = glfwGetKey(s_Window, key);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::isKeyDown(int key)
    {
        if (!s_Window)
            return false;

        auto state = glfwGetKey(s_Window, key);
        return state == GLFW_PRESS;
    }

}