#include "Axiom/Core/Window.hpp"
#include <glad/glad.h> 
#include <iostream>

namespace Axiom {

    Window::Window(int width, int height, const char* title)
    {
        if (!glfwInit())
        {
            std::cout << "GLFW init failed\n";
            abort();
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);

        if (!m_Window)
        {
            std::cout << "Window creation failed\n";
            glfwTerminate();
            abort();
        }

        glfwMakeContextCurrent(m_Window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to init GLAD\n";
            abort();
        }

        glViewport(0, 0, width, height);


        glfwSetKeyCallback(m_Window,
            [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                if (action == GLFW_PRESS)
                {
                    std::cout << "Key pressed: " << key << std::endl;
                }
            });
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    bool Window::shouldClose() const
    {
        return glfwWindowShouldClose(m_Window);
    }

    void Window::pollEvents()
    {
        glfwPollEvents();
    }

    void Window::swapBuffers()
    {
        glfwSwapBuffers(m_Window);
    }

    GLFWwindow* Window::getNative() const
    {
        return m_Window;
    }

}