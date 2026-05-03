#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Renderer/Shader.hpp"
#include "Axiom/Renderer/Texture.hpp"
#include "Axiom/Game/GameLayer.hpp"

int main()
{
    std::cout << "HELLO FROM MAIN" << std::endl;

    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Axiom", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to init GLAD\n";
        return -1;
    }

    Axiom::Renderer::init();

    std::cout << "Before layer\n";

    GameLayer layer;

    std::cout << "After layer\n";

    while (!glfwWindowShouldClose(window))
    {
        Axiom::Renderer::clear();

        layer.onRender(); // 👈 вызываем рендер слоя

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}