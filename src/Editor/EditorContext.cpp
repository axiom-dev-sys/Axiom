#include "Axiom/Editor/EditorContext.hpp"
#include "Axiom/Scene/Scene.hpp"

namespace Axiom {

    Scene* EditorContext::getScene() const
    {
        return currentScene;
    }

    void EditorContext::setScene(Scene* scene)
    {
        currentScene = scene;

        if (selectedEntity)
            clearSelection();
    }

    Entity* EditorContext::getSelectedEntity() const
    {
        return selectedEntity;
    }

    void EditorContext::setSelectedEntity(Entity* entity)
    {
        selectedEntity = entity;
    }

    void EditorContext::clearSelection()
    {
        selectedEntity = nullptr;
    }

}