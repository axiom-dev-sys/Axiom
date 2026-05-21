#include <glad/glad.h>
#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Renderer/API/OpenGL/OpenGLRenderer.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Axiom {

        void OpenGLRenderer::init() {
            glEnable(GL_DEPTH_TEST);
            float vertices[] = {
                // pos      // tex
                -0.5f, -0.5f, 0.0f, 0.0f,
                 0.5f, -0.5f, 1.0f, 0.0f,
                 0.5f,  0.5f, 1.0f, 1.0f,
                -0.5f,  0.5f, 0.0f, 1.0f
            };

            m_Shader.init();

            unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
            };

            // VAO/VBO/EBO
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // pos
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            // tex
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }

        void OpenGLRenderer::clear() {
            glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void OpenGLRenderer::draw(Texture& texture, const glm::vec2& pos, const glm::vec2& scale)
        {
            glm::mat4 view = Renderer::getCamera()->getViewMatrix();

            glm::mat4 projection = glm::ortho(
                -1.0f, 1.0f,
                -1.0f, 1.0f
            );

            glm::mat4 model = glm::translate(
            glm::mat4(1.0f),
            glm::vec3(pos.x, pos.y, 0.0f)
            );

            model = glm::scale(
            model,
            glm::vec3(scale.x, scale.y, 1.0f)
            );

            m_Shader.use();

            m_Shader.setInt("uTex", 0);

            m_Shader.setMat4("uModel", glm::value_ptr(model));

            m_Shader.setMat4("uView", glm::value_ptr(view));

            m_Shader.setMat4("uProjection", glm::value_ptr(projection));

            glBindVertexArray(VAO);

            texture.bind(0);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            std::cout << "DRAW\n";
        }

}