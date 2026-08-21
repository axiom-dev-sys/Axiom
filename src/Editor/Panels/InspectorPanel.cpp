#include "Axiom/Editor/Panels/InspectorPanel.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"
#include "Axiom/Resource/ResourceManager.hpp"
#include "Axiom/Scene/Components/SpriteComponent.hpp"
#include "Axiom/Scene/Components/VelocityComponent.hpp"
#include "Axiom/Scene/Components/ColliderComponent.hpp"
#include "Axiom/Scene/Components/PlayerControllerComponent.hpp"
#include "Axiom/Scene/Components/PlayerTag.hpp"

#include <imgui.h>
#include <cstring>

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

        const bool hasSprite =
            selectedEntity->hasComponent<SpriteComponent>();

        const bool hasVelocity =
            selectedEntity->hasComponent<VelocityComponent>();

        const bool hasCollider =
            selectedEntity->hasComponent<ColliderComponent>();

        const bool hasPlayerController =
            selectedEntity->hasComponent<PlayerControllerComponent>();

        const bool hasPlayerTag =
            selectedEntity->hasComponent<PlayerTag>();

        ImGui::Text("Entity");

        ImGui::Separator();

        ImGui::Text("Name:");
        ImGui::SameLine();

        if (ImGui::Button("Rename"))
        {
            editingName = true;

            std::strncpy(
                nameBuffer,
                selectedEntity->getName().c_str(),
                sizeof(nameBuffer)
            );

            nameBuffer[sizeof(nameBuffer) - 1] = '\0';
        }

        if (editingName)
        {
            ImGui::SetNextItemWidth(-1);

            if (ImGui::InputText(
                "##InspectorRename",
                nameBuffer,
                sizeof(nameBuffer),
                ImGuiInputTextFlags_EnterReturnsTrue))
            {
                selectedEntity->setName(nameBuffer);
                editingName = false;
            }
        }
        else
        {
            ImGui::Text("%s", selectedEntity->getName().c_str());
        }

        ImGui::Text("ID: %u", selectedEntity->getID());

        bool active = selectedEntity->isActive();

        if (ImGui::Checkbox("Active", &active))
        {
            selectedEntity->setActive(active);
        }

        ImGui::Text(
            "Destroyed: %s",
            selectedEntity->isDestroyed()
            ? "Yes"
            : "No"
        );

        if (!selectedEntity->isDestroyed())
        {
            if (ImGui::Button("Destroy Entity"))
            {
                destroyEntityRequested = true;
            }
        }

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
                
                if (ImGui::Button("Reset Position"))
                {
                    transform->position = { 0.0f, 0.0f };
                }

                ImGui::SameLine();

                if (ImGui::Button("Reset Scale"))
                {
                    transform->scale = { 1.0f, 1.0f };
                }

                if (ImGui::Button("Reset Rotation"))
                {
                    transform->rotation = 0.0f;
                }

            }
            else
            {
                ImGui::TextDisabled("No TransformComponent");
            }
        }

        if (ImGui::CollapsingHeader("Components"))
        {
            if (hasSprite)
            {
                ImGui::BulletText("SpriteComponent");
            }

            if (hasVelocity)
            {
                ImGui::BulletText("VelocityComponent");
            }

            if (hasCollider)
            {
                ImGui::BulletText("ColliderComponent");
            }

            if (hasPlayerController)
            {
                ImGui::BulletText("PlayerControllerComponent");
            }

            if (hasPlayerTag)
            {
                ImGui::BulletText("PlayerTag");
            }

            ImGui::Separator();

            if (ImGui::Button("+ Add Component"))
            {
                ImGui::OpenPopup("AddComponentPopup");
            }

            if (ImGui::BeginPopup("AddComponentPopup"))
            {
                bool hasAvailableComponents = false;

                if (!selectedEntity->hasComponent<SpriteComponent>())
                {
                    hasAvailableComponents = true;

                    if (ImGui::MenuItem("SpriteComponent"))
                    {
                        addSpriteRequested = true;
                    }
                }

                if (!selectedEntity->hasComponent<VelocityComponent>())
                {
                    hasAvailableComponents = true;

                    if (ImGui::MenuItem("VelocityComponent"))
                    {
                        addVelocityRequested = true;
                    }
                }

                if (!selectedEntity->hasComponent<ColliderComponent>())
                {
                    hasAvailableComponents = true;

                    if (ImGui::MenuItem("ColliderComponent"))
                    {
                        addColliderRequested = true;
                    }
                }

                if (!hasAvailableComponents)
                {
                    ImGui::TextDisabled("No components available");
                }

                ImGui::EndPopup();
            }

            if (hasSprite)
            {
                ImGui::Separator();

                if (ImGui::CollapsingHeader("SpriteComponent"))
                {
                    if (ImGui::Button("Remove SpriteComponent"))
                    {
                        removeSpriteRequested = true;
                    }

                    auto* sprite =
                        selectedEntity->getComponent<SpriteComponent>();

                    if (sprite)
                    {
                        ImGui::Text(
                            "Texture: %s",
                            sprite->getTextureID().c_str()
                        );
                    }
                }
            }
            
            if (hasVelocity)
            {
                ImGui::Separator();
                
                if (ImGui::CollapsingHeader("VelocityComponent"))
                {
                    if (ImGui::Button("Remove VelocityComponent"))
                    {
                        removeVelocityRequested = true;
                    }
                    
                    auto* velocity =
                        selectedEntity->getComponent<VelocityComponent>();
                    
                    if (velocity)
                    {
                        ImGui::DragFloat2(
                            "Velocity",
                            &velocity->velocity.x,
                            1.0f
                        );
                    }
                }
            }
            
            if (hasCollider)
            {
                ImGui::Separator();
                
                if (ImGui::CollapsingHeader("ColliderComponent"))
                {
                    if (ImGui::Button("Remove ColliderComponent"))
                    {
                        removeColliderRequested = true;
                    }
                    
                    auto* collider =
                        selectedEntity->getComponent<ColliderComponent>();
                    
                    if (collider)
                    {
                        ImGui::DragFloat2(
                            "Size",
                            &collider->size.x,
                            1.0f
                        );
                        
                        ImGui::DragFloat2(
                            "Offset",
                            &collider->offset.x,
                            1.0f
                        );
                        
                        ImGui::Checkbox(
                            "Is Trigger",
                            &collider->isTrigger
                        );
                    }
                }
            }
            
            if (hasPlayerController)
            {
                ImGui::Separator();
                
                if (ImGui::CollapsingHeader("PlayerControllerComponent"))
                {
                    auto* controller =
                        selectedEntity->getComponent<PlayerControllerComponent>();
                    
                    if (controller)
                    {
                        ImGui::DragFloat(
                            "Speed",
                            &controller->speed,
                            1.0f,
                            0.0f,
                            5000.0f
                        );
                    }
                }
            }
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

    bool InspectorPanel::isDestroyEntityRequested() const
    {
        return destroyEntityRequested;
    }

    void InspectorPanel::resetDestroyEntityRequest()
    {
        destroyEntityRequested = false;
    }

    bool InspectorPanel::isAddVelocityRequested() const
    {
        return addVelocityRequested;
    }

    void InspectorPanel::resetAddVelocityRequest()
    {
        addVelocityRequested = false;
    }

    bool InspectorPanel::isRemoveVelocityRequested() const
    {
        return removeVelocityRequested;
    }

    void InspectorPanel::resetRemoveVelocityRequest()
    {
        removeVelocityRequested = false;
    }

    bool InspectorPanel::isAddColliderRequested() const
    {
        return addColliderRequested;
    }

    void InspectorPanel::resetAddColliderRequest()
    {
        addColliderRequested = false;
    }

    bool InspectorPanel::isRemoveColliderRequested() const
    {
        return removeColliderRequested;
    }

    void InspectorPanel::resetRemoveColliderRequest()
    {
        removeColliderRequested = false;
    }

    bool InspectorPanel::isAddSpriteRequested() const
    {
        return addSpriteRequested;
    }

    void InspectorPanel::resetAddSpriteRequest()
    {
        addSpriteRequested = false;
    }

    bool InspectorPanel::isRemoveSpriteRequested() const
    {
        return removeSpriteRequested;
    }

    void InspectorPanel::resetRemoveSpriteRequest()
    {
        removeSpriteRequested = false;
    }

    void InspectorPanel::setEditorContext(EditorContext* context)
    {
        editorContext = context;
    }

}