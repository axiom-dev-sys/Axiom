#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Renderer/API/OpenGL/OpenGLRenderer.hpp"

namespace Axiom {

    std::unique_ptr<RendererAPI> Renderer::s_API =
        std::make_unique<OpenGLRenderer>();

    std::vector<DrawCommand> Renderer::s_Queue;

    const Camera* Renderer::s_Camera = nullptr;

    void Renderer::init() {
        s_API->init();
    }

    void Renderer::clear() {
        s_API->clear();
    }

    void Renderer::beginScene(const Camera& camera)
    {
        s_Camera = &camera;
    }

    void Renderer::submit(Texture* tex, Vec2 pos)
    {
        if (!tex) return;

        s_Queue.push_back({ tex, pos });
    }

    void Renderer::endScene()
    {
        flush();
    }

    void Renderer::flush()
    {
        for (auto& cmd : s_Queue)
        {
            s_API->draw(*cmd.texture, cmd.position);
        }

        s_Queue.clear();
    }

}