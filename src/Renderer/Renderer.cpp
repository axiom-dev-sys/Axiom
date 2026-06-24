#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Renderer/API/OpenGL/OpenGLRenderer.hpp"
#include <glm/glm.hpp>

namespace Axiom {

    std::unique_ptr<RendererAPI> Renderer::s_API =
        std::make_unique<OpenGLRenderer>();

    std::vector<DrawCommand> Renderer::s_Queue;

    glm::mat4 Renderer::s_View = glm::mat4(1.0f);

    glm::mat4 Renderer::s_Projection = glm::mat4(1.0f);

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

        s_View = camera.getViewMatrix();
        s_Projection = camera.getProjectionMatrix();

        s_Queue.clear();
    }

    void Renderer::submit(Texture* tex, glm::vec2 pos, glm::vec2 scale, float rotation)
    {
        if (!tex) return;

        s_Queue.push_back({ tex, pos, scale, rotation });
    }

    void Renderer::endScene()
    {
        flush();
    }

    void Renderer::flush()
    {
        for (auto& cmd : s_Queue)
        {
            s_API->draw(*cmd.texture,
                        cmd.position, 
                        cmd.scale, 
                        cmd.rotation
                    );
        }
        s_Queue.clear();
    }

    void Renderer::drawDebugLine(
        const glm::vec2& start,
        const glm::vec2& end
    )
    {
        s_API->drawDebugLine(start, end);
    }

    void Renderer::drawDebugRect(const glm::vec2& position, const glm::vec2& size)
    {
        drawDebugLine(position, { position.x + size.x, position.y });
        drawDebugLine({ position.x + size.x, position.y }, { position.x + size.x, position.y + size.y });
        drawDebugLine({ position.x + size.x, position.y + size.y }, { position.x, position.y + size.y });
        drawDebugLine({ position.x, position.y + size.y }, position);
    }

}