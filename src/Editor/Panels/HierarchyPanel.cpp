#include "Axiom/Editor/Panels/HierarchyPanel.hpp"

#include <imgui.h>
#include <string>
#include <cstring>

namespace Axiom {

    void HierarchyPanel::render()
    {
        if (!visible)
            return;

        ImGui::Begin("Hierarchy");

        for (Entity* entity : entities)
        {
            if (!entity)
                continue;

            if (entity->isDestroyed())
                continue;

            Entity* selectedEntity =
                editorContext ? editorContext->getSelectedEntity() : nullptr;

            bool selected = (entity == selectedEntity);

            std::string label =
                entity->getName() + "##" + std::to_string(entity->getID());

            if (renameEntity == entity)
            {
                ImGui::SetNextItemWidth(-1);

                if (ImGui::InputText(
                    "##Rename",
                    renameBuffer,
                    sizeof(renameBuffer),
                    ImGuiInputTextFlags_EnterReturnsTrue))
                {
                    entity->setName(renameBuffer);
                    renameEntity = nullptr;
                }
            }
            else
            {
                if (ImGui::Selectable(label.c_str(), selected))
                {
                    if (editorContext)
                    {
                        editorContext->setSelectedEntity(entity);
                    }
                }
            }

            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Rename"))
                {
                    renameEntity = entity;

                    std::strncpy(
                        renameBuffer,
                        entity->getName().c_str(),
                        sizeof(renameBuffer)
                    );

                    renameBuffer[sizeof(renameBuffer) - 1] = '\0';
                }

                if (ImGui::MenuItem("Duplicate"))
                {
                    duplicateEntity = entity;
                }

                if (ImGui::MenuItem("Delete"))
                {
                    entity->destroy();

                    if (editorContext &&
                        editorContext->getSelectedEntity() == entity)
                    {
                        editorContext->clearSelection();
                    }
                }

                ImGui::EndPopup();
            }
        }

        if (ImGui::BeginPopupContextWindow("HierarchyContextWindow", ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems))
        {
            if (ImGui::MenuItem("Create Empty Entity"))
            {
                createEntityRequested = true;
            }

            ImGui::EndPopup();
        }

        if (editorContext && ImGui::IsWindowFocused())
        {
            Entity* selectedEntity = editorContext->getSelectedEntity();

            if (selectedEntity && !selectedEntity->isDestroyed())
            {
                if (ImGui::IsKeyPressed(ImGuiKey_Delete))
                {
                    selectedEntity->destroy();
                    editorContext->clearSelection();
                }

                if (ImGui::IsKeyPressed(ImGuiKey_F2))
                {
                    renameEntity = selectedEntity;

                    std::strncpy(
                        renameBuffer,
                        selectedEntity->getName().c_str(),
                        sizeof(renameBuffer)
                    );

                    renameBuffer[sizeof(renameBuffer) - 1] = '\0';
                }

                if ((ImGui::IsKeyDown(ImGuiKey_LeftCtrl) ||
                    ImGui::IsKeyDown(ImGuiKey_RightCtrl)) &&
                    ImGui::IsKeyPressed(ImGuiKey_D))
                {
                    duplicateEntity = selectedEntity;
                }
            }
        }

        ImGui::End();
    }

    void HierarchyPanel::setVisible(bool value)
    {
        visible = value;
    }

    bool HierarchyPanel::isVisible() const
    {
        return visible;
    }

    void HierarchyPanel::toggle()
    {
        visible = !visible;
    }

    void HierarchyPanel::addEntity(Entity* entity)
    {
        if (!entity)
            return;

        entities.push_back(entity);
    }

    void HierarchyPanel::clear()
    {
        entities.clear();
    }

    void HierarchyPanel::setEditorContext(EditorContext* context)
    {
        editorContext = context;
    }

    bool HierarchyPanel::isCreateEntityRequested() const
    {
        return createEntityRequested;
    }

    void HierarchyPanel::resetCreateEntityRequest()
    {
        createEntityRequested = false;
    }

    Entity* HierarchyPanel::getDuplicateEntity() const
    {
        return duplicateEntity;
    }

    void HierarchyPanel::resetDuplicateEntityRequest()
    {
        duplicateEntity = nullptr;
    }

}