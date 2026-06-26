#include "Axiom/Editor/Panels/InspectorPanel.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"

#include <imgui.h>

namespace Axiom {

    void InspectorPanel::render()
    {
        if (!visible)
            return;

        ImGui::Begin("Inspector");

        Entity* selectedEntity =
            editorContext ? editorContext->getSelectedEntity() : nullptr;

        if (!selectedEntity)
        {
            ImGui::Text("No selected entity");

            ImGui::End();
            return;
        }

        ImGui::Text("Entity");

        ImGui::Separator();

        ImGui::Text("Name: %s", entityName.c_str());
        ImGui::Text("ID: %u", entityID);

        ImGui::Text(
            "Active: %s",
            selectedEntity->isActive()
            ? "Yes"
            : "No"
        );

        ImGui::Text(
            "Destroyed: %s",
            selectedEntity->isDestroyed()
            ? "Yes"
            : "No"
        );

        if (ImGui::CollapsingHeader("Transform"))
        {
            auto* transform =
                selectedEntity->getComponent<TransformComponent>();

            if (transform)
            {
                ImGui::DragFloat2(
                    "Position",
                    &transform->position.x,
                    1.0f
                );

                ImGui::DragFloat2(
                    "Scale",
                    &transform->scale.x,
                    1.0f
                );

                ImGui::DragFloat(
                    "Rotation",
                    &transform->rotation,
                    1.0f
                );
            }
        }

        if (ImGui::CollapsingHeader("Components"))
        {
            ImGui::Text(
                "SpriteComponent: %s",
                hasSprite ? "Yes" : "No"
            );

            ImGui::Text(
                "VelocityComponent: %s",
                hasVelocity ? "Yes" : "No"
            );

            ImGui::Text(
                "ColliderComponent: %s",
                hasCollider ? "Yes" : "No"
            );

            ImGui::Text(
                "PlayerControllerComponent: %s",
                hasPlayerController ? "Yes" : "No"
            );

            ImGui::Text(
                "PlayerTag: %s",
                hasPlayerTag ? "Yes" : "No"
            );
        }

        ImGui::End();
    }

    void InspectorPanel::setVisible(bool value)
    {
        visible = value;
    }

    bool InspectorPanel::isVisible() const
    {
        return visible;
    }

    void InspectorPanel::toggle()
    {
        visible = !visible;
    }

    void InspectorPanel::setHasSprite(bool value)
    {
        hasSprite = value;
    }

    void InspectorPanel::setHasVelocity(bool value)
    {
        hasVelocity = value;
    }

    void InspectorPanel::setHasCollider(bool value)
    {
        hasCollider = value;
    }

    void InspectorPanel::setHasPlayerController(bool value)
    {
        hasPlayerController = value;
    }

    void InspectorPanel::setHasPlayerTag(bool value)
    {
        hasPlayerTag = value;
    }

    void InspectorPanel::setEditorContext(EditorContext* context)
    {
        editorContext = context;
    }

}