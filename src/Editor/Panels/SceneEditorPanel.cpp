#include "Axiom/Editor/Panels/SceneEditorPanel.hpp"
#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/SceneManager.hpp"

#include <ImGuiFileDialog.h>
#include <imgui.h>
#include <cstring>

namespace Axiom {

    void SceneEditorPanel::render()
    {
        if (!visible)
            return;

        const std::string activeSceneName =
            sceneManager
            ? sceneManager->getActiveSceneName()
            : "Unknown";

        ImGui::Begin("Scene Editor");

        Scene* scene =
            editorContext ? editorContext->getScene() : nullptr;

        ImGui::Text("Scene Information");
        ImGui::Separator();

        ImGui::Text("Name:");
        ImGui::SameLine();

        if (ImGui::Button("Rename"))
        {
            editingSceneName = true;

            std::strncpy(
                sceneNameBuffer,
                activeSceneName.c_str(),
                sizeof(sceneNameBuffer)
            );

            sceneNameBuffer[sizeof(sceneNameBuffer) - 1] = '\0';
        }

        ImGui::Text("Entities: %d", scene ? static_cast<int>(scene->getEntityCount()) : 0);
        ImGui::Text("Mode: %s", sceneMode.c_str());

        if (sceneManager)
        {
            if (ImGui::BeginCombo("Active Scene", activeSceneName.c_str()))
            {
                for (const auto& sceneInfo : sceneManager->getScenes())
                {
                    const std::string& name =
                        sceneInfo.first;

                    const bool selected =
                        name == activeSceneName;

                    if (ImGui::Selectable(name.c_str(), selected))
                    {
                        requestedSceneSwitchName = name;
                        switchSceneRequested = true;
                    }

                    if (selected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }

                ImGui::EndCombo();
            }
        }

        ImGui::Separator();

        Entity* selectedEntity =
            editorContext ? editorContext->getSelectedEntity() : nullptr;

        ImGui::Text("Scene Actions");
        ImGui::Separator();

        if (ImGui::Button("Create Entity"))
        {
            createEntityRequested = true;
        }

        if (ImGui::Button("New Scene"))
        {
            newSceneRequested = true;
        }

        if (ImGui::Button("Delete Scene"))
        {
            deleteSceneRequested = true;
        }

        if (openSaveDialogRequested)
        {
            IGFD::FileDialogConfig config;
            config.path = ".";

            ImGuiFileDialog::Instance()->OpenDialog(
                "SaveSceneDialog",
                "Save Scene As",
                ".scene",
                config
            );

            openSaveDialogRequested = false;
        }

        if (ImGui::Button("Save Scene As..."))
        {
            IGFD::FileDialogConfig config;
            config.path = ".";

            ImGuiFileDialog::Instance()->OpenDialog(
                "SaveSceneDialog",
                "Save Scene As",
                ".scene",
                config
            );
        }

        if (openLoadDialogRequested)
        {
            IGFD::FileDialogConfig config;
            config.path = ".";

            ImGuiFileDialog::Instance()->OpenDialog(
                "LoadSceneDialog",
                "Load Scene",
                ".scene",
                config
            );

            openLoadDialogRequested = false;
        }

        if (ImGui::Button("Load Scene..."))
        {
            IGFD::FileDialogConfig config;
            config.path = ".";

            ImGuiFileDialog::Instance()->OpenDialog(
                "LoadSceneDialog",
                "Load Scene",
                ".scene",
                config
            );
        }

        if (ImGuiFileDialog::Instance()->Display(
            "SaveSceneDialog"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                requestedSaveScenePath =
                    ImGuiFileDialog::Instance()
                    ->GetFilePathName();

                saveSceneRequested = true;
            }

            ImGuiFileDialog::Instance()->Close();
        }

        if (ImGuiFileDialog::Instance()->Display(
            "LoadSceneDialog"))
        {
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                requestedLoadScenePath =
                    ImGuiFileDialog::Instance()
                    ->GetFilePathName();

                loadSceneRequested = true;
            }

            ImGuiFileDialog::Instance()->Close();
        }

        ImGui::Separator();

        if (!selectedEntity)
        {
            ImGui::Text("No selected entity");
            ImGui::End();
            return;
        }

        ImGui::Text("Selected Entity");
        ImGui::Separator();

        ImGui::Text("Name: %s", selectedEntity->getName().c_str());
        ImGui::Text("ID: %u", selectedEntity->getID());

        if (ImGui::Button("Destroy Entity"))
        {
            destroyEntityRequested = true;
        }

        if (editingSceneName)
        {
            ImGui::SetNextItemWidth(-1);

            if (ImGui::InputText(
                "##SceneRename",
                sceneNameBuffer,
                sizeof(sceneNameBuffer),
                ImGuiInputTextFlags_EnterReturnsTrue))
            {
                requestedSceneName = sceneNameBuffer;
                renameSceneRequested = true;
                editingSceneName = false;
            }
        }
        else
        {
            ImGui::Text("%s", activeSceneName.c_str());
        }

        ImGui::End();
    }

    void SceneEditorPanel::setVisible(bool value)
    {
        visible = value;
    }

    bool SceneEditorPanel::isVisible() const
    {
        return visible;
    }

    void SceneEditorPanel::toggle()
    {
        visible = !visible;
    }

    bool SceneEditorPanel::isCreateEntityRequested() const
    {
        return createEntityRequested;
    }

    void SceneEditorPanel::resetCreateEntityRequest()
    {
        createEntityRequested = false;
    }

    bool SceneEditorPanel::isDestroyEntityRequested() const
    {
        return destroyEntityRequested;
    }

    void SceneEditorPanel::resetDestroyEntityRequest()
    {
        destroyEntityRequested = false;
    }

    bool SceneEditorPanel::isSaveSceneRequested() const
    {
        return saveSceneRequested;
    }

    void SceneEditorPanel::resetSaveSceneRequest()
    {
        saveSceneRequested = false;
        requestedSaveScenePath.clear();
    }

    void SceneEditorPanel::requestSaveScene()
    {
        openSaveDialogRequested = true;
    }

    const std::string& SceneEditorPanel::getRequestedSaveScenePath() const
    {
        return requestedSaveScenePath;
    }

    bool SceneEditorPanel::isLoadSceneRequested() const
    {
        return loadSceneRequested;
    }

    void SceneEditorPanel::resetLoadSceneRequest()
    {
        loadSceneRequested = false;
        requestedLoadScenePath.clear();
    }

    void SceneEditorPanel::requestLoadScene()
    {
        openLoadDialogRequested = true;
    }

    const std::string& SceneEditorPanel::getRequestedLoadScenePath() const
    {
        return requestedLoadScenePath;
    }

    void SceneEditorPanel::requestNewScene()
    {
        newSceneRequested = true;
    }

    void SceneEditorPanel::setEditorContext(EditorContext* context)
    {
        editorContext = context;
    }

    void SceneEditorPanel::setSceneManager(
        SceneManager* manager)
    {
        sceneManager = manager;
    }

    void SceneEditorPanel::setSceneMode(const std::string& mode)
    {
        sceneMode = mode;
    }

    bool SceneEditorPanel::isRenameSceneRequested() const
    {
        return renameSceneRequested;
    }

    void SceneEditorPanel::resetRenameSceneRequest()
    {
        renameSceneRequested = false;
        requestedSceneName.clear();
    }

    const std::string& SceneEditorPanel::getRequestedSceneName() const
    {
        return requestedSceneName;
    }

    bool SceneEditorPanel::isNewSceneRequested() const
    {
        return newSceneRequested;
    }

    void SceneEditorPanel::resetNewSceneRequest()
    {
        newSceneRequested = false;
    }

    bool SceneEditorPanel::isSwitchSceneRequested() const
    {
        return switchSceneRequested;
    }

    void SceneEditorPanel::resetSwitchSceneRequest()
    {
        switchSceneRequested = false;
        requestedSceneSwitchName.clear();
    }

    const std::string& SceneEditorPanel::getRequestedSceneSwitchName() const
    {
        return requestedSceneSwitchName;
    }

    bool SceneEditorPanel::isDeleteSceneRequested() const
    {
        return deleteSceneRequested;
    }

    void SceneEditorPanel::resetDeleteSceneRequest()
    {
        deleteSceneRequested = false;
    }

}