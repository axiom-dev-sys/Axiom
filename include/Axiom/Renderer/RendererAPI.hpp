#pragma once
#include "Axiom/Renderer/Texture.hpp"
#include "Axiom/Math/Vec2.hpp"

namespace Axiom {

    class RendererAPI {
    public:
        virtual ~RendererAPI() = default;

        virtual void init() = 0;
        virtual void clear() = 0;
        virtual void draw(Texture& texture, const Vec2& pos) = 0;
    };

}