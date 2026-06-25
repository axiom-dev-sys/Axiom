#include "Axiom/Scene/SceneSerializer.hpp"
#include "Axiom/Core/Log.hpp"
#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"
#include "Axiom/Scene/Components/SpriteComponent.hpp"
#include <fstream>
#include <string>

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
        file << "Version: 1.0\n";
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
            // TODO: Reconstruct scene entities from serialized data.
        )
        {
            (void)scene;

            std::ifstream file(path);

            if (!file)
            {
                Log::error("[SceneSerializer] Failed to load: " + path);
                return;
            }

            std::string line;
            std::string name;
            std::string position;
            std::string scale;
            std::string texture;

            while (std::getline(file, line))
            {
                if (line.rfind("Name: ", 0) == 0)
                {
                    name = line.substr(6);
                    Log::info("[SceneSerializer] Found name: " + name);
                }

                if (line.rfind("Position: ", 0) == 0)
                {
                    position = line.substr(10);
                    Log::info("[SceneSerializer] Found position: " + position);
                }

                if (line.rfind("Scale: ", 0) == 0)
                {
                    scale = line.substr(7);
                    Log::info("[SceneSerializer] Found scale: " + scale);
                }

                if (line.rfind("Texture: ", 0) == 0)
                {
                    texture = line.substr(9);
                    Log::info("[SceneSerializer] Found texture: " + texture);
                }

            }

            Log::info("[SceneSerializer] Loaded: " + path);

        }

}