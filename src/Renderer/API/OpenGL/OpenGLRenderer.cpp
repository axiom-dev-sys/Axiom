#include <glad/glad.h>
#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Renderer/API/OpenGL/OpenGLRenderer.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Axiom {

        void OpenGLRenderer::init() {
            glEnable(GL_DEPTH_TEST);
            float vertices[] = {
                -0.5f, -0.5f, 0.0f, 0.0f,
                0.5f, -0.5f, 1.0f, 0.0f,
                0.5f,  0.5f, 1.0f, 1.0f,
                -0.5f,  0.5f, 0.0f, 1.0f
            };

            m_Shader.init();
            debugShader.initDebug();

            unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
            };

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glGenVertexArrays(1, &debugLineVAO);
            glGenBuffers(1, &debugLineVBO);

            glBindVertexArray(debugLineVAO);
            glBindBuffer(GL_ARRAY_BUFFER, debugLineVBO);

            glBufferData(
                GL_ARRAY_BUFFER,
                sizeof(float) * 4,
                nullptr,
                GL_DYNAMIC_DRAW
            );

            glVertexAttribPointer(
                0,
                2,
                GL_FLOAT,
                GL_FALSE,
                2 * sizeof(float),
                (void*)0
            );

            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void OpenGLRenderer::clear() {
            glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void OpenGLRenderer::draw(Texture& texture, const glm::vec2& pos, const glm::vec2& scale, float rotation)
        {

            glm::mat4 model(1.0f);

            model = glm::translate(
            glm::mat4(1.0f),
            glm::vec3(pos.x, pos.y, 0.0f)
            );

            model = glm::rotate(
            model,
            glm::radians(rotation),
            glm::vec3(0.0f, 0.0f, 1.0f)
            );

            model = glm::scale(
            model,
            glm::vec3(scale.x, scale.y, 1.0f)
            );

            m_Shader.use();

            m_Shader.setMat4("uModel", model);
            
            m_Shader.setMat4("uView", Renderer::s_View);
            
            m_Shader.setMat4("uProjection", Renderer::s_Projection);

            m_Shader.setInt("uTex", 0);

            glBindVertexArray(VAO);

            texture.bind(0);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glBindVertexArray(0);

        }

        void OpenGLRenderer::drawDebugLine(
            const glm::vec2& start,
            const glm::vec2& end
        )
        {
            float vertices[] = {
                start.x, start.y,
                end.x, end.y
            };

            glBindVertexArray(debugLineVAO);
            glBindBuffer(GL_ARRAY_BUFFER, debugLineVBO);

            glBufferSubData(
                GL_ARRAY_BUFFER,
                0,
                sizeof(vertices),
                vertices
            );

            glDisable(GL_DEPTH_TEST);

            debugShader.use();
            debugShader.setMat4("uView", Renderer::s_View);
            debugShader.setMat4("uProjection", Renderer::s_Projection);

            glBindVertexArray(debugLineVAO);
            glBindBuffer(GL_ARRAY_BUFFER, debugLineVBO);

            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

            glLineWidth(3.0f);
            glDrawArrays(GL_LINES, 0, 2);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            glEnable(GL_DEPTH_TEST);
        }

}