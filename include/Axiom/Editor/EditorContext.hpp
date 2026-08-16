#pragma once

#include "Axiom/Scene/Entity.hpp"

namespace Axiom {

    class Scene;

    class EditorContext
    {
    public:
        Scene* getScene() const;
        void setScene(Scene* scene);

        Entity* getSelectedEntity() const;
        void setSelectedEntity(Entity* entity);
        void clearSelection();

    private:
        Scene* currentScene = nullptr;
        Entity* selectedEntity = nullptr;
    };

}