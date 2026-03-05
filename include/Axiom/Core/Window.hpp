#pragma once
#include <GLFW/glfw3.h>

namespace Axiom {

	class Window
	{
	public:
		Window(int width, int height, const char* title);
		~Window();

		bool shouldClose() const;
		void pollEvents();
		void swapBuffers();

		GLFWwindow* getNative() const;

	private:
		GLFWwindow* m_Window;
	};

}