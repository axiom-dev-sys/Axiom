#pragma once
#include <GLFW/glfw3.h>

namespace Axiom {

    class Input
    {
    public:
        static void setWindow(GLFWwindow* window);

        static bool isKeyDown(int key);
        static bool isKeyPressed(int key);

        static bool isMouseButtonPressed(int button);

        static double getMouseX();
        static double getMouseY();

    private:
        static GLFWwindow* s_Window;
    };

}