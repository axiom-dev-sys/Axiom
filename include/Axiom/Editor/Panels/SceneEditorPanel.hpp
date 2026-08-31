#pragma once

#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Editor/EditorContext.hpp"

#include <string>

namespace Axiom {

    class SceneManager;

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
        void requestSaveScene();

        const std::string& getRequestedSaveScenePath() const;

        bool isLoadSceneRequested() const;
        void resetLoadSceneRequest();
        void requestLoadScene();

        const std::string& getRequestedLoadScenePath() const;

        void requestNewScene();

        void setEditorContext(EditorContext* context);

        void setSceneMode(const std::string& mode);

        void setSceneManager(SceneManager* manager);

        bool isRenameSceneRequested() const;
        void resetRenameSceneRequest();
        const std::string& getRequestedSceneName() const;

        bool isNewSceneRequested() const;
        void resetNewSceneRequest();

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

        bool openSaveDialogRequested = false;
        bool openLoadDialogRequested = false;

        std::string requestedSaveScenePath;
        std::string requestedLoadScenePath;

        std::string sceneMode = "Unknown";

        SceneManager* sceneManager = nullptr;

        char sceneNameBuffer[256] = {};
        bool editingSceneName = false;

        bool renameSceneRequested = false;
        std::string requestedSceneName;

        bool newSceneRequested = false;

        bool switchSceneRequested = false;
        std::string requestedSceneSwitchName;

        bool deleteSceneRequested = false;
    };

}