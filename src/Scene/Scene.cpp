#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Renderer/Texture.hpp"
#include "Axiom/Renderer/Renderer.hpp"

#include <iostream>

#include "Axiom/Scene/Components/SpriteComponent.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"

namespace Axiom {

    void Scene::onUpdate(float dt)
    {

    }

    void Scene::onRender()
    {

        Renderer::beginScene(camera);
        
        std::cout << "Entities: " << m_Entities.size() << std::endl;

        for (auto& entity : m_Entities)
        {
        auto* transform = entity->getComponent<TransformComponent>();
        auto sprite = entity->getComponent<SpriteComponent>();

        if (!transform || !sprite || !sprite->getTexture())
            continue;

        Renderer::submit(sprite->getTexture(), transform->position);
        }

        Renderer::endScene();
    }
}