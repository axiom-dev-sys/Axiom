#pragma once

namespace Axiom {

    class Scene;
    class Entity;
    class EditorContext;

    class EditorEntityOperations
    {
    public:
        Entity* createEntity(
            Scene& scene,
            EditorContext& context
        );

        Entity* duplicateEntity(
            Entity* source,
            Scene& scene,
            EditorContext& context
        );

        bool destroyEntity(
            Entity* entity,
            Scene& scene,
            EditorContext& context
        );
    };

}