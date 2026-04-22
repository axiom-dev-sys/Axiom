#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Renderer/Shader.hpp"

#include <glad/glad.h>
#include <iostream>

namespace Axiom {

    static GLuint VAO = 0;
    static GLuint VBO = 0;

    float Renderer::camX = 0;
    float Renderer::camY = 0;

    void Renderer::init()
    {
        float vertices[] = {
            // pos      // uv
            -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  1.0f, 1.0f,

             0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.0f, 0.0f
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

        // uv
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        glBindVertexArray(0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        std::cout << "Renderer initialized\n";
    }

    void Renderer::clear()
    {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::setCamera(float x, float y)
    {
        camX = x;
        camY = y;
    }

    void Renderer::draw(Texture& texture, Vec2 position)
    {
        if (texture.getID() == 0)
        {
            std::cout << "Texture ID = 0\n";
            return;
        }

        Shader::use();

        texture.bind(0);

        Shader::setTransform(
            position.x,
            position.y,
            1.0f,
            1.0f
        );

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

}