#include "Axiom/Core/Window.hpp"
#include <glad/glad.h>
#include <cstdlib>
#include "Axiom/Core/Log.hpp"

namespace Axiom {

    Window::Window(int width, int height, const char* title)
    {
        if (!glfwInit())
        {
            Log::error("Failed to initialize GLFW");
            std::exit(EXIT_FAILURE);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);

        if (!m_Window)
        {
            Log::error("Failed to create GLFW");
            std::exit(EXIT_FAILURE);

            glfwTerminate();
        }

        glfwMakeContextCurrent(m_Window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            Log::error("Failed to load GLAD");
            std::exit(EXIT_FAILURE);
        }

        glViewport(0, 0, width, height);
        
        glfwSetKeyCallback(m_Window,
            [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                if (action == GLFW_PRESS)
                {
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

    void Window::close()
    {
        glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
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