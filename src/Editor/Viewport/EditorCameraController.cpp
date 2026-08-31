#include "Axiom/Editor/Viewport/EditorCameraController.hpp"

#include "Axiom/Editor/Viewport/ViewportPanel.hpp"
#include "Axiom/Scene/Scene.hpp"
#include "Axiom/Input/Input.hpp"

#include <algorithm>
#include <imgui.h>
#include <GLFW/glfw3.h>

namespace Axiom {

    void EditorCameraController::update(
        ViewportPanel& viewport,
        Scene& scene,
        float dt)
    {
        updateKeyboard(
            viewport,
            scene,
            dt
        );

        updatePanning(
            viewport,
            scene
        );
    }

    void EditorCameraController::updateKeyboard(
        ViewportPanel& viewport,
        Scene& scene,
        float dt)
    {
        const bool ctrlPressed =
            Input::isKeyDown(GLFW_KEY_LEFT_CONTROL) ||
            Input::isKeyDown(GLFW_KEY_RIGHT_CONTROL);

        if (!viewport.isFocused() || ctrlPressed)
            return;

        const float cameraSpeed = 400.0f;

        if (Input::isKeyPressed(GLFW_KEY_W))
            scene.camera.position.y += cameraSpeed * dt;

        if (Input::isKeyPressed(GLFW_KEY_S))
            scene.camera.position.y -= cameraSpeed * dt;

        if (Input::isKeyPressed(GLFW_KEY_A))
            scene.camera.position.x -= cameraSpeed * dt;

        if (Input::isKeyPressed(GLFW_KEY_D))
            scene.camera.position.x += cameraSpeed * dt;
    }

    void EditorCameraController::updatePanning(
        ViewportPanel& viewport,
        Scene& scene)
    {
        if (!viewport.isHovered())
        {
            m_Panning = false;
            return;
        }

        if (!Input::isMouseButtonPressed(
            GLFW_MOUSE_BUTTON_MIDDLE))
        {
            m_Panning = false;
            return;
        }

        const double mouseX =
            Input::getMouseX();

        const double mouseY =
            Input::getMouseY();

        if (!m_Panning)
        {
            m_LastMouseX = mouseX;
            m_LastMouseY = mouseY;

            m_Panning = true;
            return;
        }

        const double deltaX =
            mouseX - m_LastMouseX;

        const double deltaY =
            mouseY - m_LastMouseY;

        scene.camera.position.x -=
            static_cast<float>(deltaX) *
            scene.camera.zoom;

        scene.camera.position.y +=
            static_cast<float>(deltaY) *
            scene.camera.zoom;

        m_LastMouseX = mouseX;
        m_LastMouseY = mouseY;
    }

    void EditorCameraController::updateZoom(
        ViewportPanel& viewport,
        Scene& scene)
    {
        if (!viewport.isHovered())
            return;

        const float wheel =
            ImGui::GetIO().MouseWheel;

        if (wheel == 0.0f)
            return;

        scene.camera.zoom -=
            wheel * 0.1f;

        scene.camera.zoom =
            std::clamp(
                scene.camera.zoom,
                0.1f,
                5.0f
            );
    }

    void EditorCameraController::resetCamera(
        Scene& scene)
    {
        scene.camera.position = {
            0.0f,
            0.0f
        };

        scene.camera.zoom = 1.0f;

        reset();
    }

    void EditorCameraController::reset()
    {
        m_Panning = false;

        m_LastMouseX = 0.0;
        m_LastMouseY = 0.0;
    }

}