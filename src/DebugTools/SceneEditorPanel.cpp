#include "Axiom/DebugTools/SceneEditorPanel.hpp"
#include "Axiom/Scene/Entity.hpp"

#include <imgui.h>

namespace Axiom {

    void SceneEditorPanel::render()
    {
        if (!visible)
            return;

        ImGui::Begin("Scene Editor");

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

        if (ImGui::Button("Create Entity"))
        {
            createEntityRequested = true;
        }

        if (ImGui::Button("Destroy Entity"))
        {
            destroyEntityRequested = true;
        }

        if (ImGui::Button("Save Scene"))
        {
            saveSceneRequested = true;
        }

        if (ImGui::Button("Load Scene"))
        {
            loadSceneRequested = true;
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

    void SceneEditorPanel::setSelectedEntity(Entity* entity)
    {
        selectedEntity = entity;
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
    }

    bool SceneEditorPanel::isLoadSceneRequested() const
    {
        return loadSceneRequested;
    }

    void SceneEditorPanel::resetLoadSceneRequest()
    {
        loadSceneRequested = false;
    }
}