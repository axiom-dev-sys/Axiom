#pragma once
#include <GLFW/glfw3.h>

namespace Axiom {

    class Input
    {
    public:
        static bool isKeyPressed(int key);
        static void setWindow(GLFWwindow* window);

    private:
        static GLFWwindow* s_Window;
    };

}