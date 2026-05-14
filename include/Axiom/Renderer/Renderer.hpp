#pragma once
#include "Axiom/Renderer/Camera.hpp"
#include "Axiom/Renderer/Texture.hpp"
#include "RendererAPI.hpp"
#include <memory>
#include <vector>

namespace Axiom {

    struct DrawCommand
    {
        Texture* texture;
        Vec2 position;
    };

    class Renderer {
    public:
        static void init(); 
        static void clear();
        
        virtual void draw(Texture& texture, const Vec2& position) = 0;

        static void beginScene(const Camera& camera);
        static void submit(Texture* tex, Vec2 pos);
        static void endScene();
        static void flush();
}