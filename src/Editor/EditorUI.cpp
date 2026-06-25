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

                ImGui::Text("Version: 1.0");
                ImGui::Text("Language: C++17");
                ImGui::Text("Renderer: OpenGL");
                ImGui::Text("UI: ImGui");

                ImGui::Separator();

                ImGui::Text("Author: JosephJar");

                ImGui::End();
            }

            ImGui::SetNextWindowPos(
                ImVec2(0, 690),
                ImGuiCond_Always
            );

            ImGui::SetNextWindowSize(
                ImVec2(1280, 30),
                ImGuiCond_Always
            );

            ImGui::Begin(
                "Status Bar",
                nullptr,
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoCollapse
            );

            ImGui::Text(
                "Scene: %s | State: %s | Entities: %d | FPS: %.1f | Axiom 1.0",
                sceneName.c_str(),
                gameState.c_str(),
                entityCount,
                fps
            );

            ImGui::End();
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
        float fpsValue
    )
    {
        sceneName = scene;
        gameState = state;
        entityCount = entities;
        fps = fpsValue;
    }

    bool EditorUI::isConsoleVisible() const
    {
        return showConsole;
    }

    bool EditorUI::isStatisticsVisible() const
    {
        return showStatistics;
    }

}