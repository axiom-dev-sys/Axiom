#include "Axiom/Editor/EditorComponentOperations.hpp"

#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Scene/Components/VelocityComponent.hpp"
#include "Axiom/Scene/Components/ColliderComponent.hpp"
#include "Axiom/Scene/Components/SpriteComponent.hpp"
#include "Axiom/Resource/ResourceManager.hpp"

namespace Axiom {

    bool EditorComponentOperations::addVelocityComponent(
        Entity* entity)
    {
        if (!entity ||
            entity->isDestroyed() ||
            entity->hasComponent<VelocityComponent>())
        {
            return false;
        }

        entity->addComponent<VelocityComponent>();

        return true;
    }

    bool EditorComponentOperations::removeVelocityComponent(
        Entity* entity)
    {
        if (!entity ||
            entity->isDestroyed() ||
            !entity->hasComponent<VelocityComponent>())
        {
            return false;
        }

        entity->removeComponent<VelocityComponent>();

        return true;
    }

    bool EditorComponentOperations::addColliderComponent(
        Entity* entity)
    {
        if (!entity ||
            entity->isDestroyed() ||
            entity->hasComponent<ColliderComponent>())
        {
            return false;
        }

        auto* collider =
            entity->addComponent<ColliderComponent>();

        if (!collider)
            return false;

        collider->size = { 128.0f, 128.0f };
        collider->offset = { 0.0f, 0.0f };
        collider->isTrigger = false;

        return true;
    }

    bool EditorComponentOperations::removeColliderComponent(
        Entity* entity)
    {
        if (!entity ||
            entity->isDestroyed() ||
            !entity->hasComponent<ColliderComponent>())
        {
            return false;
        }

        entity->removeComponent<ColliderComponent>();

        return true;
    }

    bool EditorComponentOperations::addSpriteComponent(
        Entity* entity)
    {
        if (!entity ||
            entity->isDestroyed() ||
            entity->hasComponent<SpriteComponent>())
        {
            return false;
        }

        entity->addComponent<SpriteComponent>(
            "test",
            ResourceManager::getTexture("test")
        );

        return true;
    }

    bool EditorComponentOperations::removeSpriteComponent(
        Entity* entity)
    {
        if (!entity ||
            entity->isDestroyed() ||
            !entity->hasComponent<SpriteComponent>())
        {
            return false;
        }

        entity->removeComponent<SpriteComponent>();

        return true;
    }

    bool EditorComponentOperations::setSpriteTexture(
        Entity* entity,
        const std::string& textureID)
    {
        if (!entity ||
            entity->isDestroyed() ||
            !entity->hasComponent<SpriteComponent>())
        {
            return false;
        }

        auto* sprite =
            entity->getComponent<SpriteComponent>();

        if (!sprite)
            return false;

        sprite->setTexture(
            textureID,
            ResourceManager::getTexture(textureID)
        );

        return true;
    }

}