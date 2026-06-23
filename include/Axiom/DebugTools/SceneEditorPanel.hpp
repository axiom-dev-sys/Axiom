#pragma once

#include "Axiom/Scene/Entity.hpp"

namespace Axiom {

    class SceneEditorPanel
    {
    public:
        void render();

        void setVisible(bool value);
        bool isVisible() const;

        void toggle();

        void setSelectedEntity(Entity* entity);

        bool isCreateEntityRequested() const;
        void resetCreateEntityRequest();

        bool isDestroyEntityRequested() const;
        void resetDestroyEntityRequest();

        bool isSaveSceneRequested() const;
        void resetSaveSceneRequest();

        bool isLoadSceneRequested() const;
        void resetLoadSceneRequest();

    private:
        bool visible = true;

        Entity* selectedEntity = nullptr;

        bool createEntityRequested = false;
        bool destroyEntityRequested = false;

        bool saveSceneRequested = false;
        bool loadSceneRequested = false;
    };

}