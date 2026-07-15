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

    bool Input::isMouseButtonPressed(int button)
    {
        if (!s_Window)
            return false;

        auto state = glfwGetMouseButton(
            s_Window,
            button
        );

        return state == GLFW_PRESS;
    }

    double Input::getMouseX()
    {
        double x, y;

        glfwGetCursorPos(
            s_Window,
            &x,
            &y
        );

        return x;
    }

    double Input::getMouseY()
    {
        double x, y;

        glfwGetCursorPos(
            s_Window,
            &x,
            &y
        );

        return y;
    }

}