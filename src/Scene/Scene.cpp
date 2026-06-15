#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Renderer/Renderer.hpp"

namespace Axiom {

    void Scene::onUpdate(float dt)
    {
        m_PlayerInputSystem.update(*this, dt);
        m_MovementSystem.update(*this, dt);
        m_TimerSystem.update(*this, dt);

        cleanupDestroyedEntities();
    }

    void Scene::followCamera(Entity* target, float dt)
    {
        m_CameraFollowSystem.follow(*this, target, dt);
    }

    void Scene::onRender()
    {
        Renderer::beginScene(camera);

        m_RenderSystem.render(*this);

        Renderer::endScene();
    }
}