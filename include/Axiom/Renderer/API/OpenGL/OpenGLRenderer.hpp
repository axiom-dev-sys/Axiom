#pragma once
#include "Axiom/Renderer/RendererAPI.hpp"
#include "Axiom/Renderer/Texture.hpp"
#include "Axiom/Renderer/Shader.hpp"

namespace Axiom {

    class OpenGLRenderer : public RendererAPI {
    public:
        void init() override;
        void clear() override;
        void draw(Texture& texture, const glm::vec2& pos, const glm::vec2& scale, float rotation) override;
        void drawDebugLine(const glm::vec2& start, const glm::vec2& end);

    private:
        unsigned int VAO = 0;
        unsigned int VBO = 0;
        unsigned int EBO = 0;
        unsigned int debugLineVAO = 0;
        unsigned int debugLineVBO = 0;

        Shader m_Shader;
        Shader debugShader;
    };

}