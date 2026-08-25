#include "Axiom/Scene/SceneSerializer.hpp"
#include "Axiom/Core/Log.hpp"
#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"
#include "Axiom/Scene/Components/SpriteComponent.hpp"
#include "Axiom/Scene/Components/ColliderComponent.hpp"
#include "Axiom/Scene/Components/VelocityComponent.hpp"
#include "Axiom/Scene/Components/PlayerControllerComponent.hpp"
#include "Axiom/Resource/ResourceManager.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include "Axiom/Core/Version.hpp"

namespace Axiom {

    void SceneSerializer::save(
        Scene& scene,
        const std::string& path
    )
    {
        std::ofstream file(path);

        if (!file)
        {
            Log::error("[SceneSerializer] Failed to save: " + path);
            return;
        }

        file << "Axiom Scene\n";
        file << "Version: " << AXIOM_VERSION << "\n";
        file << "Entities: "
            << scene.getEntityCount()
            << "\n";

        for (const auto& entity : scene.getEntities())
        {
            if (!entity || !entity->isActive() || entity->isDestroyed())
                continue;

            file << "\nEntity\n";
            file << "Name: "
                << entity->getName()
                << "\n";

            auto* transform =
                entity->getComponent<TransformComponent>();

            if (transform)
            {
                file << "Position: "
                    << transform->position.x << " "
                    << transform->position.y
                    << "\n";

                file << "Scale: "
                    << transform->scale.x << " "
                    << transform->scale.y
                    << "\n";

                file << "Rotation: "
                    << transform->rotation
                    << "\n";
            }

            auto* sprite =
                entity->getComponent<SpriteComponent>();

            if (sprite)
            {
                file << "Texture: "
                    << sprite->getTextureID()
                    << "\n";
            }

            auto* collider =
                entity->getComponent<ColliderComponent>();

            if (collider)
            {
                file << "ColliderSize: "
                    << collider->size.x << " "
                    << collider->size.y
                    << "\n";

                file << "ColliderOffset: "
                    << collider->offset.x << " "
                    << collider->offset.y
                    << "\n";

                file << "ColliderTrigger: "
                    << (collider->isTrigger ? 1 : 0)
                    << "\n";
            }

            if (entity->hasComponent<VelocityComponent>())
            {
                file << "Velocity: 1\n";
            }

            if (entity->hasComponent<PlayerControllerComponent>())
            {
                file << "PlayerController: 1\n";
            }

        }

        Log::info("[SceneSerializer] Saved: " + path);

    }
    
        void SceneSerializer::load(
            Scene& scene,
            const std::string& path
        )
        {
            std::ifstream file(path);

            if (!file)
            {
                Log::error("[SceneSerializer] Failed to load: " + path);
                return;
            }

            scene.clear();

            std::string line;
            Entity* currentEntity = nullptr;

            while (std::getline(file, line))
            {
                if (line == "Entity")
                {
                    currentEntity = nullptr;
                    continue;
                }

                if (line.rfind("Name: ", 0) == 0)
                {
                    const std::string name =
                        line.substr(6);

                    currentEntity =
                        scene.createEntity(name);

                    Log::info(
                        "[SceneSerializer] Created entity: " +
                        name
                    );

                    continue;
                }

                if (!currentEntity)
                    continue;

                if (line.rfind("Position: ", 0) == 0)
                {
                    std::istringstream stream(
                        line.substr(10)
                    );

                    float x = 0.0f;
                    float y = 0.0f;

                    stream >> x >> y;

                    auto* transform =
                        currentEntity
                        ->getComponent<TransformComponent>();

                    if (!transform)
                    {
                        transform =
                            currentEntity
                            ->addComponent<TransformComponent>();
                    }

                    transform->position = {
                        x,
                        y
                    };

                    continue;
                }

                if (line.rfind("Scale: ", 0) == 0)
                {
                    std::istringstream stream(
                        line.substr(7)
                    );

                    float x = 1.0f;
                    float y = 1.0f;

                    stream >> x >> y;

                    auto* transform =
                        currentEntity
                        ->getComponent<TransformComponent>();

                    if (!transform)
                    {
                        transform =
                            currentEntity
                            ->addComponent<TransformComponent>();
                    }

                    transform->scale = {
                        x,
                        y
                    };

                    continue;
                }

                if (line.rfind("Rotation: ", 0) == 0)
                {
                    std::istringstream stream(
                        line.substr(10)
                    );

                    float rotation = 0.0f;

                    stream >> rotation;

                    auto* transform =
                        currentEntity
                        ->getComponent<TransformComponent>();

                    if (!transform)
                    {
                        transform =
                            currentEntity
                            ->addComponent<TransformComponent>();
                    }

                    transform->rotation = rotation;

                    continue;
                }

                if (line.rfind("Texture: ", 0) == 0)
                {
                    const std::string textureID =
                        line.substr(9);

                    auto* sprite =
                        currentEntity
                        ->getComponent<SpriteComponent>();

                    if (!sprite)
                    {
                        currentEntity->addComponent<SpriteComponent>(
                            textureID,
                            ResourceManager::getTexture(textureID)
                        );
                    }
                    else
                    {
                        sprite->setTexture(
                            textureID,
                            ResourceManager::getTexture(textureID)
                        );
                    }

                    continue;
                }

                if (line.rfind("ColliderSize: ", 0) == 0)
                {
                    std::istringstream stream(
                        line.substr(14)
                    );

                    float x = 0.0f;
                    float y = 0.0f;

                    stream >> x >> y;

                    auto* collider =
                        currentEntity
                        ->getComponent<ColliderComponent>();

                    if (!collider)
                    {
                        collider =
                            currentEntity
                            ->addComponent<ColliderComponent>();
                    }

                    collider->size = { x, y };

                    continue;
                }

                if (line.rfind("ColliderOffset: ", 0) == 0)
                {
                    std::istringstream stream(
                        line.substr(16)
                    );

                    float x = 0.0f;
                    float y = 0.0f;

                    stream >> x >> y;

                    auto* collider =
                        currentEntity
                        ->getComponent<ColliderComponent>();

                    if (!collider)
                    {
                        collider =
                            currentEntity
                            ->addComponent<ColliderComponent>();
                    }

                    collider->offset = { x, y };

                    continue;
                }

                if (line.rfind("ColliderTrigger: ", 0) == 0)
                {
                    std::istringstream stream(
                        line.substr(17)
                    );

                    int trigger = 0;

                    stream >> trigger;

                    auto* collider =
                        currentEntity
                        ->getComponent<ColliderComponent>();

                    if (!collider)
                    {
                        collider =
                            currentEntity
                            ->addComponent<ColliderComponent>();
                    }

                    collider->isTrigger =
                        trigger != 0;

                    continue;
                }

                if (line == "Velocity: 1")
                {
                    if (!currentEntity->hasComponent<VelocityComponent>())
                    {
                        currentEntity
                            ->addComponent<VelocityComponent>();
                    }

                    continue;
                }

                if (line == "PlayerController: 1")
                {
                    if (!currentEntity->hasComponent<PlayerControllerComponent>())
                    {
                        currentEntity
                            ->addComponent<PlayerControllerComponent>();
                    }

                    continue;
                }
            }

            Log::info("[SceneSerializer] Loaded: " + path);

        }

}