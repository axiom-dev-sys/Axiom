#pragma once

#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Editor/EditorContext.hpp"

#include <vector>

namespace Axiom {

    class HierarchyPanel
    {
    public:
        void render();

        void setVisible(bool value);
        bool isVisible() const;

        void toggle();

        void addEntity(Entity* entity);
        void clear();

        void setEditorContext(EditorContext* context);

        bool isCreateEntityRequested() const;
        void resetCreateEntityRequest();

        Entity* getDuplicateEntity() const;
        void resetDuplicateEntityRequest();

    private:
        bool visible = true;

        std::vector<Entity*> entities;

        EditorContext* editorContext = nullptr;

        bool createEntityRequested = false;

        Entity* renameEntity = nullptr;
        char renameBuffer[256] = {};

        Entity* duplicateEntity = nullptr;
    };

}