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

    private:
        bool visible = true;

        std::vector<Entity*> entities;

        EditorContext* editorContext = nullptr;
    };

}