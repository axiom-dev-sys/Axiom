#include "Axiom/Editor/EditorEntityOperations.hpp"

#include "Axiom/Editor/EditorContext.hpp"

#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Entity.hpp"

#include "Axiom/Scene/Components/TransformComponent.hpp"
#include "Axiom/Scene/Components/SpriteComponent.hpp"
#include "Axiom/Scene/Components/VelocityComponent.hpp"
#include "Axiom/Scene/Components/ColliderComponent.hpp"
#include "Axiom/Scene/Components/PlayerControllerComponent.hpp"
#include "Axiom/Scene/Components/PlayerTag.hpp"

namespace Axiom {

    Entity* EditorEntityOperations::createEntity(
        Scene& scene,
        EditorContext& context)
    {
        Entity* entity =
            scene.createEntity("Entity");

        if (!entity)
            return nullptr;

        entity->addComponent<TransformComponent>();

        context.setSelectedEntity(entity);

        return entity;
    }

    Entity* EditorEntityOperations::duplicateEntity(
        Entity* source,
        Scene& scene,
        EditorContext& context)
    {
        if (!source ||
            source->isDestroyed() ||
            !scene.containsEntity(source))
        {
            return nullptr;
        }

        Entity* copy =
            scene.createEntity(
                source->getName() + " Copy"
            );

        if (auto* sourceTransform =
            source->getComponent<TransformComponent>())
        {
            auto* transform =
                copy->addComponent<TransformComponent>();

            *transform = *sourceTransform;

            transform->position.x += 32.0f;
            transform->position.y += 32.0f;
        }

        if (auto* sourceSprite =
            source->getComponent<SpriteComponent>())
        {
            copy->addComponent<SpriteComponent>(
                sourceSprite->getTextureID(),
                sourceSprite->getTexture()
            );
        }

        if (auto* sourceVelocity =
            source->getComponent<VelocityComponent>())
        {
            auto* velocity =
                copy->addComponent<VelocityComponent>();

            *velocity = *sourceVelocity;
        }

        if (auto* sourceCollider =
            source->getComponent<ColliderComponent>())
        {
            auto* collider =
                copy->addComponent<ColliderComponent>();

            *collider = *sourceCollider;
        }

        if (auto* sourceController =
            source->getComponent<PlayerControllerComponent>())
        {
            auto* controller =
                copy->addComponent<PlayerControllerComponent>();

            *controller = *sourceController;
        }

        if (source->hasComponent<PlayerTag>())
        {
            copy->addComponent<PlayerTag>();
        }

        context.setSelectedEntity(copy);

        return copy;
    }

    bool EditorEntityOperations::destroyEntity(
        Entity* entity,
        Scene& scene,
        EditorContext& context)
    {
        if (!entity ||
            entity->isDestroyed() ||
            !scene.containsEntity(entity))
        {
            return false;
        }

        entity->destroy();

        if (context.getSelectedEntity() == entity)
        {
            context.clearSelection();
        }

        return true;
    }
}