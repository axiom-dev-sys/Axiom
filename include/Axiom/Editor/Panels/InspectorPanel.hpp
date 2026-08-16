#pragma once

#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Editor/EditorContext.hpp"

#include <glm/glm.hpp>

namespace Axiom {

    class InspectorPanel
    {
    public:
        void render();

        void setVisible(bool value);
        bool isVisible() const;

        void toggle();

        void setEditorContext(EditorContext* context);

    private:
        bool visible = true;

        char nameBuffer[256] = {};
        bool editingName = false;

        EditorContext* editorContext = nullptr;
    };

}