#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Renderer/Shader.hpp"
#include "Axiom/Renderer/Camera.hpp"
#include "Axiom/Math/Vec2.hpp"
#include <glad/glad.h>

namespace Axiom {

    static Shader shader;

    unsigned int Renderer::VAO = 0;
    unsigned int Renderer::VBO = 0;

    void Renderer::init()
    {
        shader.init();

        float v[] = {
            -0.5f,-0.5f, 0,0,
             0.5f,-0.5f, 1,0,
             0.5f, 0.5f, 1,1,

             0.5f, 0.5f, 1,1,
            -0.5f, 0.5f, 0,1,
            -0.5f,-0.5f, 0,0
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    void Renderer::clear()
    {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::draw(Texture& tex, Vec2 pos)
    {
        shader.use();

        float w = 100.0f;
        float h = 100.0f;

        float vertices[] = {
            pos.x,     pos.y,     0,0,
            pos.x + w,   pos.y,     1,0,
            pos.x + w,   pos.y + h,   1,1,

            pos.x,     pos.y,     0,0,
            pos.x + w,   pos.y + h,   1,1,
            pos.x,     pos.y + h,   0,1
        };

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex.getID());
        shader.setInt("uTex", 0);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

}