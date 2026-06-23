#pragma once

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
    };

}