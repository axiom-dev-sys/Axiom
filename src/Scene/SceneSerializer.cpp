#include "Axiom/Scene/SceneSerializer.hpp"
#include "Axiom/Core/Log.hpp"
#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"
#include "Axiom/Scene/Components/SpriteComponent.hpp"
#include <fstream>

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
        file << "Version: 0.8.4\n";
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
            }

            auto* sprite =
                entity->getComponent<SpriteComponent>();

            if (sprite)
            {
                file << "Texture: "
                    << sprite->getTextureID()
                    << "\n";
            }

        }

        Log::info("[SceneSerializer] Saved: " + path);

    }
    
    void SceneSerializer::load(
        Scene& scene,
        const std::string& path
    )
    {
        (void)scene;
        
        std::ifstream file(path);
        
        if (!file)
        {
            Log::error("[SceneSerializer] Failed to load: " + path);
            return;
        }

        Log::info("[SceneSerializer] Loaded: " + path);
    }

}