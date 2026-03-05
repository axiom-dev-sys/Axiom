#include "Axiom/Core/Window.hpp"
#include <iostream>

namespace Axiom {

	Window::Window(int width, int height, const char* title)
	{
		if (!glfwInit())
			std::cout << "GLFW init failed\n";

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

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