#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Renderer/Texture.hpp"
#include "Axiom/Renderer/Renderer.hpp"
#include "Axiom/Scene/Components/SpriteComponent.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"
#include <iostream>
namespace Axiom {

    void Scene::onUpdate(float dt)
    {
        m_MovementSystem.update(*this, dt);
    }

    void Scene::followCamera(Entity* target)
    {
        m_CameraFollowSystem.follow(*this, target);
    }

    void Scene::onRender()
    {
        Renderer::beginScene(camera);

        m_RenderSystem.render(*this);

        Renderer::endScene();
    }
}