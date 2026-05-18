#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Renderer/API/OpenGL/OpenGLRenderer.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

    static Camera s_Camera;

    void Renderer::beginScene(const Camera& camera)
    {
        s_Camera = &camera;
    }

    void Renderer::submit(Texture* tex, glm::vec2 pos)
    {
        if (!tex) return;

        std::cout << "[Renderer] submit called\n";;

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
            std::cout << "DRAW CALL: " << cmd.position.x << ", " << cmd.position.y << std::endl;
            std::cout << "[Renderer] flush, size: " << s_Queue.size() << std::endl;
        }

        s_Queue.clear();
    }

}