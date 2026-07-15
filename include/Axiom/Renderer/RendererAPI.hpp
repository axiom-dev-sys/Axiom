#pragma once
#include "Axiom/Renderer/Texture.hpp"
#include <glm/glm.hpp>

namespace Axiom {

    class RendererAPI {
    public:
        virtual ~RendererAPI() = default;

        virtual void init() = 0;
        virtual void clear() = 0;
        virtual void draw(Texture& texture, 
                            const glm::vec2& pos, 
                            const glm::vec2& scale,
                            float rotation
                        ) = 0;

        virtual void drawDebugLine(
            const glm::vec2& start,
            const glm::vec2& end,
            const glm::vec4& color
        ) = 0;
    };

}