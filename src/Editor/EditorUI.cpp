#include "Axiom/Editor/EditorUI.hpp"

#include <imgui.h>

namespace Axiom {

    void EditorUI::render()
    {

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Save Scene"))
                {
                    saveSceneRequested = true;
                }

                if (ImGui::MenuItem("Load Scene"))
                {
                    loadSceneRequested = true;
                }

                ImGui::Separator();

                if (ImGui::MenuItem("Exit"))
                {
                    exitRequested = true;
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
            {
                ImGui::MenuItem("Debug Overlay", nullptr, &showDebugOverlay);
                ImGui::MenuItem("Debug Renderer", nullptr, &showDebugRenderer);
                ImGui::MenuItem("Inspector", nullptr, &showInspector);
                ImGui::MenuItem("Hierarchy", nullptr, &showHierarchy);
                ImGui::MenuItem("Scene Editor", nullptr, &showSceneEditor);
                ImGui::MenuItem("Asset Browser", nullptr, &showAssetBrowser);
                ImGui::MenuItem("Console", nullptr, &showConsole);
                ImGui::MenuItem("Statistics", nullptr, &showStatistics);
                ImGui::MenuItem("Status Bar", nullptr, &showStatusBar);
                ImGui::MenuItem("Preferences", nullptr, &showPreferences);
                ImGui::MenuItem("Viewport", nullptr, &showViewport);

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("About Axiom"))
                {
                    showAboutWindow = true;
                }

                ImGui::EndMenu();
            }

            ImGui::Separator();

            if (ImGui::Button("Play"))
                playRequested = true;

            ImGui::SameLine();

            if (ImGui::Button("Pause"))
                pauseRequested = true;

            ImGui::SameLine();

            if (ImGui::Button("Stop"))
                stopRequested = true;

            ImGui::SameLine();

            if (ImGui::Button("Save"))
                saveSceneRequested = true;

            ImGui::SameLine();

            if (ImGui::Button("Load"))
                loadSceneRequested = true;

            ImGui::EndMainMenuBar();

        }

            if (showAboutWindow)
            {
                ImGui::Begin(
                    "About Axiom",
                    &showAboutWindow
                );

                ImGui::Text("Axiom Engine");
                ImGui::Separator();

                ImGui::Text("Version: 1.2.9");
                ImGui::Text("Language: C++17");
                ImGui::Text("Renderer: OpenGL");
                ImGui::Text("UI: ImGui");

                ImGui::Separator();

                ImGui::Text("Author: JosephJar");

                ImGui::End();
            }

            if (showStatusBar)
            {
                ImGui::SetNextWindowPos(
                    ImVec2(0, 690),
                    ImGuiCond_Always
                );

                ImGui::SetNextWindowSize(
                    ImVec2(1280, 30),
                    ImGuiCond_Always
                );

                ImGui::SetNextWindowBgAlpha(1.0f);

                ImGui::Begin(
                    "Status Bar",
                    nullptr,
                    ImGuiWindowFlags_NoResize |
                    ImGuiWindowFlags_NoMove |
                    ImGuiWindowFlags_NoCollapse |
                    ImGuiWindowFlags_NoTitleBar |
                    ImGuiWindowFlags_NoScrollbar |
                    ImGuiWindowFlags_NoScrollWithMouse
                );

                ImGui::Text("Axiom 1.2.9");

                ImGui::SameLine(180);
                ImGui::Text("Scene: %s", sceneName.c_str());

                ImGui::SameLine(420);

                if (gameState == "Play")
                {
                    ImGui::TextColored(
                        ImVec4(0.2f, 1.0f, 0.2f, 1.0f),
                        "Mode: Play"
                    );
                }
                else if (gameState == "Pause")
                {
                    ImGui::TextColored(
                        ImVec4(1.0f, 1.0f, 0.2f, 1.0f),
                        "Mode: Pause"
                    );
                }
                else if (gameState == "Edit")
                {
                    ImGui::TextColored(
                        ImVec4(0.4f, 0.8f, 1.0f, 1.0f),
                        "Mode: Edit"
                    );
                }
                else
                {
                    ImGui::Text("Mode: %s", gameState.c_str());
                }

                ImGui::SameLine(620);
                ImGui::Text("Entities: %d", entityCount);

                ImGui::SameLine(840);
                ImGui::Text("FPS: %.1f", fps);

                ImGui::SameLine(1020);

                ImGui::Text(
                    "Snap: %s",
                    snapEnabled ? "ON" : "OFF"
                );

                ImGui::End();
            }
    }

    bool EditorUI::isDebugOverlayVisible() const
    {
        return showDebugOverlay;
    }

    bool EditorUI::isDebugRendererVisible() const
    {
        return showDebugRenderer;
    }

    bool EditorUI::isInspectorVisible() const
    {
        return showInspector;
    }

    bool EditorUI::isHierarchyVisible() const
    {
        return showHierarchy;
    }

    bool EditorUI::isSceneEditorVisible() const
    {
        return showSceneEditor;
    }

    bool EditorUI::isAssetBrowserVisible() const
    {
        return showAssetBrowser;
    }

    bool EditorUI::isSaveSceneRequested() const
    {
        return saveSceneRequested;
    }

    bool EditorUI::isLoadSceneRequested() const
    {
        return loadSceneRequested;
    }

    bool EditorUI::isExitRequested() const
    {
        return exitRequested;
    }

    void EditorUI::resetSaveSceneRequest()
    {
        saveSceneRequested = false;
    }

    void EditorUI::resetLoadSceneRequest()
    {
        loadSceneRequested = false;
    }

    void EditorUI::resetExitRequest()
    {
        exitRequested = false;
    }

    bool EditorUI::isPlayRequested() const
    {
        return playRequested;
    }

    bool EditorUI::isPauseRequested() const
    {
        return pauseRequested;
    }

    void EditorUI::resetPlayRequest()
    {
        playRequested = false;
    }

    void EditorUI::resetPauseRequest()
    {
        pauseRequested = false;
    }

    void EditorUI::setStatusInfo(
        const std::string& scene,
        const std::string& state,
        int entities,
        float fpsValue,
        bool snapValue
    )
    {
        sceneName = scene;
        gameState = state;
        entityCount = entities;
        fps = fpsValue;
        snapEnabled = snapValue;
    }

    bool EditorUI::isConsoleVisible() const
    {
        return showConsole;
    }

    bool EditorUI::isStatisticsVisible() const
    {
        return showStatistics;
    }

    bool EditorUI::isStopRequested() const
    {
        return stopRequested;
    }

    void EditorUI::resetStopRequest()
    {
        stopRequested = false;
    }

    bool EditorUI::isPreferencesVisible() const
    {
        return showPreferences;
    }

    bool EditorUI::isViewportVisible() const
    {
        return showViewport;
    }

}