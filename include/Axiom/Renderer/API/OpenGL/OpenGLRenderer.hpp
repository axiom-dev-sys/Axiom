#pragma once
#include "Axiom/Renderer/RendererAPI.hpp"
#include "Axiom/Renderer/Texture.hpp"
#include "Axiom/Math/Vec2.hpp"
#include "Axiom/Renderer/Shader.hpp"

namespace Axiom {

    class OpenGLRenderer : public RendererAPI {
    public:
        void init() override;
        void clear() override;
        void draw(Texture& texture, const Vec2& pos) override;

    private:
        unsigned int VAO = 0;
        unsigned int VBO = 0;
        unsigned int EBO = 0;

        Shader m_Shader;
    };

}