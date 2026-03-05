#include "Axiom/Renderer/Renderer.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Axiom {

void Renderer::init()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		std::cout << "GLAD init failed\n";
}

void Renderer::clear()
{
	glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

}