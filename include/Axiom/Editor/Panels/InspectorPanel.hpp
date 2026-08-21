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

        bool isDestroyEntityRequested() const;
        void resetDestroyEntityRequest();

        bool isAddVelocityRequested() const;
        void resetAddVelocityRequest();

        bool isRemoveVelocityRequested() const;
        void resetRemoveVelocityRequest();

        bool isAddColliderRequested() const;
        void resetAddColliderRequest();

        bool isRemoveColliderRequested() const;
        void resetRemoveColliderRequest();

        bool isAddSpriteRequested() const;
        void resetAddSpriteRequest();

        bool isRemoveSpriteRequested() const;
        void resetRemoveSpriteRequest();

        void setEditorContext(EditorContext* context);

    private:
        bool visible = true;

        char nameBuffer[256] = {};
        bool editingName = false;

        bool destroyEntityRequested = false;

        bool addVelocityRequested = false;
        bool removeVelocityRequested = false;

        bool addColliderRequested = false;
        bool removeColliderRequested = false;

        bool addSpriteRequested = false;
        bool removeSpriteRequested = false;

        EditorContext* editorContext = nullptr;
    };

}