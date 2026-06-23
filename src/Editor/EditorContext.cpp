#include "Axiom/Editor/EditorContext.hpp"

namespace Axiom {

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