#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"
#include "Axiom/Scene/Components/SpriteComponent.hpp"
#include "Axiom/Scene/Components/VelocityComponent.hpp"
#include "Axiom/Scene/Components/PlayerControllerComponent.hpp"
#include "Axiom/Scene/Components/PlayerTag.hpp"
#include "Axiom/Scene/Components/ColliderComponent.hpp"
#include "Axiom/Resource/ResourceManager.hpp"
#include "Axiom/Renderer/Renderer.hpp"

namespace Axiom {

    void Scene::onUpdate(float dt)
    {
        m_PlayerInputSystem.update(*this, dt);
        m_MovementSystem.update(*this, dt);
        m_TimerSystem.update(*this, dt);

        cleanupDestroyedEntities();
    }

    std::shared_ptr<Scene> Scene::clone() const
    {
        auto newScene = std::make_shared<Scene>();

        newScene->camera = camera;

        for (const auto& sourceEntityPtr : m_Entities)
        {
            Entity* source = sourceEntityPtr.get();

            if (!source || source->isDestroyed())
                continue;

            Entity* copy = newScene->createEntity(source->getName());

            if (auto* transform = source->getComponent<TransformComponent>())
            {
                auto* newTransform = copy->addComponent<TransformComponent>();
                *newTransform = *transform;
            }

            if (auto* sprite = source->getComponent<SpriteComponent>())
            {
                copy->addComponent<SpriteComponent>(
                    sprite->getTextureID(),
                    ResourceManager::getTexture(sprite->getTextureID())
                );
            }

            if (source->hasComponent<VelocityComponent>())
            {
                copy->addComponent<VelocityComponent>();
            }

            if (source->hasComponent<PlayerControllerComponent>())
            {
                copy->addComponent<PlayerControllerComponent>();
            }

            if (source->hasComponent<PlayerTag>())
            {
                copy->addComponent<PlayerTag>();
            }

            if (auto* collider = source->getComponent<ColliderComponent>())
            {
                auto* newCollider = copy->addComponent<ColliderComponent>();
                *newCollider = *collider;
            }
        }

        return newScene;
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