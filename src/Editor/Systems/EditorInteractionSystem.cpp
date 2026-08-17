#include "Axiom/Editor/Systems/EditorInteractionSystem.hpp"

#include "Axiom/Editor/EditorContext.hpp"
#include "Axiom/Editor/Viewport/ViewportPanel.hpp"

#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"
#include "Axiom/Scene/Components/ColliderComponent.hpp"

#include "Axiom/Input/Input.hpp"

#include <imgui.h>
#include <GLFW/glfw3.h>

namespace Axiom {

    void EditorInteractionSystem::beginDragging(Entity* entity)
    {
        if (!entity)
            return;

        m_EntityDragging = true;
        m_DraggedEntity = entity;
        m_JustStartedDragging = true;
    }

    void EditorInteractionSystem::stopDragging()
    {
        m_EntityDragging = false;
        m_DraggedEntity = nullptr;
        m_JustStartedDragging = false;
    }

    bool EditorInteractionSystem::isDragging() const
    {
        return m_EntityDragging;
    }

    void EditorInteractionSystem::updateSelection(
        EditorContext& context,
        ViewportPanel& viewport,
        Scene& scene)
    {
        if (!viewport.isLeftMouseClicked())
            return;

        glm::vec2 worldPosition;

        if (!viewport.getMouseWorldPosition(worldPosition))
            return;

        Entity* selectedEntity = nullptr;

        scene.forEach([&](Entity* entity)
            {
                if (!entity || entity->isDestroyed())
                    return;

                auto* transform =
                    entity->getComponent<TransformComponent>();

                if (!transform)
                    return;

                glm::vec2 size =
                    transform->scale;

                if (auto* collider =
                    entity->getComponent<ColliderComponent>())
                {
                    size = collider->size;
                }

                const glm::vec2 halfSize =
                    size * 0.5f;

                const bool inside =
                    worldPosition.x >= transform->position.x - halfSize.x &&
                    worldPosition.x <= transform->position.x + halfSize.x &&
                    worldPosition.y >= transform->position.y - halfSize.y &&
                    worldPosition.y <= transform->position.y + halfSize.y;

                if (inside)
                {
                    selectedEntity = entity;
                }
            });

        if (selectedEntity)
        {
            context.setSelectedEntity(selectedEntity);
            beginDragging(selectedEntity);
        }
        else
        {
            context.clearSelection();
            stopDragging();
        }
    }

    void EditorInteractionSystem::updateDragging(
        ViewportPanel& viewport,
        Scene& scene)
    {
        if (!m_EntityDragging)
            return;

        if (m_JustStartedDragging)
        {
            m_JustStartedDragging = false;
            return;
        }

        if (!ImGui::IsMouseDown(ImGuiMouseButton_Left))
        {
            stopDragging();
            return;
        }

        if (!m_DraggedEntity ||
            !scene.containsEntity(m_DraggedEntity) ||
            m_DraggedEntity->isDestroyed())
        {
            stopDragging();
            return;
        }

        auto* transform =
            m_DraggedEntity->getComponent<TransformComponent>();

        const ImVec2 viewportSize =
            viewport.getSize();

        if (!transform ||
            viewportSize.x <= 0.0f ||
            viewportSize.y <= 0.0f)
        {
            return;
        }

        const ImVec2 mouseDelta =
            ImGui::GetIO().MouseDelta;

        const float worldPerPixelX =
            1280.0f *
            scene.camera.zoom /
            viewportSize.x;

        const float worldPerPixelY =
            720.0f *
            scene.camera.zoom /
            viewportSize.y;

        transform->position.x +=
            mouseDelta.x * worldPerPixelX;

        transform->position.y -=
            mouseDelta.y * worldPerPixelY;
    }

    void EditorInteractionSystem::updateDelete(
        EditorContext& context,
        Scene& scene)
    {
        const bool deleteKeyPressed =
            Input::isKeyDown(GLFW_KEY_DELETE);

        Entity* selectedEntity =
            context.getSelectedEntity();

        if (deleteKeyPressed &&
            !m_DeleteKeyPressedLastFrame &&
            selectedEntity &&
            scene.containsEntity(selectedEntity) &&
            !selectedEntity->isDestroyed())
        {
            selectedEntity->destroy();

            context.clearSelection();

            stopDragging();
        }

        m_DeleteKeyPressedLastFrame =
            deleteKeyPressed;
    }

    bool EditorInteractionSystem::consumeDuplicateRequest()
    {
        const bool ctrlPressed =
            Input::isKeyDown(GLFW_KEY_LEFT_CONTROL) ||
            Input::isKeyDown(GLFW_KEY_RIGHT_CONTROL);

        const bool duplicateKeyPressed =
            Input::isKeyDown(GLFW_KEY_D);

        const bool duplicateShortcutPressed =
            ctrlPressed &&
            duplicateKeyPressed;

        const bool requested =
            duplicateShortcutPressed &&
            !m_DuplicateKeyPressedLastFrame;

        m_DuplicateKeyPressedLastFrame =
            duplicateShortcutPressed;

        return requested;
    }

    void EditorInteractionSystem::updateFocus(
        EditorContext& context,
        Scene& scene)
    {
        const bool focusKeyPressed =
            Input::isKeyDown(GLFW_KEY_F);

        if (focusKeyPressed &&
            !m_FocusKeyPressedLastFrame)
        {
            focusEntity(
                context.getSelectedEntity(),
                scene
            );
        }

        m_FocusKeyPressedLastFrame =
            focusKeyPressed;
    }

    void EditorInteractionSystem::focusEntity(
        Entity* entity,
        Scene& scene)
    {
        if (!entity ||
            entity->isDestroyed() ||
            !scene.containsEntity(entity))
        {
            return;
        }

        auto* transform =
            entity->getComponent<TransformComponent>();

        if (!transform)
            return;

        scene.camera.position =
            transform->position;
    }

}