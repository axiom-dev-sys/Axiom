#pragma once
#include "Axiom/Renderer/RendererAPI.hpp"
#include "Axiom/Camera/Camera.hpp"
#include "Axiom/Renderer/Texture.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace Axiom {

    struct DrawCommand
    {
        Texture* texture;
        glm::vec2 position;
        glm::vec2 scale;
        float rotation;
    };

    class Renderer {
    public:
        static void init(); 
        static void clear();

        static glm::mat4 s_View;
        static glm::mat4 s_Projection;

        static void beginScene(const Camera& camera);
        static void submit(Texture* tex, glm::vec2 pos, glm::vec2 scale, float rotation);
        static void endScene();
        static void flush();

        static const Camera* getCamera()
        {
            return s_Camera;
        }

    private:
        static std::unique_ptr<RendererAPI> s_API;
        static std::vector<DrawCommand> s_Queue;
        static const Camera* s_Camera;
    };

}