#pragma once
#include "Axiom/Renderer/RendererAPI.hpp"
#include "Axiom/Camera/Camera.hpp"
#include "Axiom/Renderer/Texture.hpp"
#include "Axiom/Math/Vec2.hpp"
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

        static void beginScene(const Camera& camera);
        static void submit(Texture* tex, Vec2 pos);
        static void endScene();
        static void flush();

    private:
        static std::unique_ptr<RendererAPI> s_API;
        static std::vector<DrawCommand> s_Queue;
        static const Camera* s_Camera;
    };

}