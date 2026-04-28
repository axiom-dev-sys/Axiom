#pragma once
#include "Axiom/Renderer/Texture.hpp"
#include "Axiom/Math/Vec2.hpp"

namespace Axiom {

    class Renderer {
    public:
        static void init();
        static void clear();

        static void draw(Texture& tex, Vec2 pos);

    private:
        static unsigned int VAO, VBO;
    };

}