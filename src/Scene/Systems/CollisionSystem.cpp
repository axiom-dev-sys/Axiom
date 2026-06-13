#include "Axiom/Scene/Systems/CollisionSystem.hpp"

#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"
#include "Axiom/Scene/Components/ColliderComponent.hpp"

#include <vector>
#include <iostream>

namespace Axiom {

    std::uint64_t CollisionSystem::makeCollisionKey(Entity* a, Entity* b) const
    {
        std::uint32_t idA = a->getID();
        std::uint32_t idB = b->getID();

        if (idA > idB)
        std::swap(idA, idB);

        return (static_cast<std::uint64_t>(idA) << 32) |
        static_cast<std::uint64_t>(idB);
    }

    void CollisionSystem::onCollisionEnter(Entity* a, Entity* b)
    {
        std::cout << "Collision Enter: "
        << a->getName() << " <-> "
        << b->getName() << '\n';
    }

    void CollisionSystem::onCollisionStay(Entity* a, Entity* b)
    {
        // TODO(0.5.4): Add collision stay event handling
    }

    void CollisionSystem::onCollisionExit()
    {
        // TODO(0.5.4):
        // Collision Enter/Exit may fire for several frames near collider edges.
        // Add stable collision state validation later.
        std::cout << "Collision Exit\n";
    }

    static bool checkAABB(
        TransformComponent* aTransform, ColliderComponent* aCollider,
        TransformComponent* bTransform, ColliderComponent* bCollider
    )
    {
        float aLeft   = aTransform->position.x + aCollider->offset.x - aCollider->size.x / 2.0f;
        float aRight  = aTransform->position.x + aCollider->offset.x + aCollider->size.x / 2.0f;
        float aBottom = aTransform->position.y + aCollider->offset.y - aCollider->size.y / 2.0f;
        float aTop    = aTransform->position.y + aCollider->offset.y + aCollider->size.y / 2.0f;

        float bLeft   = bTransform->position.x + bCollider->offset.x - bCollider->size.x / 2.0f;
        float bRight  = bTransform->position.x + bCollider->offset.x + bCollider->size.x / 2.0f;
        float bBottom = bTransform->position.y + bCollider->offset.y - bCollider->size.y / 2.0f;
        float bTop    = bTransform->position.y + bCollider->offset.y + bCollider->size.y / 2.0f;

        return (
            aLeft < bRight &&
            aRight > bLeft &&
            aBottom < bTop &&
            aTop > bBottom
        );
    }

    void CollisionSystem::update(Scene& scene)
    {
        std::unordered_set<std::uint64_t> currentCollisions;
        std::vector<Entity*> entities;
        
        scene.forEach([&](Entity* entity)
        {
            auto* transform = entity->getComponent<TransformComponent>();
            auto* collider = entity->getComponent<ColliderComponent>();

            if (transform && collider)
            entities.push_back(entity);
        });

        for (size_t i = 0; i < entities.size(); ++i)
        {
            for (size_t j = i + 1; j < entities.size(); ++j)
            {
                Entity* a = entities[i];
                Entity* b = entities[j];

                auto* aTransform = a->getComponent<TransformComponent>();
                auto* aCollider = a->getComponent<ColliderComponent>();

                auto* bTransform = b->getComponent<TransformComponent>();
                auto* bCollider = b->getComponent<ColliderComponent>();

                if (!checkAABB(aTransform, aCollider, bTransform, bCollider))
                continue;

                auto key = makeCollisionKey(a, b);

                if (m_PreviousCollisions.find(key) == m_PreviousCollisions.end())
                {
                    onCollisionEnter(a, b);
                }
                else
                {
                    onCollisionStay(a, b);
                }

                currentCollisions.insert(key);
            }
        }

        for (auto previousKey : m_PreviousCollisions)
        {
            if (currentCollisions.find(previousKey) == currentCollisions.end())
            {
                onCollisionExit();
            }
        }

        m_PreviousCollisions = std::move(currentCollisions);
    }

}