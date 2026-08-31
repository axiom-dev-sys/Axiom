#include "Axiom/Editor/Viewport/EditorTransformController.hpp"

#include "Axiom/Editor/EditorContext.hpp"
#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Scene/Entity.hpp"
#include "Axiom/Scene/Components/TransformComponent.hpp"
#include "Axiom/Input/Input.hpp"

#include <GLFW/glfw3.h>
#include <cmath>

namespace Axiom {

    void EditorTransformController::update(
        EditorContext& context,
        Scene& scene,
        float dt)
    {
        Entity* selectedEntity =
            context.getSelectedEntity();

        if (!selectedEntity ||
            !scene.containsEntity(selectedEntity) ||
            selectedEntity->isDestroyed())
        {
            return;
        }

        auto* transform =
            selectedEntity->getComponent<TransformComponent>();

        if (!transform)
            return;

        if (m_SnapEnabled)
        {
            const bool leftPressed =
                Input::isKeyDown(GLFW_KEY_LEFT);

            const bool rightPressed =
                Input::isKeyDown(GLFW_KEY_RIGHT);

            const bool upPressed =
                Input::isKeyDown(GLFW_KEY_UP);

            const bool downPressed =
                Input::isKeyDown(GLFW_KEY_DOWN);

            transform->position.x =
                std::round(
                    transform->position.x /
                    m_GridSize
                ) * m_GridSize;

            transform->position.y =
                std::round(
                    transform->position.y /
                    m_GridSize
                ) * m_GridSize;

            if (leftPressed &&
                !m_LeftArrowPressedLastFrame)
            {
                transform->position.x -= m_GridSize;
            }

            if (rightPressed &&
                !m_RightArrowPressedLastFrame)
            {
                transform->position.x += m_GridSize;
            }

            if (upPressed &&
                !m_UpArrowPressedLastFrame)
            {
                transform->position.y += m_GridSize;
            }

            if (downPressed &&
                !m_DownArrowPressedLastFrame)
            {
                transform->position.y -= m_GridSize;
            }

            m_LeftArrowPressedLastFrame = leftPressed;
            m_RightArrowPressedLastFrame = rightPressed;
            m_UpArrowPressedLastFrame = upPressed;
            m_DownArrowPressedLastFrame = downPressed;
        }
        else
        {
            m_LeftArrowPressedLastFrame = false;
            m_RightArrowPressedLastFrame = false;
            m_UpArrowPressedLastFrame = false;
            m_DownArrowPressedLastFrame = false;

            const float moveSpeed = 200.0f;

            if (Input::isKeyPressed(GLFW_KEY_LEFT))
                transform->position.x -= moveSpeed * dt;

            if (Input::isKeyPressed(GLFW_KEY_RIGHT))
                transform->position.x += moveSpeed * dt;

            if (Input::isKeyPressed(GLFW_KEY_UP))
                transform->position.y += moveSpeed * dt;

            if (Input::isKeyPressed(GLFW_KEY_DOWN))
                transform->position.y -= moveSpeed * dt;
        }
    }

    void EditorTransformController::updateSnapToggle()
    {
        const bool snapKeyPressed =
            Input::isKeyDown(GLFW_KEY_G);

        if (snapKeyPressed &&
            !m_SnapKeyPressedLastFrame)
        {
            toggleSnap();
        }

        m_SnapKeyPressedLastFrame =
            snapKeyPressed;
    }

    void EditorTransformController::setSnapEnabled(bool enabled)
    {
        m_SnapEnabled = enabled;
    }

    bool EditorTransformController::isSnapEnabled() const
    {
        return m_SnapEnabled;
    }

    void EditorTransformController::toggleSnap()
    {
        m_SnapEnabled = !m_SnapEnabled;
    }

    void EditorTransformController::setGridSize(float size)
    {
        if (size <= 0.0f)
            return;

        m_GridSize = size;
    }

    float EditorTransformController::getGridSize() const
    {
        return m_GridSize;
    }

    void EditorTransformController::updateGridToggle()
    {
        const bool gridKeyPressed =
            Input::isKeyDown(GLFW_KEY_H);

        if (gridKeyPressed &&
            !m_GridKeyPressedLastFrame)
        {
            toggleGrid();
        }

        m_GridKeyPressedLastFrame =
            gridKeyPressed;
    }

    void EditorTransformController::setGridVisible(bool visible)
    {
        m_GridVisible = visible;
    }

    bool EditorTransformController::isGridVisible() const
    {
        return m_GridVisible;
    }

    void EditorTransformController::toggleGrid()
    {
        m_GridVisible = !m_GridVisible;
    }

    void EditorTransformController::resetInputState()
    {
        m_SnapKeyPressedLastFrame = false;
        m_GridKeyPressedLastFrame = false;

        m_LeftArrowPressedLastFrame = false;
        m_RightArrowPressedLastFrame = false;
        m_UpArrowPressedLastFrame = false;
        m_DownArrowPressedLastFrame = false;
    }

}