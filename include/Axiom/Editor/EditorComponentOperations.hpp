#pragma once

#include <string>

namespace Axiom {

    class Entity;

    class EditorComponentOperations
    {
    public:
        bool addVelocityComponent(Entity* entity);
        bool removeVelocityComponent(Entity* entity);

        bool addColliderComponent(Entity* entity);
        bool removeColliderComponent(Entity* entity);

        bool addSpriteComponent(Entity* entity);
        bool removeSpriteComponent(Entity* entity);

        bool setSpriteTexture(
            Entity* entity,
            const std::string& textureID
        );
    };

}