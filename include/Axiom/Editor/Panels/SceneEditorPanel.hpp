#pragma once

#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Editor/EditorContext.hpp"

#include <string>
#include <vector>

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

        void setSceneInfo(const std::string& name, int entityCount);

        void setSceneMode(const std::string& mode);

        bool isRenameSceneRequested() const;
        void resetRenameSceneRequest();
        const std::string& getRequestedSceneName() const;

        bool isNewSceneRequested() const;
        void resetNewSceneRequest();

        void addSceneName(const std::string& name);
        void clearSceneNames();

        bool isSwitchSceneRequested() const;
        void resetSwitchSceneRequest();
        const std::string& getRequestedSceneSwitchName() const;

        bool isDeleteSceneRequested() const;
        void resetDeleteSceneRequest();

    private:
        bool visible = true;

        EditorContext* editorContext = nullptr;

        bool createEntityRequested = false;
        bool destroyEntityRequested = false;

        bool saveSceneRequested = false;
        bool loadSceneRequested = false;

        std::string sceneName = "Unknown";
        int sceneEntityCount = 0;

        std::string sceneMode = "Unknown";

        char sceneNameBuffer[256] = {};
        bool editingSceneName = false;

        bool renameSceneRequested = false;
        std::string requestedSceneName;

        bool newSceneRequested = false;

        std::vector<std::string> sceneNames;

        bool switchSceneRequested = false;
        std::string requestedSceneSwitchName;

        bool deleteSceneRequested = false;
    };

}