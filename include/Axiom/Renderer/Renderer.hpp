#pragma once
#include "Texture.hpp"

namespace Axiom {

    struct Vec2 { float x, y; };

    class Renderer
    {
    public:
        static void init();
        static void clear();

        static void setCamera(float x, float y);
        static void draw(Texture& tex, Vec2 pos);

    private:
        static float camX, camY;
    };

}