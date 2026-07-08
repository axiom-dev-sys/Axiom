#include "Axiom/Editor/Panels/InspectorPanel.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"
#include "Axiom/Resource/ResourceManager.hpp"
#include "Axiom/Scene/Components/SpriteComponent.hpp"
#include "Axiom/Scene/Components/VelocityComponent.hpp"
#include "Axiom/Scene/Components/ColliderComponent.hpp"
#include "Axiom/Scene/Components/PlayerControllerComponent.hpp"

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
                selectedEntity->destroy();

                if (editorContext)
                {
                    editorContext->clearSelection();
                }
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
                        selectedEntity->addComponent<SpriteComponent>(
                            "test",
                            ResourceManager::getTexture("test")
                        );
                    }
                }

                if (!selectedEntity->hasComponent<VelocityComponent>())
                {
                    hasAvailableComponents = true;

                    if (ImGui::MenuItem("VelocityComponent"))
                    {
                        selectedEntity->addComponent<VelocityComponent>();
                    }
                }

                if (!selectedEntity->hasComponent<ColliderComponent>())
                {
                    hasAvailableComponents = true;

                    if (ImGui::MenuItem("ColliderComponent"))
                    {
                        auto* collider =
                            selectedEntity->addComponent<ColliderComponent>();

                        collider->size = { 128.0f, 128.0f };
                        collider->offset = { 0.0f, 0.0f };
                        collider->isTrigger = false;
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
                        selectedEntity->removeComponent<SpriteComponent>();
                    }

                    auto* sprite =
                        selectedEntity->getComponent<SpriteComponent>();

                    if (sprite)
                    {
                        ImGui::Text(
                            "Texture: %s",
                            sprite->getTextureID().c_str()
                        );

                        if (ImGui::Button("Set Player Texture"))
                        {
                            sprite->setTexture(
                                "player",
                                ResourceManager::getTexture("player")
                            );
                        }

                        if (ImGui::Button("Set Test Texture"))
                        {
                            sprite->setTexture(
                                "test",
                                ResourceManager::getTexture("test")
                            );
                        }

                        if (ImGui::Button("Set Office Texture"))
                        {
                            sprite->setTexture(
                                "office",
                                ResourceManager::getTexture("office")
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
                            selectedEntity->removeComponent<VelocityComponent>();
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
                            selectedEntity->removeComponent<ColliderComponent>();
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