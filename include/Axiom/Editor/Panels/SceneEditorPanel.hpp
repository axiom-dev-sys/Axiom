#pragma once

#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Editor/EditorContext.hpp"

namespace Axiom {

    class SceneEditorPanel
    {
    public:
        void render();

        void setVisible(bool value);
        bool isVisible() const;

        void toggle();

        bool isCreateEntityRequested() const;
        void resetCreateEntityRequest();

        bool isDestroyEntityRequested() const;
        void resetDestroyEntityRequest();

        bool isSaveSceneRequested() const;
        void resetSaveSceneRequest();

        bool isLoadSceneRequested() const;
        void resetLoadSceneRequest();

        void setEditorContext(EditorContext* context);

    private:
        bool visible = true;

        EditorContext* editorContext = nullptr;

        bool createEntityRequested = false;
        bool destroyEntityRequested = false;

        bool saveSceneRequested = false;
        bool loadSceneRequested = false;
    };

}