#pragma once

#include <string>

namespace Axiom {

    class EditorUI
    {
    public:
        void render();

        bool isDebugOverlayVisible() const;
        bool isDebugRendererVisible() const;
        bool isInspectorVisible() const;
        bool isHierarchyVisible() const;
        bool isSceneEditorVisible() const;
        bool isAssetBrowserVisible() const;
        bool isSaveSceneRequested() const;
        bool isLoadSceneRequested() const;
        bool isExitRequested() const;
        void resetSaveSceneRequest();
        void resetLoadSceneRequest();
        void resetExitRequest();
        bool isPlayRequested() const;
        bool isPauseRequested() const;
        void resetPlayRequest();
        void resetPauseRequest();
        bool isConsoleVisible() const;
        bool isStatisticsVisible() const;

        void setStatusInfo(
            const std::string& scene,
            const std::string& state,
            int entities,
            float fpsValue
        );

        bool isStopRequested() const;
        void resetStopRequest();

    private:
        bool showDemo = false;

        bool showDebugOverlay = true;
        bool showDebugRenderer = true;
        bool showInspector = true;
        bool showHierarchy = true;
        bool showSceneEditor = true;
        bool showAssetBrowser = true;
        bool saveSceneRequested = false;
        bool loadSceneRequested = false;
        bool exitRequested = false;
        bool showAboutWindow = false;
        bool playRequested = false;
        bool pauseRequested = false;
        bool stopRequested = false;

        std::string sceneName = "None";
        std::string gameState = "Unknown";
        int entityCount = 0;
        float fps = 0.0f;

        bool showConsole = true;
        bool showStatistics = true;
    };

}