#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/RenderComponent.hpp"
#include "Axiom/Renderer/Texture.hpp"
#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Core/Log.hpp"
#include "Axiom/Scene/TextureComponent.hpp"
#include "Axiom/Scene/Transform.hpp"

namespace Axiom {

    void Scene::onUpdate(float dt)
    {

    }

    void Scene::onRender()
    {
        Renderer::beginScene(camera);

for (auto& entity : m_Entities)
{
    auto transform = entity->getComponent<Transform>();
    auto render = entity->getComponent<RenderComponent>();

    if (!transform || !render || !render->texture)
        continue;

    Renderer::submit(render->texture, transform->position);
}

        Renderer::endScene();
    }
}